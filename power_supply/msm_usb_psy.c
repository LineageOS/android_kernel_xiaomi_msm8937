#include <linux/extcon.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/printk.h>
#include <linux/regulator/consumer.h>

struct msm_usb_psy_platform_data {
	bool dpdm_always_on;
};

struct msm_usb_psy_data {
	struct msm_usb_psy_platform_data *pdata;
	struct platform_device *pdev;
	struct device *dev;

	/* DP/DM regulator */
	struct regulator *dpdm_reg;

	/* Extcon */
	struct extcon_dev *extcon;

	/* Power supply */
	bool online;
	bool present;
	enum power_supply_type usb_supply_type;
	unsigned int current_max;

	struct power_supply *usb_psy;
	struct power_supply_desc usb_psy_d;
};

static const unsigned int msm_usb_psy_extcon_cable[] = {
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
};

static char *msm_usb_psy_supplied_to[] = {
	"battery",
};

static enum power_supply_property msm_usb_psy_properties[] = {
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_REAL_TYPE,
	POWER_SUPPLY_PROP_TYPE,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_SDP_CURRENT_MAX,
	POWER_SUPPLY_PROP_DP_DM,
};

static int msm_usb_psy_set_dp_dm(struct msm_usb_psy_data *data, int value)
{
	int rc = 0;

	switch (value) {
		case POWER_SUPPLY_DP_DM_DPF_DMF:
			if (!regulator_is_enabled(data->dpdm_reg)) {
				dev_info(data->dev, "Enable DP/DM regulator\n");
				rc = regulator_enable(data->dpdm_reg);
				if (rc < 0)
					dev_err(data->dev, "Couldn't enable DP/DM regulator rc=%d\n",
						rc);
			} else {
				dev_err(data->dev, "DP/DM regulator is already enabled\n");
			}
			break;
		case POWER_SUPPLY_DP_DM_DPR_DMR:
			if (data->pdata->dpdm_always_on) {
				dev_err(data->dev, "DP/DM always on flag is set, Ignore disable request\n");
				rc = 0;
				break;
			}
			if (regulator_is_enabled(data->dpdm_reg)) {
				dev_info(data->dev, "Disable DP/DM regulator\n");
				rc = regulator_disable(data->dpdm_reg);
				if (rc < 0)
					dev_err(data->dev, "Couldn't disable DP/DM regulator rc=%d\n",
						rc);
			} else {
				dev_err(data->dev, "DP/DM regulator is already disabled\n");
			}
			break;
		default:
			rc = -EINVAL;
			break;
	}

	return rc;
}

static int msm_usb_psy_set_cable_state(struct msm_usb_psy_data *data, bool state)
{
	return extcon_set_cable_state_(data->extcon, EXTCON_USB, state);
}

static int msm_usb_psy_handle_set_present(struct msm_usb_psy_data *data, bool new_present)
{
	int rc;

	if (data->present == new_present)
		return 0;

	if (new_present) {
		dev_info(data->dev, "Set USB present\n");
		rc = msm_usb_psy_set_dp_dm(data, POWER_SUPPLY_DP_DM_DPF_DMF);
		msm_usb_psy_set_cable_state(data, true);
	} else {
		dev_info(data->dev, "Unset USB present\n");
		msm_usb_psy_set_cable_state(data, false);
		rc = msm_usb_psy_set_dp_dm(data, POWER_SUPPLY_DP_DM_DPR_DMR);
	}

	if (rc < 0)
		dev_err(data->dev, "Failed to set USB present, rc=%d\n", rc);
	else
		data->present = new_present;

	return rc;
}

static int msm_usb_psy_get_property(struct power_supply *psy,
				  enum power_supply_property psp,
				  union power_supply_propval *val)
{
	struct msm_usb_psy_data *data = power_supply_get_drvdata(psy);

	switch (psp) {
		/* Set by charger driver */
		case POWER_SUPPLY_PROP_ONLINE:
			val->intval = data->online;
			break;
		case POWER_SUPPLY_PROP_PRESENT:
			val->intval = data->present;
			break;

		/* Set by phy-msm-usb */
		case POWER_SUPPLY_PROP_REAL_TYPE:
			val->intval = data->usb_supply_type;
			break;
		case POWER_SUPPLY_PROP_TYPE:
			val->intval = data->usb_psy_d.type;
			break;
		case POWER_SUPPLY_PROP_CURRENT_MAX:
		case POWER_SUPPLY_PROP_SDP_CURRENT_MAX:
			val->intval = data->current_max * 1000;
			break;

		/* Misc */
		case POWER_SUPPLY_PROP_DP_DM:
			val->intval = !!regulator_is_enabled(data->dpdm_reg);
			break;

		default:
			return -EINVAL;
	}

	return 0;
}

static int msm_usb_psy_set_property(struct power_supply *psy,
				  enum power_supply_property psp,
				  const union power_supply_propval *val)
{
	int rc = 0;
	struct msm_usb_psy_data *data = power_supply_get_drvdata(psy);

	switch (psp) {
		/* Set by charger driver */
		case POWER_SUPPLY_PROP_ONLINE:
			data->online = !!val->intval;
			break;
		case POWER_SUPPLY_PROP_PRESENT:
			rc = msm_usb_psy_handle_set_present(data, !!val->intval);
			break;

		/* Set by phy-msm-usb */
		case POWER_SUPPLY_PROP_REAL_TYPE:
			data->usb_supply_type = val->intval;
			/* Don't report UNKNOWN charger type to prevent healthd missing
			* detecting this power_supply status change.
			*/
			if (data->usb_supply_type == POWER_SUPPLY_TYPE_UNKNOWN)
				data->usb_psy_d.type = POWER_SUPPLY_TYPE_USB;
			else
				data->usb_psy_d.type = data->usb_supply_type;
			break;
		case POWER_SUPPLY_PROP_CURRENT_MAX:
		case POWER_SUPPLY_PROP_SDP_CURRENT_MAX:
			data->current_max = val->intval / 1000;

		default:
			dev_err(data->dev, "%s: Could not set unsupported property %d\n", __func__, psp);
			return -EINVAL;
	}

	power_supply_changed(data->usb_psy);
	return rc;
}

static int msm_usb_psy_property_is_writeable(struct power_supply *psy,
						enum power_supply_property psp)
{
	switch (psp) {
		case POWER_SUPPLY_PROP_ONLINE:
		case POWER_SUPPLY_PROP_PRESENT:
		case POWER_SUPPLY_PROP_REAL_TYPE:
		case POWER_SUPPLY_PROP_CURRENT_MAX:
		case POWER_SUPPLY_PROP_SDP_CURRENT_MAX:
			return 1;
		default:
			break;
	}

	return 0;
}

static int msm_usb_psy_parse_dt(struct msm_usb_psy_data *data)
{
	struct platform_device *pdev = data->pdev;
	struct device_node *node = pdev->dev.of_node;
	struct msm_usb_psy_platform_data *pdata;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(data->dev, "Failed to allocate memory for platform data\n");
		return -ENOMEM;
	}

	pdata->dpdm_always_on = of_property_read_bool(node, "qcom,dpdm-regulator-always-on");

	data->pdata = pdata;
    return 0;
}

static int msm_usb_psy_probe(struct platform_device *pdev)
{
	int rc = 0;
	struct msm_usb_psy_data *data = NULL;
	struct power_supply_config usb_psy_cfg = {};

	/* Allocate memory, initialize data */
	data = devm_kzalloc(&pdev->dev, sizeof(struct msm_usb_psy_data),
				 GFP_KERNEL);
	if (IS_ERR_OR_NULL(data)) {
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		rc = -ENOMEM;
		goto err;
	}

	data->pdev = pdev;
	data->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, data);

	/* Get DP/DM regulator */
	data->dpdm_reg = devm_regulator_get(data->dev, "dpdm");
	if (IS_ERR_OR_NULL(data->dpdm_reg)) {
		rc = PTR_ERR(data->dpdm_reg);
		dev_err(data->dev, "Unable to get DP/DM regulator rc=%d\n",
				rc);
		goto err_undo_alloc_mem;
	}

	/* Parse device tree */
	rc = msm_usb_psy_parse_dt(data);
	if (rc < 0) {
		dev_err(data->dev, "Failed to parse device tree, rc=%d\n", rc);
		goto err_undo_get_dpdm_regulator;
	}

	/* Register extcon device */
	data->extcon = devm_extcon_dev_allocate(data->dev, msm_usb_psy_extcon_cable);
	if (IS_ERR_OR_NULL(data->extcon)) {
		rc = PTR_ERR(data->extcon);
		dev_err(data->dev, "Failed to allocate extcon device rc=%d\n", rc);
		goto err_undo_parse_dt;
	}

	rc = devm_extcon_dev_register(data->dev, data->extcon);
	if (rc < 0) {
		dev_err(data->dev, "Failed to register extcon device rc=%d\n", rc);
		goto err_undo_extcon_allocate;
	}

	/* Set initial power supply values */
	data->online = false;
	data->present = false;
	data->usb_supply_type = POWER_SUPPLY_TYPE_UNKNOWN;
	data->current_max = 0;

	/* Register USB power supply */
	data->usb_psy_d.name = "usb";
	data->usb_psy_d.type = POWER_SUPPLY_TYPE_USB;
	data->usb_psy_d.properties = msm_usb_psy_properties;
	data->usb_psy_d.num_properties = ARRAY_SIZE(msm_usb_psy_properties);
	data->usb_psy_d.get_property = msm_usb_psy_get_property;
	data->usb_psy_d.set_property = msm_usb_psy_set_property;
	data->usb_psy_d.property_is_writeable = msm_usb_psy_property_is_writeable;

	usb_psy_cfg.drv_data = data;
	usb_psy_cfg.supplied_to = msm_usb_psy_supplied_to;
	usb_psy_cfg.num_supplicants = ARRAY_SIZE(msm_usb_psy_supplied_to);

	data->usb_psy = devm_power_supply_register(data->dev, &data->usb_psy_d, &usb_psy_cfg);
	if (IS_ERR_OR_NULL(data->usb_psy)) {
		rc = PTR_ERR(data->usb_psy);
		dev_err(data->dev, "Failed to register power supply\n");
		goto err_undo_extcon_register;
	}

	dev_info(data->dev, "probed successfully!\n");
	return 0;

err_undo_extcon_register:
	devm_extcon_dev_unregister(data->dev, data->extcon);
err_undo_extcon_allocate:
	devm_extcon_dev_free(data->dev, data->extcon);
err_undo_parse_dt:
	devm_kfree(&pdev->dev, data->pdata);
err_undo_get_dpdm_regulator:
	devm_regulator_put(data->dpdm_reg);
err_undo_alloc_mem:
	devm_kfree(&pdev->dev, data);
err:
	return rc;
}

static int msm_usb_psy_remove(struct platform_device *pdev)
{
	struct msm_usb_psy_data *data =
	    (struct msm_usb_psy_data *)platform_get_drvdata(pdev);
	devm_extcon_dev_unregister(data->dev, data->extcon);
	devm_extcon_dev_free(data->dev, data->extcon);
	devm_kfree(&pdev->dev, data->pdata);
	devm_regulator_put(data->dpdm_reg);
	devm_kfree(&pdev->dev, data);
	return 0;
}

static const struct of_device_id msm_usb_psy_of_match[] = {
	{.compatible = "qcom,msm_usb_psy-mi8937",},
	{},
};

static struct platform_driver msm_usb_psy_driver = {
	.probe = msm_usb_psy_probe,
	.remove = msm_usb_psy_remove,
	.driver = {
		   .name = "msm_usb_psy-mi8937",
		   .owner = THIS_MODULE,
		   .of_match_table = msm_usb_psy_of_match,
	}
};

static int __init msm_usb_psy_init(void)
{
	return platform_driver_register(&msm_usb_psy_driver);
}

static void __exit msm_usb_psy_exit(void)
{
	return platform_driver_unregister(&msm_usb_psy_driver);
}

module_init(msm_usb_psy_init);
module_exit(msm_usb_psy_exit);

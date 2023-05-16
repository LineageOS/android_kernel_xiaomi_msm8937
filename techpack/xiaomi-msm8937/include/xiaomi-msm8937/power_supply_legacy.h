#ifndef __MI8937_POWER_SUPPLY_LEGACY_H
#define __MI8937_POWER_SUPPLY_LEGACY_H

#include <linux/power_supply.h>

/**
 * power_supply_set_present - set present state of the power supply
 * @psy:	the power supply to control
 * @enable:	sets present property of power supply
 */
static inline int power_supply_set_present(struct power_supply *psy, bool enable)
{
	const union power_supply_propval ret = {enable,};

	return power_supply_set_property(psy, POWER_SUPPLY_PROP_PRESENT, &ret);
}

/**
 * power_supply_set_online - set online state of the power supply
 * @psy:	the power supply to control
 * @enable:	sets online property of power supply
 */
static inline int power_supply_set_online(struct power_supply *psy, bool enable)
{
	const union power_supply_propval ret = {enable,};

	return power_supply_set_property(psy, POWER_SUPPLY_PROP_ONLINE, &ret);
}

/** power_supply_set_health_state - set health state of the power supply
 * @psy:       the power supply to control
 * @health:    sets health property of power supply
 */
static inline int power_supply_set_health_state(struct power_supply *psy, int health)
{
	const union power_supply_propval ret = {health,};

	return power_supply_set_property(psy, POWER_SUPPLY_PROP_HEALTH, &ret);
}

/**
 * power_supply_set_supply_type - set type of the power supply
 * @psy:	the power supply to control
 * @supply_type:	sets type property of power supply
 */
static inline int power_supply_set_supply_type(struct power_supply *psy,
				enum power_supply_type supply_type)
{
	const union power_supply_propval ret = {supply_type,};

	return power_supply_set_property(psy, POWER_SUPPLY_PROP_TYPE, &ret);
}

#endif

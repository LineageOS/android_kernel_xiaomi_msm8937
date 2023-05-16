#ifndef _DTS_MI8937_INCLUDE_MSM_CDC_PINCTRL_H
#define _DTS_MI8937_INCLUDE_MSM_CDC_PINCTRL_H

#define MSM_CDC_PINCTRL_PA_GPIO_COMMON(type) \
	&tlmm { \
		pmx_##type##_pa { \
			##type##_pa_active: ##type##_pa_active { \
				mux { \
					function = "gpio"; \
				}; \
				config { \
					output-high; \
				}; \
			}; \
			##type##_pa_suspend: ##type##_pa_suspend { \
				mux { \
					function = "gpio"; \
				}; \
				config { \
					output-low; \
				}; \
			}; \
		}; \
	}; \
	&soc { \
		##type##_pa_p: msm_cdc_pinctrl_##type##_pa { \
			compatible = "qcom,msm-cdc-pinctrl"; \
			pinctrl-names = "aud_active", "aud_sleep"; \
			pinctrl-0 = <&##type##_pa_active>; \
			pinctrl-1 = <&##type##_pa_suspend>; \
		}; \
	}; \
	&int_codec { \
		qcom,msm-##type##-pa-pinctrl = <&##type##_pa_p>; \
	};

#define MSM_CDC_PINCTRL_PA_GPIO_SINGLE_PIN(type, gpio_a) \
	MSM_CDC_PINCTRL_PA_GPIO_COMMON(type) \
	&##type##_pa_active { \
		mux { \
			pins = #gpio_a; \
		}; \
		config { \
			pins = #gpio_a; \
		}; \
	}; \
	&##type##_pa_suspend { \
		mux { \
			pins = #gpio_a; \
		}; \
		config { \
			pins = #gpio_a; \
		}; \
	};

#define MSM_CDC_PINCTRL_PA_GPIO_DOUBLE_PINS(type, gpio_a, gpio_b) \
	MSM_CDC_PINCTRL_PA_GPIO_COMMON(type) \
	&##type##_pa_active { \
		mux { \
			pins = #gpio_a, #gpio_b; \
		}; \
		config { \
			pins = #gpio_a, #gpio_b; \
		}; \
	}; \
	&##type##_pa_suspend { \
		mux { \
			pins = #gpio_a, #gpio_b; \
		}; \
		config { \
			pins = #gpio_a, #gpio_b; \
		}; \
	};

#endif

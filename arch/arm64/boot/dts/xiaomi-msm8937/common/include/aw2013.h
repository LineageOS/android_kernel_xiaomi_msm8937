#ifndef _DTS_MI8937_INCLUDE_AW2013_H
#define _DTS_MI8937_INCLUDE_AW2013_H

#ifdef CONFIG_LEDS_AW2013_MI8937

#define AW2013_LED(led_color, led_id) \
	aw2013,##led_color { \
		aw2013,name = #led_color; \
		aw2013,id = <led_id>; \
		aw2013,max-brightness = <255>; \
		aw2013,max-current = <1>; \
		aw2013,rise-time-ms = <2>; \
		aw2013,hold-time-ms = <1>; \
		aw2013,fall-time-ms = <2>; \
		aw2013,off-time-ms = <1>; \
	};

#else // CONFIG_LEDS_AW2013_MI8937=n

#include <dt-bindings/leds/common.h>

#define AW2013_MAINLINE_LED(led_color, led_id, color_id) \
	aw2013@led_id { \
		reg = <led_id>; \
		led-max-microamp = <5000>;  \
		function = LED_FUNCTION_INDICATOR;  \
		color = <color_id>;  \
		label = #led_color;  \
	};

#endif // CONFIG_LEDS_AW2013_MI8937 end

#endif

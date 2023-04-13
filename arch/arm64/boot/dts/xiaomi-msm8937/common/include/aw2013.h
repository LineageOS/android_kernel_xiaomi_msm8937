#ifndef _DTS_MITHORIUM_INCLUDE_AW2013_H
#define _DTS_MITHORIUM_INCLUDE_AW2013_H

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

#endif

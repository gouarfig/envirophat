/*
 * File:   config.h
 * Author: gouarfig
 *
 * Created on 22 March 2015, 16:48
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define WEB_SERVER_URL		"http://dashboard.local.net/pi_thp.php?pi_temperature=%d&sensor1_temperature=%d&sensor1_humidity=%d&sensor2_temperature=%d&sensor2_pressure=%d"
#define MAX_RAW_DIFFERENCE	20

#define	RHT03_PIN			7	// BCM GPIO #4
#define PUSH_BUTTON			13	// BCM GPIO #9
/*
 * LCD pins definition
 */
#define LCD_RS 2	// GPIO 27
#define LCD_EN 3	// GPIO 22
#define LCD_D4 6	// GPIO 25
#define LCD_D5 5	// GPIO 24
#define LCD_D6 4	// GPIO 23
#define LCD_D7 1	// GPIO 18
#define LCD_BACKLIGHT 0	// GPIO 17

#define LCD_ROWS 4	// 2 or 4
#define LCD_COLS 20	// 16 or 20
#define LCD_BITS 4

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */


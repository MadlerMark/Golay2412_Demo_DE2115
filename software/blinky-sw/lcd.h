/*
 * lcd.h
 *
 *  Created on: Nov 30, 2023
 *      Author: mmadler
 */

#ifndef LCD_H_
#define LCD_H_

#include <sys/alt_stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <stdint.h>
void Init_LCD(void);
void clear_display(void);
void write_char(char input);
void write_string(char* str);
void delay1ms(int loops);
void set_position(uint8_t pos);

#endif /* LCD_H_ */

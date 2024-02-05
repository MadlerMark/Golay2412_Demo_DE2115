/*
 * lcd.c
 *
 *  Created on: Nov 30, 2023
 *      Author: mmadler
 */
#include "lcd.h"
void delay1ms(int loops){
	for (int i =0; i<loops; i++)
	{
		int count = 0;
		while(count < 50000){count++;} //1ms
	}
}
void Init_LCD(void){
	for(int i =0; i<4; i++){
		//delay1ms(10);
		IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0b110000111011); //EN = 1
		delay1ms(1);
		IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x43B);//0b010000111011);//"00111011" then " EN = 0
	}
	//clear disp:
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0b1100000000001); //EN = 1
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x401);//0b010000111011);//"00111011" then "
	//DisplayOnOff:

	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0b110000001100);
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x40C);//0b010000111011);//"00111011" then " EN = 0
	//EntryMode:


	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0b110000000110); //EN = 1
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x406);//0b010000111011);//"00111011" then " EN = 0
	alt_putstr("Initialization Done!\n");
}

//clear the LCD:
void clear_display(void)
{
	//IOWR_ALTERA_AVALON_PIO_DATA(0x101000, 0x401);//0b010000111011);//"00111011" then "
	//delay1ms(5);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0xC01); //EN = 1
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x401); // EN = 0
}

void write_char(char input){
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0xE00 + input);
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020,  0x600 + input);
}

void write_string(char* str)
{
	int i=0;
	while(str[i] != '\0'){
		write_char(str[i]);
		i++;
	}
}

void set_position(uint8_t pos)
{
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0xC80 + pos); //EN = 1
	delay1ms(1);
	IOWR_ALTERA_AVALON_PIO_DATA(0x101020, 0x480 + pos); // EN = 0
}




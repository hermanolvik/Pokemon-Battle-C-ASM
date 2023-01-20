#pragma once


#include "delay.h"



#define PORT_BASE  	 (0x40021000)
#define PORT_MODER   ((volatile unsigned int *) (PORT_BASE))
#define PORT_OTYPER  ((volatile unsigned short *) (PORT_BASE + 0x4))
#define PORT_OSPEEDR ((volatile unsigned int *) (PORT_BASE + 0x8))
#define PORT_PUPDR   ((volatile unsigned int *) (PORT_BASE + 0xC))

#define PORT_IDR_LOW  ((volatile unsigned char *) (PORT_BASE + 0x10))
#define PORT_IDR_HIGH ((volatile unsigned char *) (PORT_BASE + 0x11))
#define PORT_ODR_LOW  ((volatile unsigned char *) (PORT_BASE + 0x14))
#define PORT_ODR_HIGH ((volatile unsigned char *) (PORT_BASE + 0x15))




#define B_E      0x40
#define B_SELECT 4
#define B_RW     2
#define B_RS     1



void ascii_write( char line1[], char line2[] ){
	char *s;
	*PORT_MODER = 0x55555555;				
	
	ascii_init();
	ascii_gotoxy(1, 1);
	s = line1;
	while( *s ){
		ascii_write_char( *s++ );	//*s == \0 avslutar loopen (sista tecknet på textsträngen)
		}
	ascii_gotoxy(1, 2);	//hoppa till rad två
	s = line2;
	while( *s ){
		ascii_write_char( *s++ );
	}
	return 0;
}





unsigned char ascii_read_controller( void ){
		unsigned char rv;
		ascii_ctrl_bit_set( B_E );
		delay_250ns;
		delay_250ns;
		rv = *PORT_IDR_HIGH;
		ascii_ctrl_bit_clear( B_E );
		return rv;
}

void ascii_ctrl_bit_set( unsigned char x ){
	unsigned char c;
	c = *PORT_ODR_LOW;
	*PORT_ODR_LOW = ( B_SELECT | x | c );
}

void ascii_ctrl_bit_clear( unsigned char x ){
		unsigned char c;
		c = *PORT_ODR_LOW;
		c = c & ~x;
		*PORT_ODR_LOW = ( B_SELECT | c );
}

void ascii_write_cmd( unsigned char command ){
		ascii_ctrl_bit_clear( B_RW + B_RS );
		ascii_write_controller( command );
}

void ascii_write_data( unsigned char data ){
		ascii_ctrl_bit_clear( B_RW );
		ascii_ctrl_bit_set( B_RS );
		ascii_write_controller( data );
}

void ascii_write_controller( unsigned char byte ){
		ascii_ctrl_bit_set( B_E );
		*PORT_ODR_HIGH = byte;
		delay_250ns;
		ascii_ctrl_bit_clear( B_E );
}

unsigned char ascii_read_status( void ){
		unsigned char rv;
		*PORT_MODER = 0x00005555;
		ascii_ctrl_bit_set( B_RW );
		ascii_ctrl_bit_clear( B_RS );
		rv = ascii_read_controller();
		*PORT_MODER = 0x55555555;
		return rv;
}

unsigned char ascii_read_data(void) {
    unsigned char rv;
    *PORT_MODER = 0x00005555;
    ascii_ctrl_bit_set(B_RW + B_RS);
    rv = ascii_read_controller();
    *PORT_MODER = 0x55555555;
}

void ascii_wait_ready( void ){
	while(ascii_read_status() & 0x80){}
	delay_mikro( 8 );
}

void ascii_init( void ){
	ascii_wait_ready();
	
	ascii_write_cmd(0x38);		//Sätter Function (rader och teckenstorlek)
	delay_mikro( 39 );
	ascii_wait_ready();
	
	ascii_write_cmd( 0x0C );	//tänder display och sätter blinkande markör
	delay_mikro( 39 );
	ascii_wait_ready();
	
	ascii_write_cmd( 6 );
	delay_mikro( 39 );
	ascii_wait_ready();
	
								//clear display			
	ascii_write_cmd(1);
	delay_milli( 2 );
}

void ascii_write_char( unsigned char c ){
		ascii_wait_ready();
		delay_mikro( 8 );
		ascii_write_data( c );
		
	
}

void ascii_gotoxy( int x, int y ){
		unsigned char address = x-1;
		if(y != 1){
			address = address | 0x40;
		}
		ascii_write_cmd( 0x80 | address );
	
}
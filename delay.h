//SYSTICK
#pragma once

#define STK_CTRL  ((volatile unsigned int*) (0xE000E010))
#define STK_LOAD  ((volatile unsigned int*) (0xE000E014))
#define STK_VAL   ((volatile unsigned int*) (0xE000E018))
#define STK_CALIB ((volatile unsigned int*) (0xE000E01C))


void delay_250ns( void ){
		//Klocka 168 000 000 HZ (cykler/sekund)
		*STK_CTRL = 0;
		*STK_LOAD = 42 ;
		*STK_VAL = 0;
		*STK_CTRL = 5;
		while( *STK_CTRL & 0x10000 ){}
		
		*STK_CTRL = 0;
}

void delay_mikro( unsigned int us ){
		for(int i; i <= us; i++){
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		}	
}

void delay_milli( unsigned int ms ){
	for(int i = 0; i <= ms; i++){
		delay_mikro(1000);
	}
}
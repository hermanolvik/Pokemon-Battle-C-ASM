#pragma once

#include "delay.h" 
#include "ascii.h"

void pedro_atk_func1( POBJECT o ){ //TACKLE
	char tackle[] = {"Pedro Used Tackle"};
	char tackle1[] = {"Not Very Effective"};
	char tackle2[] = {" "};
	ascii_write(tackle, tackle2);
	
	o->move(o);
	delay_milli(3000);
	ascii_write(tackle1, tackle2);
	delay_milli(5000);
}


void pedro_atk_func2( POBJECT o ){	//NOP
	char NOP[] = {"Pedro used NOP"};
	char NOP1[] = {"It did nothing"};
	ascii_write(NOP, NOP1);
	delay_milli(5000);
	
	
}


void pedro_atk_func3( POBJECT o, POBJECT p ){ //POINTER
	char ptr[] = {"Pedro use struct ptr"};
	char ptr1[] = {" "};
	char ptr2[] = {"Pika Got A Headache"};
	ascii_write(ptr, ptr1);
	p->draw(p);
	while(p->posx < 80){
	p->move(p);//pilen skjuts mot pika
	}
	p->clear(p);
	p->posx = 25;
	p->posy = 30;
	ascii_write(ptr2, ptr1);
	delay_milli(5000);
	
}


void pedro_atk_func4( POBJECT o ){ //run
	char run[] = {"Pedro ran away"};
    char run1[] = {"Pika won!"};
	ascii_write(run, run1);
	delay_milli(5000);
	
	
	
}

void pika_atk_func1(POBJECT o, POBJECT p){
	char thunder[] = {"Pika Used Thunder"};
	char thunder1[] = {"It's super effective"};
	ascii_write(thunder, thunder1);
	p->draw(p);
    delay_milli(4000);
    
    p->clear(p);
    delay_milli(1000);
    p->draw(p);
    delay_milli(4000);
    
    p->clear(p);
    delay_milli(5000);
	
}
	


void pika_atk_func2(POBJECT o, POBJECT p){	//NOP Pika
	char nop[] = {"Pika Could Not Pika"};
	char nop1[] = {"Move"};
	ascii_write(nop, nop1);
	delay_milli(5000);
}

void pika_atk_func3(POBJECT o, POBJECT p){	//Tackle Pika
	char tackle[] = {"Pika Used Tackle"};
	char tackle1[] = {"Not Very Effective"};
	char tackle2[] = {" "};
	ascii_write(tackle, tackle2);
	
	o->move(o);
	delay_milli(3000);
	ascii_write(tackle1, tackle2);
	delay_milli(5000);
	
}

int pika_atk(char s, POBJECT o, POBJECT p){
	if( s == 1 ){	//thunder
		pika_atk_func1( o, p );
		return 20;
	}
	if( s == 2 ){	//nop
		pika_atk_func2( o, p );
		return 0;
	}
	if( s == 3 ){	//tackle
		pika_atk_func3( o, p );
		return 12;
	}
}

int pedro_atk( char s, POBJECT o, POBJECT p ){
	if( s == 1 ){	//Tackle
		pedro_atk_func1( o );
		return 12;
	}
	if( s == 2 ){	//NOP
		pedro_atk_func2( o );
		return 0;
	}
	if( s == 3 ){ //Pointer
		pedro_atk_func3( o, p );
		return 12;
	}
	if( s == 4 ){	//RUN
		pedro_atk_func4( o );
		return 0;
	}
}



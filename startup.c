#pragma once


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graphics.h"
#include "keyb.h"
#include "ascii.h"
#include "atk.h"


/* Vad du behöver koppla upp är Keypad på Port D (8-15)
 * Koppla upp skärmen
 * För att en knapptryckning skall registreras så behäver du släppa knappen efter du tryckt ner den
 * */

__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}



void main(void){
		
		POBJECT pedro = &pedro_object;
		POBJECT pikatchu = &pika_object;
		POBJECT pedrobar = &pedro_lifebar;
		POBJECT pikabar = &pika_lifebar;
		POBJECT pedro_life = &pedro_health;
		POBJECT pika_life = &pika_health;
		POBJECT start_up_screen = &start_screen;
		POBJECT ptr = &arrow;
		POBJECT thunder = &blixt;
		
		char pedro_atk1[] = {"1:Tackle  2:NOP"};
		char pedro_atk2[] = {"3:Pointer 4:RUN"};
		
		char pika_atk1[] = {"Pika Used Thunder"};
		char pika_atk2[] = {"It's Super Effective"};
		
		char pika_won[] = {"Pedro Fainted..."};
		char pika_won1[] = {"Pika Won!"};
		
		char pedro_won[] = {"Pika Fainted..."};
		char pedro_won1[] = {"Pedro Won!!"};
		
	while(1){
		char s=0;
		char wait;
		int dmg;
		pika_life->geo->sizex = 135;
		pedro_life->geo->sizex = 135;
		
		graphic_clear_screen();
		start_up_screen->draw(start_up_screen);
		
		while((s = keyb()) != 1) {}
		while(s = keyb()) {}
		//print start screen
		//vänta på att spelare startar
		graphic_clear_screen(); //inför nästa scen
		
		delay_milli(3000);
			pedro->draw(pedro);		//ritar ut objekten var för sig då alla är dynamiska
			pikatchu->draw(pikatchu);
			pedrobar->draw(pedrobar);
			pikabar->draw(pikabar);
			pedro_life->draw(pedro_life);
			pika_life->draw(pika_life);
		
		
			
		while(1){ //gameloopen, när Pikalife eller pedroLife = 0 -> break och börja om
		unsigned int r = 3;	
		dmg = 0;	
		ascii_write(pedro_atk1, pedro_atk2);
		
		while(!(s = keyb())){ r+=2; }	//wait for choice of attack //r++ för rand()
		
		while(wait = keyb()){};
		dmg = pedro_atk( s, pedro, ptr);	//Pedro turn
		pikatchu->draw(pikatchu); //efter pilattack rita pika igen
		
		if(s == 4 ){	//Avslutar spelet vid run
			break;
		}
		pika_life->geo->sizex -= dmg;
		if(dmg > 0){
		pika_life->clear(pika_life);
		}
		
		delay_milli(1000);
		if(pika_life->geo->sizex <=0){
			ascii_write(pedro_won, pedro_won1);
			delay_milli(5000);
			
			break;
		}
		dmg = 0;
		r = r%3+1;
		dmg = pika_atk( r, pikatchu, thunder);	//Pika turn
		pedro_life->geo->sizex -= dmg;
		if( dmg > 0 ){
		pedro_life->clear(pedro_life);
		}
		
		delay_milli(1000);
		
		if(pedro_life->geo->sizex <=0){
			ascii_write(pika_won, pika_won1);
			delay_milli(5000);
			
			break;
		}
		
		
		
		
			//på ascii displayen ser man 4 alternativ på attacker, skriv funktioner för varje text som skall matas ut
			//if else funktion beroende på val
			//sänk risat life med 1 och kolla om det är noll, isåfall break och mata ut på ascii vem som vann
			//funktion för risat attacker använder rand() 
			//kolla om pedro lifebar är 0 isåfalla break och mata ut på ascii vem som vann
			//börja om
			
		}
	}
}
	



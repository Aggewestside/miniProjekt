/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declarations for these labs */

int mytime = 0x5957;
int tickcount = 0;
volatile int * trise;
volatile int * porte;
int resetcount = 0;
int timerresetcounter = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) 
{
	
	
	if(IFS(0) & 0x100)			/* Test time-out event flag */ 
	{
		resetcount++;
		if(resetcount == 10)
		{
			time2string( textstring, mytime );
			display_string( 3, textstring );
			display_update();
			tick( &mytime );
			resetcount = 0;
		}
		IFSCLR(0) = 0x100;				/* Reset event flag */
	}
	return;
} 

/* Lab-specific initialization goes here */
void labinit( void )
{
	volatile int * trise = (volatile int *) 0xbf886100;
	*trise = *trise & 0xffffff00;
	TRISD = 0xfe0 | TRISD;
	
	T2CON = 0x70; 
	PR2 = (80000000 / 256) / 10;
	TMR2 = 0;
	T2CONSET = 0x8000; /* Start the timer */
	
	IECSET(0) = 0x00000100;
	/* IPCSET(0) = 0x0000001E; */
	IPCSET(2) = 0x0000001F;
	enable_interrupt();
  return;
}
 
/* This function is called repetitively from the main program */
void labwork( void ) 
{  
	//prime = nextprime( prime );  
	//display_string( 0, itoaconv( prime ) );  
	//display_update(); 
	tickcount++;
	PORTE = tickcount;
	timerresetcounter++;
	
	display_image(96, icon);
}
} 


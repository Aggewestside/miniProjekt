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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	volatile int * trise = (volatile int *) 0xbf886100;
	*trise = *trise & 0xff00;
	TRISDSET = 0x0fe0;
	
	T2CON = 0x70; 
	PR2 = (80000000 / 256) / 10;
	TMR2 = 0;
	T2CONSET = 0x8000; /* Start the timer */
  return;
}
 
int timertest(void){
	if(IFS(0) & 0x100)			/* Test time-out event flag */ 
	{
		IFSCLR(0) = 0x100;				/* Reset event flag */
		return(1);
	}
	else return(0);
}
/* This function is called repetitively from the main program */
void labwork( void )
{
  //delay( 1000 );
 if(timertest())
 {
	resetcount++;
	if(resetcount == 10)
	{
		time2string( textstring, mytime );
		display_string( 3, textstring );
		display_update();
		tick( &mytime );
		tickcount++;
		//  volatile int * porte = (volatile int *) 0xbf886110;
		//  *porte = tickcount;
		PORTE = tickcount;
		resetcount = 0;
	}
 }
  if(getbtns() == 4)
	  mytime = ((mytime & 0x0fff) | (getsw() << 12));  
  if(getbtns() == 2)
	  mytime = ((mytime & 0xf0ff) | (getsw() << 8));
  if(getbtns() == 1)
	  mytime = ((mytime & 0xff0f) | (getsw() << 4)); 
  if(getbtns() == 6){
	  mytime = ((mytime & 0x0fff) | (getsw() << 12));
	  mytime = ((mytime & 0xf0ff) | (getsw() << 8));
  }
  if(getbtns() == 5){
	  mytime = ((mytime & 0x0fff) | (getsw() << 12));
	  mytime = ((mytime & 0xff0f) | (getsw() << 4));
  }
  if(getbtns() == 3){
	  mytime = ((mytime & 0xf0ff) | (getsw() << 8));
	  mytime = ((mytime & 0xff0f) | (getsw() << 4));
  }
  if(getbtns() == 7){
	  mytime = ((mytime & 0xff0f) | (getsw() << 4));
	  mytime = ((mytime & 0x0fff) | (getsw() << 12));
	  mytime = ((mytime & 0xf0ff) | (getsw() << 8));
  }
  
  
  
  
  display_image(96, icon);
}
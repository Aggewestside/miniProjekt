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
#include <stdio.h>
#include <stdbool.h>

//int mytime = 0x5957;
int tickcount = 128;
volatile int * trise;
volatile int * porte;
int i = 0;
//int timerresetcounter = 0;

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
	*trise = *trise & 0xffffff00;
	TRISD = 0xfe0 | TRISD;
 
  return;
}
 
/* This function is called repetitively from the main program */
void labwork( void )
{
// time2string( textstring, mytime );
  //display_string( 3, textstring );
  //display_update();
  //tick( &mytime );
		if (tickcount == 128)
		{
			PORTE = tickcount;
			//delay (1000);
			
			for(i = 0; i < 7; i++)
			{
				tickcount = tickcount >> 1;
				PORTE = tickcount;
				delay (1000);
				//timerresetcounter++;
			}
		}
	
		if(tickcount == 1);
		{
			PORTE = tickcount;
			//delay (1000);
			
			for(i = 0; i < 7; i++)
			{
				tickcount = tickcount << 1;
				PORTE = tickcount;
				delay (1000);
				//timerresetcounter++;
			}
		}

  
	
/*
  if(getbtns() & 4)
	  mytime = ((mytime & 0x0fff) | (getsw() << 12));  
  if(getbtns() & 2)
	  mytime = ((mytime & 0xf0ff) | (getsw() << 8));
  if(getbtns() & 1)
	  mytime = ((mytime & 0xff0f) | (getsw() << 4)); 
  
  */
  display_image(96, icon);
}
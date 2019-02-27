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
#include <math.h>

int tickcount = 128;
volatile int * trise;
volatile int * porte;
int resetcount = 0;
int i = 0;
volatile int cd = 0;
int wait = 0;
int cdMAX = 100;
int antalclicks = 0;
int player_one = 0;
int player_two = 0;
int score_player_one = 0;
int score_player_two = 0;



/* Interrupt Service Routine */
void user_isr( void )
{
		resetcount++;
		if(resetcount == 10)
		{
			resetcount = 0;
			cd+=10;

		}
		IFSCLR(0) = 0x100;				/* Reset event flag */
	return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	volatile int * trise = (volatile int *) 0xbf886100;
	*trise = *trise & 0xffffff00;
	TRISD = 0xfe0 | TRISD;


	T2CON = 0x70;
	PR2 = (80000000 / 256) / 100;
	TMR2 = 0;
	T2CONSET = 0x8000; /* Start the timer */

	IECSET(0) = 0x00000100;
	/* IPCSET(0) = 0x0000001E; */
	IPCSET(2) = 0x0000001F;
	enable_interrupt();
  return;
}

void Bristning_left_side(void)				//resettar inte till ny runda..
{
	score_player_two++;
	//LOSS SCREEN lägg till
	tickcount = 128;
	labwork();
}

void Bristning_right_side(void)				//resettar inte till ny runda..
{
	score_player_one++;
	//LOSS SCREEN lägg till
	tickcount = 1;
	labwork();
}


/* This function is called repetitively from the main program */
void labwork( void )
{
	PORTE = tickcount;
	if((tickcount == 128 && getbtns() == 4) || (tickcount == 1 && getbtns() == 1))
	{
		cd=antalclicks;				//fixa bristning höger sida????
	while (tickcount == 128)
	{

		PORTE = tickcount;
		wait = 1;
		if(getbtns() == 4 && cd < 100)
		{
			antalclicks+=10;
			if(antalclicks>80)
				antalclicks = 80;
			wait=0;
			cd = antalclicks;
			break;
		}

		if(cd > 100){
			display_string(1,"Bristning");
			display_string(3,""+antalclicks/10);
			display_update();
			wait = 0;
		}

	}

		if (tickcount == 128)
		{
			PORTE = tickcount;

			for(i = 0; i < 6; i++)
			{

				tickcount = tickcount >> 1;
				PORTE = tickcount;

				while(cd<cdMAX)
				{
						wait = 1;
				}
				wait=0;
				cd = antalclicks;

		}
		tickcount = tickcount >> 1;
		PORTE = tickcount;
	}

	while (tickcount == 1)
	{
		PORTE = tickcount;
		wait = 1;

		if(getbtns() == 1 && cd < 100)
		{
			antalclicks+=10;
			if(antalclicks>80)
				antalclicks = 80;
			wait=0;
			cd = antalclicks;
			break;
		}
		if(cd > 100){
			display_string(1,"Bristning");
			display_string(3,itoaconv((antalclicks/10)));
			display_update();
			wait=0;
		}

	}


		if(tickcount == 1);
		{
			PORTE = tickcount;

			for(i = 0; i < 6; i++)
			{
				tickcount = tickcount << 1;
				PORTE = tickcount;

				while(cd<cdMAX)
				{
						wait = 1;
				}
				wait=0;
				cd = antalclicks;
			}
		tickcount = tickcount << 1;
		PORTE = tickcount;
	}
	}
}


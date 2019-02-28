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

int solo_score = -1;
int score[3] = {0,0,0};
int game_mode = 0;
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
			if(wait=1)
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

void bristning_left_side(void)		//+1 player-mode, poäng och ny runda
{
	if(game_mode==1)
	{	
		display_string(0,"    YOU LOSE");
		display_string(1,"");
		display_string(2,"Final score:"); ////////////
		display_string(3,itoaconv(solo_score));
		display_update();
	}
	
	if(game_mode==2)
	{
		score_player_two++;
		if(score_player_two == 3)
		{
			display_string(0,"CONGRATULATIONS");
			display_string(1,"");
			display_string(2,"  PLAYER TWO");
			display_string(3,"");
			display_update();
		}
		else
		{
			display_string(0,"");
			display_string(1,"  PLAYER TWO");
			display_string(2," GETS A POINT");
			display_string(3,"");
			display_update();
		}
	}
	cd = 0;
	for(i = 0; i<=2; i++)
	{
		tickcount = 255;	//alla lampor
		PORTE = tickcount; //lys lampor
		while(cd<(cdMAX/4))
		{
			wait = 1;
		}
		wait=0;
		cd = 0;
		tickcount = 0;		//släcka
		PORTE = tickcount;	//lys lampor
		while(cd<(cdMAX/10))
		{
			wait = 1;
		}
		wait=0;
	}
	if(game_mode == 1)				// 1 player highscore
	{
		for (i = 0; i < 3; i++)
		{
			if (solo_score > score[i])
			{
				score[i] = solo_score;
				break;
			}
		}
		game_mode = 0;
	}
	if((game_mode == 2) && (score_player_one == 3 || score_player_two == 3))
	{
		score_player_one = 0;
		score_player_two = 0;
		game_mode = 0;
	}
	antalclicks = 0;
	cd = antalclicks;
	
	//LOSS SCREEN lägg till
	tickcount = 128;
	labwork();					//PROVA BREAK ISTÄLLET FÖR O KALLA FUNKTIONEN
}

void bristning_right_side(void)		//poäng och ny runda
{
	score_player_one++;
	if(score_player_one == 3)
	{
		display_string(0,"CONGRATULATIONS");
		display_string(1,"");
		display_string(2,"  PLAYER ONE");
		display_string(3,"");
		display_update();
	}
	else
	{
		display_string(0,"");
		display_string(1,"  PLAYER ONE");
		display_string(2," GETS A POINT");
		display_string(3,"");
		display_update();
	}
	cd = 0;
	for(i = 0; i<3; i++)
	{
		tickcount = 255;
		PORTE = tickcount;
		while(cd<(cdMAX/4))
		{
			wait = 1;
		}
		wait=0;
		cd = 0;
		tickcount = 0;
		PORTE = tickcount;
		while(cd<(cdMAX/10))
		{
			wait = 1;
		}
		wait=0;
	}
	if((game_mode == 2) && (score_player_one == 3 || score_player_two == 3))
	{
		score_player_one = 0;
		score_player_two = 0;
		game_mode = 0;
	}
	antalclicks = 0;
	cd = antalclicks;
	
	//LOSS SCREEN lägg till
	tickcount = 1;
	labwork();					//ny runda
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	if(game_mode == 0)	// Meny
	{
		while(cd<200)
		{
			wait = 1;
		}
		wait = 0;
		cd = 0;
		while(1)
		{
			display_string(0, "No. players?");
			display_string(1, "");
			display_string(2, "");
			display_string(3, "1            2");
			display_update();

			if(getbtns() == 4)
			{
				game_mode = 1;
				break;
			}
			
			if(getbtns() == 1)
			{
				game_mode = 2;
				break;
			}
		}
	}
	if(game_mode == 1)	// 1 player mode
	{
		
		
		while(1)
		{
			cd=0;
			display_string(0, "Loading...");
			display_string(3,"");
			display_update();
			while(cd<200)
			{
				wait = 1;
			}
			wait = 0;
			display_string(0, "  -SOLO MODE-");
			display_string(1, "Press button 4");
			display_string(2, "to start.");
			display_string(3, "");
			display_update();
			tickcount = 128;
			solo_score=-1;
			
			while(1)
			{
				PORTE = tickcount;
				if((tickcount == 128 && getbtns() == 4))
				{
					
					display_string(0,"  -SOLO MODE-");
					display_string(1,"");
					display_string(2,"Score:");
					display_string(3,itoaconv(solo_score));
					display_update();
					while(1)
					{
/////från vänster
						cd = antalclicks;
						while (tickcount == 128)
						{
							PORTE = tickcount;
							wait = 1;
							if(getbtns() == 4 && cd < 100)
							{
								antalclicks+=10;
								if(antalclicks>90)
									antalclicks = 90;
								wait=0;
								cd = antalclicks;
								solo_score++;
								display_string(3,itoaconv(solo_score));
								display_update();
								
								break;
							}
							if(cd >= cdMAX)
							{
								wait = 0;
								bristning_left_side();
							}
						}

						if (tickcount == 128)
						{
							PORTE = tickcount;

							for(i = 0; i < 7; i++)
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
						}
/////från höger
						
						
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
									if ((getbtns() == 4) && (1 < tickcount < 128))
										bristning_left_side();
								}
								wait=0;
								cd = antalclicks;
							}
							tickcount = tickcount << 1;
							PORTE = tickcount;
						}
					}
				}
			}
		}
	}
	if(game_mode == 2)	// 2 player mode
	{
		if((score_player_one == 0) && (score_player_two == 0))
		{
			display_string(0, "Loading...");
			display_string(3,"");
			display_update();
			while(cd<200)
			{
				wait = 1;
			}
			wait = 0;
		}
		while(1)				
		{
			
			
			display_string(0, "OOOO   OOOO");
			display_string(1, "O  O _ O  O");
			display_string(2, "O  O   O  O");
			display_string(3, "OOOO   OOOO");
			display_update();			
			
			PORTE = tickcount;
			if((tickcount == 128 && getbtns() == 4) || (tickcount == 1 && getbtns() == 1))
			{
				while(1)
				{
/////från vänster
					cd = antalclicks;
					while (tickcount == 128)
					{
						PORTE = tickcount;
						wait = 1;
						if(getbtns() == 4 && cd < 100)
						{
							antalclicks+=10;
							if(antalclicks>90)
								antalclicks = 90;
							wait=0;
							cd = antalclicks;
							break;
						}
						if(cd >= cdMAX)
						{
							wait = 0;
							bristning_left_side();
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
								if ((getbtns() == 1) && (1 < tickcount < 128))
								bristning_right_side();
							}
							wait=0;
							cd = antalclicks;
						}
						tickcount = tickcount >> 1;
						PORTE = tickcount;
					}
/////från höger
					while (tickcount == 1)
					{
						PORTE = tickcount;
						wait = 1;
						if(getbtns() == 1 && cd < 100)
						{
							antalclicks+=10;
							if(antalclicks>90)
								antalclicks = 90;
							wait=0;
							cd = antalclicks;
							break;
						}
						if(cd >= cdMAX)
						{
							wait = 0;
							bristning_right_side();
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
								if ((getbtns() == 4) && (1 < tickcount < 128))
									bristning_left_side();
							}
							wait=0;
							cd = antalclicks;
						}
						tickcount = tickcount << 1;
						PORTE = tickcount;
					}
				}
			}
		}
	}	
}
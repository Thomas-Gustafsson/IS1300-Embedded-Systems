/** ******************************************************************************
@brief	Pingpong statemachine for Pingpong-program
@file	pingpong.c
@author Thomas Gustafsson & Viktor Björkén
@version 1.0
@date 9-November-2023
@brief Functions and structures for program Pingpong
****************************************************************************** */
/* Includes ------------------------------------------------------------------*/
#include "Pingpong_functions.h"
#include "gpio.h"

/* Define states for state machine*/
typedef enum
{
	Start,
	MoveRight,
	MoveLeft,
	GameOver
} states;

static states State, NextState;

void Pingpong(void)
{
	bool ButtonPressed = false; // To remember that button is pressed
	bool LeftServe = true;
	bool RightServe = true; // To remember which players' serve it is

	uint32_t Varv, Speed; // Ball speed
	uint8_t Led; // LED nr
	uint8_t LeftScore = 0;
	uint8_t RightScore = 0;

	State= Start; // Initiate State to Start
	NextState= Start;

	Speed= 500000; // Number of loops

	/* Infinite loop */
	while (1)
	{
		State = NextState;
		switch (State) // State machine
		{
			case Start:
				Led_on(0); // Turn off all LEDs
				Speed = 500000;
				if (LeftScore == 4 || RightScore == 4)
				{
					NextState = GameOver;
				}
				else if ( L_hit() == true && LeftServe == true) // L serve
				{
					LeftServe = false;
					RightServe = true;
					Led = 1;
					NextState = MoveRight;
					while ( L_hit() == true ); // wait until button is released
				}
				else if ( R_hit() == true && RightServe == true) // R serve
				{
					LeftServe = true;
					RightServe = false;
					Led = 8;
					NextState= MoveLeft;
					while ( R_hit() == true ); // wait until button is released
				}
				else
				NextState = Start; // Stay in Start state
			break;
			case MoveRight:
			{
				Led_on(Led);
				Varv = Speed;
				while( Varv != 0 )
				{
					if ( R_hit() ) ButtonPressed = true; // R hit
					Varv--;
				}
				if ( ButtonPressed ) // R pressed
				{
					if ( Led == 8 ) // and LED8 active
					{
						NextState=MoveLeft; // return ball
						Led=7;
						if (Speed >= 150000) Speed = Speed * 0.85;
					}
					else
					{
						LeftScore++;
						Show_points(LeftScore, RightScore);
						NextState = Start; // hit too early
					}
				}
				else
				{
					if ( Led == 9 ) // no hit or too late
					{
						LeftScore++;
						Show_points(LeftScore, RightScore);
						NextState = Start;
					}
					else
						NextState = MoveRight; // ball continues to move right
				}
				if ( !ButtonPressed ) Led++; // prepare to turn next LED on
				ButtonPressed=false;
			}
			break;
			case MoveLeft:
			{
				Led_on(Led);
				Varv = Speed;
				while(Varv != 0)
				{
					if ( L_hit() ) ButtonPressed = true; // L hit
					Varv--;
				}
				if ( ButtonPressed ) // L pressed
				{
					if ( Led == 1 ) // and LED1 active
					{
						NextState = MoveRight; // return ball
						Led=2;
						if (Speed >= 150000) Speed = Speed * 0.85;
					}
					else
					{
						RightScore++;
						Show_points(LeftScore, RightScore);
						NextState = Start; // hit too early
					}
				}
				else
				{
					if ( Led == 0 ) // no hit or too late
					{
						RightScore++;
						Show_points(LeftScore, RightScore);
						NextState = Start;
					}
					else
						NextState = MoveLeft; // ball continues to move left
				}
				if ( !ButtonPressed ) Led--; // prepare to turn next LED on
				ButtonPressed=false;
				}
			break;
			case GameOver:
			{
				Show_gamepoints(LeftScore, RightScore);
				LeftScore = 0;
				RightScore = 0;
				LeftServe = true;
				RightServe = true;
				NextState = Start;
			}
			default:
			break;
		}
	}
} // End of function Pingpong

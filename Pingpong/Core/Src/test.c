/*
 * test.c
 *
 *  Created on: Nov 2, 2023
 *      Author: thomas
 */


#include "Test.h"
#include "Pingpong_functions.h"
#include "gpio.h"
#include "stdbool.h"

void Test_program(void) {
// Test_Led();
// Test_Points();
Test_Buttons();
}

void Test_Led(void) {
	int8_t Lednr;
/* Loop checking that all leds can be turned on*/
	for (Lednr=1; Lednr<= 8; Lednr++) {
		Led_on(Lednr);
		HAL_Delay(500);
	}
Led_on(9); // Turn off led 8 HAL_Delay(1000); // 1000 ms return;
}

void Test_Points(void) {
	Show_points(1,4);
}

void Test_Buttons(void)
{
	int8_t j;
	/* Checking buttons */
	j=4;
	Led_on(j); // Light on
	while (j<9 && j>0) {
		if ( L_hit() == true ) // Wait for left button hit
		{
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
		}
		if ( R_hit() == true ) // Wait for right button hit
		{
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j<1) j=0; // Start again from left
		}
	}
	return;
}

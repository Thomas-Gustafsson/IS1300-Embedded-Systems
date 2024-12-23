/** ******************************************************************************
@brief	Pingpong, functions for pingpong-program
@file	pingpong_functions.c
@author	Thomas Gustafsson & Viktor Björkén
@version 1.0
@date 3-Nov-2023
@brief Functions and structures for program Pingpong ******************************************************************************
*/

#include "Test.h"
#include "Pingpong.h"
#include "gpio.h"
#include "Pingpong_functions.h"
/**
@brief Led_on, turn one of the pingpong leds on
@param uint8_t Lednr , number to the Led that is turned on Lednr can be 1-8, all other values turns all leds off
@return void
*/
void Led_on(uint8_t Lednr) {
	uint8_t i;
	for (i=1; i<=8; i++){
		switch(i){
		case 1 : //Led1
		if (Lednr==i) HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		break;
		case 2 : //Led2
		if (Lednr==i) HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		break;
		case 3 : //Led3
		if (Lednr==i) HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		break;
		case 4 : //Led4
		if (Lednr==i) HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
		break;
		case 5 : //Led5
		if (Lednr==i) HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);
		break;
		case 6 : //Led6
		if (Lednr==i) HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, GPIO_PIN_RESET);
		break;
		case 7 : //Led7
		if (Lednr==i) HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED7_GPIO_Port, LED7_Pin, GPIO_PIN_RESET);
		break;
		case 8 : //Led8
		if (Lednr==i) HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(LED8_GPIO_Port, LED8_Pin, GPIO_PIN_RESET);
		break;
		default : ;
		} // end switch
		} // end for-loop return;
return;
} // End of function Led_on

void Show_points(uint8_t L_points, uint8_t R_points) {
	// Define arrays to store GPIO ports and pins for each LED
	    GPIO_TypeDef* LED_GPIO_Port[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port, LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
	    uint16_t LED_Pin[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};

	    // Turn on all LEDs
	    for (int i = 0; i < 8; i++) {
	    	HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_SET);
	    }

	    HAL_Delay(100);

	    // Turn off all LEDs
	    for (int i = 0; i < 8; i++) {
	        HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_RESET);
	    }

	    HAL_Delay(500);

	    // Display points for player L (from the left side to the middle)
	    for (int i = 0; i < L_points; i++) {
	        HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_SET);
	    }

	    // Display points for player R (from the right side to the middle)
	    for (int i = 7; i >= 8 - R_points; i--) {
	        HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_SET);
	    }

	    HAL_Delay(1000);
	    // Turn off all LEDs
	    for (int i = 0; i < 8; i++) {
	    	HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_RESET);
	    }
	    HAL_Delay(500);
}

void Show_gamepoints(uint8_t L_points, uint8_t R_points) {
    	// Define arrays to store GPIO ports and pins for each LED
        GPIO_TypeDef* LED_GPIO_Port[] = {LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port, LED5_GPIO_Port, LED6_GPIO_Port, LED7_GPIO_Port, LED8_GPIO_Port};
        uint16_t LED_Pin[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};


        // Display points for player L (from the left side to the middle)
        for (int i = 0; i < L_points; i++) {
            HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_SET);
        }

        // Display points for player R (from the right side to the middle)
        for (int i = 7; i >= 8 - R_points; i--) {
            HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_SET);
        }

        HAL_Delay(5000);
        // Turn off all LEDs
        for (int i = 0; i < 8; i++) {
            HAL_GPIO_WritePin(LED_GPIO_Port[i], LED_Pin[i], GPIO_PIN_RESET);
        }
        HAL_Delay(500);
}

bool L_hit(void)
{ if (HAL_GPIO_ReadPin(L_button_GPIO_Port, L_button_Pin) == 0) return true;
else return false; }

bool R_hit(void)
{ if (HAL_GPIO_ReadPin(R_button_GPIO_Port, R_button_Pin) == 0) return true;
else return false; }


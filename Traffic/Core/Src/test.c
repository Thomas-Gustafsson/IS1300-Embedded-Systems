/*
 * test.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Thomas
 */


#include <stdint.h>
#include "stdbool.h"
#include "test.h"
#include "trafficlights.h"
#include "pedestrian_light.h"
#include "gpio.h"
#include "spi.h"

// Function to test the north and south traffic lights
void trafficLED_Test() {
	// Set the bits corresponding to the LEDs that should illuminate
	uint8_t trafficAddress = 0x08;
	// Transmit the address data to the first shift register using SPI
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	// Update the bits and transmit the data to the first shift register via SPI.
	// This action pushes the previous transmission to the second shift register.
	trafficAddress = 0x01;
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	// Reset the address bits to low and transmit them as data to the first shift register via SPI.
	// This pushes the initial address data to the third shift register,
	// and the previous data to the second register.
	trafficAddress = 0x00;
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	// Update the latch of the shift register, transferring the shift register data to storage for output
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

// Function to test pedestrian lights
void pedestrianLED_Test() {
	// Set the bits corresponding to the LEDs that should illuminate
	uint8_t pedestrianAddress = 0x00;
	// Transmit the address data to the first shift register using SPI
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	// Reset the address bits to low and transmit them as data to the first shift register via SPI.
	// This action pushes the previous transmission to the second shift register.
	pedestrianAddress = 0x38;
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	// Update the bits and transmit the data to the first shift register via SPI.
	// This pushes the initial address data to the third shift register,
	// and the previous data to the second register.
	pedestrianAddress = 0x00;
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	// Update the latch of the shift register, transferring the shift register data to storage for output
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

// Function to test the traffic light switch
void trafficSwitch_Test() {
	// Read the state of the switches
	if(	HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == GPIO_PIN_SET
			|| HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_SET )
	{
		// If the switch state is high, activate lights by calling the relevant traffic LED function
		trafficLED_Test();
	} else {
		// Otherwise, turn off lights by setting them to low
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_SET);
	}
}

// Function to test the pedestrian light switch
void pedestrianSwitch_Test() {
	// Read the state of the switches
	if ( HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET )
	{
		// If the switch state is low, activate lights by calling the relevant pedestrian LED function
		pedestrianLED_Test();
	} else {
		// Otherwise, turn off lights by setting them to low
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_SET);
	}
}

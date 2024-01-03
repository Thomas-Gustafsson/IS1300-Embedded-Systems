/*
 * traffic_lights.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Thomas
 */

#include <stdint.h>
#include "traffic.h"
#include "gpio.h"
#include "spi.h"

uint32_t toggle;

void writeLED()
{
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&ledBuffer[0], 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&ledBuffer[1], 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&ledBuffer[2], 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

void setTrafficLights(enum LED color) {
	ledBuffer[0] = 0b000000; // NORTH
	ledBuffer[1] = 0b000000; // SOUTH
	switch(color) {
	case GREEN:
		ledBuffer[0] = ledBuffer[0] | 0b100000;
		ledBuffer[1] = ledBuffer[1] | 0b101100;
		break;
	case YELLOW:
		ledBuffer[0] = 0b010000;
		ledBuffer[1] = 0b101010;
		break;
	case RED:
		ledBuffer[0] = ledBuffer[0] | 0b001000;
		ledBuffer[1] = ledBuffer[1] | 0b010001;
		break;
	}
	writeLED();
}

void setPedestrianLight(enum STATUS status) {
	ledBuffer[1] = ledBuffer[1] & 0b100111;
	switch(status) {
	case WALK:
		ledBuffer[1] = ledBuffer[1] | 0b010000; // GREEN
		break;
	case WAIT:
		ledBuffer[1] = ledBuffer[1] | 0b001000; // RED
		break;
	}
	writeLED();
}

void toggleIndicatorLight() {
	toggle = ledBuffer[1] & 0b100000;
	if(toggle) ledBuffer[1] = ledBuffer[1] & 0b011111;
	else ledBuffer[1] = ledBuffer[1] | 0b100000;
	writeLED();
}



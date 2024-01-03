/*
 * traffic_logic.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Thomas
 */

#include <stdint.h>
#include "traffic.h"
#include "gpio.h"
#include "spi.h"

/*
uint16_t toggleFreq = 700;
uint16_t pedestrianDelay = 5000;
uint16_t walkingDelay = 8000;
uint16_t orangeDelay = 2000;


uint32_t time = 0;
uint32_t trafficLightStatus;

void crosswalk() {
	if ( HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET ) {
		trafficLightStatus = ledBuffer[1] & 000100;
		while (!ledBuffer[1]) {
			toggleIndicatorLight();
			HAL_Delay(toggleFreq);
		}
	}
}

*/

/*
 * traffic_logic.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Thomas
 */

#include <stdint.h>
#include "traffic.h"
#include "traffic_lights.c"
#include "gpio.h"
#include "spi.h"

uint8_t fromActive;
uint32_t ledBuffer[1];
uint32_t shift;

// Time keeping variables
uint32_t time = 0;
uint32_t toggleTime = 0;
uint32_t pedestrianTime = 0;

// Required variables, time constant
uint16_t toggleFreq = 500;
uint16_t orangeDelay = 4000;
uint16_t pedestrianDelay = 6000;
uint16_t walkingDelay = 8000;

typedef enum {
    ACTIVE,
    TRANSITION,
    CROSSING,
} states;

static states state, nextState;

void shiftWriteLED(uint32_t ledBuffer[]) {
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&ledBuffer[0], 3, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

uint32_t stageTrafficlight(uint8_t bits) {
    uint32_t shift = 0x000000;
    shift |= bits << 8;
    shift |= bits << 3;
    return shift;
}

uint32_t stagePedestrianlight(uint8_t bits) {
    uint32_t shift = 0x000000;
    shift |= bits << 11;
    return shift;
}

void crosswalk() {

    if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET && nextState != TRANSITION) {
        toggleTime = HAL_GetTick();
        pedestrianTime = HAL_GetTick();
        nextState = TRANSITION;
    }

    if((HAL_GetTick() - toggleTime) == toggleFreq && nextState == TRANSITION)
    	{
    		//traffic lights green, pedestrian toggle off
    		shift = stagePedestrianlight(1);
    		ledBuffer[0] |= shift;
    		shiftWriteLED(ledBuffer);
    	}
    	else if((HAL_GetTick() - toggleTime) == toggleFreq * 2  && nextState == TRANSITION)
    	{
    		// pedestrian toggle on
    		shift = stagePedestrianlight(4|1);
    		toggleTime = HAL_GetTick();
    		ledBuffer[0] |= shift;
    		shiftWriteLED(ledBuffer);
    	}
    	else if(nextState != TRANSITION)
    		shift = stagePedestrianlight(1);
}

void trafficSwitch(void) {
    state = ACTIVE;
    while (1) {
        switch (state) {
        case ACTIVE:
        	while(1) {
        		ledBuffer[0] = stageTrafficlight(4); // traffic light green
        		ledBuffer[0] &= ~shift;
        		crosswalk();

        		if ((HAL_GetTick() - time) <= orangeDelay) {
        		   ledBuffer[0] = stageTrafficlight(2);
        		}

        		ledBuffer[0] |= shift;
        		shiftWriteLED(ledBuffer);

        		if ((HAL_GetTick() - pedestrianTime) == (pedestrianDelay - orangeDelay) && nextState == TRANSITION) {
        		    break;
        		}
        	}

            fromActive = 1;
            break;

        case TRANSITION:
            time = HAL_GetTick();
            while ((HAL_GetTick() - time) <= orangeDelay) {
            	// ledBuffer[0] = stageTrafficlight(2) | stagePedestrianlight(1);

            	if ((HAL_GetTick() - toggleTime) == toggleFreq || fromActive == 0) {
                    ledBuffer[0] = stageTrafficlight(2) | stagePedestrianlight(1); // traffic light yellow, pedestrian light red
                } else if(HAL_GetTick() - toggleTime == toggleFreq * 2 || (HAL_GetTick() - toggleTime) > toggleFreq * 2 ){
                    ledBuffer[0] = stageTrafficlight(2) | stagePedestrianlight(4|1); // traffic light yellow
                    toggleTime = HAL_GetTick();
                }
                shiftWriteLED(ledBuffer);
            }

            if (fromActive == 1) {
                nextState = CROSSING;
            } else {
                nextState = ACTIVE;
            }
            break;

        case CROSSING:
        	fromActive = 0;
            time = HAL_GetTick();
            while ((HAL_GetTick() - time) <= walkingDelay) {
                ledBuffer[0] = stageTrafficlight(1) | stagePedestrianlight(2); // traffic light red, pedestrian light green
                shiftWriteLED(ledBuffer);
            }
            nextState = TRANSITION;
            break;
        }
        state = nextState;
    }
}

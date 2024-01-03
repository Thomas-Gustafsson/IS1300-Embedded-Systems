/*
 * test.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Thomas
 */


#include <stdint.h>
#include "stdbool.h"
#include "test.h"
#include "gpio.h"
#include "spi.h"
/*
uint8_t waitIndicator;
uint8_t fromActive;

uint32_t testLedBuffer[3];
uint32_t testBuffer[1];

uint32_t toggle_Test;
uint32_t trafficLightStatus_Test;

uint32_t shift;

typedef enum {
    ACTIVE,
    TRANSITION,
    CROSSING,
} states;

static states state, nextState;

uint32_t stageTrafficlight_Test(uint8_t statebit) {
    uint32_t shift = 0x000000;
    shift |= statebit << 8;
    shift |= statebit << 3;
    return shift;
}

uint32_t stagePedestrianlight_Test(uint8_t statebit) {
    uint32_t shift = 0x000000;
    shift |= statebit << 11;
    return shift;
}

uint32_t time = 0;
uint32_t toggleTime = 0;
uint32_t pedestrianTime = 0;
uint16_t orangeDelay = 4000;
uint16_t pedestrianDelay = 6000;
uint16_t walkingDelay = 8000;
uint16_t toggle_TestFreq = 500;


void crosswalkTest() {

    if (HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_RESET && nextState != TRANSITION) {
        toggleTime = HAL_GetTick();
        pedestrianTime = HAL_GetTick();
        nextState = TRANSITION;
    }

    if((HAL_GetTick() - toggleTime) == toggle_TestFreq && nextState == TRANSITION)
    	{
    		//traffic lights green, pedestrian toggle off
    		shift = stagePedestrianlight_Test(1);
    		testBuffer[0] |= shift;
    		shiftWriteLED_Test(testBuffer);
    	}
    	else if((HAL_GetTick() - toggleTime) == toggle_TestFreq * 2  && nextState == TRANSITION)
    	{
    		// pedestrian toggle on
    		shift = stagePedestrianlight_Test(4|1);
    		toggleTime = HAL_GetTick();
    		testBuffer[0] |= shift;
    		shiftWriteLED_Test(testBuffer);
    	}
    	else if(nextState != TRANSITION)
    		shift = stagePedestrianlight_Test(1);
}

void trafficSwitch_Test(void) {
    state = ACTIVE;
    while (1) {
        switch (state) {
        case ACTIVE:
        	while(1) {
        		testBuffer[0] = stageTrafficlight_Test(4); // traffic light green
        		testBuffer[0] &= ~shift;
        		crosswalkTest();

        		if ((HAL_GetTick() - time) <= orangeDelay) {
        		   testBuffer[0] = stageTrafficlight_Test(2);
        		}

        		testBuffer[0] |= shift;
        		shiftWriteLED_Test(testBuffer);

        		if ((HAL_GetTick() - pedestrianTime) == (pedestrianDelay - orangeDelay) && nextState == TRANSITION) {
        		    break;
        		}
        	}

            fromActive = 1;
            break;

        case TRANSITION:
            time = HAL_GetTick();
            while ((HAL_GetTick() - time) <= orangeDelay) {
            	// testBuffer[0] = stageTrafficlight_Test(2) | stagePedestrianlight_Test(1);

            	if ((HAL_GetTick() - toggleTime) == toggle_TestFreq || fromActive == 0) {
                    testBuffer[0] = stageTrafficlight_Test(2) | stagePedestrianlight_Test(1); // traffic light yellow, pedestrian light red
                } else if(HAL_GetTick() - toggleTime == toggle_TestFreq * 2 || (HAL_GetTick() - toggleTime) > toggle_TestFreq * 2 ){
                    testBuffer[0] = stageTrafficlight_Test(2) | stagePedestrianlight_Test(4|1); // traffic light yellow
                    toggleTime = HAL_GetTick();
                }
                shiftWriteLED_Test(testBuffer);
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
                testBuffer[0] = stageTrafficlight_Test(1) | stagePedestrianlight_Test(2); // traffic light red, pedestrian light green
                shiftWriteLED_Test(testBuffer);
            }
            nextState = TRANSITION;
            break;
        }
        state = nextState;
    }
}

void writeLED_Test()
{
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&testLedBuffer[0], 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&testLedBuffer[1], 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&testLedBuffer[2], 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

void shiftWriteLED_Test(uint32_t testBuffer[]) {
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&testBuffer[0], 3, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

void trafficLED_Test(enum testLED colour) {
	testLedBuffer[0] = 0b000000;
	testLedBuffer[1] = testLedBuffer[1] & 0b100000; //ö
	switch(colour) {
	case GREEN:
		testLedBuffer[0] = testLedBuffer[0] | 0b100000; // NORTH traffic light to GREEN
		testLedBuffer[1] = testLedBuffer[1] | 0b001100; // SOUTH traffic light to GREEN
		waitIndicator = 1;
		break;
	case YELLOW:
		testLedBuffer[0] = testLedBuffer[0] | 0b010000; // NORTH traffic light to YELLOW
		testLedBuffer[1] = testLedBuffer[1] | 0b001010; // SOUTH traffic light to YELLOW
		waitIndicator = 0;
		break;
	case RED:
		testLedBuffer[0] = testLedBuffer[0] | 0b001000; // NORTH traffic light to YELLOW
		testLedBuffer[1] = testLedBuffer[1] | 0b010001; // SOUTH traffic light to YELLOW
		waitIndicator = 1;
		break;
	}
	writeLED_Test();
}

void toggle_TestIndicatorLight_Test() {
	toggle_Test = testLedBuffer[1] & 0b100000;
	if(toggle_Test)
		testLedBuffer[1] = testLedBuffer[1] & ~0b100000;
	else
		testLedBuffer[1] = testLedBuffer[1] | 0b100000;
	writeLED_Test();
}

void crosswalk_Test() {
		// trafficLightStatus_Test = testLedBuffer[1] & 000100;

		if (waitIndicator) {
		toggle_TestIndicatorLight_Test();
		}
}
/* ------------------------------------------- */

/*

void traffic_Test() {
	state = ACTIVE;
	while(1) {
		switch(state) {
		case ACTIVE:
			while(HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_SET) {
				trafficLED_Test(GREEN);
				HAL_Delay(1000);
			}

			fromActive = 1;
			waitIndicator = 1;

			nextState = TRANSITION;

		break;

		case TRANSITION:
			trafficLED_Test(YELLOW);
			HAL_Delay(1000);
			if(fromActive)
				nextState = CROSSING;
			else if(~fromActive)
				nextState = ACTIVE;

		break;

		case CROSSING:
			trafficLED_Test(RED);
			HAL_Delay(1000);
			waitIndicator = 0;

			nextState = ACTIVE;

		break;
		}
	}
	state = nextState;
}


/* ------------------------------------------- */

/* void trafficSwitch_Test() {

	if(	HAL_GPIO_ReadPin(TL4_Car_GPIO_Port, TL4_Car_Pin) == GPIO_PIN_SET || HAL_GPIO_ReadPin(TL2_Car_GPIO_Port, TL2_Car_Pin) == GPIO_PIN_SET )
	{
		trafficLED_Test(GREEN);
		crosswalk_Test();
		HAL_Delay(1000);
		trafficLED_Test(YELLOW);
		crosswalk_Test();
		HAL_Delay(1000);
		trafficLED_Test(RED);
		crosswalk_Test();
		HAL_Delay(1000);
		trafficLED_Test(YELLOW);
		crosswalk_Test();
		HAL_Delay(1000);
		//LED_Test();
	} else {
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);;
	}

} */

void pedestrianSwitch_Test() {
	if ( HAL_GPIO_ReadPin(PL2_Switch_GPIO_Port, PL2_Switch_Pin) == GPIO_PIN_SET )
	{
		crosswalk_Test();
		//pedestrianLED_Test();
	} else {
		HAL_GPIO_WritePin(Reset_595_GPIO_Port, Reset_595_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	}
}


/* ----------------------------------------------------------------------------------------- */


void LED_Test() {
	uint8_t trafficAddress = 0b010000;
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	trafficAddress = 0b000010;
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	trafficAddress = 0b000000;
	HAL_SPI_Transmit(&hspi3, &trafficAddress, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

void pedestrianLED_Test() {
	uint8_t pedestrianAddress = 0x00;
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	pedestrianAddress = 0b100000;
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	pedestrianAddress = 0x00;
	HAL_SPI_Transmit(&hspi3, &pedestrianAddress, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}


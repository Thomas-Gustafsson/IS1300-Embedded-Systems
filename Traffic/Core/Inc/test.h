/*
 * test.h
 *
 *  Created on: Dec 7, 2023
 *      Author: Thomas
 */

#ifndef INC_TEST_H_
#define INC_TEST_H_

// LEDs
enum testLED {
	GREEN,
	YELLOW,
	RED,
};

void trafficLED_Test(enum testLED colour);
void pedestrianLED_Test_N(void);
void writeLED_Test();
void shiftWriteLED_Test(uint32_t testBuffer[]);
uint32_t stageTrafficlight(uint8_t trafficBit);
uint32_t stagePedestrianlight(uint8_t statebit);

void toggleIndicatorLight_Test();
void crosswalk_Test();
void crosswalkTest();
void testStageTrafficlight(void);


// Switches
void trafficSwitch_Test(void);
void pedestrianSwitch_Test(void);

void traffic_Test();

#endif /* INC_TEST_H_ */



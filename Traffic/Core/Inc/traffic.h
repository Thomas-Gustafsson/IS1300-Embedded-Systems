/*
 * traffic.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Thomas
 */

#ifndef INC_TRAFFIC_H_
#define INC_TRAFFIC_H_

extern uint32_t ledBuffer[1];

uint32_t stageTrafficlight(uint8_t statebit);
uint32_t stagePedestrianlight(uint8_t statebit);

void crosswalk();
void trafficSwitch(void);

void shiftWriteLED(uint32_t testBuffer[]);

#endif /* INC_TRAFFIC_H_ */

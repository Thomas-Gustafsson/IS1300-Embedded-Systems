/*
 * traffic.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Thomas
 */

#ifndef INC_TRAFFIC_H_
#define INC_TRAFFIC_H_

// LEDs
enum LED {
	GREEN,
	YELLOW,
	RED,
};

enum STATUS {
	WALK,
	WAIT,
};

extern uint32_t ledBuffer[3];

/**
 * @brief Changes north and south traffic light colours.
 * written in traffic_lights.c and called from traffic_logic.c
 *
 * Sets specific bits to high corresponding to a traffic
 * light colour and calls the writeLED() function to
 * transmit bits to the shift registers.
 *
 * @param colour The traffic light colour to set (GREEN, YELLOW, or RED).
 */
void setTrafficLights(enum LED colour);

/**
 * @brief Changes pedestrian light colours.
 * written in traffic_lights.c and called from traffic_logic.c
 *
 * Sets specific bits to high corresponding to a pedestrian
 * light colour and calls the writeLED() function to
 * transmit bits to the shift registers. WALK (green) or
 * WAIT (red).
 *
 * @param colour The pedestrian light status to set (WALK or WAIT).
 */
void setPedestrianLight(enum STATUS colour);

/**
 * @brief Toggles the pedestrian indicator light.
 * written in traffic_lights.c and called from traffic_logic.c
 *
 * Sets specific bit to high or low corresponding to a blue pedestrian
 * light. Negates current value, thus toggling the LED on or off.
 */
void toggleIndicatorLight();

/**
 * @brief Updates traffic and pedestrian lights.
 * written in traffic_lights.c and called from traffic_logic.c
 *
 * Stages bits meant for third, second and third shift registers.
 * Latches the shift register and reset, updating the LED's on or off.
 */
void writeLED();

/**
 * @brief Toggles the pedestrian indicator light.
 * written in traffic_logic.c
 *
 * Sets specific bit to high or low corresponding to a blue pedestrian
 * light. Negates current value, thus toggling the LED on or off.
 */
void crosswalk();

/* ----- Currently unused functions ----- */

// Switches
void carSwitch(void);
void pedestrianSwitch(void);

#endif /* INC_TRAFFIC_H_ */

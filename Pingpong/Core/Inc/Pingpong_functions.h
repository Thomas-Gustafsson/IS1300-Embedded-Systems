/*
 * pingpong_functions.h
 *
 *  Created on: Nov 3, 2023
 *      Author: Thomas Gustafsson & Viktor Björkén
 */
#include "stdbool.h"
#include <stdint.h>

#ifndef INC_PINGPONG_FUNCTIONS_H_
#define INC_PINGPONG_FUNCTIONS_H_

/**
@brief L_hit, check if L button is pressed
@param void
@return bool, true if L button pushed, false otherwise */
bool L_hit(void);
/**
@brief R_hit, check if R button is pressed
@param void
@return bool, true if R button pushed, false otherwise */
bool R_hit(void);
/**
@brief Show_points, shows points after missed ball
@param1 uint8_t L_points points for left player
@param2 uint8_t R_points points for right player
@return void, no return value
*/
void Show_points(uint8_t L_points, uint8_t R_points);
void Show_gamepoints(uint8_t L_points, uint8_t R_points);

void Led_on(uint8_t Lednr);

#endif /* INC_PINGPONG_FUNCTIONS_H_ */

/*
 * Test.h
 *
 *  Created on: Nov 2, 2023
 *      Author: Thomas Gustafsson & Viktor Björkén
 */

#include <stdint.h>

#ifndef INC_TEST_H_
#define INC_TEST_H_

void Test_program(void);
void Test_Led(void);
void Led_on(uint8_t Lednr);
void Test_Points(void);
void Show_points(uint8_t L_points, uint8_t R_points);
void Test_Buttons(void);

#endif /* INC_TEST_H_ */

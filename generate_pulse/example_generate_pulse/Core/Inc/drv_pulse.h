/*
 * drv_pulse.h
 *
 *  Created on: Oct 22, 2026
 *      Author: maith
 */

#ifndef SRC_DRV_PULSE_H_
#define SRC_DRV_PULSE_H_

#include "main.h"
void drv_pulse_init(TIM_HandleTypeDef* tim_init, uint16_t clock_input);
void drv_pulse_set_period(uint8_t TIM_Channel, uint16_t pulse);
void drv_pulse_deinit();

#endif /* SRC_DRV_PULSE_H_ */

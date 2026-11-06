/*
 * timer.h
 *
 *  Created on: Oct 28, 2026
 *      Author: ADMIN
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

#define TIMER_CYCLE_MS   10

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;

void setTimer1(int duration_ms);
void setTimer2(int duration_ms);
void setTimer3(int duration_ms);

void timerRun(void);

#endif /* INC_TIMER_H_ */

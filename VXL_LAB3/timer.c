/*
 * timer.c
 *
 *  Created on: Oct 28, 2026
 *      Author: ADMIN
 */

#include "timer.h"

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int timer3_counter = 0;
int timer3_flag = 0;

void setTimer1(int duration_ms) {
    timer1_counter = duration_ms / TIMER_CYCLE_MS;
    timer1_flag = 0;
}

void setTimer2(int duration_ms) {
    timer2_counter = duration_ms / TIMER_CYCLE_MS;
    timer2_flag = 0;
}

void setTimer3(int duration_ms) {
    timer3_counter = duration_ms / TIMER_CYCLE_MS;
    timer3_flag = 0;
}

void timerRun(void) {
    if (timer1_counter > 0) {
        timer1_counter--;
        if (timer1_counter <= 0) {
            timer1_flag = 1;
        }
    }

    if (timer2_counter > 0) {
        timer2_counter--;
        if (timer2_counter <= 0) {
            timer2_flag = 1;
        }
    }

    if (timer3_counter > 0) {
        timer3_counter--;
        if (timer3_counter <= 0) {
            timer3_flag = 1;
        }
    }
}

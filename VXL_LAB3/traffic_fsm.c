#include "traffic_fsm.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"

static int time_red = 5;
static int time_yellow = 2;
static int time_green = 3;

static int temp_time = 0;

static enum SystemMode current_mode = MODE_1_NORMAL;
static enum TrafficState traffic_state = AUTO_RED_GREEN;

static int count_way1 = 0;
static int count_way2 = 0;

void traffic_fsm_init(void) {
    current_mode = MODE_1_NORMAL;
    traffic_state = AUTO_RED_GREEN;
    count_way1 = time_red;
    count_way2 = time_green;
    setTimer3(1000);
    setTimer1(250);
}

static void run_traffic_normal(void) {
    switch (traffic_state) {
        case AUTO_RED_GREEN:
            setTrafficLeds(1, 0, 0, 0, 0, 1);
            if (timer3_flag == 1) {
                setTimer3(1000);
                count_way1--;
                count_way2--;
                if (count_way2 <= 0) {
                    traffic_state = AUTO_RED_YELLOW;
                    count_way2 = time_yellow;
                }
            }
            break;

        case AUTO_RED_YELLOW:
            setTrafficLeds(1, 0, 0, 0, 1, 0);
            if (timer3_flag == 1) {
                setTimer3(1000);
                count_way1--;
                count_way2--;
                if (count_way1 <= 0) {
                    traffic_state = AUTO_GREEN_RED;
                    count_way1 = time_green;
                    count_way2 = time_red;
                }
            }
            break;

        case AUTO_GREEN_RED:
            setTrafficLeds(0, 0, 1, 1, 0, 0);
            if (timer3_flag == 1) {
                setTimer3(1000);
                count_way1--;
                count_way2--;
                if (count_way1 <= 0) {
                    traffic_state = AUTO_YELLOW_RED;
                    count_way1 = time_yellow;
                }
            }
            break;

        case AUTO_YELLOW_RED:
            setTrafficLeds(0, 1, 0, 1, 0, 0);
            if (timer3_flag == 1) {
                setTimer3(1000);
                count_way1--;
                count_way2--;
                if (count_way2 <= 0) {
                    traffic_state = AUTO_RED_GREEN;
                    count_way1 = time_red;
                    count_way2 = time_green;
                }
            }
            break;
    }

    updateLedBuffer(count_way1, count_way2);
}

void traffic_fsm_run(void) {
    if (is_button_pressed(0)) {
        current_mode++;
        if (current_mode > MODE_4_MODIFY_GREEN) {
            current_mode = MODE_1_NORMAL;
            traffic_fsm_init();
        }

        clearAllLeds();
        setTimer1(250);

        if (current_mode == MODE_2_MODIFY_RED) {
            temp_time = time_red;
        } else if (current_mode == MODE_3_MODIFY_AMBER) {
            temp_time = time_yellow;
        } else if (current_mode == MODE_4_MODIFY_GREEN) {
            temp_time = time_green;
        }
    }

    switch (current_mode) {
        case MODE_1_NORMAL:
            run_traffic_normal();
            break;

        case MODE_2_MODIFY_RED:
            if (timer1_flag == 1) {
                setTimer1(250);
                toggleRedLeds();
            }

            if (is_button_pressed(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }

            if (is_button_pressed(2)) {
                time_red = temp_time;
            }

            updateLedBuffer(temp_time, 2);
            break;

        case MODE_3_MODIFY_AMBER:
            if (timer1_flag == 1) {
                setTimer1(250);
                toggleAmberLeds();
            }

            if (is_button_pressed(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }

            if (is_button_pressed(2)) {
                time_yellow = temp_time;
            }

            updateLedBuffer(temp_time, 3);
            break;

        case MODE_4_MODIFY_GREEN:
            if (timer1_flag == 1) {
                setTimer1(250);
                toggleGreenLeds();
            }

            if (is_button_pressed(1)) {
                temp_time++;
                if (temp_time > 99) temp_time = 1;
            }

            if (is_button_pressed(2)) {
                time_green = temp_time;
            }

            updateLedBuffer(temp_time, 4);
            break;
    }
}

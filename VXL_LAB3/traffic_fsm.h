#ifndef INC_TRAFFIC_FSM_H_
#define INC_TRAFFIC_FSM_H_

#include "main.h"

enum SystemMode {
    MODE_1_NORMAL = 1,
    MODE_2_MODIFY_RED,
    MODE_3_MODIFY_AMBER,
    MODE_4_MODIFY_GREEN
};

enum TrafficState {
    AUTO_RED_GREEN = 0,
    AUTO_RED_YELLOW,
    AUTO_GREEN_RED,
    AUTO_YELLOW_RED
};

void traffic_fsm_init(void);
void traffic_fsm_run(void);

#endif /* INC_TRAFFIC_FSM_H_ */

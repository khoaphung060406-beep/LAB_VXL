#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"

void display7SEG(int num);
void update7SEG(int index);
void updateLedBuffer(int time1, int time2);

void setTrafficLeds(int red1, int yel1, int gre1, int red2, int yel2, int gre2);

void clearAllLeds(void);

void toggleRedLeds(void);
void toggleAmberLeds(void);
void toggleGreenLeds(void);

#endif /* INC_LED_DISPLAY_H_ */

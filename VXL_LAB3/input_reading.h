#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

#define NUM_OF_BUTTONS               3

#define BUTTON_IS_PRESSED            GPIO_PIN_RESET
#define BUTTON_IS_RELEASED           GPIO_PIN_SET

void button_reading(void);
unsigned char is_button_pressed(unsigned char index);
unsigned char is_button_pressed_1s(unsigned char index);

#endif /* INC_INPUT_READING_H_ */

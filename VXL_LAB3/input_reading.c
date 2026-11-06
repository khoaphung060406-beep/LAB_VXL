#include "input_reading.h"
#include "timer.h"

#define DURATION_FOR_AUTO_INCREASING (1000 / TIMER_CYCLE_MS)

static GPIO_TypeDef* BUTTON_PORT[NUM_OF_BUTTONS] = {GPIOA, GPIOA, GPIOA};
static const uint16_t BUTTON_PIN[NUM_OF_BUTTONS] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2};

static GPIO_PinState debounceButtonBuffer1[NUM_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NUM_OF_BUTTONS];
static GPIO_PinState buttonBuffer[NUM_OF_BUTTONS];

static uint16_t counterForButtonPress1s[NUM_OF_BUTTONS];
static uint8_t flagForButtonPress1s[NUM_OF_BUTTONS];

static uint8_t flagForButtonPressed[NUM_OF_BUTTONS];

void button_reading(void) {
    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON_PORT[i], BUTTON_PIN[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            if (buttonBuffer[i] == BUTTON_IS_RELEASED && debounceButtonBuffer1[i] == BUTTON_IS_PRESSED) {
                flagForButtonPressed[i] = 1;
            }

            buttonBuffer[i] = debounceButtonBuffer1[i];

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                } else {
                    flagForButtonPress1s[i] = 1;
                }
            } else {
                counterForButtonPress1s[i] = 0;
                flagForButtonPress1s[i] = 0;
            }
        }
    }
}

unsigned char is_button_pressed(unsigned char index) {
    if (index >= NUM_OF_BUTTONS) return 0;
    if (flagForButtonPressed[index] == 1) {
        flagForButtonPressed[index] = 0;
        return 1;
    }
    return 0;
}

unsigned char is_button_pressed_1s(unsigned char index) {
    if (index >= NUM_OF_BUTTONS) return 0;
    return (flagForButtonPress1s[index] == 1);
}

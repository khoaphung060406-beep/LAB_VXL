#include "led_display.h"

int led_buffer[4] = {0, 0, 0, 0};

const uint8_t segment_codes[10] = {
    0x40, // 0: 0100 0000 (G tắt, ABCDEF sáng)
    0x79, // 1: 0111 1001 (BC sáng)
    0x24, // 2: 0010 0100
    0x30, // 3: 0011 0000
    0x19, // 4: 0001 1001
    0x12, // 5: 0001 0010
    0x02, // 6: 0000 0010
    0x78, // 7: 0111 1000
    0x00, // 8: 0000 0000 (Tất cả sáng)
    0x10  // 9: 0001 0000
};

// Cập nhật giá trị hiển thị lên buffer
void updateLedBuffer(int val1, int val2) {
    led_buffer[0] = val1 / 10;
    led_buffer[1] = val1 % 10;
    led_buffer[2] = val2 / 10;
    led_buffer[3] = val2 % 10;
}

// Xuất mã số ra 7 chân SEG_A -> SEG_G (PB0 -> PB6)
void display7SEG(int num) {
    if (num < 0 || num > 9) return;
    uint8_t code = segment_codes[num];
    for (int i = 0; i < 7; i++) {
        HAL_GPIO_WritePin(GPIOB, (GPIO_PIN_0 << i), (code & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

// Quét 1 trong 4 LED 7 đoạn (Transistor PNP: Mức 0 dẫn/sáng, mức 1 tắt)
void update7SEG(int index) {
    // Tắt hết 4 LED trước khi quét để tránh bóng mờ
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10, GPIO_PIN_SET);

    // Xuất dữ liệu số ra các thanh LED
    display7SEG(led_buffer[index]);

    // Bật đúng LED tương ứng
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); // EN0
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); // EN1
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET); // EN2
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // EN3
            break;
        default:
            break;
    }
}

// Điều khiển bật tắt từng đèn tín hiệu giao thông (PA3 -> PA8)
void setTrafficLeds(int red1, int yel1, int gre1, int red2, int yel2, int gre2) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, red1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, yel1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, gre1 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, red2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, yel2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, gre2 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void clearAllLeds(void) {
    setTrafficLeds(0, 0, 0, 0, 0, 0);
}

// Đảo trạng thái đèn Đỏ ở Mode 2
void toggleRedLeds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_6);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_RESET);
}

// Đảo trạng thái đèn Vàng ở Mode 3
void toggleAmberLeds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_7);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8, GPIO_PIN_RESET);
}

// Đảo trạng thái đèn Xanh ở Mode 4
void toggleGreenLeds(void) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_8);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);
}

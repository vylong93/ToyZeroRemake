/**
  ******************************************************************************
  * @file           : ws2812b_driver.h
  * @brief          : Header for ws2812b_driver.c file.
  *                   This file contains the common defines for driving WS2812B
  ******************************************************************************
  * @attention
  *
  * This software component is created base on STM32F1 HAL library.
  *
  ******************************************************************************
  */

#ifndef __WS2812B_DRIVER_H
#define __WS2812B_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define NUM_LEDS              (8)

/* Constain */
#define NUM_COLOR             (3)
#define COLOR_BIT_LENGTH      (8)
#define LEDSTRIP_DATA_LENGTH  (NUM_LEDS * NUM_COLOR * COLOR_BIT_LENGTH + 32 /* Zero bytes padding for >50us RES */)

/* Transmission coding for SPI 6.0 MBits/s */
#define CODE_LOW              (0xC0)  // b1100.0000
#define CODE_HIGH             (0xF8)  // b1111.1000

/* WS2812B have GRB/24-bit format */
typedef struct {
    uint8_t green;
    uint8_t red;
    uint8_t blue;
} rgbled_t;

/* Helper functions */
void setLedStripColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b);
void setAllLedStripColor(uint8_t r, uint8_t g, uint8_t b);
void showLedStrip(void);
void testLedStrip(void);

#ifdef __cplusplus
}
#endif

#endif /* __WS2812B_DRIVER_H */

/***************************************************************END OF FILE****/

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

#define NUM_LEDS        (8)     // NOTE: need to match with real hardware
#define MAX_BRIGHTNESS  (255)   // TODO: implement brightness adjustment

/* Transmission coding */
#define CODE_LOW        (0xC0)  // b11000000
#define CODE_HIGH       (0xF1)  // b11111000

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

#ifdef __cplusplus
}
#endif

#endif /* __WS2812B_DRIVER_H */

/***************************************************************END OF FILE****/

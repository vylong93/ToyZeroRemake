/**
  ******************************************************************************
  * @file    ws2812b_driver.c
  * @brief   This file implement SPI to driving WS2812B strip of 8 LEDs.
  ******************************************************************************
  * @attention
  *
  * This software component is created base on STM32F1 HAL library.
  *
  ******************************************************************************
  */

#include "ws2812b_driver.h"
#include "main.h"

extern SPI_HandleTypeDef hspi2; /* main.c */

static rgbled_t g_ledstrip[NUM_LEDS] = {{0, 0, 0}};

/**
  * @brief  Set one LED color in the strip
  * @param  i LED index start from 0 to NUM_LEDS - 1
  * @param  r RED value range from 0 to 255
  * @param  g GREEN value range from 0 to 255
  * @param  b BLUE value range from 0 to 255
  * @retval None
  */
void setLedStripColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
  if (i < NUM_LEDS) {
    /* TODO: fuse with global brightness value */
    g_ledstrip[i].red = r;
    g_ledstrip[i].green = g;
    g_ledstrip[i].blue = b;
  } /* else index out of range - simply do nothing */
}

/**
  * @brief  Set all LEDs color in the strip
  * @param  r RED value range from 0 to 255
  * @param  g GREEN value range from 0 to 255
  * @param  b BLUE value range from 0 to 255
  * @retval None
  */
void setAllLedStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setLedStripColor(i, r, g, b);
  }
}

/**
  * @brief  Output current LED strip value array.
  *         Global interrupts must be disabled while processing.
  * @retval None
  */
void showLedStrip(void) {
  __disable_irq(); // Protect critical section below due to timing constraints
  
  /*
  uint8_t ui8Data = 0;
  uint8_t* pui8Color = 0;
  uint32_t ui32Mask = 0;
  uint32_t ui32LastColorIndex = NUM_LEDS * 3; // GRB 3 colors
  for (uint32_t i = 0; i < ui32LastColorIndex; i++) {
    pui8Color = (uint8_t*)g_ledstrip + i;
    ui32Mask = 0x80; // b1000000
    while (ui32Mask != 0) {
      ui8Data = (*pui8Color & ui32Mask) ? (CODE_HIGH) : (CODE_LOW);
      // TODO: do software coding first and then offload to DMA transmit all the data
      HAL_SPI_Transmit(&hspi2, &ui8Data, 1, 1);
      ui32Mask >>= 1;
    }
  }
  */
 
  // send RGB color for every LED
  unsigned int i, j;
  for (i = 0; i < NUM_LEDS; i++) {
    uint8_t *rgb = (uint8_t *)&g_ledstrip[i]; // get GRB color for this LED

    // send green, then red, then blue
    for (j = 0; j < 3; j++) {
      uint8_t mask = 0x80;    // b1000000

      // check each of the 8 bits
      while (mask != 0) {
        if (rgb[j] & mask) {
          HAL_GPIO_WritePin(SW_WS2812B_GPIO_Port, SW_WS2812B_Pin, GPIO_PIN_SET);
  
          HAL_GPIO_WritePin(SW_WS2812B_GPIO_Port, SW_WS2812B_Pin, GPIO_PIN_RESET);
  
        } else {
          HAL_GPIO_WritePin(SW_WS2812B_GPIO_Port, SW_WS2812B_Pin, GPIO_PIN_SET);
  
          HAL_GPIO_WritePin(SW_WS2812B_GPIO_Port, SW_WS2812B_Pin, GPIO_PIN_RESET);
  
        }
        mask >>= 1;  // check next bit
      }
    }
  }

  __enable_irq();
}

/***************************************************************END OF FILE****/

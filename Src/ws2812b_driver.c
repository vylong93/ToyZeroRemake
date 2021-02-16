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
static uint8_t g_ledstripData[LEDSTRIP_DATA_LENGTH] = {0};

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
    g_ledstrip[i].red = r;
    g_ledstrip[i].green = g;
    g_ledstrip[i].blue = b;
    // TODO: fuse with global brightness value

    uint32_t ui32Mask = 0;
    uint32_t ui32dataIndex = 0;
    uint32_t ui32BitLength = NUM_COLOR * COLOR_BIT_LENGTH;
    uint32_t ui32ColorCode = g << 16 | r << 8 | b;

    // Scan bit from MSB and convert to WS2812B encoding
    for (int b = (ui32BitLength - 1); b >= 0; b--) {
        ui32Mask = 1 << b;
        ui32dataIndex = i * NUM_COLOR * COLOR_BIT_LENGTH + (ui32BitLength - 1 - b);
        g_ledstripData[ui32dataIndex] = (ui32ColorCode & ui32Mask) ? (CODE_HIGH) : (CODE_LOW);
    }
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
  HAL_SPI_Transmit(&hspi2, (unsigned char *)&g_ledstripData, LEDSTRIP_DATA_LENGTH, 1);
  __enable_irq();
}

/**
  * @brief  Led strip dummy function for testing only
  * @retval None
  */
void dummyLedStripData(void) {
  g_ledstrip[0].green = 0x00;
  g_ledstrip[0].red = 0x1F;
  g_ledstrip[0].blue = 0x00;

  g_ledstrip[1].green = 0x1F;
  g_ledstrip[1].red = 0x00;
  g_ledstrip[1].blue = 0x00;

  g_ledstrip[2].green = 0x00;
  g_ledstrip[2].red = 0x00;
  g_ledstrip[2].blue = 0x1F;

  g_ledstrip[3].green = 0x1F;
  g_ledstrip[3].red = 0x1F;
  g_ledstrip[3].blue = 0x00;

  g_ledstrip[4].green = 0x1F;
  g_ledstrip[4].red = 0x00;
  g_ledstrip[4].blue = 0x1F;

  g_ledstrip[5].green = 0x00;
  g_ledstrip[5].red = 0x1F;
  g_ledstrip[5].blue = 0x1F;

  g_ledstrip[6].green = 0x1F;
  g_ledstrip[6].red = 0x1F;
  g_ledstrip[6].blue = 0x1F;

  g_ledstrip[7].green = 0x07;
  g_ledstrip[7].red = 0x07;
  g_ledstrip[7].blue = 0x07;

  // WS2812B coding full conversion
  uint8_t* pui8Color = 0;
  uint8_t ui8Mask = 0;
  uint32_t ui32dataIndex = 0;
  // Scan strip
  for (int iLed = 0; iLed < NUM_LEDS; iLed++) {
    // Scan color
    for (int iColor = 0; iColor < NUM_COLOR; iColor++) {
      pui8Color = (uint8_t*)g_ledstrip + (iLed * NUM_COLOR + iColor);
      // Scan bit
      for (int i = COLOR_BIT_LENGTH - 1; i >= 0; i--) {
        ui32dataIndex = ((iLed * NUM_COLOR) + iColor) * COLOR_BIT_LENGTH + (COLOR_BIT_LENGTH - 1 - i);
        ui8Mask = 1 << i;
        g_ledstripData[ui32dataIndex] = (*pui8Color & ui8Mask) ? (CODE_HIGH) : (CODE_LOW);
      }
    }
  }
}

/**
  * @brief  Led strip testing function
  * @retval None
  */
void testLedStrip(void) {
  uint32_t test_delay = 250;

  setAllLedStripColor(0, 0, 0);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(255, 0, 0);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(0, 255, 0);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(0, 0, 255);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(0, 255, 255);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(255, 255, 0);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(255, 0, 255);
  showLedStrip();
  HAL_Delay(test_delay);

  setAllLedStripColor(255, 255, 255);
  showLedStrip();
  HAL_Delay(test_delay);

  dummyLedStripData();
  showLedStrip();
}

/***************************************************************END OF FILE****/

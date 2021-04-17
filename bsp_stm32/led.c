#include "led.h"
#include <stm32h743xx.h>
#include <stm32h7xx_hal_gpio.h>
#include <stm32h7xx_hal_rcc.h>

/* Configure GPIO pin : PB14 (LD3) */
GPIO_InitTypeDef GPIO_InitStruct =
{
  .Pin = GPIO_PIN_14,
  .Mode = GPIO_MODE_OUTPUT_PP,
  .Speed = GPIO_SPEED_LOW
};

void ledInit() {
   __HAL_RCC_GPIOB_CLK_ENABLE();
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void ledOn() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}
void ledOff() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

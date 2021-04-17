#ifndef BSP_STM32_BOARDCONFIG_HARDWARE_INIT_H_
#define BSP_STM32_BOARDCONFIG_HARDWARE_INIT_H_

#include <stdint.h>
#include <stm32h7xx_hal_gpio.h>
#include <stm32h7xx_hal_uart.h>
#include <stm32h7xx_hal_dma.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Declaration of global hardware handlers here.
 * Definition inside respective .cpp or .c files.
 */
extern UART_HandleTypeDef huart3;
extern GPIO_InitTypeDef gpio_uart_init_struct;

void hardware_init();

void MX_USART3_UART_Init(uint32_t baudRate);

#ifdef __cplusplus
}
#endif

#endif /* BSP_STM32_BOARDCONFIG_HARDWARE_INIT_H_ */

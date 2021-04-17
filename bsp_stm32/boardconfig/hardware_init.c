#include "hardware_init.h"
#include <stm32h7xx_hal_rcc.h>
#include <stdio.h>

void hardware_init() {
	MX_USART3_UART_Init(115200);
}


/**
 * ST-LINK UART3
 * CN5 pins on board
 */
UART_HandleTypeDef huart3;
GPIO_InitTypeDef gpio_uart_init_struct;

void MX_USART3_UART_Init(uint32_t baudRate)
{
	__HAL_RCC_USART3_CONFIG(RCC_USART3CLKSOURCE_HSI);
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_USART3_CLK_ENABLE();

	int result;
	huart3.Instance = USART3;
	huart3.Init.BaudRate = baudRate;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    //huart3.Init.FIFOMode = UART_FIFOMODE_DISABLE;
	//huart3.Init.TXFIFOThreshold = UART_TXFIFO_THRESHOLD_1_8;
	//huart3.Init.RXFIFOThreshold = UART_RXFIFO_THRESHOLD_1_8;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	// we can't do error handling (simple print out first) here because UART3 is our print interface
	result = HAL_UART_Init(&huart3);
	if(result == HAL_OK) {
		printf("\rUART3 configured successfully!\r\n");
	}
}

// Will be called by HAL_UART_Init
void HAL_UART_MspInit(UART_HandleTypeDef* huart) {
	/*Configure GPIO pins : PD8 PD9 */
	gpio_uart_init_struct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	gpio_uart_init_struct.Mode = GPIO_MODE_AF_PP;
	gpio_uart_init_struct.Pull = GPIO_NOPULL;
	gpio_uart_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart_init_struct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &gpio_uart_init_struct);
}

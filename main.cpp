#include <stm32h7xx_nucleo.h>
#include <hardware_init.h>

#include <rtems.h>
#include <stdio.h>
#include <rtems/console.h>

int main() {
	hardware_init();
	printf("Hallo Welt!\n\r");
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	while (1) {
		(void) rtems_task_wake_after( 1.0 * rtems_clock_get_ticks_per_second() );
		BSP_LED_Toggle(LED1);
		BSP_LED_Toggle(LED2);
		BSP_LED_Toggle(LED3);
	}

}

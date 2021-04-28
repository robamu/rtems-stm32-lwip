#include "common.h"
#include "stm32h7xx_nucleo.h"

#include <lwip/opt.h>

#if NO_SYS == 0

#include <lwip/sys.h>

#include <rtems_lwip/rtems_lwip.h>
#include <rtems_lwip/app_ethernet.h>
#include <rtems_lwip/app_dhcp.h>
#include <rtems_lwip/ethernetif.h>

#include <bsp.h>


void start_networking_utility_threads() {
  rtems_lwip_start_link_thread(100, RTEMS_MINIMUM_STACK_SIZE, RTEMS_MINIMUM_PRIORITY + 50);
  rtems_lwip_start_dhcp_thread(500, RTEMS_MINIMUM_STACK_SIZE, RTEMS_MAXIMUM_PRIORITY - 70);
}

void led_thread() {
  while(true) {
    BSP_LED_Toggle(LED1);
    usleep(LWIP_APP_LED_BLINK_INTERVAL * 1000);
  }
}

#endif

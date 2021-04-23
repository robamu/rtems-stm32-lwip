#include "common.h"
#include "stm32h7xx_nucleo.h"

#include "lwip/opt.h"

#if NO_SYS == 0

#include "lwip/sys.h"

#include "rtems_lwip.h"
#include "lwip_port/app_dhcp.h"
#include "lwip_port/ethernetif.h"

#include <bsp.h>


void start_networking_utility_threads() {
  sys_thread_new("LINK", ethernet_link_thread, (void*) rtems_lwip_get_netif(0),
      RTEMS_MINIMUM_STACK_SIZE, RTEMS_MINIMUM_PRIORITY + 50);
  sys_thread_new("DHCP", dhcp_thread, (void*) rtems_lwip_get_netif(0), RTEMS_MINIMUM_STACK_SIZE,
      RTEMS_MAXIMUM_PRIORITY - 70);
}

void led_thread() {
  while(true) {
    BSP_LED_Toggle(LED1);
    usleep(LWIP_APP_LED_BLINK_INTERVAL * 1000);
  }
}

#endif

#include "netcon_app.h"
#include "lwip_port/app_dhcp.h"
#include "lwip_port/ethernetif.h"

#include "lwip/opt.h"

#if LWIP_NETCONN

#include "udpecho.h"
#include "tcpecho.h"
#include <conf_app.h>
#include <stm32h7xx_nucleo.h>

#include "lwip/sys.h"

#include <stdio.h>

void led_thread();

void stm32_lwip_netcon_api_app() {


#if LWIP_APP_SELECT == LWIP_APP_UDP_ECHOSERVER
  /* Initialize the UDP echo server thread */
  //udpecho_init();
  //printf("Listener port for UDP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#elif LWIP_APP_SELECT == LWIP_APP_TCP_ECHOSERVER
  /* Initialize the TCP echo server thread */
  tcpecho_init();
  printf("Listener port for TCP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#endif
  //sys_thread_new("led0", led_thread, NULL, RTEMS_MINIMUM_STACK_SIZE, RTEMS_MAXIMUM_PRIORITY - 20);
//  sys_thread_new("link", ethernet_link_thread, NULL, RTEMS_MINIMUM_STACK_SIZE,
//      RTEMS_MINIMUM_PRIORITY + 50);
//  sys_thread_new("dhcp", dhcp_thread, NULL, RTEMS_MINIMUM_STACK_SIZE, RTEMS_MAXIMUM_PRIORITY - 70);
  while(true) {
    usleep(500 * 1000);
  }
  //rtems_task_delete( RTEMS_SELF );
}

void led_thread() {
  BSP_LED_Toggle(LED1);
  usleep(LWIP_APP_LED_BLINK_INTERVAL * 1000);
}

#endif

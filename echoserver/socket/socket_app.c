#include "socket_app.h"
#include "echoserver/common/common.h"

#include <rtems_lwip/rtems_lwip.h>
#include <rtems_lwip/app_dhcp.h>
#include <rtems_lwip/ethernetif.h>
#include <lwip/opt.h>

#if LWIP_SOCKET

#include "tcp_echo_socket.h"
#include "udp_echo_socket.h"
#include <conf_app.h>
#include <stm32h7xx_nucleo.h>

#include "lwip/sys.h"

#include <stdio.h>

uint8_t recv_buffer[ETH_RX_BUFFER_SIZE] RTEMS_ALIGNED(32);

void stm32_lwip_socket_api_app() {


#if LWIP_APP_SELECT == LWIP_APP_UDP_ECHOSERVER
  /* Initialize the UDP echo server thread */
  udp_socket_init();
  printf("Listener port for UDP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#elif LWIP_APP_SELECT == LWIP_APP_TCP_ECHOSERVER
  /* Initialize the TCP echo server thread */
  tcp_socket_init();
  printf("Listener port for TCP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#endif
  start_networking_utility_threads();
  sys_thread_new("led0", led_thread, NULL, RTEMS_MINIMUM_STACK_SIZE, RTEMS_MAXIMUM_PRIORITY - 20);
  rtems_task_delete( RTEMS_SELF );
}

#endif

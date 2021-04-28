#include "raw_app.h"

#include <lwip/opt.h>

#if NO_SYS == 1

#include "conf_app.h"
#include "stm32h7xx_nucleo.h"
#include "udp_echo_raw.h"
#include "tcp_echo_raw.h"

#include <rtems_lwip/ethernetif.h>
#include <rtems_lwip/app_ethernet.h>
#include <rtems_lwip/app_dhcp.h>
#include <rtems_lwip/rtems_lwip.h>

#include <lwip/timeouts.h>

#if LWIP_APP_BLINK_LED_PERIODIC == 1
void led_periodic_handle();
uint32_t led_timer = 0;
#endif

void stm32_lwip_raw_api_app() {

#if LWIP_APP_SELECT == LWIP_APP_UDP_ECHOSERVER
  udp_echoserver_init(LWIP_APP_TCPIP_PORT);
  printf("Listener port for UDP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#elif LWIP_APP_SELECT == LWIP_APP_TCP_ECHOSERVER
  tcp_echoserver_init(LWIP_APP_TCPIP_PORT);
  printf("Listener port for TCP server: %d\n\r", LWIP_APP_TCPIP_PORT);
#endif

  while (1) {
    /* Read a received packet from the Ethernet buffers and send it
           to the lwIP for handling */
    ethernetif_input(rtems_lwip_get_netif(0));

    /* Handle timeouts */
    sys_check_timeouts();

#if LWIP_NETIF_LINK_CALLBACK
    ethernet_link_periodic_handle(rtems_lwip_get_netif(0));
#endif

#if LWIP_DHCP
    dhcp_periodic_handle(rtems_lwip_get_netif(0));
#endif

    led_periodic_handle();

  }
}

void led_periodic_handle() {
  uint32_t time_now = HAL_GetTick();
  /* Blink LED every configured ms */
  if (time_now - led_timer >= LWIP_APP_LED_BLINK_INTERVAL) {
    led_timer = time_now;
    BSP_LED_Toggle(LED1);
  }
}

#endif /* NO_SYS == 0 */

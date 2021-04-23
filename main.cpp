#include <conf_app.h>

#include <stm32h7xx_nucleo.h>
#include <networking/udp_echoserver.h>

#include <lwip_port/app_ethernet.h>
#include <lwip_port/ethernetif.h>
#include <lwip_port/app_dhcp.h>

#include <lwip/netif.h>
#include <lwip/timeouts.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems_lwip.h>

#include <stdio.h>

#if LWIP_APP_BLINK_LED_PERIODIC == 1
void led_periodic_handle();
uint32_t led_timer = 0;
#endif

void stm32_lwip_raw_api_app();

int main() {
  printf("\n\r-- STM32 RTEMS lwIP Application -- \n\r");

  {
    char api[10] = {};
    char type[25] = {};

#if LWIP_APP_API_SELECT == LWIP_APP_RAW_API
    sprintf(api, "Raw");
#elif LWIP_APP_API_SELECT == LWIP_APP_NETCON_API
    sprintf(api, "Netcon");
#elif LWIP_APP_API_SELECT == LWIP_APP_SOCKET_API
    sprintf(api, "Socket");
#endif

#if LWIP_APP_SELECT == LWIP_APP_UDP_ECHOSERVER
    sprintf(type, "UDP Echoserver");
#else
    sprintf(type, "TCP Echoserver");
#endif

    printf("-- Application information | API: %s | Type: %s --\n\r", api, type);
  }

  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);

  set_dhcp_state(DHCP_START);

  rtems_lwip_init(NULL, &ethernet_link_status_updated);

  /* Raw API (mainloop) */
#if LWIP_APP_API_SELECT == LWIP_APP_RAW_API
  stm32_lwip_raw_api_app();
#endif

}

void led_periodic_handle() {
  uint32_t time_now = HAL_GetTick();
  /* Blink LED every configured ms */
  if (time_now - led_timer >= LWIP_APP_LED_BLINK_INTERVAL) {
    led_timer = time_now;
    BSP_LED_Toggle(LED1);
  }
}

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

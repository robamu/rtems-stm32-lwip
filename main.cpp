#include "conf_app.h"
#include "rtems_lwip.h"
#include "stm32h7xx_nucleo.h"

#include "echoserver/socket/socket_app.h"
#include "echoserver/raw/raw_app.h"
#include "echoserver/netcon/netconn_app.h"

#include "lwip_port/app_ethernet.h"
#include "lwip_port/app_dhcp.h"

#include <rtems.h>
#include <rtems/console.h>

#include <stdio.h>

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
#elif LWIP_APP_API_SELECT == LWIP_APP_NETCON_API
  stm32_lwip_netconn_api_app();
#elif LWIP_APP_API_SELECT == LWIP_APP_SOCKET_API
  stm32_lwip_socket_api_app();
#endif

}

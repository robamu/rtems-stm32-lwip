/**
 * @brief   Demo application for the STM32 RTEMS lwIP support.
 * @details
 * This example was used to test all three major lwIP APIs on the STM32H7 with RTEMS
 *
 *  1. RAW API, high performance using callbacks
 *  2. Netcon API, sequential API
 *  3. Socket API, sequential API, less performance but portable API.
 *
 * This demo can be configured through the CMake build system or by manually editing the
 * conf_app.h file in the build folder.
 * @author  R. Mueller
 * @return
 */
#include "conf_app.h"
#include "rtems_lwip/rtems_lwip.h"

#include "stm32h7xx_nucleo.h"

#include "echoserver/socket/socket_app.h"
#include "echoserver/raw/raw_app.h"
#include "echoserver/netcon/netconn_app.h"

#include <rtems_lwip/ethernetif.h>
#include <rtems_lwip/app_ethernet.h>
#include <rtems_lwip/app_dhcp.h>

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

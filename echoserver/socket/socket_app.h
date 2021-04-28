#ifndef NETWORKING_NETCON_SOCKET_APP_H_
#define NETWORKING_NETCON_SOCKET_APP_H_

#include "rtems_lwip/ethernetif.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t recv_buffer[ETH_RX_BUFFER_SIZE];

void stm32_lwip_socket_api_app();

#ifdef __cplusplus
}
#endif

#endif /* NETWORKING_NETCON_SOCKET_APP_H_ */

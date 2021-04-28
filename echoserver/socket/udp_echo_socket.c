#include "socket_app.h"
#include "udp_echo_socket.h"
#include "rtems_lwip/ethernetif.h"

#include "lwip/opt.h"

#if LWIP_SOCKET == 1

#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"


void udp_socket_thread(void* args) {
  int sock, newconn, size;
  struct sockaddr_in address;

  /* create a UDP socket */
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("udp_socket_init: Socket creation failed\n");
    return;
  }

  /* bind to port 80 at any interface */
  address.sin_family = AF_INET;
  address.sin_port = htons(LWIP_APP_TCPIP_PORT);
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (const struct sockaddr*) &address, sizeof(address)) < 0) {
    printf("udp_socket_init: Socket bind failed\n");
    return;
  }

  while(true) {
    struct sockaddr_in remotehost = {};
    int remotehostlen = sizeof(remotehost);

    int recv_size = recvfrom(
        sock,
        recv_buffer,
        ETH_RX_BUFFER_SIZE,
        0,
        (struct sockaddr *) &remotehost,
        &remotehostlen
    );

#if LWIP_APP_RECEIVE_WIRETAPPING == 1
    recv_buffer[recv_size] = '\0';
    printf("UDP Socket Server received %d bytes\n", recv_size);
    printf("Received string: %s\n", recv_buffer);
#endif

    if(recv_size > 0) {
        int send_flags = 0;
        int send_ret = sendto(
                sock,
                recv_buffer,
                recv_size,
                send_flags,
                (const struct sockaddr *) &remotehost,
                sizeof(remotehost)
        );
#if LWIP_APP_RECEIVE_WIRETAPPING == 1
        printf("Sent back %d bytes\n", send_ret);
#endif

    }
    else if(recv_size == 0) {
        printf("Empty packet received\n");
    }
    else {
        printf("udp_socket_init: recvfrom failed\n");
    }
  }
}

void udp_socket_init() {
  sys_thread_new("udpecho_thread", udp_socket_thread, NULL, (RTEMS_MINIMUM_STACK_SIZE*3),
      LWIP_APP_SERVER_THREAD_PRIO);
}

#endif

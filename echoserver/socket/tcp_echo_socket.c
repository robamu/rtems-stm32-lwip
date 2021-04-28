#include "socket_app.h"
#include "tcp_echo_socket.h"
#include "rtems_lwip/ethernetif.h"

#include "lwip/opt.h"

#if LWIP_SOCKET == 1

#include "lwip/sys.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"


void tcp_socket_thread(void* args) {
  int sock, newconn, size;
  struct sockaddr_in address, remotehost;

  /* create a TCP socket */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("tcp_socket_init: Socket creation failed\n");
    return;
  }

  /* bind to port 80 at any interface */
  address.sin_family = AF_INET;
  address.sin_port = htons(LWIP_APP_TCPIP_PORT);
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (const struct sockaddr*) &address, sizeof(address)) < 0) {
    printf("tcp_socket_init: Socket bind failed\n");
    return;
  }

  uint8_t tcp_backlog = 5;
  if(listen(sock, tcp_backlog) < 0) {
    printf("tcp_socket_init: Listen call failed\n");
  }

  size = sizeof(remotehost);
  ssize_t bytes_recvd = 0;
  ssize_t bytes_sent = 0;

  while (1) {
    newconn = accept(sock, (struct sockaddr *)&remotehost, (socklen_t *)&size);
    do {
      bytes_recvd = recv(newconn, recv_buffer, sizeof(recv_buffer) - 1, 0);

      if(bytes_recvd > 0) {
#if LWIP_APP_RECEIVE_WIRETAPPING == 1
      recv_buffer[bytes_recvd] = '\0';
      printf("TCP Socket Server received %d bytes\n", bytes_recvd);
      printf("Received string: %s\n", recv_buffer);
#endif

        /* Echo back received data */
        bytes_sent = send(newconn, recv_buffer, bytes_recvd, 0);
        if(bytes_sent != bytes_recvd) {
          printf("tcp_socket_thread: Number of bytes sent not equal to "
              "number of bytes received!\n");
        }

#if LWIP_APP_RECEIVE_WIRETAPPING == 1
        printf("Sent back %d bytes\n", bytes_sent);
#endif

      }
      else if(bytes_recvd == 0) {
        /* Client closed connection */
#if LWIP_APP_RECEIVE_WIRETAPPING == 1
        printf("Client closed connection\n");
#endif
      }
      else {
        /* Error receiving data */
        printf("tcp_socket_thread: Error receiving TCP data with code %d\n", bytes_recvd);
      }
    } while(bytes_recvd > 0);
   closesocket(newconn);
 }

}

void tcp_socket_init() {
  sys_thread_new("tcp0", tcp_socket_thread, NULL, (RTEMS_MINIMUM_STACK_SIZE * 3),
      LWIP_APP_SERVER_THREAD_PRIO);
}

#endif

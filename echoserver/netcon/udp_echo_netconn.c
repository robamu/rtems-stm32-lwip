/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "udp_echo_netconn.h"

#include <lwip/opt.h>

#if LWIP_NETCONN

#include <lwip/api.h>
#include <lwip/sys.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void
udpecho_thread(void *arg)
{
  struct netconn *conn;
  struct netbuf *buf, *tx_buf;
  err_t err;
  LWIP_UNUSED_ARG(arg);
  
  conn = netconn_new(NETCONN_UDP);
  netconn_bind(conn, IP_ADDR_ANY, LWIP_APP_TCPIP_PORT);
  
  LWIP_ERROR("udpecho: invalid conn", (conn != NULL), return;);
  
  while (1) {
    err = netconn_recv(conn, &buf);
    if (err == ERR_OK) {
      
      tx_buf = netbuf_new();
      netbuf_alloc(tx_buf, buf->p->tot_len);

      pbuf_take(tx_buf->p, (const void *)buf->p->payload, buf->p->tot_len);

#if LWIP_APP_RECEIVE_WIRETAPPING == 1
      char* data = (char*) buf->p->payload;
      *(data + buf->p->len) = '\0';
      printf("UDP Netcon Server received %d bytes\n\r", buf->p->len);
      printf("Received string: %s\n\r", data);
#endif

      err = netconn_sendto(conn, tx_buf, (const ip_addr_t *)&(buf->addr), buf->port);
      if(err != ERR_OK) {
        LWIP_DEBUGF(LWIP_DBG_ON, ("netconn_send failed: %d\n", (int)err));
      } else {
        LWIP_DEBUGF(LWIP_DBG_ON, ("got %s\n", buffer));
      }
      netbuf_delete(tx_buf);
    }
    netbuf_delete(buf);
  }
}
/*-----------------------------------------------------------------------------------*/
void
udpecho_init(void)
{
  sys_thread_new("udpecho_thread", udpecho_thread, NULL, (RTEMS_MINIMUM_STACK_SIZE*2), LWIP_APP_SERVER_THREAD_PRIO);
}

#endif /* LWIP_NETCONN */

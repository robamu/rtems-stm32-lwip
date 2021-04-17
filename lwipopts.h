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
 * Author: Simon Goldschmidt
 *
 */
#ifndef LWIP_HDR_LWIPOPTS_H__
#define LWIP_HDR_LWIPOPTS_H__

/* Prevent having to link sys_arch.c (we don't test the API layers in unit tests) */
#define NO_SYS                          0
#define LWIP_NETCONN                    1
#define LWIP_SOCKET                     1
#define LWIP_DNS                        1

#define LWIP_IPV6                       1
#define LWIP_IPV4                       1

#define LWIP_ETHERNET                   1
#define LWIP_NETIF_API                  1
/* Enable DHCP to test it, disable UDP checksum to easier inject packets */
#define LWIP_DHCP                       1
#define LWIP_TIMEVAL_PRIVATE            0
#define LWIP_POSIX_SOCKETS_IO_NAMES     0

/* Minimal changes to opt.h required for tcp unit tests: */
#define MEM_SIZE                        16000
#define TCP_SND_QUEUELEN                40
#define MEMP_NUM_TCP_SEG                TCP_SND_QUEUELEN
#define TCP_SND_BUF                     (12 * TCP_MSS)
#define TCP_WND                         (10 * TCP_MSS)
#define LWIP_WND_SCALE                  1
#define TCP_RCV_SCALE                   0
#define PBUF_POOL_SIZE                  400 // pbuf tests need ~200KByte

/* Minimal changes to opt.h required for etharp unit tests: */
#define ETHARP_SUPPORT_STATIC_ENTRIES   1

#define LWIP_NETIF_LINK_CALLBACK 		1

#define ETH_MAC_ADDR0    ((uint8_t)0x02)
#define ETH_MAC_ADDR1    ((uint8_t)0x00)
#define ETH_MAC_ADDR2    ((uint8_t)0x00)
#define ETH_MAC_ADDR3    ((uint8_t)0x00)
#define ETH_MAC_ADDR4    ((uint8_t)0x00)
#define ETH_MAC_ADDR5    ((uint8_t)0x00)
#define ETH_MAC_ADDR 	 { ETH_MAC_ADDR0, ETH_MAC_ADDR1, ETH_MAC_ADDR2, ETH_MAC_ADDR3, ETH_MAC_ADDR4, ETH_MAC_ADDR5 }

/* Static IP ADDRESS */
#define IP_ADDR0   169
#define IP_ADDR1   254
#define IP_ADDR2   1
#define IP_ADDR3   38

/* NETMASK */
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   0
#define NETMASK_ADDR3   0

/* Gateway Address */
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   178
#define GW_ADDR3   1

#endif /* LWIP_HDR_LWIPOPTS_H__ */

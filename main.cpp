#include <stm32h7xx_nucleo.h>

#include <lwip_port/app_ethernet.h>
#include <lwip_port/ethernetif.h>
#include <eth_lwip.h>

#include <lwip/netif.h>
#include <lwip/timeouts.h>

#include <rtems.h>
#include <rtems/console.h>

#include <stdio.h>

struct netif gnetif;

int main() {
	printf("STM32 RTEMS lwIP Application!\n\r");

#if NO_SYS == 1
	set_eth_lwip_link_callback_fnc(&ethernet_link_status_updated);

	eth_lwip_init(NULL);

	while (1) {
//	    /* Read a received packet from the Ethernet buffers and send it
//	       to the lwIP for handling */
//	    ethernetif_input(&gnetif);
//
//	    /* Handle timeouts */
//	    sys_check_timeouts();

	#if LWIP_NETIF_LINK_CALLBACK
	    //ethernet_link_periodic_handle(&gnetif);
	#endif

		(void) rtems_task_wake_after( 1.0 * rtems_clock_get_ticks_per_second() );
	}
#endif

}

#include "conf_app.h"

#include <bsp.h>
#include <rtems/rtems/tasks.h>

#include <stdio.h>

extern int main();

rtems_task Init(rtems_task_argument argument) {
	main();
	while(1) {}
	(void) rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/

#define CONFIGURE_MICROSECONDS_PER_TICK         1000

//! Specify the allocation scheme used for RTEMS.
//! See: https://docs.rtems.org/branches/master/c-user/config/intro.html
#define RTEMS_USE_UNLIMITED_OBJECTS_ALLOCATION  0

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#if RTEMS_USE_UNLIMITED_OBJECTS_ALLOCATION == 1

#define CONFIGURE_UNIFIED_WORK_AREAS
#define CONFIGURE_UNLIMITED_OBJECTS
#define CONFIGURE_INIT_TASK_STACK_SIZE              (RTEMS_MINIMUM_STACK_SIZE * 6)

#else

#if LWIP_APP_API_SELECT == LWIP_APP_RAW_API

#define CONFIGURE_MAXIMUM_TASKS                     5
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES            1
#define CONFIGURE_MAXIMUM_SEMAPHORES                1
#define CONFIGURE_MAXIMUM_TIMERS                    1
#define CONFIGURE_INIT_TASK_STACK_SIZE              (RTEMS_MINIMUM_STACK_SIZE * 2)
#define CONFIGURE_EXTRA_TASK_STACKS                 (2 * RTEMS_MINIMUM_STACK_SIZE)

#elif LWIP_APP_API_SELECT == LWIP_APP_NETCON_API || LWIP_APP_API_SELECT == LWIP_APP_SOCKET_API

#define CONFIGURE_MAXIMUM_TASKS                     10
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES            8
#define CONFIGURE_MAXIMUM_SEMAPHORES                8
#define CONFIGURE_MAXIMUM_TIMERS                    1
#define CONFIGURE_INIT_TASK_STACK_SIZE              (RTEMS_MINIMUM_STACK_SIZE * 2)
#define CONFIGURE_EXTRA_TASK_STACKS                 (2 * RTEMS_MINIMUM_STACK_SIZE)

#endif

#endif /* RTEMS_USE_UNLIMITED_OBJECTS_ALLOCATION == 1 */

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/

#include <stdio.h>
#include <bsp.h>
#include <rtems/rtems/tasks.h>

extern int main();

rtems_task Init(rtems_task_argument argument) {
	main();
	while(1) {}
	(void) rtems_task_delete( RTEMS_SELF );
}

/**************** START OF CONFIGURATION INFORMATION ****************/
//! Specify the allocation scheme used for RTEMS.
//! See: https://docs.rtems.org/branches/master/c-user/config/intro.html
#define RTEMS_USE_UNLIMITED_OBJECTS_ALLOCATION  1

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK     1000

#define CONFIGURE_MAXIMUM_TASKS             10
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    10
#define CONFIGURE_MAXIMUM_SEMAPHORES        10

#define CONFIGURE_EXTRA_TASK_STACKS         (6 * RTEMS_MINIMUM_STACK_SIZE)
#define CONFIGURE_INIT_TASK_STACK_SIZE      (RTEMS_MINIMUM_STACK_SIZE * 5)
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/

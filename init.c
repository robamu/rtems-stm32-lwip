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

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK     1000

#define CONFIGURE_MAXIMUM_TASKS             10
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    10
#define CONFIGURE_MAXIMUM_SEMAPHORES        10

#define CONFIGURE_EXTRA_TASK_STACKS         (5 * RTEMS_MINIMUM_STACK_SIZE)

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/****************  END OF CONFIGURATION INFORMATION  ****************/

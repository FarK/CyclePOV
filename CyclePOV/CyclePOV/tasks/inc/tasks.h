#ifndef TASKS_H_
#define TASKS_H_

#define LEDS_STRIPE_PRIORITY	(LOADER_PRIORITY + 1)
#define LOADER_PRIORITY			(IDLE_PRIORITY + 1)
#define IDLE_PRIORITY			tskIDLE_PRIORITY

#define LEDS_STRIPE_STACK_SIZE	256
#define LOADER_STACK_SIZE		1024*2
#define IDLE_STACK_SIZE			configMINIMAL_STACK_SIZE

void createTasks();

#endif /* TASKS_H_ */

// Kernel includes
#include "FreeRTOSIncludes.h"

//STM32F4 includes
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//Tasks
#include "tasks.h"

#include "defines.h"

//Setup the hardware
static void hardwareSetup(void);

int main(void)
{
	hardwareSetup();
	createTasks();
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following line
	will never be reached.  If the following line does execute, then there was
	insufficient FreeRTOS heap memory available for the idle and/or timer tasks
	to be created.  See the memory management section on the FreeRTOS web site
	for more details. */
	while(1);
}

static void hardwareSetup( void )
{
	// Setup STM32 system (clock, PLL and Flash configuration)
	SystemInit();

	//Ensure all priority bits are assigned as preemption priority bits
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
}

/******************************************************************************
 * File        : main.c
 * Description : Entry point of the Mini RTOS.
 ******************************************************************************/

#include "kernel.h"
#include "task.h"
#include "app_task.h"

int main(void)
{
    /* Initialize the RTOS kernel */
    Kernel_Init();

    /**********************************************************************
     * Create Application Tasks
     **********************************************************************/

    /*
     * Low Priority Tasks
     */
    Task_Create(LED_Task, PRIORITY_LOW);
    Task_Create(Display_Task, PRIORITY_LOW);

    /*
     * Medium Priority Task
     */
    Task_Create(Sensor_Task, PRIORITY_MEDIUM);

    /*
     * High Priority Tasks
     */
    Task_Create(UART_Task1, PRIORITY_HIGH);
    Task_Create(UART_Task2, PRIORITY_HIGH);

    /* Idle Task (Lowest Priority) */
    Task_Create(Idle_Task, PRIORITY_IDLE);

    /* Start the scheduler */
    Kernel_Start();

    return 0;
}
/******************************************************************************
 * File        : app_task.c
 * Description : Application task implementations.
 ******************************************************************************/

#include "app_task.h"
#include "delay.h"
#include <stdio.h>

/******************************************************************************
 * LED Task (Low Priority)
 ******************************************************************************/

void LED_Task(void)
{
    printf("LED Task Executing...\n");

    /* Blink LED every 5 ticks */
    Task_Delay(5);
}

/******************************************************************************
 * Display Task (Low Priority)
 ******************************************************************************/

void Display_Task(void)
{
    printf("Display Task Executing...\n");

    /* Refresh display every 4 ticks */
    Task_Delay(4);
}

/******************************************************************************
 * Sensor Task (Medium Priority)
 ******************************************************************************/

void Sensor_Task(void)
{
    printf("Sensor Task Executing...\n");

    /* Read sensor every 3 ticks */
    Task_Delay(3);
}

/******************************************************************************
 * UART Task 1 (High Priority)
 ******************************************************************************/

void UART_Task1(void)
{
    printf("UART Task 1 Executing...\n");

    /* Simulate UART processing */
    Task_Delay(6);
}

/******************************************************************************
 * UART Task 2 (High Priority)
 ******************************************************************************/

void UART_Task2(void)
{
    printf("UART Task 2 Executing...\n");

    /* Simulate UART transmission */
    Task_Delay(6);
}
/******************************************************************************
 * Function : Idle_Task
 ******************************************************************************/

void Idle_Task(void)
{
    printf("Idle Task Running...\n");

    Task_Delay(1);
}
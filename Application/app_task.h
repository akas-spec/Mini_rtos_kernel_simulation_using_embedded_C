/******************************************************************************
 * File        : app_task.h
 * Description : Application task declarations.
 ******************************************************************************/

#ifndef APP_TASK_H
#define APP_TASK_H

/******************************************************************************
 * Application Task Prototypes
 ******************************************************************************/

/*
 * Low Priority Tasks
 */
void LED_Task(void);
void Display_Task(void);

/*
 * Medium Priority Task
 */
void Sensor_Task(void);

/*
 * High Priority Tasks
 */
void UART_Task1(void);
void UART_Task2(void);

/* Idle Task */
void Idle_Task(void);

#endif
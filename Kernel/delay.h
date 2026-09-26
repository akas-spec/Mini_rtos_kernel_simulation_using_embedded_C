/******************************************************************************
 * File        : delay.h
 * Description : Delay management APIs for the Mini RTOS.
 ******************************************************************************/

#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

/******************************************************************************
 * Public APIs
 ******************************************************************************/

/*
 * Delays the currently running task for the specified number of ticks.
 */
void Task_Delay(uint32_t ticks);

/*
 * Updates the delay counter of all blocked tasks.
 * This function is called periodically by the scheduler.
 */
void Delay_Update(void);

#endif
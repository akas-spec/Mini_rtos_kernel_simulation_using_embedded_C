/******************************************************************************
 * File        : tick.h
 * Description : System Tick management APIs for the Mini RTOS.
 *
 * The System Tick acts as the RTOS clock.
 * Every tick represents one unit of RTOS time.
 *
 * In a real embedded system, a hardware timer interrupt would generate
 * these ticks periodically (for example, every 1 millisecond).
 *
 * In this project, we simulate the tick in software.
 ******************************************************************************/

#ifndef TICK_H
#define TICK_H

#include <stdint.h>

/******************************************************************************
 * Public APIs
 ******************************************************************************/

/*
 * Initializes the System Tick module.
 * This should be called once during kernel initialization.
 */
void Tick_Init(void);

/*
 * Increments the system tick count.
 * This function is called once every scheduler iteration.
 */
void Tick_Increment(void);

/*
 * Returns the current system tick count.
 */
uint32_t Tick_GetCount(void);

#endif
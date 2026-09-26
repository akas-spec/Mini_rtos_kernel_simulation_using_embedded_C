/******************************************************************************
 * File        : tick.c
 * Description : Implements the System Tick functionality for the Mini RTOS.
 *
 * The System Tick acts as the internal clock of the RTOS.
 * Every scheduler cycle increments the tick count.
 *
 * Later in the project, this software tick can be replaced with
 * a hardware timer interrupt without changing the rest of the RTOS.
 ******************************************************************************/

#include "tick.h"

/******************************************************************************
 * Tick Module Internal Variables
 ******************************************************************************/

/*
 * Stores the current system tick count.
 *
 * This variable is static because it should only be accessible
 * within this source file.
 */
static uint32_t systemTick = 0;

/******************************************************************************
 * Function : Tick_Init
 ******************************************************************************/

void Tick_Init(void)
{
    /* Start counting from zero */
    systemTick = 0;
}

/******************************************************************************
 * Function : Tick_Increment
 ******************************************************************************/

void Tick_Increment(void)
{
    /* Advance the RTOS clock by one tick */
    systemTick++;
}

/******************************************************************************
 * Function : Tick_GetCount
 ******************************************************************************/

uint32_t Tick_GetCount(void)
{
    /* Return the current tick count */
    return systemTick;
}
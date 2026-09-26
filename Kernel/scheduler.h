#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>      // Standard integer types

/******************************************************************************
 * Scheduler APIs
 ******************************************************************************/

// Initializes scheduler variables.
void Scheduler_Init(void);

// Starts the scheduler.
// This function never returns.
void Scheduler_Run(void);

#endif
/******************************************************************************
 * File        : kernel.h
 * Description : Public APIs for the Mini RTOS Kernel.
 ******************************************************************************/

#ifndef KERNEL_H
#define KERNEL_H

/******************************************************************************
 * Kernel APIs
 ******************************************************************************/

// Initializes the Mini RTOS Kernel.
void Kernel_Init(void);

// Starts the scheduler.
// This function never returns.
void Kernel_Start(void);

#endif
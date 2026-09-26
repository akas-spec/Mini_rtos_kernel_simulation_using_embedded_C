/******************************************************************************
 * File        : ready_queue.h
 * Description : Ready Queue Management for the Mini RTOS.
 *
 * This module maintains one Ready Queue for each priority level.
 * The scheduler interacts with this module to obtain the next READY task
 * without directly manipulating the queue internals.
 ******************************************************************************/

#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include "task.h"
#include <stdint.h>

/******************************************************************************
 * Configuration Macros
 ******************************************************************************/

/******************************************************************************
 * Number of Ready Queues
 *
 * One queue per priority level:
 * Priority 0 -> Idle
 * Priority 1 -> Low
 * Priority 2 -> Medium
 * Priority 3 -> High
 ******************************************************************************/

#define MAX_PRIORITIES 4

/******************************************************************************
 * Ready Queue Structure
 *
 * Each priority level owns one queue.
 *
 * Example:
 *
 * Priority 3 Queue
 *
 * Head --> UART1 --> UART2 --> NULL
 * Tail ----------------------^
 ******************************************************************************/

typedef struct
{
    /* Pointer to the first READY task */
    TCB *head;

    /* Pointer to the last READY task */
    TCB *tail;

} ReadyQueue;

/******************************************************************************
 * Public APIs
 ******************************************************************************/

/*
 * Initializes all Ready Queues.
 */
void ReadyQueue_Init(void);

/*
 * Adds a READY task to the end of its priority queue.
 *
 * Parameters:
 *      task - Pointer to the Task Control Block.
 */
void ReadyQueue_Enqueue(TCB *task);

/*
 * Removes a task from its priority queue.
 *
 * Parameters:
 *      task - Pointer to the Task Control Block.
 */
void ReadyQueue_Dequeue(TCB *task);

/*
 * Returns the highest-priority READY task.
 *
 * The task is NOT removed from the queue.
 *
 * Returns:
 *      Pointer to the selected task.
 *      NULL if no READY task exists.
 */
TCB* ReadyQueue_GetNextTask(void);

/*
 * Rotates a priority queue.
 *
 * The task at the head of the queue is moved to the tail.
 * Used to implement Round Robin scheduling.
 *
 * Parameters:
 *      priority - Priority queue to rotate.
 */
void ReadyQueue_Rotate(uint8_t priority);

/*
 * Checks whether a priority queue is empty.
 *
 * Parameters:
 *      priority - Queue to check.
 *
 * Returns:
 *      1 -> Queue is empty
 *      0 -> Queue contains at least one task
 */
uint8_t ReadyQueue_IsEmpty(uint8_t priority);

/*
 * Returns a pointer to the Ready Queue corresponding
 * to the given priority.
 *
 * Mainly intended for debugging and future extensions.
 */
ReadyQueue* ReadyQueue_GetQueue(uint8_t priority);

#endif
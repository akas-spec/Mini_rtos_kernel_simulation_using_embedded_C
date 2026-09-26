/******************************************************************************
 * File        : task.h
 * Description : Task Management Module for the Mini RTOS.
 ******************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <stdint.h>

/******************************************************************************
 * Configuration Macros
 ******************************************************************************/

/* Maximum number of tasks that can be created */
#define MAX_TASKS      10

/******************************************************************************
 * Task Priority Definitions
 *
 * Higher value means higher priority.
 ******************************************************************************/

#define PRIORITY_IDLE      0
#define PRIORITY_LOW       1
#define PRIORITY_MEDIUM    2
#define PRIORITY_HIGH      3

/******************************************************************************
 * Scheduler Configuration
 ******************************************************************************/

/* Number of scheduler iterations allocated to each task */
#define DEFAULT_TIME_SLICE    2

/******************************************************************************
 * Task State Definitions
 ******************************************************************************/

typedef enum
{
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED

} TaskState;

/******************************************************************************
 * Task Creation Status
 ******************************************************************************/

typedef enum
{
    TASK_OK,
    TASK_ERROR_FULL

} TaskStatus;

/******************************************************************************
 * Task Function Pointer
 ******************************************************************************/

typedef void (*TaskFunction_t)(void);

/******************************************************************************
 * Task Control Block (TCB)
 ******************************************************************************/

typedef struct TCB
{
    /* Unique Task ID */
    uint8_t taskID;

    /* Pointer to the task function */
    TaskFunction_t taskFunction;

    /* Current state of the task */
    TaskState state;

    /* Delay counter (used when task is blocked) */
    uint32_t delayTicks;

    /*------------------------------------------------------------
     * Task Priority
     *
     * Higher value = Higher priority
     *-----------------------------------------------------------*/
    uint8_t priority;

    /*------------------------------------------------------------
     * Remaining scheduler time slice.
     *
     * This value is decremented by the scheduler.
     * When it reaches zero, the scheduler rotates the task
     * within its priority queue and reloads this value.
     *-----------------------------------------------------------*/
    uint8_t timeSlice;

    /* Pointer used by the Ready Queue linked list */
    struct TCB *next;

} TCB;

/******************************************************************************
 * Public APIs
 ******************************************************************************/

/*
 * Creates a new task.
 *
 * Parameters:
 *  taskFunction - Pointer to the task entry function.
 *  priority     - Priority assigned to the task.
 *
 * Returns:
 *  TASK_OK          -> Task created successfully.
 *  TASK_ERROR_FULL  -> Task table is full.
 */
TaskStatus Task_Create(TaskFunction_t taskFunction,
                       uint8_t priority);

/*
 * Returns the total number of tasks currently created.
 */
uint8_t Task_GetCount(void);

/*
 * Returns a pointer to the Task Control Block (TCB)
 * corresponding to the given index.
 */
TCB* Task_GetTask(uint8_t index);

#endif
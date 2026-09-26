/******************************************************************************
 * File        : task.c
 * Description : Implements task management functions.
 ******************************************************************************/

#include "task.h"
#include <stddef.h>
#include "ready_queue.h"

/******************************************************************************
 * Task Table
 *
 * Stores all Task Control Blocks (TCBs).
 ******************************************************************************/

static TCB taskTable[MAX_TASKS];

/* Number of tasks currently created */
static uint8_t taskCount = 0;

/******************************************************************************
 * Function : Task_Create
 ******************************************************************************/

TaskStatus Task_Create(TaskFunction_t taskFunction,
                       uint8_t priority)
{
    /*------------------------------------------------------------
     * Check whether the task table is full.
     *-----------------------------------------------------------*/
    if(taskCount >= MAX_TASKS)
    {
        return TASK_ERROR_FULL;
    }

    /*------------------------------------------------------------
     * Initialize the Task Control Block.
     *-----------------------------------------------------------*/
    taskTable[taskCount].taskID = taskCount;

    taskTable[taskCount].taskFunction = taskFunction;

    taskTable[taskCount].state = TASK_READY;

    taskTable[taskCount].delayTicks = 0;

    /*------------------------------------------------------------
     * Store the task priority.
     *-----------------------------------------------------------*/
    taskTable[taskCount].priority = priority;

    /*------------------------------------------------------------
     * Initialize the scheduler time slice.
     * Every newly created task starts with a full time quantum.
     *-----------------------------------------------------------*/
    taskTable[taskCount].timeSlice = DEFAULT_TIME_SLICE;

    /*------------------------------------------------------------
     * Initialize Ready Queue link.
     *-----------------------------------------------------------*/
    taskTable[taskCount].next = NULL;

    /*------------------------------------------------------------
     * Since every newly created task starts in the READY state,
     * insert it into its corresponding Ready Queue.
     *-----------------------------------------------------------*/
    ReadyQueue_Enqueue(&taskTable[taskCount]);

    /*------------------------------------------------------------
     * One more task has been created.
     *-----------------------------------------------------------*/
    taskCount++;

    return TASK_OK;
}

/******************************************************************************
 * Function : Task_GetCount
 ******************************************************************************/

uint8_t Task_GetCount(void)
{
    return taskCount;
}

/******************************************************************************
 * Function : Task_GetTask
 ******************************************************************************/

TCB* Task_GetTask(uint8_t index)
{
    if(index >= taskCount)
    {
        return NULL;
    }

    return &taskTable[index];
}
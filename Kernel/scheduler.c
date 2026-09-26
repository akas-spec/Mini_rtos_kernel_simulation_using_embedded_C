/******************************************************************************
 * File        : scheduler.c
 * Description : Implements the Priority-Based Round Robin Scheduler.
 ******************************************************************************/

#include "scheduler.h"
#include "task.h"
#include "tick.h"
#include "delay.h"
#include "ready_queue.h"

#include <stddef.h>

/******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

/* Updates the scheduler every system tick. */
static void Scheduler_Tick(void);

/* Returns the highest-priority READY task. */
static TCB* Scheduler_SelectTask(void);

/* Executes the selected task. */
static void Scheduler_RunTask(TCB *task);

/* Performs post execution processing. */
static void Scheduler_PostProcess(TCB *task);

/******************************************************************************
 * Function : Scheduler_Init
 ******************************************************************************/

void Scheduler_Init(void)
{
    /*------------------------------------------------------------
     * Nothing to initialize for now.
     *-----------------------------------------------------------*/
}

/******************************************************************************
 * Function : Scheduler_Run
 ******************************************************************************/

void Scheduler_Run(void)
{
    TCB *currentTask;

    while(1)
    {
        /* Update scheduler state */
        Scheduler_Tick();

        /* Select next task */
        currentTask = Scheduler_SelectTask();

        /* No READY task available */
        if(currentTask == NULL)
        {
            continue;
        }

        /* Execute selected task */
        Scheduler_RunTask(currentTask);

        /* Handle task after execution */
        Scheduler_PostProcess(currentTask);
    }
}

/******************************************************************************
 * Function : Scheduler_Tick
 ******************************************************************************/

static void Scheduler_Tick(void)
{
    /*--------------------------------------------------------
     * Update the system tick.
     *-------------------------------------------------------*/
    Tick_Increment();

    /*--------------------------------------------------------
     * Update delayed tasks.
     *-------------------------------------------------------*/
    Delay_Update();
}

/******************************************************************************
 * Function : Scheduler_SelectTask
 ******************************************************************************/

static TCB* Scheduler_SelectTask(void)
{
    /*--------------------------------------------------------
     * Return the highest-priority READY task.
     *-------------------------------------------------------*/
    return ReadyQueue_GetNextTask();
}

/******************************************************************************
 * Function : Scheduler_RunTask
 ******************************************************************************/

static void Scheduler_RunTask(TCB *task)
{
    /*--------------------------------------------------------
     * Mark task as RUNNING.
     *-------------------------------------------------------*/
    task->state = TASK_RUNNING;

    /*--------------------------------------------------------
     * Execute task.
     *-------------------------------------------------------*/
    task->taskFunction();
}

/******************************************************************************
 * Function : Scheduler_PostProcess
 ******************************************************************************/

static void Scheduler_PostProcess(TCB *task)
{
    /*--------------------------------------------------------
     * If the task did not block itself,
     * move it back to READY and rotate the queue.
     *-------------------------------------------------------*/
    if(task->state == TASK_RUNNING)
    {
        task->state = TASK_READY;

        ReadyQueue_Rotate(task->priority);
    }
}
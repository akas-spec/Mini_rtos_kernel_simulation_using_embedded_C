/******************************************************************************
 * File        : delay.c
 * Description : Implements task delay functionality.
 ******************************************************************************/

#include "delay.h"
#include "task.h"
#include "ready_queue.h"

#include <stddef.h>

/******************************************************************************
 * Function : Task_Delay
 ******************************************************************************/

void Task_Delay(uint32_t ticks)
{
    uint8_t i;

    /*------------------------------------------------------------
     * Search for the currently running task.
     *-----------------------------------------------------------*/
    for(i = 0; i < Task_GetCount(); i++)
    {
        TCB *task = Task_GetTask(i);

        if(task == NULL)
        {
            continue;
        }

        if(task->state == TASK_RUNNING)
        {
            /*----------------------------------------------------
             * Store the requested delay.
             *---------------------------------------------------*/
            task->delayTicks = ticks;

            /*----------------------------------------------------
             * Remove the task from the Ready Queue since it is
             * no longer eligible for scheduling.
             *---------------------------------------------------*/
            ReadyQueue_Dequeue(task);

            /*----------------------------------------------------
             * Move the task to the BLOCKED state.
             *---------------------------------------------------*/
            task->state = TASK_BLOCKED;

            break;
        }
    }
}

/******************************************************************************
 * Function : Delay_Update
 ******************************************************************************/

void Delay_Update(void)
{
    uint8_t i;

    /*------------------------------------------------------------
     * Check every task in the Task Table.
     *-----------------------------------------------------------*/
    for(i = 0; i < Task_GetCount(); i++)
    {
        TCB *task = Task_GetTask(i);

        if(task == NULL)
        {
            continue;
        }

        /*--------------------------------------------------------
         * Process only BLOCKED tasks.
         *-------------------------------------------------------*/
        if(task->state == TASK_BLOCKED)
        {
            if(task->delayTicks > 0)
            {
                task->delayTicks--;
            }

            /*----------------------------------------------------
             * Delay expired.
             *---------------------------------------------------*/
            if(task->delayTicks == 0)
            {
                task->state = TASK_READY;

                /*------------------------------------------------
                 * Insert the task back into its Ready Queue.
                 *-----------------------------------------------*/
                ReadyQueue_Enqueue(task);
            }
        }
    }
}
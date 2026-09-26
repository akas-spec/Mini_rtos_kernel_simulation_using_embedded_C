/******************************************************************************
 * File        : ready_queue.c
 * Description : Implements Ready Queue Management.
 ******************************************************************************/

#include "ready_queue.h"
#include<stddef.h>
/******************************************************************************
 * Ready Queue Table
 *
 * One Ready Queue is maintained for each priority.
 *
 * Index Mapping:
 *      Index 0 -> Priority 1 (LOW)
 *      Index 1 -> Priority 2 (MEDIUM)
 *      Index 2 -> Priority 3 (HIGH)
 ******************************************************************************/

static ReadyQueue readyQueues[MAX_PRIORITIES];

/******************************************************************************
 * Function : ReadyQueue_Init
 ******************************************************************************/

void ReadyQueue_Init(void)
{
    uint8_t i;

    for(i = 0; i < MAX_PRIORITIES; i++)
    {
        readyQueues[i].head = NULL;
        readyQueues[i].tail = NULL;
    }
}

/******************************************************************************
 * Function : ReadyQueue_GetQueue
 ******************************************************************************/

/******************************************************************************
 * Function : ReadyQueue_GetQueue
 ******************************************************************************/

ReadyQueue* ReadyQueue_GetQueue(uint8_t priority)
{
    if(priority >= MAX_PRIORITIES)
    {
        return NULL;
    }

    return &readyQueues[priority];
}
/******************************************************************************
 * Function : ReadyQueue_IsEmpty
 ******************************************************************************/

uint8_t ReadyQueue_IsEmpty(uint8_t priority)
{
    ReadyQueue *queue = ReadyQueue_GetQueue(priority);

    if(queue == NULL)
    {
        return 1;
    }

    return (queue->head == NULL);
}

/******************************************************************************
 * Function : ReadyQueue_Enqueue
 ******************************************************************************/

void ReadyQueue_Enqueue(TCB *task)
{
    ReadyQueue *queue;

    if(task == NULL)
    {
        return;
    }

    queue = ReadyQueue_GetQueue(task->priority);

    if(queue == NULL)
    {
        return;
    }

    /* New task will become the last task */
    task->next = NULL;

    /* Queue is empty */
    if(queue->head == NULL)
    {
        queue->head = task;
        queue->tail = task;
    }
    else
    {
        queue->tail->next = task;
        queue->tail = task;
    }
}

/******************************************************************************
 * Function : ReadyQueue_Dequeue
 ******************************************************************************/

void ReadyQueue_Dequeue(TCB *task)
{
    ReadyQueue *queue;
    TCB *current;
    TCB *previous;

    if(task == NULL)
    {
        return;
    }

    queue = ReadyQueue_GetQueue(task->priority);

    if(queue == NULL)
    {
        return;
    }

    current = queue->head;
    previous = NULL;

    while(current != NULL)
    {
        if(current == task)
        {
            /* Removing the first node */
            if(previous == NULL)
            {
                queue->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            /* Removing the last node */
            if(current == queue->tail)
            {
                queue->tail = previous;
            }

            current->next = NULL;
            return;
        }

        previous = current;
        current = current->next;
    }
}

/******************************************************************************
 * Function : ReadyQueue_GetNextTask
 ******************************************************************************/

TCB* ReadyQueue_GetNextTask(void)
{
    int8_t priority;

    /* Search from HIGH priority to LOW priority */
    for(priority = PRIORITY_HIGH; priority >= PRIORITY_LOW; priority--)
    {
        if(!ReadyQueue_IsEmpty(priority))
        {
            return readyQueues[priority - 1].head;
        }
    }

    return NULL;
}

/******************************************************************************
 * Function : ReadyQueue_Rotate
 ******************************************************************************/

void ReadyQueue_Rotate(uint8_t priority)
{
    ReadyQueue *queue;
    TCB *first;

    queue = ReadyQueue_GetQueue(priority);

    if(queue == NULL)
    {
        return;
    }

    /* Zero or one task -> nothing to rotate */
    if(queue->head == NULL || queue->head == queue->tail)
    {
        return;
    }

    first = queue->head;

    queue->head = first->next;

    queue->tail->next = first;

    queue->tail = first;

    first->next = NULL;
}
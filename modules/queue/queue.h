/**
 * \file queue.h
 * \brief 
 * \note 
 * \copyright Impact Clean Power Technology 2016
 * \version Template ICPT-H-Eclipse-Template-v1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define QUEUE_MIN_SIZE 5

typedef enum
{
    QERR_OK = 0,
    QERR_FULL = 1,
    QERR_EMPTY = 2,
    QERR_MEM = 3
}qerr_t;

typedef struct _QueueRecord
{
    uint32_t Capacity;
    uint32_t Front;
    uint32_t Rear;
    uint32_t Size;
    void *ElementsArray;
    size_t Element_Size;
} QueueRecord_t;

uint32_t queue_isfull(QueueRecord_t* Q);
uint32_t queue_isempty(QueueRecord_t* Q);
QueueRecord_t* queue_init(int MaxElements, size_t ElementSize);
void queue_flush(QueueRecord_t* Q);
qerr_t queue_dispose(QueueRecord_t* Q);
qerr_t queue_enqueue(QueueRecord_t* Q,void* X);
void* queue_front(QueueRecord_t* Q);
qerr_t queue_dequeue(QueueRecord_t* Q);
qerr_t queue_front_and_dequeue(QueueRecord_t* Q, void* X);

#endif /* QUEUE_H_ */

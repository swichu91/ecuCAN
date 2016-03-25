#include "queue.h"
#include <stdint.h>
#include <string.h>

uint32_t queue_isempty(QueueRecord_t* Q);
uint32_t queue_isfull(QueueRecord_t* Q);
QueueRecord_t* queue_init(int MaxElements, size_t ElementSize);
void queue_flush(QueueRecord_t* Q);
qerr_t queue_dispose(QueueRecord_t* Q);
qerr_t queue_enqueue(QueueRecord_t* Q,void* X);
void* queue_front(QueueRecord_t* Q);
qerr_t queue_dequeue(QueueRecord_t* Q);
qerr_t queue_front_and_dequeue(QueueRecord_t* Q, void* X);

uint32_t queue_isempty(QueueRecord_t* Q)
{
    return Q->Size == 0;
}

uint32_t queue_isfull(QueueRecord_t* Q)
{
    return Q->Size == Q->Capacity;
}

QueueRecord_t* queue_init(int MaxElements, size_t ElementSize)
{
    QueueRecord_t* Q;

    if (MaxElements < QUEUE_MIN_SIZE)
    {
        //(void)Error("CreateQueue Error: Queue size is too small.");
    }

    Q = malloc(sizeof(QueueRecord_t));
    if (Q == NULL)
    {
        //(void)FatalError("CreateQueue Error: Unable to allocate more memory.");
    }

    Q->Element_Size = ElementSize;
    Q->ElementsArray = malloc(Q->Element_Size * MaxElements);
    if (Q->ElementsArray == NULL)
    {
        // (void)FatalError("CreateQueue Error: Unable to allocate more memory.");
    }

    Q->Capacity = MaxElements;
    queue_flush(Q);

    return Q;
}

void queue_flush(QueueRecord_t* Q)
{

    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;

}

qerr_t queue_dispose(QueueRecord_t* Q)
{
    if (Q != NULL)
    {
        free(Q->ElementsArray);
        free(Q);
        return QERR_OK;
    }
    else
    {
        return QERR_MEM;
    }
}

static int queue_succ(QueueRecord_t* Q,int Value)
{
    if (Value == Q->Capacity)
    {
        Value = 0;
    }
    return Value;
}

qerr_t queue_enqueue(QueueRecord_t* Q,void* X)
{

    if (queue_isfull(Q))
    {
        return QERR_FULL;
    }
    else
    {
        Q->Size++;
        Q->Rear = queue_succ(Q,Q->Rear);

        (void) memcpy(( Q->ElementsArray + ( Q->Rear * Q->Element_Size ) ), X, Q->Element_Size);
        Q->Rear++;

        return QERR_OK;
    }

}

void* queue_front(QueueRecord_t* Q)
{

    if (!queue_isempty(Q))
    {
        return ( Q->ElementsArray + ( Q->Rear * Q->Element_Size ) );
    }
    else
    {
        return NULL;
    }

}

qerr_t queue_dequeue(QueueRecord_t* Q)
{

    if (queue_isempty(Q))
    {
        return QERR_EMPTY;
    }
    else
    {
        Q->Size--;
        Q->Front = queue_succ(Q,Q->Front);
        return QERR_OK;
    }

}

qerr_t queue_front_and_dequeue(QueueRecord_t* Q, void* X)
{

    if (queue_isempty(Q))
    {
        X = NULL;
        return QERR_EMPTY;
    }
    else
    {
        Q->Size--;
        /* X = &(Q->Array[Q->Front]); */
        (void) memcpy(X, ( Q->ElementsArray + ( (Q->Front-1) * Q->Element_Size ) ), Q->Element_Size);
        Q->Front = queue_succ(Q,Q->Front);
        Q->Front++;

        return QERR_OK;
    }

}


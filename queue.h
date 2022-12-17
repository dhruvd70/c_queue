/*
* @Name :       queue.h
* @author:      Dhruv Dohare(dhruv.dohare04@gmail.com)
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define SUCCESS      0
#define FAILURE     -1

typedef struct node_t
{
    void *pData;
    struct node_t *pNext;
}node_t;

typedef struct QueueHandle_t
{
    node_t *head;
    node_t *tail;
    bool isStatic;
    uint16_t Item_size;
    int16_t MaxQ_Length;
    uint16_t CurrentQ_Length;
}QueueHandle_t;


/*
*
*/
#define CreateQueue_Generic(QueueHandle, Element_Size)\
    CreateQueue((QueueHandle), (Element_Size), 0, false)

/*
*
*/
#define CreateQueue_Static(QueueHandle, Element_Size, Queue_Length)\
    CreateQueue((QueueHandle), (Element_Size), (Queue_Length), true)

/*
*
*/
#define Queue_SendToFront(Queue, txBuff)\
    QueueSend((Queue), (txBuff), true)

/*
*
*/
#define Queue_Send(Queue, txBuff)\
    QueueSend((Queue), (txBuff), false)

/*
*
*/
int QueueReceive(QueueHandle_t *Queue, void *rxBuff);
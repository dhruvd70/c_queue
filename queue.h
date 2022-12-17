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
int CreateQueue_Generic(QueueHandle_t* QueueHandle, uint16_t Element_Size);

/*
*
*/
int CreateQueue_StaticLength(QueueHandle_t* QueueHandle, uint16_t Element_Size, uint16_t Queue_Length);

/*
*
*/
int QueueSend(QueueHandle_t *Queue, void *txBuff);

/*
*
*/
int QueueSendToFront(QueueHandle_t *Queue, void *txBuff);

/*
*
*/
int QueueReceive(QueueHandle_t *Queue, void *rxBuff);
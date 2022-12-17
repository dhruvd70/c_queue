/*
* @Name :       queue.c
* @author:      Dhruv Dohare(dhruv.dohare04@gmail.com)
* 
*/

#include "queue.h"

static node_t *Create_Node(QueueHandle_t *Queue, void *data)
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->pData = (void *)malloc(sizeof(Queue->Item_size));
    memcpy(node->pData, data,sizeof(Queue->Item_size));
    node->pNext = NULL;
    return node;
}

int CreateQueue_Generic(QueueHandle_t* QueueHandle, uint16_t Element_Size)
{
    QueueHandle_t* Queue = (QueueHandle_t *)malloc(sizeof(QueueHandle_t));
    if(Queue == NULL) {
        printf("Queue Creation Failed\n");
        return FAILURE;
    }
    QueueHandle->isStatic = false;
    QueueHandle->CurrentQ_Length = 0;
    QueueHandle->MaxQ_Length = -1;
    QueueHandle->Item_size = Element_Size;
    QueueHandle->head = NULL;
    QueueHandle->tail = NULL;
    
    return SUCCESS;
}

int CreateQueue_StaticLength(QueueHandle_t* QueueHandle, uint16_t Element_Size, uint16_t Queue_Length)
{
    QueueHandle_t* Queue = (QueueHandle_t *)malloc(sizeof(QueueHandle_t));
    if(Queue == NULL) {
        printf("Queue Creation Failed\n");
        return FAILURE;
    }
    QueueHandle->isStatic = false;
    QueueHandle->CurrentQ_Length = 0;
    QueueHandle->MaxQ_Length = Queue_Length;
    QueueHandle->Item_size = Element_Size;
    QueueHandle->head = NULL;
    QueueHandle->tail = NULL;
    
    return SUCCESS;
}

int QueueSend(QueueHandle_t *Queue, void *txBuff)
{
    if(txBuff == NULL) {
        goto error;
    }

    if(Queue->isStatic) {
        if(Queue->CurrentQ_Length = Queue->MaxQ_Length) {
            printf("Q-Drop, Queue is Full\n");
            goto error;
        }
    }

    node_t *newNode = Create_Node(Queue, txBuff);
    if(newNode == NULL) {
        goto error;
    }

    if(Queue->CurrentQ_Length == 0) {
        if(Queue->head == NULL && Queue->tail == NULL) {
            Queue->head = newNode;
            Queue->tail = newNode;
            Queue->CurrentQ_Length++; 
        }
        else {
            goto error;
        }
    }
    else {
        if(Queue->head != NULL && Queue->tail != NULL) {
            Queue->tail->pNext = newNode;
            Queue->tail = Queue->tail->pNext;
            Queue->CurrentQ_Length++;
        }
        else {
            goto error;
        }
    }
    return SUCCESS;
error:
    return FAILURE;
}

int QueueSendToFront(QueueHandle_t *Queue, void *txBuff)
{
    if(txBuff == NULL) {
        goto error;
    }

    if(Queue->isStatic) {
        if(Queue->CurrentQ_Length = Queue->MaxQ_Length) {
            printf("Q-Drop, Queue is Full\n");
            goto error;
        }
    }

    node_t *newNode = Create_Node(Queue, txBuff);
    if(newNode == NULL) {
        goto error;
    }

    if(Queue->CurrentQ_Length == 0) {
        if(Queue->head == NULL && Queue->tail == NULL) {
            Queue->head = newNode;
            Queue->tail = newNode;
            Queue->CurrentQ_Length++; 
        }
        else {
            goto error;
        }
    }
    else {
        if(Queue->head != NULL && Queue->tail != NULL) {
            newNode->pNext = Queue->head;
            Queue->head = newNode;
            Queue->CurrentQ_Length++;
        }
        else {
            goto error;
        }
    }
    return SUCCESS;
error:
    return FAILURE;
}

int QueueReceive(QueueHandle_t *Queue, void *rxBuff) 
{
    if((rxBuff) == NULL || Queue->CurrentQ_Length == 0) {
        goto error;
    }

    node_t *node = Queue->head;
    memcpy(rxBuff, Queue->head->pData, sizeof(Queue->Item_size));
    free(Queue->head->pData);
    if(Queue->head->pNext) {
        Queue->head = Queue->head->pNext;
    }
    else {
        Queue->tail = NULL;
        Queue->head = NULL;
    }
    free(node);
    Queue->CurrentQ_Length--;
    return SUCCESS;
error:
    return FAILURE;
}

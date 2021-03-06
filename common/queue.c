//
// Created by 厉宇桐 on 2020/11/19.
//
// Data structure: queue

#include "queue.h"

lac_queue_t *queue_create() {
    /* Create a queue dynamically, the pointer to the queue will be returned
     * This function will call malloc, must be careful with mem leak*/

    lac_queue_t *pQueue;
    pQueue = (lac_queue_t *) malloc(sizeof(lac_queue_t));
    if (NULL == pQueue) return NULL;
    pQueue->pFront = NULL;
    pQueue->pRear = NULL;

    pQueue->iLength = 0;
    return pQueue;
}

void queue_init(lac_queue_t *pQueue) {
    /* Initiate the queue that is defined outside of function */

    pQueue->pFront = NULL;
    pQueue->pRear = NULL;

    pQueue->iLength = 0;
}

int queue_is_empty(lac_queue_t *pQueue) {
    /* Tell if a queue is empty, return TRUE if it is, FALSE if not */

    if (pQueue->pFront == NULL && pQueue->pRear == NULL) return TRUE;
    else return FALSE;
}

int queue_has_node(lac_queue_t *pQueue, struct queue_node_t *pNode) {
    if (queue_is_empty(pQueue)) return FALSE;
    queue_node_t *Cursor = pQueue->pFront;
    while (Cursor != NULL) {
        if (Cursor == pNode) {
            return TRUE;
        }
        queue_next(&Cursor);
    }
    return FALSE;
}

int queue_push_front(lac_queue_t *pQueue, const void *pData, int iNumBytes) {
    /* This function enqueue pData at the rear end */

    /* Allocate memory */
    queue_node_t *pNode;
    pNode = (queue_node_t *) malloc(sizeof(queue_node_t));
    if (pNode == NULL) return FALSE;
    pNode->pData = malloc((size_t) iNumBytes);
    if (pNode->pData == NULL) return FALSE;
    memcpy(pNode->pData, pData, (size_t) iNumBytes);
    pNode->iNumBytes = iNumBytes;

    /* Join pNode in the pQueue */
    pNode->pPrev = pNode;
    if (pQueue->pFront != NULL) {
        pNode->pNext = pQueue->pFront;
    } else {
        pNode->pNext = pNode;
    }

    /* Modify the pQueue */
    if (pQueue->pFront == NULL) {
        pQueue->pFront = pNode;
    } else {
        pQueue->pFront->pPrev = pNode;
    }
    pQueue->pFront = pNode;
    if (pQueue->pRear == NULL) {
        pQueue->pRear = pNode;
    }

    pQueue->iLength += 1;
    return TRUE;
}

int queue_push_back(lac_queue_t *pQueue, void *pData, int iNumBytes) {
    /* This function enqueue pData at the rear end */

    /* Allocate memory */
    queue_node_t *pNode;
    pNode = (queue_node_t *) malloc(sizeof(queue_node_t));
    if (pNode == NULL) return FALSE;
    pNode->pData = malloc((size_t) iNumBytes);
    if (pNode->pData == NULL) return FALSE;
    memcpy(pNode->pData, pData, (size_t) iNumBytes);
    pNode->iNumBytes = iNumBytes;

    /* Join pNode in the pQueue */
    pNode->pNext = pNode;
    if (pQueue->pRear != NULL) {
        pNode->pPrev = pQueue->pRear;
    } else {
        pNode->pPrev = pNode;
    }

    /* Modify the pQueue */
    if (pQueue->pRear == NULL) {
        pQueue->pRear = pNode;
    } else {
        pQueue->pRear->pNext = pNode;
    }
    pQueue->pRear = pNode;
    if (pQueue->pFront == NULL) {
        pQueue->pFront = pNode;
    }

    pQueue->iLength += 1;
    return TRUE;
}

int queue_pop_front(lac_queue_t *pQueue, void *pData) {
    /* This function deque the data(ptr) at the front end
     * This function will free the memory of queue node automatically
     */

    if (queue_is_empty(pQueue)) {
        return FALSE;
    }

    if (pData != NULL) {
        memcpy(pData, pQueue->pFront->pData, (size_t) pQueue->pFront->iNumBytes);
    }

    queue_node_t *pNodeTmp = pQueue->pFront;
    /* Modify the pQueue */
    if (pQueue->pFront != pQueue->pRear) {
        pQueue->pFront = pQueue->pFront->pNext;
        pQueue->pFront->pPrev = pQueue->pFront;
    } else {
        pQueue->pFront = pQueue->pRear = NULL;
    }

    /* Free the node */
    free(pNodeTmp->pData);
    free(pNodeTmp);

    pQueue->iLength -= 1;
    return TRUE;
}

int queue_pop_front_no_free(lac_queue_t *pQueue, void *pData) {
    /* This function deque the data(ptr) at the front end
     * This function will not free the memory of queue node automatically
     */

    if (queue_is_empty(pQueue)) {
        return FALSE;
    }

    if (pData != NULL) {
        memcpy(pData, pQueue->pFront->pData, (size_t) pQueue->pFront->iNumBytes);
    }

    queue_node_t *pNodeTmp = pQueue->pFront;
    /* Modify the pQueue */
    if (pQueue->pFront != pQueue->pRear) {
        pQueue->pFront = pQueue->pFront->pNext;
        pQueue->pFront->pPrev = pQueue->pFront;
    } else {
        pQueue->pFront = pQueue->pRear = NULL;
    }

    /* Free the node */
    free(pNodeTmp);

    pQueue->iLength -= 1;
    return TRUE;
}

int queue_pop_back(lac_queue_t *pQueue, void *pData) {
    /* This function deque the data(ptr) at the back end
     * This function will free the memory of queue node automatically
     */
    if (queue_is_empty(pQueue)) {
        return FALSE;
    }

    if (pData != NULL) {
        memcpy(pData, pQueue->pRear->pData, (size_t) pQueue->pRear->iNumBytes);
    }

    queue_node_t *pNodeTmp = pQueue->pRear;
    /* Modify the pQueue */
    if (pQueue->pRear != pQueue->pFront) {
        pQueue->pRear = pQueue->pRear->pPrev;
        pQueue->pRear->pNext = pQueue->pRear;
    } else {
        pQueue->pRear = pQueue->pFront = NULL;
    }

    /* Free the node */
    free(pNodeTmp->pData);
    free(pNodeTmp);

    pQueue->iLength -= 1;
    return TRUE;
}

int queue_pop_back_no_free(lac_queue_t *pQueue, void *pData) {
    /* This function deque the data(ptr) at the back end
     * This function will not free the memory of queue node automatically
     */
    if (queue_is_empty(pQueue)) {
        return FALSE;
    }

    if (pData != NULL) {
        memcpy(pData, pQueue->pRear->pData, (size_t) pQueue->pRear->iNumBytes);
    }

    queue_node_t *pNodeTmp = pQueue->pRear;
    /* Modify the pQueue */
    if (pQueue->pRear != pQueue->pFront) {
        pQueue->pRear = pQueue->pRear->pPrev;
        pQueue->pRear->pNext = pQueue->pRear;
    } else {
        pQueue->pRear = pQueue->pFront = NULL;
    }

    /* Free the node */
    free(pNodeTmp);

    pQueue->iLength -= 1;
    return TRUE;
}


int queue_del(lac_queue_t *pQueue, struct queue_node_t *pNode, void *pData, bool Check) {
    /* This function removes a node from a queue */
    if (pNode == NULL) return FALSE;
    if (Check == TRUE) {
        if (!queue_has_node(pQueue, pNode)) return FALSE;
    }

    if (pNode == pQueue->pFront) {
        queue_pop_front_no_free(pQueue, pData);
        return TRUE;
    } else if (pNode == pQueue->pRear) {
        queue_pop_back_no_free(pQueue, pData);
        return TRUE;
    } else {
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        if (pData != NULL) {
            memcpy(pData, pNode->pData, (size_t) pNode->iNumBytes);
        }

        free(pNode->pData);
        free(pNode);
        return TRUE;
    }
}


int queue_del_no_free(lac_queue_t *pQueue, struct queue_node_t *pNode, void *pData, bool Check) {
    /* This function removes a node from a queue, but dont free its data, incase the data is a dynamic structure */
    if (pNode == NULL) return FALSE;
    if (Check == TRUE) {
        if (!queue_has_node(pQueue, pNode)) return FALSE;

    }

    if (pNode == pQueue->pFront) {
        queue_pop_front_no_free(pQueue, pData);
        return TRUE;
    } else if (pNode == pQueue->pRear) {
        queue_pop_back_no_free(pQueue, pData);
        return TRUE;
    } else {
        pNode->pPrev->pNext = pNode->pNext;
        pNode->pNext->pPrev = pNode->pPrev;

        if (pData != NULL) {
            memcpy(pData, pNode->pData, (size_t) pNode->iNumBytes);
        }

        free(pNode);
        return TRUE;
    }
}


void queue_destroy(lac_queue_t *pQueue) {
    /* This function destroys a to a dynamically created queue */

    while (pQueue->pFront != NULL) {
        queue_pop_front(pQueue, NULL);
    }
    free(pQueue);
}

void queue_clear(lac_queue_t *pQueue) {
    /* This function applies to a dynamically created queue or defined queue */

    while (pQueue->pFront != NULL) {
        queue_pop_front(pQueue, NULL);
    }
    pQueue->iLength = 0;
}

void queue_next(queue_node_t **ppNode) {
    /* Return the pointer of next node in the queue */
    /* This function can be used to access queue nodes 1-by-1 with out pop them */

    queue_node_t *pRet = (*ppNode)->pNext;
    if (pRet == (*ppNode)) {
        /* It is the end of the queue */
        *ppNode = NULL;
    } else {
        *ppNode = pRet;
    }
}

void queue_prev(queue_node_t **ppNode) {
    /* Return the pointer of previous node in the queue */
    /* This function can be used to access queue nodes 1-by-1 with out pop them */

    queue_node_t *pRet = (*ppNode)->pPrev;

    if (pRet == (*ppNode)) {
        /* It is the end of the queue */
        *ppNode = NULL;
    } else {
        *ppNode = pRet;
    }
}
//
// Created by Fatema Moharam
//
#include "Queue.h"
Node * new_node (Data d){
    Node * n = malloc(sizeof(Node));
    n->data = d;
    n->next = NULL;
    return n;
}

Queue* init()
{
    Queue * q = malloc(sizeof(Queue));
    q ->front = q ->rear = NULL;
    return q;
}

int isEmpty(Queue *q)
{
    return !(q->front);
    //return -1;
}

Data dequeue(Queue *q)
{
    Data d ;
    if (isEmpty(q)){
        perror("Queue is empty!");
    } else{
        d = q->front->data;
        q->front = q->front->next;
        return d;
    }
}

void enqueue(Queue *q, Data val)
{
    Node * n = new_node(val);
    if (isEmpty(q))
        q->front = q->rear = n;
    else{
        q->rear->next = n;
        q->rear = n;
    }
}

void destroy(Queue *q)
{
    while(!isEmpty(q))
        dequeue(q);
    free(q->front);
    free(q->rear);
    free(q);
}
//
// Created by Fatema Moharam on ١٧/٠٥/٢٠٢٠.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef union{
    int intdata;
}Data;

typedef struct Node
{
    Data data;
    struct Node* next;
} Node;

typedef struct
{
    Node * front;
    Node * rear;
} Queue;

Node * new_node (Data d);
Queue* init();
int isEmpty(Queue *q);
Data dequeue(Queue *q);
void enqueue(Queue *q, Data val);
void destroy(Queue *q);
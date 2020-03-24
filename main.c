#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
Node * new_node (Process p){
    Node * n = malloc(sizeof(Node));
    n->data = p;
    n->next = NULL;
    return n;
}
/*
 *
 */
typedef struct
{
    /* TODO: ADD YOUR CODE HERE */
    Node * front;
    Node * rear;
} Queue;
/*
 *
 */
Queue* init()
{
    /* TODO: ADD YOUR CODE HERE */
    Queue * q = malloc(sizeof(Queue));
    q ->front = q ->rear = NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    return !(q->front);
    //return -1;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    Process p ;
    if (isEmpty(q)){
        perror("Queue is empty!");
    } else{
        p = q->front->data;
        q->front = q->front->next;
        return p;
    }
}
/*
 *
 */
void enqueue(Queue *q, Process val)
{
    /* TODO: ADD YOUR CODE HERE */
    Node * n = new_node(val);
    if (isEmpty(q))
        q->front = q->rear = n;
    else{
        q->rear->next = n;
        q->rear = n;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    /* TODO: ADD YOUR CODE HERE */
    
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}

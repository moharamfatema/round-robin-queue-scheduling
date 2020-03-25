#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
    free(q->front->data.name);
    free(q->rear->data.name);
    free(q->front->next);
    free(q->rear->next);
    free(q->front);
    free(q->rear);
    free(q);
}
/*
 *
 */
Process *fetch_data(char *filename,int * time_slot){
    //TODO: Implement
    FILE *fp = fopen(filename,"r");
    if (!fp)
        perror("File not found.");
    else{

        /*getting time slot value*/
        char* line = malloc(LINE_MAX);
        fgets(line,LINE_MAX/ sizeof(char),fp);
        while ((line)&&(*line != '='))
            line++;
        if (*line == ' ')
            line++;
        *time_slot = atoi(line);

        /*getting processes data*/
        Process *processes = malloc(sizeof(Process)*(*time_slot));
        int i = 0;
        char *data;
        while (fgets(line,LINE_MAX/ sizeof(char),fp)){
            /*first token*/
            data = strtok(line," ");
            processes[i].name = data;
            /*continue*/
            data = strtok (NULL, " ");
            processes[i].starting_time = atoi(data);
            /*continue*/
            data = strtok (NULL, " ");
            processes[i].remaining_time = atoi(data);
            i++;
        }

        fclose(fp);
        return processes;
    }
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    /* TODO: ADD YOUR CODE HERE */
    int time_slot = 0;
    Process *processes = fetch_data(filename,&time_slot);
    

    free(processes);
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
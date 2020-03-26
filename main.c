#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
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
    while(!isEmpty(q))
        dequeue(q);
    free(q->front);
    free(q->rear);
    free(q);
}
/*
 *
 */
Queue *fetch_data(char *filename,int * time_slot,int* numofProcesses){
    //TODO: Implement
    FILE *fp = fopen(filename,"r");
    if (!fp)
        perror("File not found.");
    else{

        /*getting time slot value*/
        char* line = malloc(LINE_MAX);
        fgets(line,LINE_MAX/ sizeof(char),fp);
        while ((line)&&!isdigit(*line))
            line++;
        if (!line)
            perror("Incompatible file template.");
        else{
            *time_slot = atoi(line);

            /*getting processes data*/
            Queue *q = init();
            int i = 0;
            char *data;
            char *name[*time_slot];
            Process *currentp = malloc(sizeof(Process));
            while (fgets(line,LINE_MAX/ sizeof(char),fp)){
                /*first token*/
                data = strtok(line," ");
                currentp->name = malloc(sizeof(char)*strlen(data));
                //currentp->name = name[i];
                strcpy(currentp->name,data);
                /*continue*/
                data = strtok (NULL, " ");
                currentp->starting_time = atoi(data);
                /*continue*/
                data = strtok (NULL, " ");
                currentp->remaining_time = atoi(data);

                i++;
                data = "";
                enqueue(q,*currentp);
            }
            *numofProcesses = i;
            free(currentp);
            fclose(fp);
            return q;
        }
    }
}
/*
 *
 */
void printProcesses(Queue* processes){
    //TODO:fix
    Process p;
    int n = 0;
    while (!isEmpty(processes))
    {
        p = dequeue(processes);
        printf("%s %d %d\n",p.name,p.starting_time,p.remaining_time);
        n++;
    }
    printf("number of prcesses = %d\n",n);
}
/*
 *
 */
void sort(Queue* q, int n)
{
    Process p[n];
    Process swap;
    /*convert to array*/
    int i = 0;
    while (!isEmpty(q)) {
        p[i] = dequeue(q);
        i++;
    }
    /*bubble sort*/
    for (int j = 0 ; j < n - 1; j++)
    {
        for (int k = 0 ; k < n - j - 1; k++)
        {
            if (p[k].starting_time > p[k + 1].starting_time) /* For decreasing order use < */
            {
                swap = p[k];
                p[k] = p[k + 1];
                p[k + 1] = swap;
            }
        }
    }
    /*convert to queue*/
    for(int h = 0;h < n;h++) {
        enqueue(q,p[h]);
    }
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    /* TODO: ADD YOUR CODE HERE */
    int time_slot = 0;
    int numofProcesses = 0;
    Queue *q = fetch_data(filename,&time_slot,&numofProcesses);
    /*sort them according to starting time*/
    sort(q,numofProcesses);
    int clock = 0;
    Queue *robin = init();
    Process currentp,nextp;
    while (!isEmpty(q)) {
        nextp = q->front->data;
        while ((nextp.starting_time <= clock)){
            enqueue(robin, dequeue(q));
            if(!isEmpty(q)){
                nextp = q->front->data;
            } else
                break;
        }
        if (!isEmpty(robin)){
            currentp = dequeue(robin);
            printf("%s \t(%d-->%d)", currentp.name, clock++, clock);
            currentp.remaining_time--;
            if (currentp.remaining_time) {
                enqueue(robin, currentp);
            } else{
                printf(" %s aborts", currentp.name);
            }
            printf("\n");
        } else
            printf("idle (%d-->%d)\n",clock++,clock);

    }
    while (!isEmpty(robin)){
        currentp = dequeue(robin);
        printf("%s \t(%d-->%d)", currentp.name, clock++, clock);
        currentp.remaining_time--;
        if (currentp.remaining_time) {
            enqueue(robin, currentp);
        } else{
            printf(" %s aborts", currentp.name);
        }
        printf("\n");
    }
    while (clock < time_slot)
        printf("idle (%d-->%d)\n",clock++,clock);
    printf("Stop\n");
    destroy(q);
}

/*
 *
 */
int main()
{
    setbuf(stdout,NULL);
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
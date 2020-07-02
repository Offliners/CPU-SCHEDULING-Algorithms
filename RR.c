#define _GNU_SOURCE

#include <signal.h>
#include <sys/wait.h>
#include "library/common.h"
#include "library/merge_sort.h"
#include "library/priority.h"

#define MAX_QUEUE_SIZE (1000000 + 7)
#define TIME_QUANTUM 500

char N[MAX_PROCESS_NUM][PROCESS_NAME];
unsigned int R[MAX_PROCESS_NUM], T[MAX_PROCESS_NUM];

extern int nProcess;
extern int idProcess[MAX_PROCESS_NUM];
extern pid_t pid[MAX_PROCESS_NUM];
extern int ptr_Ready;
extern int run;

int counting_time = 0, block_flag = 0;
int queue[MAX_QUEUE_SIZE], ptr_Front = 0, ptr_Back = 0;

void push_queue(int x)
{
    queue[ptr_Back++] = x;
}

int front_queue()
{
    return queue[ptr_Front];
}

int size_queue()
{
    return ptr_Back - ptr_Front;
}

int empty_queue()
{
    return ptr_Front < ptr_Back ? 0 : 1;
}

void pop_queue()
{
    if (ptr_Front < ptr_Back)
        ptr_Front++;
}

void sig_child(int signum)
{
    static int nFinish = 0;

    wait(NULL);
    nFinish++;
    pop_queue();
    run = 0;
    block_flag = 0;
    counting_time = 0;
    if (nFinish == nProcess)
        exit(0);
}

void increase_next_process_priority()
{
    int next_Run = queue[ptr_Front + 1];
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_INIT);
}

void run_next_process()
{
    counting_time = 0;
    int next_Run = queue[ptr_Front];
    
    if (T[next_Run] <= TIME_QUANTUM)
        block_flag = 1;

    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_HIGH);	
    run = 1;						
}

void change_priority()
{
    if (!run && size_queue() >= 1)		
        run_next_process();

    if (run && size_queue() >= 2)	
        increase_next_process_priority();
}

int main (void)
{    
    READ_INPUT();
    
    for(int i = 0; i < nProcess; i++)
        idProcess[i] = i;

    sort(nProcess, idProcess, R);
    
    SIGACT_SIGCHILD();
    
    int next_Ready = idProcess[ptr_Ready];    

    for (int t = 0, i = nProcess; i > 0; t++)
    {
        change_priority();

        while(ptr_Ready < nProcess && t == R[next_Ready])
        {
            create_process(&pid[next_Ready], N[next_Ready], next_Ready, T[next_Ready]);
            push_queue(next_Ready);
            next_Ready = idProcess[ptr_Ready++];
            change_priority();
        }

        unit_time();

        counting_time++;
        if (!block_flag && run && counting_time == TIME_QUANTUM)
        { 
            int id = front_queue();
            pop_queue();
            T[id] -= TIME_QUANTUM;
            SET_PRIORITY(pid[id], SCHED_FIFO, PRIORITY_LOW);	
            push_queue(id);
            run = 0;
            change_priority();
        }
    }
}

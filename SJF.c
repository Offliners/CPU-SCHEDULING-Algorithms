#define _GNU_SOURCE

#include <signal.h>
#include <sys/wait.h>
#include "library/common.h"
#include "library/merge_sort.h"
#include "library/priority.h"
#include "library/heap.h"

char N[MAX_PROCESS_NUM][PROCESS_NAME];
unsigned int R[MAX_PROCESS_NUM], T[MAX_PROCESS_NUM];

extern int nProcess;
extern int idProcess[MAX_PROCESS_NUM];
extern pid_t pid[MAX_PROCESS_NUM];
extern int ptr_Ready;
extern int ptr_Run;
extern int run;

struct Node *heap_root = NULL;

void sig_child(int signum)
{
    static int nFinish = 0;
    wait(NULL);
    nFinish++;
    ptr_Run++;
    run = 0;
    if (nFinish == nProcess)
        exit(0);
}

void increase_next_process_priority()
{
    int next_Run = heap_root->index;
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_INIT);
}

void decrease_next_process_priority()
{
    if (!run || heap_root == NULL)
        return;

    int next_Run = heap_root->index;
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_LOW);
}

void run_next_process()
{
    int next_Run = heap_root->index;
    heap_root = pop_heap(heap_root);
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_HIGH);	
    run = 1;						
}

void change_priority()
{
    if (!run && heap_root != NULL)		
        run_next_process();

    if (run && heap_root != NULL)	
        increase_next_process_priority();
}

int main (void)
{    
    READ_INPUT();
    
    for(int i = 0; i < nProcess; ++i)
        idProcess[i] = i;

    sort(nProcess, idProcess, T);
    sort(nProcess, idProcess, R);
    
    SIGACT_SIGCHILD();
    
    int next_Ready = idProcess[ptr_Ready];    

    for (int t = 0, i = nProcess; i > 0; t++)
    {
        change_priority();

        while (ptr_Ready < nProcess && t == R[next_Ready])
        {
            decrease_next_process_priority();
            create_process(&pid[next_Ready], N[next_Ready], next_Ready, T[next_Ready]);
            heap_root = insert_heap(heap_root, T[next_Ready], next_Ready);
            next_Ready = idProcess[ptr_Ready++];
            change_priority();
        }
        
        unit_time();
    }
}

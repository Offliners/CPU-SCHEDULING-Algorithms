#define _GNU_SOURCE

#include<signal.h>
#include<sys/wait.h>
#include"library/common.h"
#include"library/merge_sort.h"
#include"library/priority.h"
#include"library/heap.h"

char N[MAX_PROCESS_NUM][PROCESS_NAME];
unsigned int R[MAX_PROCESS_NUM], T[MAX_PROCESS_NUM];

extern int nProcess;
extern int idProcess[MAX_PROCESS_NUM];
extern pid_t pid[MAX_PROCESS_NUM];
extern int ptr_Ready;
extern int run;

int nFinish = 0;
int now_time = 0;
int counting_time = 0;
struct Node *heap_root = NULL;

#define BLOCK_SIGCHILD()			                                       \
sigset_t set, oset;				                                       \
do                                                                                     \
{                   					                               \
    sigfillset(&set);			                                               \
    sigprocmask(SIG_BLOCK, &set, &oset);	                                       \
}while(0)

#define UNBLOCK_SIGCHILD() sigprocmask(SIG_SETMASK, &oset, NULL)

#define WAIT_CHILD() do                                                                \
{                                                                                      \
    BLOCK_SIGCHILD();						                       \
    while(heap_root != NULL && waitpid(pid[heap_root->index], NULL, WNOHANG) != 0)     \
    {                                                                                  \
        nFinish++;			                                               \
        heap_root = pop_heap(heap_root);			                       \
        run = 0;		      	                                               \
        if(nFinish == nProcess)                                                        \
            exit(0);                      	                                       \
    }			       	                                                       \
    UNBLOCK_SIGCHILD();			                                               \
}while(0)

void sig_child(int signum)
{
    wait(NULL);
    nFinish++;
    heap_root = pop_heap(heap_root);
    run = 0;

    if(nFinish == nProcess)
        exit(0);
}

void increase_next_process_priority()
{
    BLOCK_SIGCHILD();
    int i1 = heap_root->index;
    heap_root = pop_heap(heap_root);
    SET_PRIORITY(pid[i1], SCHED_FIFO, PRIORITY_HIGH);
    
    WAIT_CHILD();

    if(heap_root)
    {
        int i2 = heap_root->index;
        SET_PRIORITY(pid[i2], SCHED_FIFO, PRIORITY_INIT);
    }

    heap_root = insert_heap(heap_root, T[i1], i1);
    
    UNBLOCK_SIGCHILD();
}

void decrease_next_two_processes_priority()
{
    BLOCK_SIGCHILD();
    if(!run || heap_root == NULL)
        return;

    int i1 = heap_root->index;
    heap_root = pop_heap(heap_root);
    T[i1] -= counting_time;

    WAIT_CHILD();

    if(heap_root)
    {
        int i2 = heap_root->index;
        SET_PRIORITY(pid[i2], SCHED_FIFO, PRIORITY_LOW);
    }

    SET_PRIORITY(pid[i1], SCHED_FIFO, PRIORITY_LOW);
    heap_root = insert_heap(heap_root, T[i1], i1);
    counting_time = 0;

    UNBLOCK_SIGCHILD();
}

void run_next_process()
{
    BLOCK_SIGCHILD();
    int nextRun = heap_root->index;
    SET_PRIORITY(pid[nextRun], SCHED_FIFO, PRIORITY_HIGH);	
    run = 1;						
    counting_time = 0;

    UNBLOCK_SIGCHILD();
}

void change_priority()
{
    WAIT_CHILD();
    BLOCK_SIGCHILD();

    if(!run && heap_root != NULL)		
        run_next_process();

    if(run && heap_root != NULL)	
        increase_next_process_priority();
    
    UNBLOCK_SIGCHILD();
}

int main (void)
{    
    READ_INPUT();
    
    for(int i = 0; i < nProcess; i++)
        idProcess[i] = i;

    sort(nProcess, idProcess, T);
    sort(nProcess, idProcess, R);
    
    SIGACT_SIGCHILD();
    
    int next_Ready = idProcess[ptr_Ready];    

    for(int t = 0;; t++)
    {
        change_priority();

        while(ptr_Ready < nProcess && t == R[next_Ready])
        {
            decrease_next_two_processes_priority();

            create_process(&pid[next_Ready], N[next_Ready], next_Ready, T[next_Ready]);
            heap_root = insert_heap(heap_root, T[next_Ready], next_Ready);
            next_Ready = idProcess[ptr_Ready++];

            change_priority();
        }

        unit_time();

        counting_time++;
        now_time++;
        
        WAIT_CHILD();
    }
}

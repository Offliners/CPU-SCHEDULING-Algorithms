#define _GNU_SOURCE

#include<signal.h>
#include<sys/wait.h>
#include"library/common.h"
#include"library/merge_sort.h"
#include"library/priority.h"

char N[MAX_PROCESS_NUM][PROCESS_NAME];
unsigned int R[MAX_PROCESS_NUM], T[PROCESS_NAME];
extern int nProcess;
extern int idProcess[MAX_PROCESS_NUM];
extern pid_t pid[MAX_PROCESS_NUM];
extern int ptr_Ready;
extern int ptr_Run;
extern int run;

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
    int next_Run = idProcess[ptr_Run + 1];
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_INIT);
}

void run_next_process()
{
    int next_Run = idProcess[ptr_Run];			
    SET_PRIORITY(pid[next_Run], SCHED_FIFO, PRIORITY_HIGH);	
    run = 1;						
}

void change_priority() {
    if (!run && ptr_Run < ptr_Ready)		
        run_next_process();

    if (run && ptr_Run + 1 < ptr_Ready)	
        increase_next_process_priority();
}


int main(void)
{
	READ_INPUT();

	for(int i = 0; i < nProcess; i++)
		idProcess[i] = i;

	sort(nProcess, idProcess, R);

	SIGACT_SIGCHILD();

	int nextReady = idProcess[ptr_Ready];

	for(int i = nProcess, t = 0; i > 0; t++)
	{
		change_priority();

		while(ptr_Ready < nProcess && t == R[nextReady])
		{
			create_process(&pid[nextReady], N[nextReady], nextReady, T[nextReady]);
			nextReady = idProcess[ptr_Ready++];
			change_priority();
		}

		unit_time();
	}
}

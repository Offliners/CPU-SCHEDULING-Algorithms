#define _GNU_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sched.h>
#include "library/common.h"
#include "library/priority.h"

int nProcess;
int idProcess[MAX_PROCESS_NUM];
pid_t pid[MAX_PROCESS_NUM];
int ptr_Ready = 0;
int ptr_Run = 0;
int run = 0;

void unit_time()
{
    volatile unsigned long i;
    for (i = 0; i < TIME_UNIT; i++);
}

void create_process (pid_t *pid, char *N, int I, int T)
{
    if ((*pid = fork()) < 0)
        ERR_EXIT("Fork error!");

    if (*pid == 0)
    {
        char execute_time[20], id[10];
        sprintf(execute_time, "%u", T);
        sprintf(id, "%u", I);
        execl("./process", "./process", N, id, execute_time, (char *)0);
    }

    if (*pid > 0)
    {
        fflush(stderr);
        SET_PRIORITY(*pid, SCHED_FIFO, PRIORITY_LOW);
        CPU(*pid, 1);
    }
}

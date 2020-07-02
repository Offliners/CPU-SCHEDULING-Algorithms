#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "library/merge_sort.h"
#include "library/common.h"
#include "library/heap.h"

extern int nProcess;
extern int idProcess[MAX_PROCESS_NUM];

char N[MAX_PROCESS_NUM][PROCESS_NAME];
unsigned int R[MAX_PROCESS_NUM], T[MAX_PROCESS_NUM];
int first_time = -1, last_time = 0;
unsigned int start_time[MAX_PROCESS_NUM], finish_time[MAX_PROCESS_NUM];

void calc_FCFS()
{
    sort(nProcess, idProcess, R);
    for(int i = 0; i < nProcess; ++i)
    {
        int nxt = idProcess[i];
        start_time[nxt] = (last_time > R[nxt] ? last_time : R[nxt]);
        if (first_time == -1)
            first_time = start_time[nxt];
        last_time = finish_time[nxt] = start_time[nxt] + T[nxt];
        fprintf(stderr, "%s %u %u\n", N[nxt], start_time[nxt], finish_time[nxt]);
    }
}

void calc_SJF()
{
    sort(nProcess, idProcess, T);
    sort(nProcess, idProcess, R);

    struct Node *heap_root = NULL;

    int *p = idProcess;

    while(heap_root != NULL || p - idProcess < nProcess)
    {
        if(heap_root == NULL && R[*p] > last_time)
            last_time = R[*p];

        while(p - idProcess < nProcess && R[*p] <= last_time)
        {
            heap_root = insert_heap(heap_root, T[*p], *p);
            p++;
        }

        int nxt = heap_root->index;
        heap_root = pop_heap(heap_root);
        start_time[nxt] = last_time;

        if (first_time == -1)
            first_time = start_time[nxt];

        last_time = finish_time[nxt] = last_time + T[nxt];
        fprintf(stderr, "%s %u %u\n", N[nxt], start_time[nxt], finish_time[nxt]);
    }
}

void calc_RR()
{
    static const int MAX_QUEUE_SIZE = 1000000 + 7;
    static const int TIME_QUANTUM = 500;

    int queue[MAX_QUEUE_SIZE], time_left[MAX_PROCESS_NUM];
    int ptr_Front = 0, ptr_Back = 0;

    memcpy(time_left, T, sizeof(int) * nProcess);
    memset(start_time, -1, sizeof(int) * nProcess);
    sort(nProcess, idProcess, R);

    int nFinish = 0, *p = idProcess, nxt = -1;
    while(nFinish < nProcess)
    {
        if(ptr_Back == ptr_Front && nxt == -1 && R[*p] > last_time)
            last_time = R[*p];

        while(p - idProcess < nProcess && R[*p] <= last_time)
        {
            queue[ptr_Back++] = *p;
            p++;
        }

        if(nxt != -1)
            queue[ptr_Back++] = nxt;

        nxt = queue[ptr_Front++];

        if(start_time[nxt] == -1)
        {
            start_time[nxt] = last_time;
            if(first_time == -1)
                first_time = start_time[nxt];
        }

        int exec_time = TIME_QUANTUM < time_left[nxt] ? TIME_QUANTUM : time_left[nxt];
        last_time += exec_time;
        time_left[nxt] -= exec_time;

        if(time_left[nxt] == 0)
        {
            finish_time[nxt] = last_time;
            nFinish++;
            fprintf(stderr, "%s %u %u\n", N[nxt], start_time[nxt], finish_time[nxt]);
            nxt = -1;
        }
    }
}

void calc_PSJF()
{
    sort(nProcess, idProcess, T);
    sort(nProcess, idProcess, R);

    struct Node *heap_root = NULL;

    int time_left[MAX_PROCESS_NUM];
    memcpy(time_left, T, sizeof(int) * nProcess);
    memset(start_time, -1, sizeof(int) * nProcess);

    int *p = idProcess;

    while(heap_root != NULL || p - idProcess < nProcess)
    {
        if(heap_root == NULL && R[*p] > last_time)
            last_time = R[*p];

        while(p - idProcess < nProcess && R[*p] == last_time)
        {
            heap_root = insert_heap(heap_root, time_left[*p], *p);
            p++;
        }

        int nxt = heap_root->index;
        heap_root = pop_heap(heap_root);
        if(start_time[nxt] == -1)
        {
            start_time[nxt] = last_time;
            if(first_time == -1)
                first_time = start_time[nxt];
        }

        if(p - idProcess < nProcess && last_time + time_left[nxt] > R[*p])
        {
            int exec_time = R[*p] - last_time;
            time_left[nxt] -= exec_time;
            last_time += exec_time;
            heap_root = insert_heap(heap_root, time_left[nxt], nxt);
        }
        else
        {
            last_time = finish_time[nxt] = last_time + time_left[nxt];
            time_left[nxt] = 0;
            fprintf(stderr, "%s %u %u\n", N[nxt], start_time[nxt], finish_time[nxt]);
        }
    }
}

int main(int argc, char **argv)
{
    char sched_policy[SCHEDULE_NAME];

    assert(scanf("%s", sched_policy) == 1);

    const char sched_types[NUM_SCHEDULING_TYPE][SCHEDULE_NAME] = { "FIFO", "RR", "SJF", "PSJF" };
    
    for(int i = 0; i <= NUM_SCHEDULING_TYPE; i++)
    {
        if(i == NUM_SCHEDULING_TYPE)
        {
            fprintf(stderr, "Error! Can't find this scheduling algorithm.\n");
            return 1;
        }

        if(strcmp(sched_policy, sched_types[i]) == 0)
            break;
    }

    READ_INPUT();

    for (int i = 0; i < nProcess; i++)
        idProcess[i] = i;

    switch(sched_policy[0])
    {                                               
        case 'F':
            calc_FCFS();
            break;                                                               
        case 'R':                                                                
            calc_RR();
            break;                                                               
        case 'S':                                                                
            calc_SJF();
            break;                                                               
        case 'P':                                                                
            calc_PSJF();
            break;                                                               
    }                                        
    fprintf(stderr, "first time = %d\n", first_time);
    fprintf(stderr, "last time = %d\n", last_time);

    double exec_first_time = 1e100, exec_last_time = 0;
    double exec_start_time[MAX_PROCESS_NUM], exec_finish_time[MAX_PROCESS_NUM];
    char message[1000];

    FILE *pFile = fopen(argv[1], "r");
    while(fgets(message, 1000, pFile) != NULL)
    {
        if(strncmp(message, "[Project1]", 10) == 0)
        {
            strtok(message, " ");
            int id = atoi(strtok(NULL, " "));
            exec_start_time[id] = atof(strtok(NULL, " "));
            if (exec_start_time[id] < exec_first_time)
                exec_first_time = exec_start_time[id];
            exec_finish_time[id] = atof(strtok(NULL, " "));
            exec_last_time = exec_finish_time[id];
        }
    }

    fclose(pFile);

    fprintf(stderr, "exec first time = %.8f\n", exec_first_time);
    fprintf(stderr, "exec last time = %.8f\n", exec_last_time);

    double avg_unit_time = (exec_last_time - exec_first_time) / (last_time - first_time);
    fprintf(stderr, "avg unit time = %0.8f\n", avg_unit_time);
    double total_error = 0;
    for(int i = 0; i < nProcess; i++)
    {
        double start_time_error = (start_time[i] - first_time) * avg_unit_time - (exec_start_time[i] - exec_first_time);
        double finish_time_error = (finish_time[i] - first_time) * avg_unit_time - (exec_finish_time[i] - exec_first_time);
        fprintf(stderr, "error of %s: start time: %1.8f, finish time: %1.8f\n", N[i], start_time_error, finish_time_error);
        
        total_error += (start_time_error < 0 ? -start_time_error : start_time_error);
        total_error += (finish_time_error < 0 ? -finish_time_error : finish_time_error);
    }
    
    fprintf(stderr, "total error = %1.8f\n", total_error);
}

#define _GNU_SOURCE

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/syscall.h>
#include"library/common.h"

int main(int argc, char **argv) 
{    
    if (argc != 4) 
    {
        fprintf(stderr, "usage: ./this_program process_name process_idx exec_time\n");
        return 0;
    }
    
    struct timespec start_time, end_time;
    double elapsedTime;
    pid_t pid = getpid(); 
    char *name = argv[1];
    int id = atoi(argv[2]);
    int exec_time = atoi(argv[3]);

    printf("%s %d\n", name, pid);
    
    clock_gettime(CLOCK_REALTIME, &start_time);

    for (int i = 0; i < exec_time; i++)
        unit_time();

    clock_gettime(CLOCK_REALTIME, &end_time);
    elapsedTime = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
    elapsedTime += (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
    fprintf(stderr, "[CPU : %s] time : %lf\n", argv[1], elapsedTime/2);

    return 0;
}

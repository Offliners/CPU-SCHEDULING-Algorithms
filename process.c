#define _GNU_SOURCE                                                                                                                                                                                         

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/syscall.h>
#include"library/common.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "usage: ./this_program process_name process_idx exec_time\n");
        return 0;
    }

    char *name = argv[1];
    int id = atoi(argv[2]);
    int exec_time = atoi(argv[3]);

    long start_time = syscall(334);

    for (int i = 0; i < exec_time; i++)
        unit_time();

    long end_time = syscall(334);

    static const long BASE = 1000000000;
    fprintf(stderr, " P%d\t%ld.%09ld\t%ld.%09ld\n", id+1, start_time / BASE, start_time % BASE, end_time / BASE, end_time % BASE);

    return 0;
}


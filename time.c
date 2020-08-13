#define _GNU_SOURCE                                                                                                                                                                                         

#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include"library/common.h"

int main()
{
        long start_time = syscall(334);

        for (int i = 0; i < 1000; i++)
                unit_time();

        long end_time = syscall(334);

        static const long BASE = 1000000000;
        printf("Unit time : %lf\n", (double)(end_time - start_time) / BASE / 1000);

        return 0;
}

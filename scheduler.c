#define _GNU_SOURCE

#include<stdio.h>
#include<string.h>
#include<sched.h>
#include<assert.h>
#include"library/common.h"
#include"library/priority.h"

int main(void)
{
	char sched_policy[SCHEDULE_NAME];
	assert(scanf("%s", sched_policy) == 1);
	const char sched_types[NUM_SCHEDULING_TYPE][SCHEDULE_NAME] = {"FCFS", "SJF", "PSJF", "RR"};

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

	CPU(getpid(), 0);
	SET_PRIORITY(getpid(), SCHED_FIFO, PRIORITY_INIT);

	fflush(stdin);

	switch(sched_policy[0])
	{
		case 'F':
			execl("./FCFS", "./FCFS", (char *)0);
			break;
		case 'S':
			execl("./SJF", "./SJF", (char *)0);
			break;
		case 'P':
			execl("./PSJF", "./PSJF", (char *)0);
			break;
		case 'R':
			execl("./RR", "./RR", (char *)0);
			break;
	}

	return 0;
}

all : process scheduler calc time                                                                                                                                                                           

process :
        gcc process.c common.c -o process

scheduler :
        gcc FCFS.c common.c merge_sort.c -o FCFS
        gcc RR.c common.c merge_sort.c -o RR
        gcc SJF.c common.c merge_sort.c heap.c -o SJF
        gcc PSJF.c common.c merge_sort.c heap.c -o PSJF
        gcc scheduler.c common.c -o scheduler
        gcc time.c common.c -o time

calc :
        gcc calc.c common.c merge_sort.c heap.c -o calc

clean:
        @rm process scheduler FCFS SJF RR PSJF calc time

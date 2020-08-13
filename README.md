# CPU SCHEDULING Algorithms
* [FCFS (First-Come, First-Served)](#FCFS (First-Come, First-Served))
* [SJF (Shortest Job First)](#SJF (Shortest Job First))
* [PSJF (Preemptive Shortest Job First)](#PSJF (Preemptive Shortest Job First))
* [RR (Round-Robin)](#RR (Round-Robin))

## Usage
```shell
$ make                                       // compile all program
$ sudo ./scheduler < data/FCFS_1.txt         // test the first data of FCFS
$ ./calc < data/FCFS_1.txt                   // calculate the the preiod of the first data of FCFS
$ sudo sh time.sh                            // calculate the period of all ideal cases and real cases
$ python ganttChart_plot.py                  // plot the gantt chart of all scheduling algorithms
```

## FCFS (First-Come, First-Served)
* FCFS_1

|Process|Arrived time|Burst time|
|-|-|-|
|P1|0|1000|
|P2|0|1000|
|P3|0|1000|
|P4|0|1000|
|P5|0|1000|

![FCFS_1](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_1.png)

## SJF (Shortest Job First)
## PSJF (Preemptive Shortest Job First)
## RR (Round-Robin)

## Reference
https://github.com/wangyenjen/OS-Project-1

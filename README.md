# CPU SCHEDULING Algorithms
* [Usage](#Usage)
* [FCFS (First-Come, First-Served)](#FCFS)
* [SJF (Shortest Job First)](#SJF)
* [PSJF (Preemptive Shortest Job First)](#PSJF)
* [RR (Round-Robin)](#RR)
* [Linux Kernel add Syscall (Ubuntu)](https://blog.kaibro.tw/2016/11/07/Linux-Kernel%E7%B7%A8%E8%AD%AF-Ubuntu/)

## Usage
```shell
$ make                                       // compile all program
$ sudo ./time                                // calaulate the period of a time unit
$ sudo ./scheduler < data/FCFS_1.txt         // test the first data of FCFS
$ ./calc < data/FCFS_1.txt                   // calculate the the preiod of the first data of FCFS
$ sudo sh time.sh                            // calculate the period of all ideal cases and real cases
$ python ganttChart_plot.py                  // plot the gantt chart of all scheduling algorithms
```

## FCFS
#### FCFS_1

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|1000|
|P2|0|1000|
|P3|0|1000|
|P4|0|1000|
|P5|0|1000|

![FCFS_1](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_1.png)

#### FCFS_2

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|80000|
|P2|100|5000|
|P3|200|1000|
|P4|300|1000|

![FCFS_2](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_2.png)

#### FCFS_3

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|8000|
|P2|200|5000|
|P3|300|3000|
|P4|400|1000|
|P5|500|1000|
|P6|500|1000|
|P7|600|4000|

![FCFS_3](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_3.png)

#### FCFS_4

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|2000|
|P2|500|500|
|P3|500|200|
|P4|1500|500|

![FCFS_4](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_4.png)

#### FCFS_5

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|8000|
|P2|200|5000|
|P3|200|3000|
|P4|400|1000|
|P5|400|1000|
|P6|600|1000|
|P7|600|4000|

![FCFS_5](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/FCFS_5.png)

## SJF
#### SJF_1

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|5000|
|P2|0|2500|
|P3|200|1000|
|P4|300|2000|

![SJF_1](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/SJF_1.png)

#### SJF_2

|Process|Arrive time|Burst time|
|-|-|-|
|P1|100|100|
|P2|100|4000|
|P3|200|200|
|P4|200|4000|
|P5|200|7000|

![SJF_2](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/SJF_2.png)

#### SJF_3

|Process|Arrive time|Burst time|
|-|-|-|
|P1|100|3000|
|P2|100|5000|
|P3|100|7000|
|P4|200|10|
|P5|200|10|
|P6|300|4000|
|P7|400|4000|
|P8|500|9000|

![SJF_3](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/SJF_3.png)

#### SJF_4

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|3000|
|P2|1000|1000|
|P3|2000|4000|
|P4|5000|2000|
|P5|7000|1000|

![SJF_4](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/SJF_4.png)

#### SJF_5

|Process|Arrive time|Burst time|
|-|-|-|
|P1|0|2000|
|P2|500|500|
|P3|1000|500|
|P4|1500|500|

![SJF_5](https://github.com/Offliners/CPU-SCHEDULING-Algorithms/blob/master/images/FCFS/SJF_5.png)

## PSJF
## RR

## Reference
https://sls.weco.net/node/21325

https://github.com/wangyenjen/OS-Project-1

https://blog.kaibro.tw/2016/11/07/Linux-Kernel%E7%B7%A8%E8%AD%AF-Ubuntu/

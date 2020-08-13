#!/bin/bash                                                                                                                                                                                                 

mkdir outputs

for t in FCFS SJF PSJF RR ;
do
END=5
    for i in $(seq 1 $END) ;
    do
        sudo ./time > "outputs/unit_time_"$t"_$i.txt"
        sudo ./scheduler < "data/"$t"_$i.txt" 2> "outputs/schd_"$t"_$i.txt"
        ./calc < "data/"$t"_$i.txt" 2> "outputs/calc_"$t"_$i.txt"
        echo ""$t"_$i-----------------------------Done"
    done
done

echo "All Done"

#!/bin/bash 
echo "Enter the number of processes: "
read n

declare -a AT
declare -a BT
declare -a WT
declare -a TAT
declare -a PID

declare tot_WT=0
declare tot_TAT=0

echo "Enter Arrival Time and Burst Time for each process:"
for((i=0; i<n; i++))
do
    echo "Process P$((i+1))"
    echo -n "Arrival Time: "
    read at
    AT[i]=$at
    echo -n "Burst Time: "
    read bt
    BT[i]=$bt
    PID[i]=$i
done

for((i=0; i<n-1; i++))
do
    for((j=i+1; j<n; j++))
    do
        if (( AT[i] > AT[j] )); then
            
            temp=${AT[i]}
            AT[i]=${AT[j]}
            AT[j]=$temp
            
            temp=${BT[i]}
            BT[i]=${BT[j]}
            BT[j]=$temp
            
            temp=${PID[i]}
            PID[i]=${PID[j]}
            PID[j]=$temp
        fi
    done
done

WT[0]=0
TAT[0]=$((BT[0]))
completion_time=$((AT[0] + BT[0]))
for((i=1; i<n; i++))
do
    if (( completion_time < AT[i] )); then
        completion_time=${AT[i]}
    fi
    WT[i]=$((completion_time - AT[i]))
    if (( WT[i] < 0 )); then WT[i]=0; fi
    completion_time=$((completion_time + BT[i]))
    TAT[i]=$((WT[i] + BT[i]))
    tot_WT=$((tot_WT + WT[i]))
    tot_TAT=$((tot_TAT + TAT[i]))
done

tot_WT=$((tot_WT + WT[0]))
tot_TAT=$((tot_TAT + TAT[0]))

printf "Process\tArrival Time\tBurst Time\tWaiting Time\tTurn Around Time\n"
for ((i = 0; i < n; i++))
do
    printf "P%d\t%d\t\t%d\t\t%d\t\t%d\n" "$((PID[i]+1))" "${AT[$i]}" "${BT[$i]}" "${WT[$i]}" "${TAT[$i]}"
done

printf "Average Waiting time is %f\n" $(( 10**3  *tot_WT/n ))e-3
printf "Average Turn Around time is %f\n" $(( 10**3  *tot_TAT/n ))e-3

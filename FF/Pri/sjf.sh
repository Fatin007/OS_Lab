#!/bin/bash
echo "Number of process:"
read n_process
declare -a bt
declare -a wt
declare -a tat

declare totalwt=0
declare totaltat=0

for ((i = 0; i < n_process; i++))
do
        echo "Enter Burst Time for process $i"
        read tmp
        bt[i]=$tmp
done

new_bt=($(printf "%s\n" "${bt[@]}" | sort -n))

for ((i = 0; i < n_process; i++))
do
        if [ $i -eq 0 ]; then
                wt[i]=0
        else
                wt[i]=$(( ${wt[i-1]} + ${new_bt[i-1]} ))
        fi
        tat[i]=$(( wt[i] + new_bt[i] ))
        totalwt=$(( totalwt + wt[i] ))
        totaltat=$(( totaltat + tat[i] ))
done


printf "\n%-10s %-12s %-15s %-17s\n" "Process" "Burst Time" "Waiting Time" "Turnaround Time"

for ((i = 0; i < n_process; i++))
do
        printf "%-10s %-12s %-15s %-17s\n" "P$i" "${new_bt[i]}" "${wt[i]}" "${tat[i]}"
done

echo
echo "Total waiting time $totalwt"
echo "Total turn around time $totaltat"

avgwt=$(echo "scale=2; $totalwt / $n_process" | bc -l)
avgtat=$(echo "scale=2; $totaltat / $n_process" | bc -l)
echo "Average waiting time $avgwt"
echo "Average turn around time $avgtat"

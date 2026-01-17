#!/bin/bash

echo "Enter number of processes:"
read n

declare -a pid
declare -a bt
declare -a rt 
declare -a wt
declare -a tat

total_wt=0
total_tat=0


for ((i = 0; i < n; i++)); do
    pid[i]=$i
    echo "Enter Burst Time for Process $i:"
    read bt[i]
    rt[i]=${bt[i]}
    wt[i]=0
done


echo "Enter the size of time slice:"
read tq


time=0


while true; do
    done=1  

    for ((i = 0; i < n; i++)); do
        # Convert to float using bc
        remaining=$(echo "${rt[i]} > 0" | bc)

        if (( remaining == 1 )); then
            done=0

            if (( $(echo "${rt[i]} > $tq" | bc -l) )); then
                time=$(echo "$time + $tq" | bc)
                rt[i]=$(echo "${rt[i]} - $tq" | bc)
            else
                time=$(echo "$time + ${rt[i]}" | bc)
                wt[i]=$(echo "$time - ${bt[i]}" | bc)
                rt[i]=0
            fi
        fi
    done

    if (( done == 1 )); then
        break
    fi
done


for ((i = 0; i < n; i++)); do
    tat[i]=$(echo "${bt[i]} + ${wt[i]}" | bc)
    total_wt=$(echo "$total_wt + ${wt[i]}" | bc)
    total_tat=$(echo "$total_tat + ${tat[i]}" | bc)
done


avg_wt=$(echo "scale=2; $total_wt / $n" | bc -l)
avg_tat=$(echo "scale=2; $total_tat / $n" | bc -l)


printf "\n%-10s %-12s %-15s %-17s\n" "Process" "Burst Time" "Waiting Time" "Turnaround Time"
for ((i = 0; i < n; i++)); do
    printf "%-10s %-12s %-15s %-17s\n" "P${pid[i]}" "${bt[i]}" "${wt[i]}" "${tat[i]}"
done

echo
printf "Total Waiting Time: %.2f\n" "$total_wt"
printf "Total Turnaround Time: %.2f\n" "$total_tat"
printf "Average Waiting Time: %.2f\n" "$avg_wt"
printf "Average Turnaround Time: %.2f\n" "$avg_tat"

#!/bin/bash

echo "Enter number of processes:"
read n

# Declare arrays
declare -a pid
declare -a bt
declare -a pr
declare -a wt
declare -a tat

total_wt=0
total_tat=0


for ((i = 0; i < n; i++)); do
    pid[i]=$i
    echo "Process $i:"
    echo -n "  Enter Burst Time: "
    read bt[i]
    echo -n "  Enter Priority (lower = higher): "
    read pr[i]
done


temp_file=$(mktemp)
for ((i = 0; i < n; i++)); do
    echo "${pr[i]} ${pid[i]} ${bt[i]}" >> "$temp_file"
done


mapfile -t sorted_data < <(sort -nk1 "$temp_file")
rm "$temp_file"


wt[0]=0
for ((i = 0; i < n; i++)); do
    read -r priority pid_i bt_i <<< "${sorted_data[$i]}"

    if (( i > 0 )); then
        # Get previous process burst time
        prev_bt=$(echo "${sorted_data[$((i - 1))]}" | awk '{print $3}')
        wt[i]=$(( wt[i - 1] + prev_bt ))
    fi

    tat[i]=$(( wt[i] + bt_i ))
    total_wt=$(( total_wt + wt[i] ))
    total_tat=$(( total_tat + tat[i] ))


    sorted_pid[i]=$pid_i
    sorted_pr[i]=$priority
    sorted_bt[i]=$bt_i
done

avg_wt=$(echo "scale=2; $total_wt / $n" | bc -l)
avg_tat=$(echo "scale=2; $total_tat / $n" | bc -l)


printf "\n%-10s %-12s %-10s %-15s %-17s\n" "Process" "Priority" "BT" "Waiting Time" "Turnaround Time"


for ((i = 0; i < n; i++)); do
    printf "%-10s %-12s %-10s %-15s %-17s\n" "P${sorted_pid[i]}" "${sorted_pr[i]}" "${sorted_bt[i]}" "${wt[i]}" "${tat[i]}"
done


echo
printf "Total Waiting Time: %d\n" "$total_wt"
printf "Total Turnaround Time: %d\n" "$total_tat"
printf "Average Waiting Time: %.2f\n" "$avg_wt"
printf "Average Turnaround Time: %.2f\n" "$avg_tat"

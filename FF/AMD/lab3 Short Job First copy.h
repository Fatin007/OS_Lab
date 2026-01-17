# Step 1: Starting the process
declare -A process
declare -a waiting
declare -a turnaroundtime
declare -a prevBurstTime
declare totalWaitingTime
declare totalTurnaroundTimes
echo "Enter number of processes: "
read noOfProcesses

for ((i = 0; i < noOfProcesses; i++)); do

echo "Enter BT for process $((i + 1)): "
read temp
process+=(["$i"]=$temp)
done

sorted_pid=($(for key in "${!process[@]}"; do
    echo "$key ${process[$key]}"
done | sort -k 2n | awk '{print $1}'
))

# for key in "${sorted_pid[@]}"; do
#     echo "Key: $key Value: ${process[$key]}"
# done
printf "Process\tBurst Time\tWaiting Time\tTurnaroundTime\n"
for ((i = 0; i < noOfProcesses; i++)); do
    processKey=${sorted_pid[$i]}
    bursttime=${process[$processKey]}
    #  echo "Process key $(( i+1 )) = $processKey"
    if [ $i -eq 0 ]; then
        waiting[i]=0
        turnaroundtime[i]=$bursttime
        prevBurstTime[i]=$bursttime
    else 
        prevIndex=$(($i - 1))
        waiting[$i]=$(( ${waiting[$prevIndex]} + ${prevBurstTime[$prevIndex]} ))
        turnaroundtime[$i]=$(( ${waiting[$i]} + $bursttime))
        prevBurstTime[i]=$bursttime

    fi
    totalWaitingTime=$(( $totalWaitingTime + ${waiting[$i]} ))
    totalTurnaroundTimes=$(( $totalTurnaroundTimes + ${turnaroundtime[$i]}))
    printf "P%d\t%d\t\t%d\t\t%d\n" "${processKey}" "${bursttime}" "${waiting[$i]}" "${turnaroundtime[$i]}"
done
printf "Average Waiting Time is %f\n" $(( 10**3 * $totalWaitingTime / $noOfProcesses))e-3
printf "Average TurnAround Time is %f\n" $(( 10**3 * $totalTurnaroundTimes / $noOfProcesses))e-3
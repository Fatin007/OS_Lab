#!/bin/bash
echo "Enter the number of processes: "
read noOfProcesses


# Considering no Arrival Time

declare currentTime=0
declare completed=0
declare -a burstTime
declare -a theBurstTime

declare -a completedTime

declare -a tat
declare -a waiting=( $(for (( i = 0; i < noOfProcesses; i++)); do echo -1; done))
declare time=0

declare totalBurstTime=0
echo "Enter quantum value: "
read quantum

for((i = 0; i < noOfProcesses; i++))
do 
    echo "Enter the Burst time for Process $(($i + 1))" 
    read temp
    echo "Burst time for Process $i is $temp"
    burstTime[$i]=$temp
    theBurstTime[$i]=$temp
    completedTime[$i]=0
    totalBurstTime=$(( $totalBurstTime + ${burstTime[$i]}))
done

echo "Total Burst time is $totalBurstTime"
printf "Process\tBurst Time\tWaiting Time\tTurnaroundTime\n"

while [ $completed -lt $noOfProcesses ]; do
    
    for((i = 0; i < noOfProcesses; i++)); do
        remainingBurstTime=$(( burstTime[$i] ))
       
        if [ $remainingBurstTime -ne 0 ]; then
            if [ $remainingBurstTime -lt $quantum ]; then
                burstTime[$i]=0
                time=$(( $time + $remainingBurstTime ))
                tat[$i]=$(( $time ))
                waiting[$i]=$(( ${tat[$i]} - ${theBurstTime[$i]} ))
                completed=$(( $completed + 1 ))
                # printf "P%d\t%d\t\t%d\t\t%d\n" "$i" "${theBurstTime[$i]}" "${waiting[$i]}" "${tat[$i]}"


            else 
                burstTime[$i]=$(( $remainingBurstTime - $quantum ))
                time=$(( $time + $quantum ))
                if [ ${burstTime[$i]} -eq 0 ]; then
                    tat[$i]=$(( $time ))
                    waiting[$i]=$(( ${tat[$i]} - ${theBurstTime[$i]} ))
                    completed=$(( $completed + 1 ))
                   # printf "P%d\t%d\t\t%d\t\t%d\n" "$i" "${theBurstTime[$i]}" "${waiting[$i]}" "${tat[$i]}"

                fi
            fi
        fi
    done
done

declare totalWaitingTime=0
declare totalTurnAroundTime=0
for((i = 0; i < noOfProcesses; i++))
do 
    totalWaitingTime=$(( $totalWaitingTime + ${waiting[$i]} ))
    totalTurnAroundTime=$(( $totalTurnAroundTime + ${tat[$i]} ))
    # echo "waiting time for process $i is ${waiting[$i]}"
    printf "P%d\t%d\t\t%d\t\t%d\n" "$i" "${theBurstTime[$i]}" "${waiting[$i]}" "${tat[$i]}"

done

printf "Avg waiting time is %f\n" $(( 10**3  *totalWaitingTime/noOfProcesses ))e-3
printf "Avg Turn Around time is %f\n" $(( 10**3  *totalTurnAroundTime/noOfProcesses ))e-3

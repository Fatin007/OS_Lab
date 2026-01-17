#!/bin/bash
echo "Enter the number of processes: "
read noOfProcesses


# Considering no Arrival Time

declare currentTime=0
declare completed=0
declare -a tat
declare -a burstTime
declare -a waiting

for((i = 0; i < noOfProcesses; i++))
do 
    echo "Enter the Burst time for Process $(($i + 1))" 
    read temp
    echo "Burst time for Process $i is $temp"
    burstTime[$i]=$temp
done

burstTime=($(printf '%d\n' "${burstTime[@]}"|sort))

for((i = 0; i < noOfProcesses; i++))
do 
    echo "Processing process with burst time of $((burstTime[$i])) s"
    if [ $i -eq 0 ]; then
		waiting[i]=0
	else 
		newtemp=i-1
		echo "Waiting[$i] is ${waiting[$newtemp]}"
		echo "Bursttime[$i] is ${burstTime[$newtemp]}"
		waiting[i]=$(( ${waiting[$newtemp]} + ${burstTime[$newtemp]}  ))
	fi
	tat[i]=$[waiting[i] + burstTime[i]] 
	totalTAT=$[totalTAT + tat[i]]
	totalWaitingTime=$[totalWaitingTime + waiting[i]]
	echo "Waiting time is $totalWaitingTime"

done

declare avgwait=$(( totalWaitingTime/noOfProcesses ))
declare avgtat=$(( totalTAT/noOfProcesses ))
echo "Avg Waiting time is $avgwait"
echo "Avg TAT is $avgtat"
#!/bin/bash
echo "Enter the number of processes: "
read numproc


declare -a bursttime
declare -a waiting
declare -a tat

declare totalWaitingTime=0
declare totalTAT=0

for ((i = 0; i < numproc; i++))
do
	echo "Enter Burst Time for Process $i"
	read tempVal
	bursttime[i]=$tempVal
	if [ $i -eq 0 ]; then
		waiting[i]=0
	else 
		newtemp=i-1
		echo "Waiting[$i] is ${waiting[$newtemp]}"
		echo "Bursttime[$i] is ${bursttime[$newtemp]}"
		waiting[i]=$(( ${waiting[$newtemp]} + ${bursttime[$newtemp]}  ))
	fi
	tat[i]=$[waiting[i] + bursttime[i]] 
	totalTAT=$[totalTAT + tat[i]]
	totalWaitingTime=$[totalWaitingTime + waiting[i]]
	echo "Waiting time is $totalWaitingTime"
done
echo "Total Waiting time is $totalWaitingTime"
echo "Total TAT is $totalTAT"
declare avgwait=$(( totalWaitingTime/numproc ))
declare avgtat=$(( totalTAT/numproc ))
echo "Avg Waiting time is $avgwait"
echo "Avg TAT is $avgtat"

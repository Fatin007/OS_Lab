# FIFO page Replacement Algorithm
echo "Enter the number of pages: "
read numberOfPages
echo "Enter the frame size: "
read frameSize
echo "Enter the reference String length: "
read refStringLength
echo "Enter the refStr "

declare -a arrivalTime
declare -a burstTime
declare -a tat
declare -a waitingTime
declare -A process
declare totalWaitingTime
declare totalTurnaroundTimes
for ((i = 0; i < numberOfProcess; i++)); do
    echo "Enter Burst Time for Process $i"
    read temp
    burstTime[$i]=$temp
    echo "Enter Arrival Time for Process $i"
    read temp2
    arrivalTime[$i]=$temp2
    process+=(["$i"]=$temp2)
done

for((i = 0; i < numberOfProcess; i++)); do
    echo "Process $i BurstTime ${burstTime[$i]} ArrivalTime ${arrivalTime[$i]}"
done

sorted_arrival=($(for key in "${!process[@]}"; do
    echo "$key ${process[$key]}"
done | sort -k 2n | awk '{print $1}'
))

for key in "${sorted_arrival[@]}"; do
    echo "Key: $key Value: ${process[$key]}"
    
done

declare time=${process[${sorted_arrival[0]}]}
echo "Time starting is $time"

echo " "
completedProcess=0
for key in "${sorted_arrival[@]}"; do
    #echo "Key: $key Value: ${process[$key]}"
    processID=$key
    burstTimeOfCurrentProcess=${burstTime[$key]}
    arrivaltimeofcurrentProcess=${process[$key]}
    echo "Process ID: $processID BurstTime: $burstTimeOfCurrentProcess Arrival Time: $arrivaltimeofcurrentProcess"
    if [ $arrivaltimeofcurrentProcess -gt $time ]; then
    # it means the process have to wait till arrivaltime
    # which means we have to updated the time to arrivaltime of currentprocesss
    time=$arrivaltimeofcurrentProcess
    echo "entered in if"
    fi
    #now we compute the completedtime for the current process
    time=$(( $time + $burstTimeOfCurrentProcess )) 
    completedtime=$time
    echo "CurrentTime: $time complete time: $completedtime" 
    #now we compute the turnaround time for current process
    turnaroundtimeforcurrentprocess=$(( $completedtime - $arrivaltimeofcurrentProcess ))
    #now we print tat
    echo "turnaroundtime: $turnaroundtimeforcurrentprocess"   
    #now we compute the waiting time
    waitingtimeforcurrentprocess=$(( $time - $burstTimeOfCurrentProcess))
    echo "waitingtime: $waitingtimeforcurrentprocess"
    totalTAT=$(( $totalTAT + $turnaroundtimeforcurrentprocess ))
    totalWaitingTime=$(( $totalWaitingTime + $waitingtimeforcurrentprocess ))
    echo " "
done

    echo "CurrentTime: $time totalWait: $totalWaitingTime totalTAT: $totalTAT"
    printf "Average Waiting Time is %f\n" $(( 10**6 * $totalWaitingTime / $numberOfProcess))e-6
    printf "Average TurnAround Time is %f\n" $(( 10**6 * $totalTAT / $numberOfProcess))e-6

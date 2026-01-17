echo "Enter number of processes: "
read noOfProcesses

declare -A process
declare -A pid
declare -a waiting
declare -a turnaroundtime
for ((i = 0; i < noOfProcesses; i++)); do

echo "Enter BT & Priority for process $i: "
read bt
read priority
process+=(["$priority"]="$bt")
pid+=(["$priority"]="$i")
done
# for key in ${!pid[@]}; do
#     echo "Key: $key Value: ${pid[$key]}"
# done

# for key in ${!pid[@]}; do
#         echo "${pid[$key]} $key" 
# done | sort -k 2n | awk '{print $2}'
# echo " " 
sorted_priority=($(for key in ${!pid[@]}; do
        echo "${pid[$key]} $key" 
done | sort -k 2n | awk '{print $2}'
))

isFirst=1
prevWaiting=0
prevBT=0
declare totalWaitingTime=0
declare totalTurnaroundTime=0
printf "Process\tPriority\tBurst Time\tWaiting Time\tTurnaroundTime\n"
i=0
for prioKey in ${sorted_priority[@]}; do
    index=${pid[$prioKey]}
    bursttime=${process[$prioKey]}
    # echo "P${index} BT: ${bursttime} Priority: ${prioKey}"
    #Finding if it is the first process to be processed!
    if [ $isFirst -eq 1 ]; then
        waiting[${i}]=$(( prevWaiting + prevBT))
        turnaroundtime[${i}]=$(( waiting[$i] + bursttime ))
        prevWaiting=0
        prevBT=$bursttime
        isFirst=0
    else 
        waiting[$i]=$(( prevWaiting + prevBT))
        turnaroundtime[${i}]=$(( waiting[$i] + bursttime ))
        prevWaiting=${waiting[$i]}
        prevBT=$bursttime
    fi
    printf "P%d\t%d\t\t%d\t\t%d\t\t%d\n" "${index}" "${prioKey}" "${bursttime}" "${waiting[$i]}" "${turnaroundtime[$i]}"
    totalWaitingTime=$(( $totalWaitingTime + $prevWaiting ))
    totalTurnaroundTime=$(( $totalTurnaroundTime + turnaroundtime[$i] ))
    i=$(( $i + 1 ))
   
done

printf "Average Waiting Time is %f\n" $(( 10**3 * $totalWaitingTime / $noOfProcesses))e-3
printf "Average TurnAround Time is %f\n" $(( 10**3 * $totalTurnaroundTime / $noOfProcesses))e-3
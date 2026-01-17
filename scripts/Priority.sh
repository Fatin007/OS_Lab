#!/bin/bash
echo "Enter number of processes: "
read n

declare -A process
declare -A pid
declare -a WT
declare -a TAT
for ((i = 0; i < n; i++)); do

echo "Enter Burst Time & Priority for process P$((i+1)): "
read bt
read priority
process+=(["$priority"]="$bt")
pid+=(["$priority"]="$i")
done

sort=($(for key in ${!pid[@]}; do
        echo "${pid[$key]} $key" 
done | sort -k 2n | awk '{print $2}'
))

isFirst=1
prevWT=0
prevBT=0
declare totWT=0
declare totTAT=0
printf "Process\tPriority\tBurst Time\tWaiting Time\tTurnaroundTime\n"
i=0
for prioKey in ${sort[@]}; do
    idx=${pid[$prioKey]}
    bursttime=${process[$prioKey]}
    
    if [ $isFirst -eq 1 ]; then
        WT[${i}]=$(( prevWT + prevBT))
        TAT[${i}]=$(( WT[$i] + bursttime ))
        prevWT=0
        prevBT=$bursttime
        isFirst=0
    else 
        WT[$i]=$(( prevWT + prevBT))
        TAT[${i}]=$(( WT[$i] + bursttime ))
        prevWT=${WT[$i]}
        prevBT=$bursttime
    fi
    printf "P%d\t%d\t\t%d\t\t%d\t\t%d\n" "${idx}" "${prioKey}" "${bursttime}" "${WT[$i]}" "${TAT[$i]}"
    totWT=$(( $totWT + $prevWT ))
    totTAT=$(( $totTAT + TAT[$i] ))
    i=$(( $i + 1 ))
   
done

printf "Average Waiting Time is %f\n" $(( 10**3 * $totWT / $n))e-3
printf "Average Turn Around Time is %f\n" $(( 10**3 * $totTAT / $n))e-3
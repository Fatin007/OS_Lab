#!/bin/bash
echo "Enter the number of processes: "
read n

declare currentTime=0
declare completed=0
declare -a BT
declare -a nextBT
declare -a CT
declare -a TAT
declare -a WT=( $(for (( i = 0; i < n; i++)); do echo -1; done))
declare t=0

declare tot_BT=0
echo "Enter quantum value: "
read q

for((i = 0; i < n; i++))
do 
    echo "Enter the Burst time for P$(($i + 1))" 
    read x
    
    BT[$i]=$x
    nextBT[$i]=$x
    CT[$i]=0
    tot_BT=$(( $tot_BT + ${BT[$i]}))
done

echo "Total Burst time is $tot_BT"
printf "Process\tBurst Time\tWaiting Time\tTurn Around Time\n"

while [ $completed -lt $n ]; 
do  
    for((i = 0; i < n; i++)); 
    do
        remBT=$(( BT[$i] ))
        if [ $remBT -ne 0 ]; then
            if [ $remBT -lt $q ]; then
                BT[$i]=0
                t=$(( $t + $remBT ))
                TAT[$i]=$(( $t ))
                WT[$i]=$(( ${TAT[$i]} - ${nextBT[$i]} ))
                completed=$(( $completed + 1 ))
                
            else 
                BT[$i]=$(( $remBT - $q ))
                t=$(( $t + $q ))
                if [ ${BT[$i]} -eq 0 ]; then
                    TAT[$i]=$(( $t ))
                    WT[$i]=$(( ${TAT[$i]} - ${nextBT[$i]} ))
                    completed=$(( $completed + 1 ))
                fi
            fi
        fi
    done
done

declare tot_WT=0
declare tot_TAT=0
for((i = 0; i < n; i++))
do 
    tot_WT=$(( $tot_WT + ${WT[$i]} ))
    tot_TAT=$(( $tot_TAT + ${TAT[$i]} ))
    printf "P%d\t%d\t\t%d\t\t%d\n" "$((i+1))" "${nextBT[$i]}" "${WT[$i]}" "${TAT[$i]}"

done

printf "Average Waiting Time is %f\n" $(( 10**3  *tot_WT/n ))e-3
printf "Average Turn Around Time is %f\n" $(( 10**3  *tot_TAT/n ))e-3

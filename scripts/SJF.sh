    declare -a BT
    declare -a WT
    declare -a TAT
    declare -a preBT
    declare tot_WT
    declare tot_TAT
    echo "Enter number of processes: "
    read n

    for ((i = 0; i < n; i++)); 
    do
        echo "Enter Burst Time for P$((i+1)): "
        read x
        BT+=(["$i"]=$x)
    done

    sort=($(for key in "${!BT[@]}";
    do
        echo "$key ${BT[$key]}"
    done | sort -k 2n | awk '{print $1}'
    ))

    printf "Process\tBurst Time\tWaiting Time\tTurnaround Time\n"
    for ((i = 0; i < n; i++)); 
    do
        y=${sort[$i]}
        t=${BT[$y]}
        if [ $i -eq 0 ]; then
            WT[i]=0
            TAT[i]=$t
            preBT[i]=$t
        else 
            prevIndex=$(($i - 1))
            WT[i]=$(( ${WT[$prevIndex]} + ${preBT[$prevIndex]} ))
            TAT[i]=$(( ${WT[$i]} + $t))
            preBT[i]=$t

        fi
        tot_WT=$(( $tot_WT + ${WT[$i]} ))
        tot_TAT=$(( $tot_TAT + ${TAT[$i]} ))
        printf "P%d\t%d\t\t%d\t\t%d\n" "$((y + 1))" "${t}" "${WT[$i]}" "${TAT[$i]}"
    done
    printf "Average Waiting Time is %f\n" $(( 10**3 * $tot_WT / $n))e-3
    printf "Average Turn Around Time is %f\n" $(( 10**3 * $tot_TAT / $n))e-3
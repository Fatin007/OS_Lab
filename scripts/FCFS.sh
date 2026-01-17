	#!/bin/bash 
	echo "Enter the number of processes: "
	read n


	declare -a BT
	declare -a WT
	declare -a TAT

	declare tot_WT=0
	declare tot_TAT=0

	for((i=0; i<n; i++))
	do
		echo "Enter Burst Time for P$((i+1))"
		read x
		BT[i]=$x
		if [ $i -eq 0 ]; then
			WT[i]=0
		else 
			WT[i]=$(( ${WT[$i-1]} + ${BT[$i-1]}  ))
		fi
		TAT[i]=$((WT[i] + BT[i]))
		tot_TAT=$((tot_TAT + TAT[i]))
		tot_WT=$((tot_WT + WT[i]))
	done

	printf "Process\tBurst Time\tWaiting Time\tTurn Around Time\n"

	for ((i = 0; i < n; i++))
	do
		printf "P%d\t%d\t\t%d\t\t%d\n" "$i" "${BT[$i]}" "${WT[$i]}" "${TAT[$i]}"
	done

	printf "Average Waiting time is %f\n" $(( 10**3  *tot_WT/n ))e-3
	printf "Average Turn Around time is %f\n" $(( 10**3  *tot_TAT/n ))e-3
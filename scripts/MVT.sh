#!/bin/bash

read -p "Enter total memory available (in Bytes): " nm
total=$nm
process=()
i=0

while (( nm > 0 )); do
    read -p "Enter memory required for process $((i+1)) (in Bytes): " x
    if (( x > nm )); then
        echo "Memory is full"
        break
    else
        nm=$((nm - x))
        process+=("$x")
        i=$((i+1))
        echo "Memory is allocated for process $i"
    fi
    read -p "Do you want to Continue?: " op
    if [[ "$op" != "y" ]]; then
        break
    fi
done

echo -e "Process\tMemory Allocated"
for idx in "${!process[@]}"; do
    echo -e "$((idx+1))\t${process[$idx]}"
done
echo "Total Memory Allocated: $((total-nm))"
echo "Total External Fragmentation: $nm"

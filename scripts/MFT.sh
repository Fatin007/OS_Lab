
#!/bin/bash

MAX=100
process=()

echo -n "Enter the total memory available (in Bytes): "
read nb
echo -n "Enter the block Size (in Bytes): "
read blockSz
echo -n "Enter number of processes: "
read np
for ((i=0; i<np; i++)); do
    echo -n "Enter memory required for process $((i+1)) (in Bytes): "
    read process[i]
done

available=$((nb / blockSz))
echo -e "Process\t\tMemory Required\t\tAllocated\tInternal Fragmentation"

if [ $np -gt $available ]; then
    allocatable=$available
else
    allocatable=$np
fi

allocated=0
curr=0
internal=0
while [ $allocated -lt $allocatable ]; do
    i=$((curr+1))
    memoryLagbe=${process[curr]}
    if [ $memoryLagbe -gt $blockSz ]; then
        echo -e "$i\t\t$memoryLagbe\t\t\tNO\t\t---"
    else
        frag=$((blockSz - memoryLagbe))
        echo -e "$i\t\t$memoryLagbe\t\t\tYES\t\t$frag"
        allocated=$((allocated+1))
        internal=$((internal + frag))
    fi
    curr=$((curr+1))
done

if [ $np -gt $available ]; then
    external=$((nb - (blockSz * available)))
    echo "Memory is full. Remaining processes can't be Accomodated"
    echo "Internal Fragmentation is $internal"
    echo "Total External Fragmentation: $external"
else
    external=$((nb - (blockSz * available)))
    echo "Memory is not full, more processed may be accomodated."
    echo "Internal Fragmentaiton is $internal"
fi

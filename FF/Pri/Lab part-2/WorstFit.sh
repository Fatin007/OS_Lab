echo "Enter the number of Blocks: "
read numberOfBlocks
echo "Enter the number of files: "
read numberOfFiles
declare -a Blocks
declare -a files
declare -a allocatedblock
echo "Enter the the size of block: "
for ((i = 0; i < numberOfBlocks; i++)); do
    allocatedblock[$i]=-1
done



for ((i = 0; i < numberOfBlocks; i++)); do
    echo "Block $i:"
    read temp
    block[$i]=$temp   
done

for ((i = 0; i < numberOfFiles; i++)); do
    echo "File $i:"
    read temp
    files[$i]=$temp   
done


for(( i = 0; i < numberOfFiles; i++)); do
    declare biggestBlockAvailable
    sizeOfCurrentFile=${files[$i]}
    for((j = 0; j < numberOfBlocks; j++)); do
          if [ [$allocatedblock -eq 0] && [block[$i] -gte sizeOfCurrentFile] && [block[$i] -gt ] ]; then
            # it means the process have to wait till arrivaltime
            # which means we have to updated the time to arrivaltime of currentprocesss
            time=$arrivaltimeofcurrentProcess
            echo "entered in if"
    fi

    done
done
#include<stdio.h>
#define MAX 100
int main() {
    //TODO
    // 1. Take input
    //      i. Number of bytes available
    //      ii. Block Size in bytes
    //      iii. Number of processes
    //      iv. Memory required for each process
    //      v. Blocks available in memory

    int numberOfAvailableBytes;
    int blockSize;
    int noOfProcesses;
    int processBytes[MAX];
    

    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &numberOfAvailableBytes);
    printf("Enter the block Size (in Bytes): ");
    scanf("%d", &blockSize);
    printf("Enter number of processes: ");
    scanf("%d", &noOfProcesses);
    for(int i = 0; i < noOfProcesses; i++){
        printf("Enter memory required for process %d (in Bytes): ", i+1);
        scanf("%d", &processBytes[i]);
    }
    int numberOfBlocksAvailableInMemory = numberOfAvailableBytes / blockSize;
    printf("Process\t\tMemory Required\t\tAllocated\t.Internal Fragmentation\n");
    int maxProcessesAllocatable;
    if(noOfProcesses > numberOfBlocksAvailableInMemory) {
        maxProcessesAllocatable = numberOfBlocksAvailableInMemory;
    }
    else {
        maxProcessesAllocatable = noOfProcesses;
    }
    int allocatedProcesses = 0;
    int currentProcess = 0;
    // for(int i = 0; i < noOfProcesses; i++){
    //     printf("Process %d Bytes: %d", i+1, processBytes[i]);
    // }
    int internalFragmentation = 0;
    while(allocatedProcesses < maxProcessesAllocatable){
        int processID = currentProcess + 1;
        int processMemoryRequired = processBytes[currentProcess];
        if(processMemoryRequired > blockSize){
            // printf("Debug Statement: Process %d cannot be allocated\n", processID);
            printf("%d\t\t%d\t\t\tNO\t\t---\n", processID, processMemoryRequired);
        }
        else {
            printf("%d\t\t%d\t\t\tYES\t\t%d\n", processID, processMemoryRequired, blockSize - processMemoryRequired);
            allocatedProcesses++;
            internalFragmentation = internalFragmentation + (blockSize - processMemoryRequired);
        }
        currentProcess++;
    }
    if(noOfProcesses > numberOfBlocksAvailableInMemory){
        int externalFragmentation = numberOfAvailableBytes - (blockSize * numberOfBlocksAvailableInMemory);
        printf("Memory is full. Remaining processes can't be Accomodated\n");
        printf("Internal Fragmentation is %d\n", internalFragmentation);
        printf("Total External Fragmentation: %d\n", externalFragmentation);
    }
    else {
        int ExternalFragmentation = numberOfAvailableBytes - (blockSize * numberOfBlocksAvailableInMemory);
        printf("Memory is not full, more processed may be accomodated.\n");
        printf("Internal Fragmentaiton is %d\n", internalFragmentation);

    }



}
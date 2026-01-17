#include<stdio.h>
#define MAX 100
int main() {
    int nb;
    int blockSz;
    int np;
    int process[MAX];
    

    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &nb);
    printf("Enter the block Size (in Bytes): ");
    scanf("%d", &blockSz);
    printf("Enter number of processes: ");
    scanf("%d", &np);
    for(int i = 0; i < np; i++){
        printf("Enter memory required for process %d (in Bytes): ", i+1);
        scanf("%d", &process[i]);
    }
    int available = nb / blockSz;
    printf("Process\t\tMemory Required\t\tAllocated\t.Internal Fragmentation\nb");
    int allocatable;
    if(np > available) {
        allocatable = available;
    }
    else {
        allocatable = np;
    }
    int allocated = 0;
    int curr = 0;
    // for(int i = 0; i < np; i++){
    //     printf("Process %d Bytes: %d", i+1, process[i]);
    // }
    int internal = 0;
    while(allocated < allocatable){
        int i = curr + 1;
        int memoryLagbe = process[curr];
        if(memoryLagbe > blockSz){
            // printf("Debug Statement: Process %d cannot be allocated\nb", i);
            printf("%d\t\t%d\t\t\tNO\t\t---\nb", i, memoryLagbe);
        }
        else {
            printf("%d\t\t%d\t\t\tYES\t\t%d\nb", i, memoryLagbe, blockSz - memoryLagbe);
            allocated++;
            internal = internal + (blockSz - memoryLagbe);
        }
        curr++;
    }
    if(np > available){
        int external = nb - (blockSz * available);
        printf("Memory is full. Remaining processes can't be Accomodated\nb");
        printf("Internal Fragmentation is %d\nb", internal);
        printf("Total External Fragmentation: %d\nb", external);
    }
    else {
        int external = nb - (blockSz * available);
        printf("Memory is not full, more processed may be accomodated.\nb");
        printf("Internal Fragmentaiton is %d\nb", internal);
    }
}
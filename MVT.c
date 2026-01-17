#include<stdio.h>

#define MAX 100
int main() {
    int availableMemory;
    printf("Enter total memory available (in Bytes): ");
    scanf("%d", &availableMemory);
    int totalMem = availableMemory;
    int processMemory[MAX];
    int processID = 0;
    while(availableMemory > 0){
        
        printf("Enter memory required for process %d (in Bytes): ", processID + 1);
        int processMem;
        scanf("%d", &processMem);
        if(processMem > availableMemory){
            printf("Memory is full\n");
            break;
        }
        else {
            availableMemory = availableMemory - processMem;
            processMemory[processID] = processMem;
            processID++;
            printf("Memory is allocated for process %d\n", processID);
        }
        printf("Do you want to Continue?: ");
        char character;
        scanf(" %c", &character);
        if(character != 'y'){
            break;
        }
    }
    printf("Process\tMemory Allocated\n");
    for(int i = 0; i < processID; i++){
        printf("%d\t%d\n", i + 1, processMemory[i]);
    }
    printf("Total Memory Allocated: %d\n", totalMem - availableMemory);
    printf("Total External Fragmentation: %d\n", availableMemory);
}
#include<stdio.h>
#define MAX 100
int main(){
    int noOfBlocks, noOfFiles;
    printf("Enter number of blocks: ");
    scanf("%d", &noOfBlocks);
    printf("Enter number of files: ");
    scanf("%d", &noOfFiles);

    int blocks[MAX], files[MAX], blockAlloc[MAX], fileToBlock[MAX];
    for(int i = 0; i < MAX; i++){
        blockAlloc[i] = -1;
    }

    for(int i = 0; i < noOfBlocks; i++){
        printf("Block %d", i+1);
        int t;
        scanf("%d", &t);
        blocks[i] = t;
    }


    for(int i = 0; i < noOfFiles; i++){
        printf("File %d", i+1);
        int t;
        scanf("%d", &t);
        files[i] = t;
    }

    for(int i = 0; i < noOfFiles; i++){
        int sizeOfCurrentFile = files[i];
        int indexOfBiggestBlockAvailable = 0;
        for(int j = 0; j < noOfBlocks; j++){
            int sizeOfBlock = blocks[j];
            int whatIsCurrentlyAtTheBlock = blockAlloc[j];
            if(whatIsCurrentlyAtTheBlock == -1 && sizeOfBlock > blocks[indexOfBiggestBlockAvailable]) {
                indexOfBiggestBlockAvailable = j;
            }
        }
        printf("The biggest Block: index: %d and size of block: %d\n", indexOfBiggestBlockAvailable, blocks[indexOfBiggestBlockAvailable]);
        blockAlloc[indexOfBiggestBlockAvailable] = i;
        fileToBlock[i] = indexOfBiggestBlockAvailable;
    }
    printf("File No\t\tFile Size\t\tBlock No\t\tBlock Size\t\tFragment\n");
    for(int i = 0; i < noOfFiles; i++){
        int blkIdx = fileToBlock[i];
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\n", i, files[i], fileToBlock[i], blocks[blkIdx], blocks[blkIdx] - files[i]);
    }



    // For worst fit, we find the 
    
}
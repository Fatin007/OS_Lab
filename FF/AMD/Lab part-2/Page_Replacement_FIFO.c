#include<stdio.h>
#include<stdlib.h>
#define MAX 100

/*
FIFO Algorithm
1. Start the process
2. Read the numer of pages n
3. Read the page no.
4. Read page number into an array a[i]
5. Initialize avail[i] = 0 to check page hit
6. Replace the page with a circular queue while replacing
the check page availability in the fram 
Place avail[i] = 1 if page is placed in frame count pagefaults
7. Print the results
8. Stop the process



*/

/*
    

*/

int main() {

    int numberOfPage;
    int refStringLength;
    int frameSize;

    int theMainMemState[MAX];
    memset(theMainMemState, -1, MAX*sizeof(int));

// for(int i =0; i < MAX; i++){
//     printf("State of %d cell: %d\n", i+1, theMainMemState[i]);
// }

    printf("Enter the number of pages: \n");
    scanf("%d", &numberOfPage);
    printf("Enter the frame size: \n");
    scanf("%d", &frameSize);
    printf("Enter the reference String length: \n");
    scanf("%d", &refStringLength);
    int theRefString[MAX];
   
    printf("Enter the ref String: ");
    for(int i = 0; i < refStringLength; i++){
        scanf("%d", &theRefString[i]);
    }
    
    int pagefaultcount = 0;
    int oldestIndex = 0;
    for(int i = 0; i < refStringLength; i++){
        int pageRequested = theRefString[i];
        int frameWhereTheRequestPageIsAt = linearSearch(theMainMemState, pageRequested, frameSize);
        if(frameWhereTheRequestPageIsAt == -1){
            // The page requested is not found, thus it is a page fault
            theMainMemState[oldestIndex] = pageRequested;
            pagefaultcount++;
            oldestIndex = (oldestIndex + 1) % frameSize;
        }
        else {
            // The page requested is found, it is a page hit.
        }    
        showStateOfMainMemory(theMainMemState, frameSize);

    }
    printf("Page fault count: %d\n", pagefaultcount);


}

int linearSearch(int *arr, int tobefound, int length){
    for(int i = 0; i < length; i++){
        if(arr[i] == tobefound){
            return i;
        }
    }
    return -1;
}
void showStateOfMainMemory(int *arr, int length){
    printf("Main Memory: ");
    for(int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
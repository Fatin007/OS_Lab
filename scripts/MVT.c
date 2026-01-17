#include<stdio.h>

#define MAX 100
int main() {
    int nm;
    printf("Enter total memory available (in Bytes): ");
    scanf("%d", &nm);
    int total = nm;
    int process[MAX];
    int i = 0;
    while(nm > 0){
        
        printf("Enter memory required for process %d (in Bytes): ", i + 1);
        int x;
        scanf("%d", &x);
        if(x > nm){
            printf("Memory is full\n");
            break;
        }
        else {
            nm = nm - x;
            process[i] = x;
            i++;
            printf("Memory is allocated for process %d\n", i);
        }
        printf("Do you want to Continue?: ");
        char character;
        scanf(" %c", &character);
        if(character != 'y'){
            break;
        }
    }
    printf("Process\tMemory Allocated\n");
        int process_count = i;
        for(int j = 0; j < process_count; j++){
            printf("%d\t%d\n", j + 1, process[j]);
        }
    printf("Total Memory Allocated: %d\n", total - nm);
    printf("Total External Fragmentation: %d\n", nm);
}
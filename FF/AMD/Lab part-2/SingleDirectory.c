#include <stdio.h>
#include <string.h>

#define MAX 100

int main()
{
    char dirName[MAX];
    char fileName[MAX][MAX];
    int fileAlloc[MAX];
    for(int i = 0; i < MAX; i++){
        fileAlloc[i] = -1;
    }
    printf("Enter name of Directory: ");
    scanf("%s", dirName);
    printf("Name of Dir: %s\n", dirName);
    int fileCount = 0;

    while (1)
    {
        char fName[MAX];
                    int indexForFile = -1;

        printf("Enter a choice: 1. Create File. 2. Delete File 3. Search File. 4.Display File 5.Exit.\n");
        int t;
        scanf("%d", &t);
        switch (t)
        {
        case 1:
            printf("Enter name of File: ");
            scanf("%s", fName);
            indexForFile = -1;
            for(int i = 0; i< MAX; i++){
                if(fileAlloc[i] != 1){
                    indexForFile = i;
                    break;
                }
            }
            if(indexForFile == -1){
                printf("No free slot available. Please delete a file and try again.\n");
                break;
            }
            fileAlloc[indexForFile] = 1;
            printf("Index to store filename = %d\n", indexForFile);
            strcpy(fileName[indexForFile], fName);
            printf("File %s is stored at index %d\n", fName, indexForFile);
            break;  
        case 2:
            printf("Enter name of File to be Deleted: ");
            scanf("%s", fName);
            indexForFile = -1;
            for(int i = 0; i < MAX; i++){
                char fileInMem[MAX];
                strcpy(fileInMem, fileName[i]);
                if(strcmp(fileInMem, fName) == 0){
                    indexForFile = i;
                    break;
                }
            }
            if(indexForFile == -1){
                printf("%s file not found. Operation delete is cancelled.\n", fName);
                break;
            }
            fileAlloc[indexForFile] = -1;
            strcpy(fileName[indexForFile], "");
            printf("%s file at index %d is Deleted\n", fName, indexForFile);
            break;
        case 3:
         printf("Enter name of File to be Searched: ");
            scanf("%s", fName);
            indexForFile = -1;
            for(int i = 0; i < MAX; i++){
                char fileInMem[MAX];
                strcpy(fileInMem, fileName[i]);
                if(strcmp(fileInMem, fName) == 0){
                    indexForFile = i;
                    break;
                }
            }
            if(indexForFile == -1){
                printf("%s file not found.\n", fName);
                break;
            }
            printf("%s file is found at index %d.\n", fName, indexForFile);
            break;
        case 4:
            int fCtr = 1;
            for(int i = 0; i < MAX; i++){
                char theFileStr[MAX];
                if(fileAlloc[i] != -1){
                    strcpy(theFileStr, fileName[i]);
                    printf("%d. %s\n", fCtr, theFileStr);
                    fCtr++;
                }
            }
            break;
        case 5:
            return 0;
            break;
        
        }
    }
}
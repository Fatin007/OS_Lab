#include<stdio.h>
#include<stdlib.h>

void one(int n, int hungry_cnt, int hungry_pos[], int hungry[]) {
    int eating[n];
    for(int i = 0; i < n; i++) eating[i] = 0;

    for(int round = 0; round < hungry_cnt; round++) {
        int pos = hungry_pos[round];
        printf("P %d is granted to eat\n", pos);
        eating[pos] = 1;

        for(int i = 0; i < n; i++) {
            if(eating[i]) {
                printf("P %d is eating\n", i);
            } else if(hungry[i]) {
                printf("P %d is waiting\n", i);
            }
        }
        eating[pos] = 0;
    }
}

void two(int n, int hungry_cnt, int hungry_pos[]) {
    int eating[n];
    for(int i = 0; i < n; i++) eating[i] = 0;

    for(int round = 0; round < hungry_cnt; round += 2) {
        int pos1 = hungry_pos[round];
        int pos2 = (round + 1 < hungry_cnt) ? hungry_pos[round + 1] : -1;

        if(pos2 != -1) {
            printf("P %d and P %d are granted to eat\n", pos1, pos2);
            eating[pos1] = 1;
            eating[pos2] = 1;
        } else {
            printf("P %d is granted to eat\n", pos1);
            eating[pos1] = 1;
        }

        for(int i = 0; i < n; i++) {
            if(eating[i]) {
                printf("P %d is eating\n", i);
            } else {
                printf("P %d is waiting\n", i);
            }
        }

        if(pos2 != -1) {
            eating[pos1] = 0;
            eating[pos2] = 0;
        } else {
            eating[pos1] = 0;
        }
    }
}

int main(){
    int n; 
    printf("Enter the number of philosophers: ");
    scanf("%d", &n);
    int hungry_cnt;
    printf("Enter the number of hungry philosophers: ");
    scanf("%d", &hungry_cnt);
    int hungry_pos[hungry_cnt];
    int hungry[n];
    for(int i = 0; i < n; i++) hungry[i] = 0;
    for(int i = 0; i < hungry_cnt; i++) {
        printf("Enter philosopher %d position: ", i + 1);
        int pos;
        scanf("%d", &pos);
        hungry_pos[i] = pos;
        hungry[pos] = 1;
    }

    printf("1.One can eat at a time\n2.Two can eat at a time\n3.Exit Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("\nAllow one philosopher to eat at any time\n");
            one(n, hungry_cnt, hungry_pos, hungry);
            break;
        case 2:
            printf("\nAllow two philosophers to eat at any time\n");
            two(n, hungry_cnt, hungry_pos);
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice!\n");
            return 1;
    }
    return 0;
}
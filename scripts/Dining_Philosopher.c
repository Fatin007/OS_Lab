#include<stdio.h>
#include<stdlib.h>

void one(int n, int hungry_cnt, int hungry_pos[], int hungry[]) {
    int eating[n];
    int has_eaten[n];
    for(int i = 0; i < n; i++) {
        eating[i] = 0;
        has_eaten[i] = 0;
    }

    for(int round = 0; round < hungry_cnt; round++) {
        int pos = hungry_pos[round];
        printf("P %d is granted to eat\n", pos);
        eating[pos] = 1;
        has_eaten[pos] = 1;

        for(int i = 0; i < n; i++) {
            if(hungry[i] && !has_eaten[i]) {
                if(eating[i]) {
                    printf("P %d is eating\n", i);
                } else {
                    printf("P %d is waiting\n", i);
                }
            } else if(hungry[i] && has_eaten[i] && eating[i]) {
                printf("P %d is eating\n", i);
            }
        }
        eating[pos] = 0;
    }
}

void two(int n, int hungry_cnt, int hungry_pos[]) {
    int eating[n];
    int has_eaten[n];
    for(int i = 0; i < n; i++) {
        eating[i] = 0;
        has_eaten[i] = 0;
    }

    int remaining = hungry_cnt;
    while (remaining > 0) {
        int first = -1, second = -1;
        // Find first hungry philosopher who hasn't eaten
        for (int i = 0; i < hungry_cnt; i++) {
            int pos = hungry_pos[i];
            if (!has_eaten[pos]) {
                first = pos;
                break;
            }
        }
        // Find second hungry philosopher who hasn't eaten and is not adjacent to first
        for (int i = 0; i < hungry_cnt; i++) {
            int pos = hungry_pos[i];
            if (!has_eaten[pos] && pos != first && !(abs(pos - first) == 1 || abs(pos - first) == n - 1)) {
                second = pos;
                break;
            }
        }
        if (first != -1 && second != -1) {
            printf("P %d and P %d are granted to eat\n", first, second);
            eating[first] = 1;
            eating[second] = 1;
            has_eaten[first] = 1;
            has_eaten[second] = 1;
            remaining -= 2;
        } else if (first != -1) {
            printf("P %d is granted to eat\n", first);
            eating[first] = 1;
            has_eaten[first] = 1;
            remaining -= 1;
        }

        for(int i = 0; i < n; i++) {
            int isHungry = 0;
            for(int j = 0; j < hungry_cnt; j++) {
                if(hungry_pos[j] == i) {
                    isHungry = 1;
                    break;
                }
            }
            if(isHungry && !has_eaten[i]) {
                if(eating[i]) {
                    printf("P %d is eating\n", i);
                } else {
                    printf("P %d is waiting\n", i);
                }
            } else if(isHungry && has_eaten[i] && eating[i]) {
                printf("P %d is eating\n", i);
            }
        }

        if (first != -1) eating[first] = 0;
        if (second != -1) eating[second] = 0;
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
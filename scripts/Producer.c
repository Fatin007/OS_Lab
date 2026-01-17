#include <stdio.h>

#define BUFFER_SIZE 10

int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

void producer() {
    if(full == BUFFER_SIZE) {
        printf("Buffer is Full\n");
        return;
    }

    int item;
    printf("Enter the value of your item: ");
    scanf("%d", &item);
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    full++;
    empty--;
}

void consumer() {
    if(empty == BUFFER_SIZE){
        printf("Nothing to consumer\n");
        return;

    }

    int item;
    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    full--;
    empty++;
    printf("The consumed value is %d", item);
 }

int main() {
    int choice;
    while (1) {
        printf("\n1. Produce\t2. Consume\t3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                return;
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
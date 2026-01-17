#include <stdio.h>

#define BUFFER_SIZE 10

int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

void producer() {
    // TODO LIST
    // Check if the buffer is full
    // If full, wait or block until space is available
    // If not full, produce an item and add it to the buffer
    // Mutex lock would be here in a threaded app.
    // Check if the buffer is full
    // If full, wait or block until space is available
    // Update value of in
    if(full == BUFFER_SIZE) {
        printf("Buffer is Full\n");
        return;
    }


    // Create a new item
    int item;
    printf("Enter the value of your item: ");
    scanf("%d", &item);
    buffer[in] = item;
    // printf("Item is %d, Buffer is %d", item, buffer[in]);
    // updating the index for the producer to insert new items
    in = (in + 1) % BUFFER_SIZE;


    // Now we will update the counting semaphores.
    full++;
    empty--;
}

void consumer() {
    // Check if buffer list is empty
    // If empty wait for buffer to be filled by producer but in this case
    // just print to console that buffer is empty and return
    // Now set item variable to buffer[out]
    // update out variable
    // update semaphore variables
    
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
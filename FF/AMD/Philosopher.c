#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int main() {

    int numberOfPhilosophers;
    printf("Enter number of Philosophers: ");
    scanf("%d", &numberOfPhilosophers);
    printf("Enter number of hungry philosophers: ");
    int hungryPhilosophers;
    scanf("%d", &hungryPhilosophers);
    int theHungryIndices[MAX];
    int isEating[MAX];
    memset(isEating, 0, MAX * sizeof(int));
    for(int i = 0; i < hungryPhilosophers; i++){
        printf("Enter Philosopher %d position: ", i + 1);
        scanf("%d", &theHungryIndices[i]);
    }

    printf("1. One can eat\t2. Two can eat\t3. Exit\n");
    int choice;
    scanf("%d", &choice);
    switch(choice){
        case 1:
        for(int i = 0; i < hungryPhilosophers; i++){
            int indexOfCurrentHungryPhilosopher = theHungryIndices[i];
            printf("Philosopher %d is eating.\n", indexOfCurrentHungryPhilosopher);
            for(int j = i + 1; j < hungryPhilosophers; j++){
                printf("Philosopher %d is waiting.\n", theHungryIndices[j]);
            }
        }
        break;
        case 2:
        for(int i = 0; i < hungryPhilosophers; i++){
            int indexOfFirstPhilosopher = theHungryIndices[i];
            isEating[indexOfCurrentHungryPhilosopher] = 1;
            for(int j = i + 1; j < hungryPhilosophers; j++){
                int indexOfSecondPhilosopher = theHungryIndices[j];
                isEating[indexOfSecondPhilosopher] = 1;
                int theFirstRightIndex = (indexOfFirstPhilosopher + 1) % numberOfPhilosophers;
                int theFirstLeftIndex = (indexOfSecondPhilosopher + numberOfPhilosophers - 1) % numberOfPhilosophers;
                int theSecondRightIndex = (indexOfSecondPhilosopher + 1) % numberOfPhilosophers;
                int theSecondLeftIndex = (indexOfSecondPhilosopher + numberOfPhilosophers - 1) % numberOfPhilosophers;
                if(!(isEating[theFirstLeftIndex] && isEating[theFirstRightIndex]) && !(isEating[theSecondLeftIndex] && isEating[theSecondRightIndex])) {
                    
                }
            }
        }
        break;
        case 3:
        break;
    }
}
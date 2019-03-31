//15.03.2019
//Saurabh Singh Gautam
//Sauram
/*

Following is the solution of Sleeping Barber Problem

*/
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#define MAX_CUSTOMERS 20

void *customer(void *num); 
void *barber(void *); 
void randwait(int secs); 

//Define the semaphores. 
sem_t waiting_rm; 
sem_t onChair; 
sem_t onPillow; 
sem_t st_belt;
int cmpt = 0; 

int main(int argc, char *argv[]) 
{
    pthread_t btid; 
    pthread_t tid[MAX_CUSTOMERS]; 
    int i, x, numCustomers, numChairs; int Number[MAX_CUSTOMERS]; 
    printf("The number of customer must be less than 21. Enter the number of customers and chairs for the shop.\n");
    scanf("%d",&x);
    numCustomers = x; 
    scanf("%d",&x);
    numChairs = x;
    if (numCustomers > MAX_CUSTOMERS) { 
       printf("The maximum number of Customers is %d.\n", MAX_CUSTOMERS); 
       system("PAUSE");    
       return 0;
    } 
    printf("This is a solution to the sleeping barber problem using semaphores.\n"); 
    for (i = 0; i < MAX_CUSTOMERS; i++) { 
        Number[i] = i; 
    } 
    sem_init(&waiting_rm, 0, numChairs);       // Initializing the semaphores with initial values.
    sem_init(&onChair, 0, 1);
    sem_init(&onPillow, 0, 0); 
    sem_init(&st_belt, 0, 0); 
    
    pthread_create(&btid, NULL, barber, NULL);    // Creating Barber
    
    for (i = 0; i < numCustomers; i++) {                                       // Creating Customers
        pthread_create(&tid[i], NULL, customer, (void *)&Number[i]); 
    } 
    for (i = 0; i < numCustomers; i++) { 
        pthread_join(tid[i],NULL); 
    } 
    cmpt = 1; 
    sem_post(&onPillow); // Wake barber to make him exit. 
    pthread_join(btid,NULL); 
    system("PAUSE");    
    return 0;
} 

void *customer(void *number) { 
     int num = *(int *)number; 
     printf("Customer %d leaving for barber shop.\n", num); 
     randwait(5); 
     printf("Customer %d arrived at barber shop.\n", num);
     sem_wait(&waiting_rm); 
     printf("Customer %d entering waiting room.\n", num);
     sem_wait(&onChair);
     sem_post(&waiting_rm);
     printf("Customer %d waking the barber.\n", num); 
     sem_post(&onPillow); 
     sem_wait(&st_belt);
     sem_post(&onChair); 
     printf("Customer %d leaving barber shop.\n", num); 
} 

void *barber(void *junk) { 

  while (!cmpt) { 
    printf("The barber is sleeping\n"); 
    sem_wait(&onPillow); 
    if (!cmpt) { 
     printf("The barber is cutting hair\n"); 
     randwait(3);
     printf("The barber has finished cutting hair.\n"); 
     sem_post(&st_belt); 
    } 
    else { 
         printf("The barber is going home for the day.\n"); 
    } 
   }
}
    
void randwait(int secs) { 
     int len = 1; 
     sleep(len); 
}

  

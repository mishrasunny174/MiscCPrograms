#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

bool flag[2] = {false, false};
int turn = 0;
int value;

void *producer(void *params)
{
    while (true)
    {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1)
            ; //busy waiting
        // critical section starts;
        sleep(1);
        value = rand() % 100;
        fprintf(stdout, "producer: %d\n", value);
        //exiting critical section
        flag[0] = false;
    }
}

void *consumer(void *params)
{
    while (true)
    {
        flag[1] = true;
        turn = 0;
        while (flag[1] && turn == 0)
            ; //busy waiting
        // critical section starts;
        sleep(1);
        fprintf(stdout, "consumer: %d\n", value);
        //exiting critical section
        flag[1] = false;
    }
}

int main()
{
    srand(time(0));
    pthread_t t1, t2;
    pthread_attr_t attr1, attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_create(&t1, &attr1, producer, NULL);
    pthread_create(&t2, &attr2, consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

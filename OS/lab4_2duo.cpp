#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x, y;

void *threadFunction1(void *selector);
void *threadFunction2(void *selector);
void *threadFunction3(void *selector);

int main(void)
{
	pthread_t tid1, tid2, tid3;			// Thread ID
	pthread_attr_t attr1, attr2, attr3; // Thread attributes
										// int section1=0,section2=1;

	pthread_attr_init(&attr1); // Get default attributes
	pthread_attr_init(&attr2); // Get default attributes
	pthread_attr_init(&attr3);

	// Create 3 threads
	pthread_create(&tid1, &attr1, threadFunction1, NULL);
	pthread_create(&tid2, &attr2, threadFunction2, NULL);
	pthread_create(&tid3, &attr3, threadFunction3, NULL);

	// Wait until all threads finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	return 0;
}

void *threadFunction1(void *selector)
{
	while (1)
	{
		printf("Thread A, Input First: ");
		scanf("%d", &x);
		if (x < 0)
			break;
		printf("Thread A, Input Second: ");
		scanf("%d", &y);
	}
	return (NULL);
}

void *threadFunction2(void *selector)
{
	while (1)
	{
		sleep(3);
		if (x < 0)
			pthread_exit(0);
		printf("\nThread B, value: %d\n", x);
	}
}

void *threadFunction3(void *selector)
{
	while (1)
	{
		sleep(3);
		if (x < 0)
			pthread_exit(0);
		printf("\nThread C, value: %d\n", y);
	}
}

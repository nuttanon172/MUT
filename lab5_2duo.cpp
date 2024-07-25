#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int x, y;
pthread_mutex_t mutex_x;
pthread_mutex_t mutex_y;

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
	pthread_mutex_init(&mutex_x, NULL); // Init mutex for x
	pthread_mutex_init(&mutex_y, NULL); // Init mutex for y

	// Create 3 threads
	pthread_create(&tid1, &attr1, threadFunction1, NULL);
	pthread_create(&tid2, &attr2, threadFunction2, NULL);
	pthread_create(&tid3, &attr3, threadFunction3, NULL);

	// Wait until all threads finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_mutex_destroy(&mutex_x);
	pthread_mutex_destroy(&mutex_y);
	return 0;
}

bool xneg(int *x)
{
	pthread_mutex_lock(&mutex_x);
	if (*x < 0)
		return (pthread_mutex_unlock(&mutex_x), true);
	return (pthread_mutex_unlock(&mutex_x), false);
}

void *threadFunction1(void *selector)
{
	int tmp_x, tmp_y;
	while (1)
	{
		// First Input
		printf("Thread A, First Input: ");
		scanf("%d", &tmp_x);
		pthread_mutex_lock(&mutex_x); // lock for write x
		x = tmp_x;
		pthread_mutex_unlock(&mutex_x); // unlock
		if (x < 0)
			break;
		// Second Input
		printf("Thread A, Second Input: ");
		scanf("%d", &tmp_y);
		pthread_mutex_lock(&mutex_y); // lock for write y
		y = tmp_y;
		pthread_mutex_unlock(&mutex_y); // unlock
	}
	return (NULL);
}

void *threadFunction2(void *selector)
{
	while (1)
	{
		sleep(3);
		if (xneg(&x))
			pthread_exit(0);
		pthread_mutex_lock(&mutex_x); // lock for read x
		printf("\nThread B, value: %d\n", x);
		pthread_mutex_unlock(&mutex_x); // unlock
	}
}

void *threadFunction3(void *selector)
{
	while (1)
	{
		sleep(3);
		if (xneg(&x))
			pthread_exit(0);
		pthread_mutex_lock(&mutex_y); // lock for read y
		printf("\nThread C, value: %d\n", y);
		pthread_mutex_unlock(&mutex_y); // unlock
	}
}



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <wait.h>   // for wait()
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <wait.h>   // for wait()
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

struct shmareatype
{
    int x;
    int y;
};

void consumer(struct shmareatype *shmarea);
void consumer2(struct shmareatype *shmarea);
void producer(struct shmareatype *shmarea);

int main()
{
    pid_t pid1;
    pid_t pid2;
    int shmid;                   // Share memory ID
    struct shmareatype *shmarea; // Pointer to the shared segment
    int shmsize;                 // share segment size

    shmsize = sizeof(struct shmareatype);
    // Allocate the shared block from OS
    shmid = shmget(IPC_PRIVATE, shmsize, 0666 | IPC_CREAT); // return Id of shared memory

    // Attach the shared block to the pointer so we can use it.
    shmarea = (struct shmareatype *)shmat(shmid, NULL, 0);
    pid1 = fork(); // Fork a child process
    if (pid1 < 0)
    { // Fork error
        fprintf(stderr, "Fork failed.\n");
        exit(-1);
    }
    else if (pid1 == 0)
    { // This is the path of child process
        // printf("Process B!!\n");
        consumer(shmarea);
        exit(0);
        // execlp("/usr/bin/ls","ls",NULL); // call a text editor
    }
    else
    { // This is the path of parent process
        pid2 = fork();
        if (pid2 == 0)
        { // This is the path of child process
            // printf("Process C!!\n");
            consumer2(shmarea);
            exit(0);
            // execlp("/usr/bin/ls","ls",NULL); // call a text editor
        }
        // printf("Process A!!\n");
        producer(shmarea);
        // printf("Before going into the wait  state...\n");
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        printf("Child process has terminated\n");
        // execlp("/usr/bin/ls","ls",NULL);
        exit(0);
    }
}

void consumer(struct shmareatype *shmarea)
{
    while (1) // consume data for 16 times
    {
        sleep(10);
        // printf("shmarea->x = %d\n", shmarea->x);
        //  Wait 2 minutes if no data in the circular buffer
        // printf("x = %d\n", shmarea->x);
        if (shmarea->x < 0)
            break;
        printf("\nProcess B Data:%d\n", shmarea->x);
    }
}

void consumer2(struct shmareatype *shmarea)
{
    while (1) // consume data for 16 times
    {
        sleep(10);
        // printf("y = %d\n", shmarea->y);
        if (shmarea->x < 0)
            break;
        printf("\nProcess C Data:%d\n", shmarea->y);
    }
}

void producer(struct shmareatype *shmarea)
{
    char temp[20];

    while (1) // produce data for 16 times
    {
        printf("Process A: Please enter a character No 1 :");
        scanf("%d", &(shmarea->x)); // read data from keyboard
        if (shmarea->x < 0)
            break;
        printf("Process A: Please enter a character No 2 :");
        scanf("%d", &(shmarea->y)); // read data from keyboard
                                    // move the write pointer so that the consumer know when to read.
        sleep(10);
    }
}

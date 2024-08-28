#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // for exit()
#include <wait.h>   // for wait()

int main()
{
    pid_t pid1;
    pid_t pid2;

    pid1 = fork(); // Fork a child process

    if (pid1 < 0)
    { // Fork error
        fprintf(stderr, "Fork failed.\n");
        exit(-1);
    }
    else if (pid1 == 0)
    { // This is the path of child process
        printf("Process B!!\n");
        sleep(10);
        exit(0);
        // execlp("/usr/bin/ls","ls",NULL); // call a text editor
    }
    else
    { // This is the path of parent process
        pid2 = fork();
        if (pid2 == 0)
        { // This is the path of child process
            printf("Process C!!\n");
            sleep(10);
            exit(0);
            // execlp("/usr/bin/ls","ls",NULL); // call a text editor
        }
        printf("Process A!!\n");
        // printf("Before going into the wait  state...\n");
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        printf("Child process has terminated\n");
        // execlp("/usr/bin/ls","ls",NULL);
        exit(0);
    }
}

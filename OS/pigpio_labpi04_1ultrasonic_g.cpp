#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int ledGPIO[4] = {4, 5, 6, 12};
int runningSpeed = 5;
int trig = 19;
int echo = 20;

int keyGPIO_row[4] = {21, 22, 23, 24};
int keyGPIO_col[3] = {25, 26, 27};
int keyMap[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
int running = 1;

int getch();
void initGPIO();
int ultraSonic();
void *runningLED(void *param);
void *getKey(void *param);
void *caluls(void *param);

void gpio_stop(int sig)
{
    printf("User pressing CTRL-C");
    running = 0;
    gpioTerminate();
    exit(0);
}

int main()
{
    int ch;
    initGPIO();
    signal(SIGINT, gpio_stop);

    pthread_t tid[3];
    pthread_attr_t attr[3];
    void *(*thread[3])(void *) = {runningLED, getKey, caluls};
    int i;

    for (i = 0; i < 3; i++)
    {
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i], &attr[i], thread[i], NULL);
    }
    printf("Waiting all threads to stop...\n");
    for (i = 0; i < 3; i++)
    {
        pthread_join(tid[i], NULL);
    }
    for (i = 0; i < 3; i++)
    {
        pthread_attr_destroy(&attr[i]);
    }
    gpioTerminate();
    return 0;
}

void initGPIO()
{
    int i;

    if (gpioInitialise() < 0)
        exit(1);
    for (i = 0; i < 4; i++)
    {
        gpioSetMode(keyGPIO_row[i], PI_OUTPUT);
        gpioWrite(keyGPIO_row[i], 1);
    }
    for (i = 0; i < 3; i++)
    {
        gpioSetMode(keyGPIO_col[i], PI_INPUT);
        gpioSetPullUpDown(keyGPIO_col[i], PI_PUD_UP);
    }
    gpioSetMode(trig, PI_OUTPUT);
    gpioWrite(trig, 0);
    gpioSetMode(echo, PI_INPUT);
    gpioSetPullUpDown(echo, PI_PUD_OFF);
}

void *runningLED(void *param)
{
    int i, j;
    int pattern[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    while (running)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
                gpioWrite(ledGPIO[j], pattern[i][j]);
            usleep(runningSpeed * 20000);
        }
        if (runningSpeed > 9)
            break;
    }
    pthread_exit(0);
}

int getch()
{
    int row, col;
    while (running)
    {
        for (row = 0; row < 4; row++)
        {
            gpioWrite(keyGPIO_row[row], 0);
            for (col = 0; col < 3; col++)
            {
                if (gpioRead(keyGPIO_col[col]) == 0)
                    break;
            }
            if (col < 3)
                break; // key pressing detected
            gpioWrite(keyGPIO_row[row], 1);
        }
        if (row < 4)
        {
            while (gpioRead(keyGPIO_col[col]) == 0)
                usleep(100000);
            gpioWrite(keyGPIO_row[row], 1);
            return keyMap[row][col];
        }

        // usleep(100000);
    }
}

void *getKey(void *param)
{
    while (running)
    {
        printf("Please enter speed (1 upto 9 or 10 to stop program):");
        fflush(stdout);
        runningSpeed = getch();
        runningSpeed -= 0x30;
        printf("\nKey = %d\n", runningSpeed);
        if (runningSpeed == '#')
            break;
        // scanf("%d",&runningSpeed);
        if ((runningSpeed > 9) || (runningSpeed < 1))
            break;
    }
    pthread_exit(0);
}

void *caluls(void *param)
{
    int freq;
    int freqArr[9] = {167, 443, 702, 841, 1097, 1306, 1416, 1507, 1772};
    while (running)
    {
        freq = ultraSonic();
        if (freq > freqArr[8])
            continue;
        for (int i = 1; i <= 9; i++)
        {
            if (freq <= freqArr[i - 1])
            {
                runningSpeed = i;
                break;
            }
        }
        printf("ultrasonic = %d\n", freq);
        printf("runningSpeed = %d\n", runningSpeed);
        sleep(1);
    }
}

int ultraSonic()
{
    int clock1, clock2, timeout;

    gpioWrite(trig, 1);
    usleep(10);
    gpioWrite(trig, 0);
    for (timeout = 0; (timeout < 100000) && (gpioRead(echo) == 0); timeout++)
        usleep(10);
    clock1 = clock();
    for (timeout = 0; (timeout < 100000) && (gpioRead(echo) == 1); timeout++)
        usleep(10);
    clock2 = clock();
    return clock2 - clock1;
}

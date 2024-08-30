#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int keyGPIO_row[4] = {21, 22, 23, 24};
int keyGPIO_col[3] = {25, 26, 27};
int keyMap[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
int running = 1;

void initGPIO();
int getch();

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
    while (running)
    {
        printf("Please press a key on keypad:");
        fflush(stdout);
        ch = getch();
        printf("\nKey = %c\n", ch);
        if (ch == '#' || ch == '*')
            break;
        runningLED(ch - '0');
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
        usleep(100000);
    }
}

void runningLED(int speed){
    int i,j;
    int pattern[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    if (speed < 0 || speed > 9)
        return ;
    while(running){
        for(i=0;i<4;i++){
            for(j=0;j<4;j++)
                gpioWrite(ledGPIO[j],pattern[i][j]);
            usleep(speed*20000);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t p;
    p = fork();
    if (p < 0)
    {
        printf("fork failed");
        exit(1);
    }
    else
    {
        if (p == 0)
        {
            exit(0);
        }
        else
        {
            sleep(10);
            printf("parent is not going");
        }
    }
}
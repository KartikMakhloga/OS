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
            sleep(20);
            printf("CHILD pid = %d", getpid());
        }
        else
        {
            sleep(2);
            printf("parent pid = %d", getpid());
        }
    }
}
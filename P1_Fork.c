#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("process pid = %d\n", getpid());
    fork();
    printf("process pid = %d\n", getpid());
}
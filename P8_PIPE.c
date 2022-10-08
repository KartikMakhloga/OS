#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 30

int main()
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    int p = fork();
    if (p < 0)
    {
        printf("fork failed");
        exit(1);
    }
    if (p > 0)
    {
        close(fd1[0]);
        close(fd2[1]);
        char buff[SIZE];
        memset(buff, '\0', SIZE);
        char *msg = "hi child how are you";
        write(fd1[1], msg, strlen(msg));
        read(fd2[0], buff, SIZE);
        printf("Answer from child = %s", buff);
        close(fd1[1]);
        close(fd2[0]);
        wait(NULL);
    }
    else
    {
        close(fd2[0]);
        close(fd1[1]);
        char buff[SIZE];
        memset(buff, '\0', SIZE);
        int rd = read(fd1[0], buff, SIZE);
        printf("parent ques = %s", buff);
        write(fd2[1], "i am good\n", SIZE);
        close(fd2[1]);
        close(fd1[0]);
    }
}
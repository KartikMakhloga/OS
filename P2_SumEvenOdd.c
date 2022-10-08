#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int n, i = 0, sum = 0;
    printf("Enter the size of an array");
    scanf("%d", &n);
    int arr[n];
    printf("Entry the value of array");
    for (int j = 0; j < n; j++)
    {
        scanf("%d", &arr[j]);
    }
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
            while (i < n)
            {
                if (arr[i] % 2 != 0)
                {
                    printf("%d + ", arr[i]);
                    sum += arr[i];
                }
                i++;
            }
            printf("= %d\n", sum);
        }
        else
        {
            wait(NULL);
            while (i < n)
            {
                if (arr[i] % 2 == 0)
                {
                    printf("%d + ", arr[i]);
                    sum += arr[i];
                }
                i++;
            }
            printf("= %d\n", sum);
        }
    }
}
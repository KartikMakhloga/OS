#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct process_struct
{
    int pid, p, at, bt, ct, wt, tat, rt, start_time;
} ps[100];

int findmax(int a, int b)
{
    return a > b ? a : b;
}
int findmin(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int n, current_time = 0, completed = 0;
    float bt_remaining[100];
    bool is_complete[100] = {false}, is_first_process = true;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0, length_cycle, total_idle_time = 0, prev = 0;
    float cpu_uti;
    int max_completion_time, min_arrival_time;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &ps[i].bt);
        bt_remaining[i] = ps[i].bt;
    }

    while (completed != n)
    {
        int max_index = -1;
        int maximum = -1;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_complete[i] == false)
            {
                if (ps[i].p > maximum)
                {
                    maximum = ps[i].p;
                    max_index = i;
                }
                if (ps[i].p == maximum)
                {
                    if (ps[i].at < ps[max_index].at)
                    {
                        maximum = ps[i].p;
                        max_index = i;
                    }
                }
            }
        }
        if (max_index == -1)
            current_time++;
        else
        {
            if (bt_remaining[max_index] == ps[max_index].bt)
            {
                ps[max_index].start_time = current_time;
                total_idle_time += (is_first_process == true) ? 0 : (ps[max_index].start_time - prev);
                is_first_process = false;
            }
            bt_remaining[max_index] -= 1;
            current_time++;
            prev = current_time;
            if (bt_remaining[max_index] == 0)
            {
                ps[max_index].ct = current_time;
                ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
                ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
                ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;
                sum_tat += ps[max_index].tat;
                sum_wt += ps[max_index].wt;
                sum_rt += ps[max_index].rt;
                completed++;
                is_complete[max_index] = true;
            }
        }
    }

    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int max_arrival_time = findmax(max_completion_time, ps[i].ct);
        min_arrival_time = findmin(min_arrival_time, ps[i].at);
    }

    length_cycle = max_completion_time - min_arrival_time;

    printf("\nProcess NO.\tAT\tCPU Burst Time\tCT\tAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
    printf("\n");
    cpu_uti = (float)(length_cycle - total_idle_time) / length_cycle;
    printf("\nAverage Turn Around Time = %f", sum_tat / n);
    printf("\nAverage Waiting Time = %f", sum_wt / n);
    printf("\nAverage Response Time = %f", sum_rt / n);
    printf("\nThroughput = %f", n / (float)length_cycle);
    printf("\nCPU Utilization(Percentage) = %f", cpu_uti * 100);
    printf("\n");
    return 0;
}
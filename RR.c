#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#define TIME_QUANTUM 5


typedef struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
} process;

void RoundRobin(process processes[], int n)
{
    int time = 1;
    int remaining = n;
    bool noprocready = false;
    
    while (remaining > 0)
    {
        noprocready = false;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) // process already arrived and not finished
            {
                noprocready = true;
                if (processes[i].start_time == 0)
                {
                    processes[i].start_time = time;
                    processes[i].response_time = time - processes[i].arrival_time;
                }

                if (processes[i].remaining_time > TIME_QUANTUM) // not done yet
                {
                    time += TIME_QUANTUM;
                    processes[i].remaining_time -= TIME_QUANTUM;
                }
                else // done
                {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].burst_time - processes[i].arrival_time;
                    processes[i].turnaround_time = time - processes[i].arrival_time;
                    processes[i].remaining_time = 0;
                    remaining = remaining - 1;
                }

            }
            if (noprocready == false)
            {
                time += 1;
            }
        }
    }
}

int main()
{
    int n; // n is number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    process processes[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        processes[i].burst_time = rand() % 20 + 1; // random burst time between 1 and 20
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].arrival_time = rand() % 50; // random arrival between 0 and 9
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = -1;
        processes[i].start_time = 0;
    }

    RoundRobin(processes, n);

    printf("Process ID \t Burst \t\t Remaining \t Arrival \t Start \t\t Turnaround \t Waiting \t Response \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
        processes[i].pid,
        processes[i].burst_time,
        processes[i].remaining_time,
        processes[i].arrival_time,
        processes[i].start_time,
        processes[i].turnaround_time,
        processes[i].waiting_time,
        processes[i].response_time);
        
    }
    return 0;
}
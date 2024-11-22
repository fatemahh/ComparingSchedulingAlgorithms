#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct process {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int start_time;
    bool finished;
} process;

void ShortestJobFirst(process processes[], int n)
{
    // sort processes by arrival time and burst time
    process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if ((processes[j].arrival_time > processes[j+1].arrival_time) || 
            (processes[j].arrival_time == processes[j+1].arrival_time && 
            processes[j].burst_time > processes[j+1].burst_time) ) {
                temp = processes[j];
                processes[j] = processes[j+1];
                processes[j+1] = temp;
            }
        }
    }
    
    int ctime = 0;
    int remaining = n;

    while (remaining > 0)
    {
        int min_time = __INT_MAX__;
        int shortest = -1;

        // find process in ready queue with shortest burst time
        for (int i = 0; i < n; i++)
        {
            if (!processes[i].finished && processes[i].arrival_time <= ctime) {
                if (processes[i].burst_time < min_time) {
                    min_time = processes[i].burst_time;
                    shortest = i;
                }
            }        
        
        }

        // no process
        if (shortest == -1) {
            ctime++;
            continue;
        }

        // process the shortest job
        processes[shortest].start_time = ctime;
        processes[shortest].waiting_time = ctime - processes[shortest].arrival_time;
        processes[shortest].response_time = processes[shortest].waiting_time;
        ctime += processes[shortest].burst_time;
        processes[shortest].turnaround_time = ctime - processes[shortest].arrival_time;
        processes[shortest].finished = true;
        remaining = remaining - 1;
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
        processes[i].finished = false;
    }

    ShortestJobFirst(processes, n);

    printf("Shortest Job First Schedule \n");
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
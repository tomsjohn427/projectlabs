#include <stdio.h>

int main() {
    int n, i;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n], waiting_time[n], turnaround_time[n], completion_time[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d (Arrival Time Burst Time): ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    // Calculate completion time for each process
    completion_time[0] = arrival_time[0] + burst_time[0];
    for (i = 1; i < n; i++) {
        if (arrival_time[i] > completion_time[i - 1])
            completion_time[i] = arrival_time[i] + burst_time[i];
        else
            completion_time[i] = completion_time[i - 1] + burst_time[i];
    }

    // Calculate waiting time for each process
    for (i = 0; i < n; i++) {
        waiting_time[i] = completion_time[i] - arrival_time[i] - burst_time[i];
        avg_waiting_time += waiting_time[i];
    }

    // Calculate turnaround time for each process
    for (i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        avg_turnaround_time += turnaround_time[i];
    }

    // Calculate averages
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    // Print results
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

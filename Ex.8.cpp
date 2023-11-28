#include <stdio.h>

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    
    int burst_time[n], remaining_time[n], waiting_time = 0, turnaround_time = 0;
    
    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
    }
    
    // Simulate Round Robin scheduling
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int time = 0;
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;
                if (remaining_time[i] > time_quantum) {
                    time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time += time - burst_time[i];
                    remaining_time[i] = 0;
                    printf("P%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], time - burst_time[i], time);
                    turnaround_time += time - burst_time[i];
                }
            }
        }
        if (done == 1) {
            break;
        }
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)turnaround_time / n);
    
    return 0;
}

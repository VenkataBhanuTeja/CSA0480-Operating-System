#include <stdio.h>

struct process {
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int total_time;
};

void calculate_sjf_scheduling(struct process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrival_time < processes[i].arrival_time) {
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].arrival_time - processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        processes[i].total_time = processes[i].turnaround_time + processes[i].waiting_time;
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and turnaround time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].turnaround_time);
    }

    calculate_sjf_scheduling(processes, n);

    return 0;
}

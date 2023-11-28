#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int arrival_time;
};

void sort(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n, time = 0, total_waiting_time = 0, total_turnaround_time = 0, completed = 0;
    float average_waiting_time, average_turnaround_time;
    struct process p[20], temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
    }

    sort(p, n);

    printf("\nGantt Chart:\n");
    printf("0");
    while (completed != n) {
        int highest_priority = -1, index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].remaining_time > 0 && p[i].priority > highest_priority) {
                highest_priority = p[i].priority;
                index = i;
            }
        }
        if (index == -1) {
            time++;
            continue;
        }
        p[index].remaining_time--;
        printf(" -> [P%d] <- %d", p[index].pid, time + 1);
        if (p[index].remaining_time == 0) {
            completed++;
            p[index].turnaround_time = time + 1 - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            total_waiting_time += p[index].waiting_time;
            total_turnaround_time += p[index].turnaround_time;
        }
        time++;
    }

    average_waiting_time = (float) total_waiting_time / n;
    average_turnaround_time = (float) total_turnaround_time / n;

    printf("\n\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}

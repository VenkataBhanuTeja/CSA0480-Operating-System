#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

bool isSafe(int process) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        if (need[process][i] > available[i])
            return false;
    }
    return true;
}

void allocateResources(int process) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        available[i] -= allocation[process][i];
        allocation[process][i] = 0;
    }
}

void releaseResources(int process) {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        available[i] += max[process][i];
    }
}

int main() {
    printf("Enter the number of resources: ");
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        for (int j = 0; j < MAX_RESOURCES; ++j) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Run Banker's algorithm
    int numCompleted = 0;
    bool deadlockDetected = false;

    while (numCompleted < MAX_PROCESSES) {
        bool canAllocate = false;

        for (int i = 0; i < MAX_PROCESSES; ++i) {
            if (!finished[i] && isSafe(i)) {
                allocateResources(i);
                printf("Process %d allocated resources.\n", i);
                finished[i] = true;
                numCompleted++;
                canAllocate = true;
                break;
            }
        }

        if (!canAllocate) {
            deadlockDetected = true;
            break;
        }
    }

    if (deadlockDetected) {
        printf("Deadlock detected.\n");
    } else {
        printf("All processes completed safely.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define NUM_BLOCKS 5
#define NUM_REQUESTS 10

struct Block {
    int size;
    int allocated;
};

struct Request {
    int size;
};

void firstFit(struct Block blocks[], struct Request requests[]) {
    for (int i = 0; i < NUM_REQUESTS; ++i) {
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (blocks[j].allocated == 0 && blocks[j].size >= requests[i].size) {
                blocks[j].allocated = 1;
                printf("Request %d of size %d is allocated to block %d\n", i + 1, requests[i].size, j + 1);
                break;
            }
        }
    }
}

void bestFit(struct Block blocks[], struct Request requests[]) {
    for (int i = 0; i < NUM_REQUESTS; ++i) {
        int bestBlock = -1;
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (blocks[j].allocated == 0 && blocks[j].size >= requests[i].size) {
                if (bestBlock == -1 || blocks[j].size < blocks[bestBlock].size) {
                    bestBlock = j;
                }
            }
        }
        if (bestBlock != -1) {
            blocks[bestBlock].allocated = 1;
            printf("Request %d of size %d is allocated to block %d\n", i + 1, requests[i].size, bestBlock + 1);
        }
    }
}

void worstFit(struct Block blocks[], struct Request requests[]) {
    for (int i = 0; i < NUM_REQUESTS; ++i) {
        int worstBlock = -1;
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (blocks[j].allocated == 0 && blocks[j].size >= requests[i].size) {
                if (worstBlock == -1 || blocks[j].size > blocks[worstBlock].size) {
                    worstBlock = j;
                }
            }
        }
        if (worstBlock != -1) {
            blocks[worstBlock].allocated = 1;
            printf("Request %d of size %d is allocated to block %d\n", i + 1, requests[i].size, worstBlock + 1);
        }
    }
}

int main() {
    struct Block blocks[NUM_BLOCKS] = {
        {100, 0}, {200, 0}, {300, 0}, {400, 0}, {500, 0}
    };

    struct Request requests[NUM_REQUESTS] = {
        {50}, {200}, {75}, {300}, {100}, {250}, {150}, {100}, {200}, {50}
    };

    printf("First Fit:\n");
    firstFit(blocks, requests);

    for (int i = 0; i < NUM_BLOCKS; ++i) {
        blocks[i].allocated = 0;
    }

    printf("\nBest Fit:\n");
    bestFit(blocks, requests);

    for (int i = 0; i < NUM_BLOCKS; ++i) {
        blocks[i].allocated = 0;
    }

    printf("\nWorst Fit:\n");
    worstFit(blocks, requests);

    return 0;
}

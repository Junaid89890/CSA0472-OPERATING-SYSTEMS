#include <stdio.h>
#define MAX_BLOCKS 10
void bestFit(int block_size[], int m, int process_size[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;
    for (int i = 0; i < n; i++) {
        int best_fit_index = -1;
        for (int j = 0; j < m; j++) {
            if (block_size[j] >= process_size[i]) {
                if (best_fit_index == -1 || block_size[j] < block_size[best_fit_index]) {
                    best_fit_index = j;
                }
            }
        }
        if (best_fit_index != -1) {
            allocation[i] = best_fit_index;
            block_size[best_fit_index] -= process_size[i];
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d \t\t%d \t\t", i + 1, process_size[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}
int main() {
    int m, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int block_size[MAX_BLOCKS];
    int process_size[MAX_BLOCKS];
    printf("\nEnter the size of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block_size[i]);
    }
    printf("\nEnter the size of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &process_size[i]);
    }
    bestFit(block_size, m, process_size, n);
    return 0;
}

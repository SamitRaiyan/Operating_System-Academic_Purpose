#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], allocation[n][m], need[n][m], available[m];

    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d", &allocation[i][j]);

    // Input Maximum Matrix
    printf("Enter Maximum Matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d", &max[i][j]);

    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int i=0;i<m;i++)
        scanf("%d", &available[i]);

    // Calculate Need Matrix
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max[i][j] - allocation[i][j];

    bool finish[n];
    for(int i=0;i<n;i++) finish[i]=false;

    int safeSeq[n], count=0;

    while(count < n) {
        bool found = false;
        for(int i=0;i<n;i++) {
            if(!finish[i]) {
                bool canAllocate = true;
                for(int j=0;j<m;j++) {
                    if(need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if(canAllocate) {
                    for(int j=0;j<m;j++)
                        available[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if(!found) break; // No safe process found
    }

    // Check if system is in safe state
    bool safe = true;
    for(int i=0;i<n;i++)
        if(!finish[i]) safe=false;

    if(safe) {
        printf("System is in SAFE state.\nSafe sequence is: ");
        for(int i=0;i<n;i++)
            printf("P%d ", safeSeq[i]);
        printf("\n");
    } else {
        printf("System is in UNSAFE state! Deadlock possible.\n");
    }

    return 0;
}
// Banker's Algorithm in C
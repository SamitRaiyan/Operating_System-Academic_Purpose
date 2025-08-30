// First Come First Serve (FCFS) Scheduling
#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, tat, wt;
    // pid = Process ID
    // at  = Arrival Time
    // bt  = Burst Time
    // ct  = Completion Time
    // tat = Turnaround Time
    // wt  = Waiting Time
};

// Line printing function (void pline(int x))
void pline(int x) {
    int i;
    for(i = 0; i < x; i++) printf("-");
    printf("\n");
}

int main() {
    int num, i, j, time = 0;  // num = Total number of processes.
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &num);

    struct pcb p[num+1], temp;  // The temp variable is use for sorting. 

   

    // Input AT and BT
    for(i = 0; i < num; i++) {
        printf("Enter Arrival Time and Burst Time of Process %d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i+1;
    }

    // Sort by Arrival Time
    for(i = 0; i < num-1; i++) {
        for(j = 0; j < num-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Calculate CT, TAT, WT
    time = p[0].at;
    for(i = 0; i < num; i++) {
        if(time < p[i].at)  // যদি CPU idle থাকে
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at; // TAT = CT - AT
        p[i].wt  = p[i].tat - p[i].bt; // WT = TAT - BT

        avg_tat += p[i].tat;
        avg_wt  += p[i].wt;
    }

    // Output
    pline(60);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    pline(60);
    for(i = 0; i < num; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    pline(60);

    printf("Average Turnaround Time = %.2f\n", avg_tat/num);
    printf("Average Waiting Time = %.2f\n", avg_wt/num);

    return 0;
}

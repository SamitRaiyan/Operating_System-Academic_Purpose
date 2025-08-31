// Shortest Job First (Preemptive - SRTF) Scheduling
#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, tat, wt, rt; 
    // pid = Process ID
    // at  = Arrival Time
    // bt  = Burst Time
    // ct  = Completion Time
    // tat = Turnaround Time
    // wt  = Waiting Time
    // rt = Remaining Time (need er for SRTF)
};

// Line printing function (void pline(int x))
void pline(int x) {
    int i;
    for(i = 0; i < x; i++){ 
        printf("-");
    }
    printf("\n");
}

int main(){
    int NoP,i,j,time = 0, completed = 0, min_index;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d",&NoP);
    struct pcb p[NoP];

    // Input AT and BT
    for(i = 0; i < NoP; i++) {
        printf("Enter Arrival Time and Burst Time of Process %d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i+1;
        p[i].rt = p[i].bt; // Initially remaining time = burst time
    }

    // SJF Preemptive Execution
    int is_completed[NoP];
    for(i = 0; i < NoP; i++) is_completed[i] = 0;

    time = 0;
    while(completed != NoP) {
        min_index = -1;
        int min_rt = 1e9; // a very large value

        // To get the shortest job from the ready queue
        for(i = 0; i < NoP; i++) {
            if(p[i].at <= time && is_completed[i] == 0) {
                if(p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    min_index = i;
                }
                else if(p[i].rt == min_rt) {
                    // if burst time same then check shortest arrival time to pick
                    if(p[i].at < p[min_index].at) {
                        min_index = i;
                    }
                }
            }
        }

        if(min_index == -1) {
            time++; // CPU idle
        }
        else {
            p[min_index].rt--; // 1 unit execute
            time++;

            if(p[min_index].rt == 0) {
                p[min_index].ct = time; // Completion time
                p[min_index].tat = p[min_index].ct - p[min_index].at; // TAT = CT - AT
                p[min_index].wt  = p[min_index].tat - p[min_index].bt; // WT = TAT - BT

                avg_tat += p[min_index].tat;
                avg_wt  += p[min_index].wt;

                is_completed[min_index] = 1;
                completed++;
            }
        }
    }
//  To sort the processes by completion time
    for(i = 0; i < NoP-1; i++) {
        for(j = i+1; j < NoP; j++) {
            if(p[i].ct > p[j].ct) {
                struct pcb temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Output
    pline(60);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    pline(60);
    for(i = 0; i < NoP; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    pline(60);

    printf("Average Turnaround Time = %.2f\n", avg_tat/NoP);
    printf("Average Waiting Time = %.2f\n", avg_wt/NoP);

    return 0;
}
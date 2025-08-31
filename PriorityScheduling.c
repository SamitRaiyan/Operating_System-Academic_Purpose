// Priority Scheduling (Preemptive) 
// less priority means higher importance    
#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, tat, wt, rt, pr;  
    // pid = Process ID
    // at  = Arrival Time
    // bt  = Burst Time
    // ct  = Completion Time
    // tat = Turnaround Time
    // wt  = Waiting Time
    // rt  = Remaining Time (for execution)
    // pr  = Priority (lower value = higher priority)
};

// Line printing function
void pline(int x) {
    for(int i = 0; i < x; i++) printf("-");
    printf("\n");
}

int main(){
    int NoP,i,j,time = 0, completed = 0, min_index;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d",&NoP);
    struct pcb p[NoP];

    // Input AT, BT, Priority
    for(i = 0; i < NoP; i++) {
        printf("Enter Arrival Time, Burst Time and Priority of Process %d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].pid = i+1;
        p[i].rt = p[i].bt; // Initially remaining time = burst time
    }

    int is_completed[NoP];
    for(i = 0; i < NoP; i++) is_completed[i] = 0;

    time = 0;
    while(completed != NoP) {
        min_index = -1;
        int min_pr = 1e9; // a very large value

        // To get the highest priority process from the ready queue
        for(i = 0; i < NoP; i++) {
            if(p[i].at <= time && is_completed[i] == 0) {
                if(p[i].pr < min_pr) {  
                    min_pr = p[i].pr;
                    min_index = i;
                }
                else if(p[i].pr == min_pr) {
                    // if priority same then check shortest arrival time to pick
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
                p[min_index].tat = p[min_index].ct - p[min_index].at; 
                p[min_index].wt  = p[min_index].tat - p[min_index].bt; 

                avg_tat += p[min_index].tat;
                avg_wt  += p[min_index].wt;

                is_completed[min_index] = 1;
                completed++;
            }
        }
    }

    // Sort by Completion time
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
    pline(70);
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    pline(70);
    for(i = 0; i < NoP; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }
    pline(70);

    printf("Average Turnaround Time = %.2f\n", avg_tat/NoP);
    printf("Average Waiting Time = %.2f\n", avg_wt/NoP);

    return 0;
}

// Round Robin (Preemptive) Scheduling
#include <stdio.h>

struct pcb {
    int pid, at, bt, ct, tat, wt, rt;
    // pid = Process ID
    // at  = Arrival Time
    // bt  = Burst Time
    // ct  = Completion Time
    // tat = Turnaround Time
    // wt  = Waiting Time
    // rt  = Remaining Time
};

// Line printing function
void pline(int x) {
    for(int i = 0; i < x; i++) printf("-");
    printf("\n");
}

int main() {
    int NoP, i, time = 0, completed = 0, tq;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &NoP);
    struct pcb p[NoP];

    // Input AT and BT
    for(i = 0; i < NoP; i++) {
        printf("Enter Arrival Time and Burst Time of Process %d: ", i+1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].pid = i+1;
        p[i].rt = p[i].bt; // remaining time = burst time
    }

    // Input Time Quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Round Robin execution
    int is_completed[NoP];
    for(i = 0; i < NoP; i++) is_completed[i] = 0;

    int queue[1000]; // simple queue array
    int front = 0, rear = 0;

    // Initially add the arriving processes to the queue
    int visited[NoP];
    for(i = 0; i < NoP; i++) visited[i] = 0;

    queue[rear++] = 0; // enqueue the first process
    visited[0] = 1;
    time = p[0].at;

    while(completed != NoP) {
        if(front == rear) { // if queue is empty (idle time), find next process that has not arrived yet
            int min_at = 1e9, index = -1;
            for(i = 0; i < NoP; i++) {
                if(!is_completed[i] && p[i].at < min_at) {
                    min_at = p[i].at;
                    index = i;
                }
            }
            time = p[index].at;
            queue[rear++] = index;
            visited[index] = 1;
        }

        int idx = queue[front++];
        
        if(p[idx].rt > 0) {
            int exec_time = (p[idx].rt > tq) ? tq : p[idx].rt;
            p[idx].rt -= exec_time;
            time += exec_time;

            // Enqueue the processes that arrived in the meantime
            for(i = 0; i < NoP; i++) {
                if(!visited[i] && p[i].at <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            if(p[idx].rt == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                avg_tat += p[idx].tat;
                avg_wt += p[idx].wt;

                is_completed[idx] = 1;
                completed++;
            } else {
                // Enqueue the process again at the end
                queue[rear++] = idx;
            }
        }
    }

    // Sort by Completion Time
    for(i = 0; i < NoP-1; i++) {
        for(int j = i+1; j < NoP; j++) {
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

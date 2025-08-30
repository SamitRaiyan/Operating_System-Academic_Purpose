// Experiment 1: First-Come, First-Served (FCFS) Scheduling 
# include <stdio.h>

struct pcb{
    int pid,at,bt,tat;
    // pid: Process ID
    // at: Arrival Time
    // bt: Burst Time
    // tat: Turnaround Time
};

void pline(int x)
{
    int i;
    for(i = 0; i < x; i++)
        printf("-");
    printf("\n");
}

void main()
{
    int i,num,j;
    float avg = 0.0, sum = 0.0;
    struct pcb p[10], temp;

    // Input process details
    printf("Enter the total number of processes: ");
    scanf("%d", &num);

    // Input Arrival Time and Burst Time
    for(i = 0; i < num; i++)
    {
       printf("Enter the Arrival Time and Burst Time of process %d: ", i + 1);
    scanf("%d %d", &p[i].at, &p[i].bt);
    p[i].pid = i + 1;
    }

    // Sorting processes based on Arrival Time
    for(i = 0; i < num - 1; i++)
    {
        for(j = 0; j < num - i - 1; j++)
        {
            if(p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Calculating Turnaround Time
    for(i = 0; i < num; i++)
    {
        sum = sum + p[i].bt;
        p[i].tat = sum;
    }
    sum = 0;
    pline(50);
    printf(" Process ID \t Arrival Time \t Burst Time \t Turnaround Time \n");
    pline(50);
    for(i = 0; i < num; i++)
    {
        printf("      %d      \t      %d      \t     %d      \t       %d       \n",
               p[i].pid, p[i].at, p[i].bt, p[i].tat);
               sum += p[i].tat;
    }
    pline(50);
    avg = sum /(float) num;
    printf("Total Turnaround Time: %.2f\n", sum);
    printf("Average Turnaround Time: %.2f\n", avg);

}
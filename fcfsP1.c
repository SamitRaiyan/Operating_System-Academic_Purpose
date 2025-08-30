#include<stdio.h>

struct pcb{
    int pid,at,bt,ct,tat,wt;
};

void line(int x){
    for(int i = 0;i < x;i++){
        printf("-");
    }
    printf("\n");
}

void main(){
    int NoP,i,j, time = 0;
    float avg_tat = 0, avg_wt = 0;
    printf("Input the total number of process: ");
    scanf("%d",&NoP);

    struct pcb p[NoP],temp;

    for ( i = 0; i < NoP; i++)
    {
        printf("Input at and bt of process%d:", i+1);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].pid = i+1;
    }
    
    for(i = 0; i < NoP-1; i++){
        for ( j = 0; j < NoP-i-1; j++)
        {
            if (p[j].at > p[j+1].at)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
            
        }
    }

    time = p[0].at;
    for ( i = 0; i < NoP; i++){
        if (time < p[i].at){
            time = p[i].at;
        }
    
        time = time + p[i].bt;
    p[i].ct = time;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;
    avg_tat = avg_tat + p[i].tat;
    avg_wt = avg_wt + p[i].wt;
    }

    line(60);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    line(60);
    for ( i = 0; i < NoP; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    line(60);
    printf("TaT: %.3f\n",avg_tat/NoP);
    printf("WT: %.3f\n",avg_wt/NoP);
    


}
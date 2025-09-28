#include <stdio.h>
#include <stdlib.h>

typedef struct { int id; int profit; int dead; } Job;
int cmp(const void *a, const void *b){
    Job A = *(Job*)a, B = *(Job*)b;
    return B.profit - A.profit;
}

int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    Job *jobs = malloc(n*sizeof(Job));
    int maxd=0;
    for(int i=0;i<n;i++){ scanf("%d %d %d",&jobs[i].id, &jobs[i].profit, &jobs[i].dead); if(jobs[i].dead>maxd) maxd=jobs[i].dead; }
    qsort(jobs,n,sizeof(Job),cmp);
    int *slot = calloc(maxd+1, sizeof(int)); 
    int count=0; int profit=0;
    for(int i=0;i<n;i++){
        for(int d = jobs[i].dead; d>0; d--){
            if(slot[d]==0){ slot[d] = jobs[i].id; profit += jobs[i].profit; count++; break; }
        }
    }
    printf("%d %d\n", count, profit);
    free(jobs); free(slot);
    return 0;
} 
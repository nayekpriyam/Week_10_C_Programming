#include <stdio.h>
#include <stdlib.h>

int cmpint(const void *a, const void *b){ return (*(int*)a) - (*(int*)b); }

int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    int *arr = malloc(n*sizeof(int));
    int *dep = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    for(int i=0;i<n;i++) scanf("%d",&dep[i]);
    qsort(arr, n, sizeof(int), cmpint);
    qsort(dep, n, sizeof(int), cmpint);
    int i=0,j=0,plat=0,maxp=0;
    while(i<n && j<n){
        if(arr[i] <= dep[j]){ plat++; if(plat>maxp) maxp=plat; i++; }
        else { plat--; j++; }
    }
    printf("%d\n", maxp);
    free(arr); free(dep);
    return 0;
} 
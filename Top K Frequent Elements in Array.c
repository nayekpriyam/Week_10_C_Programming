#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int val;
    int used;
} MapEntry;

MapEntry *map;
int MAPSZ;

unsigned int h(int x){ return ((unsigned int)x*2654435761u) % MAPSZ; }

void map_init(int sz){
    MAPSZ = sz*2 + 5;
    map = calloc(MAPSZ, sizeof(MapEntry));
}

void map_add(int key){
    unsigned int idx = h(key);
    while(map[idx].used && map[idx].key != key) idx = (idx+1)%MAPSZ;
    if(map[idx].used) map[idx].val++;
    else { map[idx].used = 1; map[idx].key = key; map[idx].val = 1;}
}

int map_collect(int **keys, int **freqs){
    int cnt=0;
    for(int i=0;i<MAPSZ;i++) if(map[i].used) cnt++;
    *keys = malloc(cnt * sizeof(int));
    *freqs = malloc(cnt * sizeof(int));
    int j=0;
    for(int i=0;i<MAPSZ;i++) if(map[i].used){
        (*keys)[j] = map[i].key;
        (*freqs)[j] = map[i].val;
        j++;
    }
    return cnt;
}

int cmp_pair(const void *a, const void *b){
    int ai = *(int*)a, bi = *(int*)b;
    // unused
    return 0;
}

typedef struct { int key,f; } P;
int cmpP(const void *a, const void *b){
    P pa = *(P*)a, pb = *(P*)b;
    if(pa.f != pb.f) return pb.f - pa.f;
    return pa.key - pb.key;
}

int main(){
    int n;
    if(scanf("%d",&n)!=1) return 0;
    int *arr = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&arr[i]);
    int k; scanf("%d",&k);
    map_init(n);
    for(int i=0;i<n;i++) map_add(arr[i]);
    int *keys,*freqs;
    int cnt = map_collect(&keys,&freqs);
    P *ps = malloc(cnt*sizeof(P));
    for(int i=0;i<cnt;i++){ ps[i].key = keys[i]; ps[i].f = freqs[i]; }
    qsort(ps, cnt, sizeof(P), cmpP);
    for(int i=0;i<k && i<cnt;i++) printf("%d ", ps[i].key);
    printf("\n");
    return 0;
} 
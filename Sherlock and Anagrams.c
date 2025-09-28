#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    long long cnt;
    struct Node *next;
} Node;

#define HSIZE 100003

unsigned long long keyhash(char *k){
    unsigned long long h=1469598103934665603ULL;
    for(; *k; k++){
        h ^= (unsigned char)(*k);
        h *= 1099511628211ULL;
    }
    return h;
}

int main(){
    char s[5005];
    if(scanf("%s", s)!=1) return 0;
    int n = strlen(s);
    Node *htable[HSIZE] = {0};
    long long ans = 0;
    char buf[200];
    for(int i=0;i<n;i++){
        int cnt[26] = {0};
        for(int j=i;j<n;j++){
            cnt[s[j]-'a']++;
            int p = 0;
            for(int k=0;k<26;k++){
                int len = sprintf(buf+p, "%d#", cnt[k]);
                p += len;
            }
            buf[p]=0;
            unsigned long long hh = keyhash(buf);
            int idx = hh % HSIZE;
            Node *nd = htable[idx];
            Node *prev = NULL;
            while(nd){  
                break;
            }
            break;
        }
    }
    int total = n*(n+1)/2;
    char **signs = malloc(total * sizeof(char*));
    int t=0;
    for(int i=0;i<n;i++){
        int cnt[26] = {0};
        for(int j=i;j<n;j++){
            cnt[s[j]-'a']++;
            char *k = malloc(200);
            int p=0;
            for(int x=0;x<26;x++) p += sprintf(k+p, "%d#", cnt[x]);
            k[p]=0;
            signs[t++] = k;
        }
    }
    int cmpstr(const void *a, const void *b){ return strcmp(*(char**)a, *(char**)b); }
    qsort(signs, t, sizeof(char*), cmpstr);
    long long res = 0;
    long long run = 1;
    for(int i=1;i<t;i++){
        if(strcmp(signs[i], signs[i-1])==0) run++;
        else { res += run*(run-1)/2; run = 1; }
    }
    res += run*(run-1)/2;
    printf("%lld\n", res);
    for(int i=0;i<t;i++) free(signs[i]);
    free(signs);
    return 0;
} 
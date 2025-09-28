#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char s[1000005];
    if(scanf("%s", s)!=1) return 0;
    int n = strlen(s);
    int *stack = malloc((n+1)*sizeof(int));
    int top = -1;
    int maxlen = 0;
    // push -1 index
    stack[++top] = -1;
    for(int i=0;i<n;i++){
        if(s[i]=='(') stack[++top] = i;
        else {
            if(top!=-1) top--;
            if(top == -1) stack[++top] = i;
            else {
                int len = i - stack[top];
                if(len > maxlen) maxlen = len;
            }
        }
    }
    printf("%d\n", maxlen);
    free(stack);
    return 0;
} 
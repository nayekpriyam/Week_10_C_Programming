#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int *heights, int n){
    int *stack = malloc((n+1)*sizeof(int));
    int top = -1;
    int maxA = 0;
    for(int i=0;i<=n;i++){
        int h = (i==n)?0:heights[i];
        while(top!=-1 && h < heights[stack[top]]){
            int height = heights[stack[top--]];
            int left = (top==-1)?0:stack[top]+1;
            int width = i - left;
            if(height*width > maxA) maxA = height*width;
        }
        stack[++top] = i;
    }
    free(stack);
    return maxA;
}

int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    int *a = malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    printf("%d\n", largestRectangleArea(a,n));
    free(a);
    return 0;
} 
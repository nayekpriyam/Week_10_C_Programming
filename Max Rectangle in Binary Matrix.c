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
    int r,c;
    if(scanf("%d %d",&r,&c)!=2) return 0;
    int *h = calloc(c, sizeof(int));
    int maxArea = 0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int x; scanf("%d",&x);
            if(x) h[j] += 1; else h[j] = 0;
        }
        int area = largestRectangleArea(h, c);
        if(area > maxArea) maxArea = area;
    }
    printf("%d\n", maxArea);
    free(h);
    return 0;
} 
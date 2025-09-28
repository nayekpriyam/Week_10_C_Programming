#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *a; int top; int cap;
} Stack;

Stack* make_stack(int cap){ Stack *s = malloc(sizeof(Stack)); s->a = malloc(cap*sizeof(int)); s->top=0; s->cap=cap; return s; }
void push(Stack *s, int x){ if(s->top==s->cap){ s->cap *=2; s->a = realloc(s->a, s->cap*sizeof(int));} s->a[s->top++] = x; }
int pop(Stack *s){ if(s->top==0) return -1; return s->a[--s->top]; }
int empty(Stack *s){ return s->top==0; }
int peek(Stack *s){ if(s->top==0) return -1; return s->a[s->top-1]; }

typedef struct {
    Stack *in, *out;
} Queue2;

Queue2* make_queue(){ Queue2 *q = malloc(sizeof(Queue2)); q->in = make_stack(4); q->out = make_stack(4); return q; }
void enqueue(Queue2 *q, int x){ push(q->in, x); }
int dequeue(Queue2 *q){
    if(empty(q->out)){
        while(!empty(q->in)) push(q->out, pop(q->in));
    }
    if(empty(q->out)) return -1;
    return pop(q->out);
}
int frontq(Queue2 *q){
    if(empty(q->out)){
        while(!empty(q->in)) push(q->out, pop(q->in));
    }
    if(empty(q->out)) return -1;
    return peek(q->out);
}

int main(){
    Queue2 *q = make_queue();
    int cmd;
    while(scanf("%d",&cmd)==1){
        if(cmd==0) break;
        if(cmd==1){ int x; scanf("%d",&x); enqueue(q,x); }
        else if(cmd==2){ printf("%d\n", dequeue(q)); }
        else if(cmd==3){ printf("%d\n", frontq(q)); }
    }
    return 0;
} 
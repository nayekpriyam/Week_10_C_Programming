#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *s;
    int len;
    int cap;
} Str;

void s_init(Str *st){ st->cap = 1024; st->s = malloc(st->cap); st->s[0]=0; st->len=0; }
void s_append(Str *st, const char *t){
    int tl = strlen(t);
    if(st->len + tl + 1 > st->cap) { while(st->len+tl+1>st->cap) st->cap*=2; st->s = realloc(st->s, st->cap); }
    memcpy(st->s + st->len, t, tl); st->len += tl; st->s[st->len]=0;
}
char* s_pop_last(Str *st, int k){ 
    if(k > st->len) k = st->len;
    char *res = malloc(k+1);
    memcpy(res, st->s + st->len - k, k);
    res[k]=0;
    st->len -= k; st->s[st->len]=0;
    return res;
}
char s_char_at(Str *st, int k){ if(k<=0 || k>st->len) return '\0'; return st->s[k-1]; }

typedef struct Op {
    int type; 
    char *data; 
    struct Op *next;
} Op;

int main(){
    int q; if(scanf("%d",&q)!=1) return 0;
    Str cur; s_init(&cur);
    Op *opstack = NULL;
    while(q--){
        int type; scanf("%d",&type);
        if(type==1){
            char buf[100005]; scanf("%s", buf);
            s_append(&cur, buf);
            Op *op = malloc(sizeof(Op)); op->type = 1; op->data = strdup(buf); op->next = opstack; opstack = op;
        } else if(type==2){
            int k; scanf("%d",&k);
            char *deleted = s_pop_last(&cur, k);
            Op *op = malloc(sizeof(Op)); op->type = 2; op->data = deleted; op->next = opstack; opstack = op;
        } else if(type==3){
            int k; scanf("%d",&k);
            char c = s_char_at(&cur, k);
            if(c) putchar(c);
            putchar('\n');
        } else if(type==4){
            if(opstack){
                Op *op = opstack; opstack = op->next;
                if(op->type == 1){
                    int len = strlen(op->data);
                    free(s_pop_last(&cur, len));
                    free(op->data);
                    free(op);
                } else if(op->type == 2){
                    s_append(&cur, op->data);
                    free(op->data);
                    free(op);
                }
            }
        }
    }
    return 0;
} 
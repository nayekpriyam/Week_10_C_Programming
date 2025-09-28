#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, val;
    struct Node *prev, *next;
} Node;

typedef struct HEntry {
    int key;
    Node *node;
    struct HEntry *next;
} HEntry;

typedef struct {
    int capacity, size;
    Node *head, *tail; 
    HEntry **htable;
    int hsize;
} LRUCache;

unsigned int hashfn(LRUCache *c, int key){ return ((unsigned int)key) % c->hsize; }

LRUCache* lRUCacheCreate(int capacity){
    LRUCache *c = malloc(sizeof(LRUCache));
    c->capacity = capacity; c->size = 0;
    c->head = c->tail = NULL;
    c->hsize = capacity * 3 + 1;
    c->htable = calloc(c->hsize, sizeof(HEntry*));
    return c;
}

Node* make_node(int key, int val){
    Node *n = malloc(sizeof(Node));
    n->key = key; n->val = val; n->prev = n->next = NULL;
    return n;
}

void remove_node(LRUCache *c, Node *n){
    if(!n) return;
    if(n->prev) n->prev->next = n->next;
    else c->head = n->next;
    if(n->next) n->next->prev = n->prev;
    else c->tail = n->prev;
}

void insert_front(LRUCache *c, Node *n){
    n->prev = NULL;
    n->next = c->head;
    if(c->head) c->head->prev = n;
    c->head = n;
    if(!c->tail) c->tail = n;
}

HEntry* hfind(LRUCache *c, int key){
    unsigned int h = hashfn(c, key);
    HEntry *e = c->htable[h];
    while(e){
        if(e->key == key) return e;
        e = e->next;
    }
    return NULL;
}

void hput(LRUCache *c, int key, Node *node){
    unsigned int h = hashfn(c, key);
    HEntry *e = malloc(sizeof(HEntry));
    e->key = key; e->node = node;
    e->next = c->htable[h];
    c->htable[h] = e;
}

void hremove(LRUCache *c, int key){
    unsigned int h = hashfn(c, key);
    HEntry *e = c->htable[h], *prev = NULL;
    while(e){
        if(e->key == key){
            if(prev) prev->next = e->next;
            else c->htable[h] = e->next;
            free(e);
            return;
        }
        prev = e; e = e->next;
    }
}

int lRUCacheGet(LRUCache* c, int key){
    HEntry *e = hfind(c, key);
    if(!e) return -1;
    Node *n = e->node;
    remove_node(c, n);
    insert_front(c, n);
    return n->val;
}

void lRUCachePut(LRUCache* c, int key, int value){
    HEntry *e = hfind(c, key);
    if(e){
        e->node->val = value;
        remove_node(c, e->node);
        insert_front(c, e->node);
        return;
    }
    if(c->size == c->capacity){
        Node *to = c->tail;
        hremove(c, to->key);
        remove_node(c, to);
        free(to);
        c->size--;
    }
    Node *n = make_node(key, value);
    insert_front(c, n);
    hput(c, key, n);
    c->size++;
}

void lRUCacheFree(LRUCache* c){
    Node *cur = c->head, *nxt;
    while(cur){ nxt = cur->next; free(cur); cur = nxt; }
    for(int i=0;i<c->hsize;i++){
        HEntry *e = c->htable[i], *nx;
        while(e){ nx = e->next; free(e); e = nx; }
    }
    free(c->htable);
    free(c);
}

int main(){
    LRUCache *cache = lRUCacheCreate(2);
    lRUCachePut(cache, 1, 10);
    lRUCachePut(cache, 2, 20);
    printf("%d\n", lRUCacheGet(cache, 1)); 
    lRUCachePut(cache, 3, 30); 
    printf("%d\n", lRUCacheGet(cache, 2)); 
    lRUCachePut(cache, 4, 40); 
    printf("%d\n", lRUCacheGet(cache, 1)); 
    printf("%d\n", lRUCacheGet(cache, 3)); 
    printf("%d\n", lRUCacheGet(cache, 4)); 
    lRUCacheFree(cache);
    return 0;
} 
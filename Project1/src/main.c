#include <stdio.h>
#include <stdlib.h>

typedef enum color{white, gray, black} Color;

//Linked List
typedef struct node{
    Color color;
    int start;
    int finish;
    struct node* parent;
    struct node** link;
}Node;

void addNode(Node* node_p, Node* node_c){
    int n = sizeof(node_p->link) / sizeof(Node*);
    node_p->link = (Node**) realloc(node_p->link, sizeof(Node*) * ++n);
    node_p->link[n-1] = node_c;
}


void main(){
    int n, l, u, v, i;

    scanf("%d %d", &n, &l);
    Node graph[n];
    
    //graph initialization
    for(i=0; i<n ; i++){
        graph[i].color = white;
        graph[i].start = -1;
        graph[i].finish = -1;
        graph[i].parent = NULL;
        graph[i].link = NULL;
    }

    for(i=0 ; i<l ; i++){
        scanf("%d %d", &u, &v);
        addNode(&graph[u], &graph[v]);       
    }
    
    exit(0);
}
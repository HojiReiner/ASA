#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef enum color{white, gray, black} Color;

/*Node*/
typedef struct node{
    bool is_source;
    struct node* source;
    int depth;
    int max_depth;
    struct node* parent;
    struct node** link;
    int link_size;
}Node;


void addNode(Node* node_p, Node* node_c){
    node_p->link = (Node**) realloc(node_p->link, sizeof(Node*) * ++node_p->link_size);
    node_p->link[node_p->link_size-1] = node_c;
}


/*BFS*/
int visit(Node* node){
    int i;
    int n = node->link_size;

    if(n == 0){
        if(node->source->max_depth < node->depth){
            node->source->max_depth = node->depth;
        }
        return -1;
    }
    
    for(i = 0; i<n ; i++){
        if(node->link[i]->source == node->source){
            if(node->link[i]->depth < (node->depth + 1)){
                node->link[i]->depth = node->depth + 1;
                return i;
            }
        
        }else{
            node->link[i]->source = node->source;
            node->link[i]->depth = node->depth + 1;
            return i;
        }
    }

    return -1;
}

int DFS(Node* src){
    int depth = 1;
    Node* current = src;

    while(depth > 0){
        int next = visit(current);
        if(next == -1){
            depth --;
            current = current->parent;
            continue;
        }

        depth++;
        current->link[next]->parent = current;
        current = current->link[next];
    }
    
    return src->max_depth;
}


int main(){
    int n, l, u, v, i;
    int max_depth = 0;
    int min_src = 0;

    int number = scanf("%d %d", &n, &l);
    Node graph[n];
    
    /*graph initialization*/

    for(i=0; i<n ; i++){
        graph[i].is_source = true;
        graph[i].source = &graph[i];
        graph[i].depth = 1;
        graph[i].max_depth = 1;
        graph[i].parent = NULL;
        graph[i].link = NULL;
        graph[i].link_size = 0;
    }

    for(i=0 ; i<l ; i++){
        number = scanf("%d %d", &u, &v);
        addNode(&graph[u-1], &graph[v-1]);
        graph[v-1].is_source = false; 
    }

    number++;
    /*k = O(v)*/
    for(i=0; i<n ; i++){
        if(graph[i].is_source){
            min_src++;
            int max = DFS(&graph[i]);
            if(max > max_depth){
                max_depth = max;
            }
        }
    }

    printf("%d %d\n", min_src,max_depth);
    
    exit(0);
}
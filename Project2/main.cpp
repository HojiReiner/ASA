#include <iostream>
#include <queue>
#include <cstdlib>
using namespace std;

enum class Colors {white, gray, black};

struct Edge{
  int flow;
  int cap;
};

struct Node{
  int ident;
  Colors color;
  int d;
  Node* parent;
  Node** link;
  int link_size;
};

struct Graph{
  Edge **edges;
  Node *nodes;
  int n;
};

//BFS
int BFS(Graph *graph){
  int i;
  int minFlow = 2147483647;
  Node* target = &graph->nodes[graph->n - 1];

  graph->nodes[0].color = Colors::white;
  graph->nodes[0].parent = nullptr;
  graph->nodes[0].d = 0;

  for(i=1; i<graph->n ; i++){
    graph->nodes[i].color = Colors::white;
    graph->nodes[i].parent = nullptr;
  }

  queue<Node*> Queue;
  Queue.push(&graph->nodes[0]);

  while(!Queue.empty()){
    Node *current = Queue.front();
    Queue.pop();

    for(i=0; i<current->link_size; i++){
      Node *next = current->link[i];
      int possibleFlow = graph->edges[current->ident][next->ident].cap - graph->edges[current->ident][next->ident].flow;

      if(next->color == Colors::white && possibleFlow > 0){
        Queue.push(next);
        next->color = Colors::gray;
        next->parent = current;
        next->d = current->d + 1;
        minFlow = min(minFlow, possibleFlow);
        if(next->ident == target->ident){
          return minFlow;
        }

      }
    }

    current->color = Colors::black;
  }
  
  return -1;
}


//Ford Fulkerson
/*int ComputeLowestCost(Graph *graph){
  


  target = graph.nodes[n-1];

  while(graph.nodes[i] != nullptr){
    pi = graph.nodes[n-1].parent;

  }
}*/

int main(){
  int n,k;
  int i, j;
  int x,y;
  
  Graph graph;
  
  if(scanf("%d %d", &n, &k) ==-1){
    exit(1);
  }
  graph.n = n+2;

  graph.nodes = (Node*) malloc(sizeof(Node) * (n+2));
  for(i=0; i<n+2; i++){
    graph.nodes[i].ident = i;
    graph.nodes[i].link = nullptr;
    graph.nodes[i].link_size = 0;
  }


  graph.edges = (Edge**) malloc(sizeof(Edge*) * (n+2));
  for(i=0; i< n+2; i++){
    graph.edges[i] = (Edge*) malloc(sizeof(Edge) * (n+2));
    for(j=0; j<n+2 ; j++){
      graph.edges[i][j].flow = 0;
      graph.edges[i][j].cap = 0;
    }
  }
  
  for(i=1; i<n+1; i++){
    if(scanf("%d %d", &x, &y) == -1){
      exit(1);
    }

    graph.edges[0][i].cap = x;
    graph.edges[i][n+1].cap = y;

    graph.nodes[0].link = (Node**) realloc(graph.nodes[0].link, sizeof(Node*) * ++graph.nodes[0].link_size);
    
    graph.nodes[0].link[graph.nodes[0].link_size-1] = &graph.nodes[i];

 
    graph.nodes[i].link = (Node**) realloc(graph.nodes[i].link, sizeof(Node*) * ++graph.nodes[i].link_size);
    
    graph.nodes[i].link[graph.nodes[i].link_size-1] = &graph.nodes[n+1];

  }

  for(i=0; i<k ; i++){
    if(scanf("%d %d %d", &x, &y, &j) == -1){
      exit(1);
    }
    
    graph.edges[x][y].cap = j;
    graph.edges[y][x].cap = j;

    
    graph.nodes[x].link = (Node**) realloc(graph.nodes[x].link, sizeof(Node*) * ++graph.nodes[x].link_size);
    graph.nodes[x].link[ graph.nodes[x].link_size-1] = &graph.nodes[y];

    graph.nodes[y].link = (Node**) realloc( graph.nodes[y].link, sizeof(Node*) * ++graph.nodes[y].link_size);
    graph.nodes[y].link[ graph.nodes[y].link_size-1] = &graph.nodes[x];
  }

  //printf("%d",ComputeLowestCost(&graph));
  printf("%d\n", BFS(&graph));
 
 
  
  
  return 0;
}
#include <iostream>
#include<forward_list>

using namespace std;

enum Color {white, gray, black};

class Node{
    public:
        Node(){}
        void addNode(Node node){
            link.push_front(node);
        }

    private:
        Color color = white;
        Node* parent = nullptr;
        int start = -1;
        int finish = -1;
        forward_list<Node> link;
};

/*typedef struct Node{
    Color color;
    node* parent;
    int start;
    int finish;
}node;
*/
//build graph


int main(){
    int n, c, u, v;
    int i;
    
    forward_list<Node> graph;
    cin >> n >> c;

    graph.assign(n, new Node());
    
    for(i=0; i<n ; i++){
        scanf("%d %d", &u, &v);

        graph[u-1].addNode(graph[v-1]);
    }

    return 0;
}
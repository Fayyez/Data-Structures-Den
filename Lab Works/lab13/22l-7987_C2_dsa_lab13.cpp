#include<iostream>
#include<list>
#include<queue>
#include<stack>

using namespace std;

#include<iostream>
#include<list>

using namespace std;

class GraphSearch
{
    int V; // No. of vertices
    list<int> *adj; // is an array of vectors
public:
    GraphSearch(int V); // Constructor
    void addEdgeToGraph(int v, int w);
    void BFSearch(int s); 
    void DFSearch(int s); 
};

GraphSearch::GraphSearch(int V) // constructor
{
    this->V = V;
    adj = new list<int>[V];
}

void GraphSearch::addEdgeToGraph(int v, int w)
{
    // if out of bound
    if(v>this->V || v<0) {cout<<"out of bound"; return; }
    adj[v].push_back(w); // is a directed list
}

void GraphSearch::BFSearch(int s)
{
    // TODO: Implement Breadth First Search
    // using queue
    queue<int> q;
    q.push(s);
    // const int s(V);
    bool * visited = new bool[V];
    cout<<"BF Path: ";
    for(int i=0; i<V; i++) visited[i] = false;
    visited[s] = true;// first tu visited he na isslie bhai
    while(!q.empty()) {
        int temp = q.front();
        cout << temp <<" ";
        q.pop();
        for(int i: adj[temp]) {
            if(!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout<<endl;
    delete[]visited;
}

void GraphSearch::DFSearch(int q)
{
    // TODO: Implement Depth First Search
    // using stack
    stack<int> s;
    s.push(q);
    // const int s(V);
    bool * visited = new bool[V];
    cout<<"DF Path: ";
    for(int i=0; i<V; i++) visited[i] = false;
    visited[q] = true;// first tu visited he na isslie bhai
    while(!s.empty()) {
        int temp = s.top();
        cout << temp << " ";
        s.pop();
        for(int i: adj[temp]) {
            if(!visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
    cout<<endl;
    delete[]visited;

}


int main() {
    int V = 5; // Number of vertices in the graph
    GraphSearch g(V); // Create a graph with V vertices

    // Adding
    g.addEdgeToGraph(0, 1);
    g.addEdgeToGraph(0, 2);
    g.addEdgeToGraph(1, 2);
    g.addEdgeToGraph(2, 0);
    g.addEdgeToGraph(2, 3);
    g.addEdgeToGraph(3, 3);

    int startVertex = 2; // Starting vertex for the search

    cout << "Breadth First Search: ";
    g.BFSearch(startVertex);

    cout << "Depth First Search: ";
    g.DFSearch(startVertex);

    return 0;
}

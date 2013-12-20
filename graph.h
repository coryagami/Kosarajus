#include <list>
#include <stack>
#include "DisjointSet.h"

using namespace std;

class Graph
{
public:
    Graph(int V);
	// add edge given 2 vertices
    void addEdge(int v, int w);
 
    // main function to find the SCC's
    DisjointSet findSCC();
 
    // transposes (reverses) the edge directions
    Graph getTranspose();

private:
    int V;
    list<int> *adj;    // array of adjacency lists
 
    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void DFS(int v, bool visited[], DisjointSet* GSetRef);
};
#include <list>
#include <stack>
#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
// A recursive function to print DFS starting from v
void Graph::DFS(int v, bool visited[], DisjointSet* GSetRef)
{
    visited[v] = true;
 
    // DFS each child if it hasn't yet been visited
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
        	if (!visited[*i])
		{
			// merging the parent and child that are part of the current SCC
			// using a reference to the disjoint set
			GSetRef->merge(v, *i);
                        DFS(*i, visited, GSetRef);
		}
	}
}
 
Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
        // this creates a new graph g with all the adjacent vertices pushed
		// onto adj in the reverse order, transposing the graph
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
		}
	}
	return g;
}
 
void Graph::addEdge(int v, int w)
{
	// Add w to v�s adj list
	adj[v].push_back(w); 
}
 
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack)
{
	visited[v] = true;
 
	// recursively iterates through vertices by order of finishing time
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
			fillOrder(*i, visited, Stack);
 
    // v has now been explored, push it to stack for Kosarajus algorithm
	Stack.push(v);
}
 
DisjointSet Graph::findSCC()
{
	stack<int> Stack;
	DisjointSet GSet(V);

	// reference to disjoint set allowing modification
	DisjointSet* GSetRef = &GSet; 
 
    // clear all vertices to WHITE (not visited) <- for first DFS
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;
 
    // call fillOrder to fill stack correctly
	for(int i = 0; i < V; i++)
		if(visited[i] == false)
			fillOrder(i, visited, Stack);
 
	Graph gr = getTranspose();
 
    // clear all vertices to WHITE (not visited) <- for second DFS
	for(int i = 0; i < V; i++)
		visited[i] = false;
 
    // now DFS all vertices again in the correct order
	while (Stack.empty() == false)
	{
        // top vertex off stack to v
		int v = Stack.top();
		Stack.pop();
 
        // find SCC of v and store it in GSetRef
		if (visited[v] == false)
        		gr.DFS(v, visited, GSetRef);
    	}
	return GSet;
}

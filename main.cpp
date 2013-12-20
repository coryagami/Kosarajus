#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include "graph.h"

using namespace std;

//basic edge struct for edges vector
struct Edge {
	int v1, v2;
	Edge(int q, int w) : v1(q), v2(w) {}
};

int main(int argc, char* argv[])
{
	if(argc != 2)
	{cout << "Usage: " << argv[0] << " <filename>\n"; return 0;}

	string word;
	int nodeCount = 0;
	int edgeCount = 0;
	int v1, v2;
	vector<Edge> edges;

	// skip comments and read in node and edge count from file
	ifstream myFile(argv[1]);
	myFile.ignore(256, '\n');
	myFile.ignore(256, '\n');
	myFile >> word >> word >> nodeCount >> word >> edgeCount;
	myFile.ignore(256, '\n');
	myFile.ignore(256, '\n');
	
	cout << "NODE: " << nodeCount << endl << "EDGE: " << edgeCount << endl;

	// Create a graph  and disjoint set with given number of vertices
	Graph g(nodeCount+1);
	DisjointSet Set(nodeCount);

	// read in each vertex pair from file and add to graph g
	for(int i=1; i<=edgeCount; i++)
	{
		myFile >> v1 >> v2;
		// vertex for iterating through edges later
		edges.push_back(Edge(v1, v2));
		g.addEdge(v1, v2);

		// merge all adjacent vertices (to form WCC's)
		if(Set.find(v1) != Set.find(v2))
			Set.merge(v1, v2);
	}

	// Use Set find() to find representative node for biggest set and use that
	// to find number of edges with mathching representative
	cout << "Largest WCC Node Count: " << Set.getmaxSetSize() << endl;
	int maxSetNode = Set.getmaxSetSizeNode();
	int WCCedges = 0;
	for(int i=0; i<edgeCount; i++)
	{
		// counting edges that share the set with the max WCC representative
		if(Set.find(maxSetNode) == Set.find(edges[i].v1))
			WCCedges++;
	}
	cout << "Largest WCC Edge Count: " << WCCedges << endl;

	// calling the main Kosarajus algorithm step to find set with all SCC's
	DisjointSet SCCSet = g.findSCC();
	cout << "Largest SCC Node Count: " << SCCSet.getmaxSetSize() << endl;
	maxSetNode = SCCSet.getmaxSetSizeNode();
	int SCCedges = 0;
	for(int i=0; i<edgeCount; i++)
	{
		// same as above to find edges, only counting directional edges (via &&)
		if(SCCSet.find(maxSetNode) == SCCSet.find(edges[i].v2) && 
			SCCSet.find(maxSetNode) == SCCSet.find(edges[i].v1))
			SCCedges++;
	}
	cout << "Largest SCC Edge Count: " << SCCedges << endl;
	cout << "Have a great day! \n";
    return 0;
}
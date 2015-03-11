#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Edge.h"

//Credits: Original header by Professor Leyk.

using namespace std;

class Graph;
class Edge;

class Vertex {

private:
	vector<Edge*> inList; // source vertex
    vector<Edge*> outList; // end vertex 
	int id;
	friend class Graph;
public:

	Vertex(int sid);
	int getID() const;
	vector<Edge*> getOutEdges() const;
	vector<Edge*> getInEdges() const;
};

#endif
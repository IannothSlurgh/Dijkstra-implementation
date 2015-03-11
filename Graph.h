#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "locator.h"
#include "supp_exception.h"

using namespace std;

//Credits: Original header by Professor Leyk.

class Edge;
class Vertex;

class Graph
{

	private:
	bool failed_input;
	vector<Vertex*> vertList;
	vector<Edge*> edgeList;
	public:
	Graph(string filename);
	~Graph();
	vector<Vertex*> getVertices() const;
	void PrintGraph();
	void add_vertex();
	void add_edge(int svert, int evert, int weight);
	bool are_adjacent(Vertex * a, Vertex * B);
	void apply_locator(locator<Vertex*>* loc);
	void finalize_locator(locator<Vertex*>* loc);
	int get_num_vertices();
	int get_num_edges();
	bool get_state();
};
#endif
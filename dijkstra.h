#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Graph.h"
//#include "distance_finder.h"
#include "minimum_priority_queue.h"
#include "locator.h"
#include <climits>

//struct that helps mimic some notation in textbook.
struct distance_finder
{
	distance_finder(){}	
	//The distance function
	int operator[](locator<Vertex*> * v) const
	{
		return v->get_location()->get_key();
	}
};

//Contains 2 ints.
struct paired_int
{
	int predecessor_ID;
	int final_weight;
	paired_int(){predecessor_ID=-1; final_weight=-1;}
};

class dijkstra
{
	distance_finder D;
	int comparisons;
	int spec_compare; //Num of comparisons to return a specific shortest path to user.
	vector<paired_int> shortest_paths;
	locator<Vertex*> * source; //The quick way to get source's position in MPQ.
	Graph * my_graph; //Used in constructor operations and then worthless afterwards.
	minimum_priority_queue_heap <Vertex*> MPQ;
	void relax(locator<Vertex *> * u, locator<Vertex *> * z, Edge * e);
	void recurse_path(int destination);
	public:
	dijkstra(Graph * g, int source);//Sets up the MPQ, applies MPQ's locators to graph. Runs the cloud_phase.
	void cloud_phase(); //Workhorse.
	void print_shortest_path(int destination);//Some kind of "get answer" function.
};
#endif

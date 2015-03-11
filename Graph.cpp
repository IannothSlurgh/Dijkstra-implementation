#include "Graph.h"
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <fstream>

using namespace std;

class Edge;
class Vertex;

Graph::Graph(string filename)
{
	failed_input=false;
	try
	{
		ifstream ifs(filename.c_str());
		if(!ifs)
			throw invalid_file_exception(filename);
		int vertnum;
		ifs>>vertnum;
		for(unsigned int i=0;i<vertnum;i++) // push all vertices into the vertex vector before assigning the in and out list
		{
			Vertex *vert = new Vertex(i+1);
			vertList.push_back(vert);
		}
		int svert,evert,weit; 
		ifs>>svert; 
		while(svert!=-1)
		{
			ifs>>evert; 
			while(evert!=-1)
			{
				ifs>>weit; // one weight means one edge
				Edge *tempedge = new Edge(vertList[svert-1],vertList[evert-1],weit); // new edge
				edgeList.push_back(tempedge);				
				vertList[svert-1]->outList.push_back(tempedge);
				vertList[evert-1]->inList.push_back(tempedge);
				ifs>>evert; 
			}
			ifs>>svert; 
		}
		ifs.close();
	}
	catch(invalid_file_exception(filename))
	{
		failed_input=true;
		cerr<<invalid_file_exception(filename); 
	}
}

Graph::~Graph()
{
	for(unsigned int i = 0; i < vertList.size(); i++)
		delete vertList[i];
	for(unsigned int i = 0; i < edgeList.size(); i++)
		delete edgeList[i];
}

void Graph::add_vertex()
{
	Vertex * vert= new Vertex(vertList.size()+1);
	vertList.push_back(vert);
}

void Graph::add_edge(int svert, int evert, int weit)
{
	Edge * tempedge = new Edge(vertList[svert-1], vertList[evert-1], weit);
	edgeList.push_back(tempedge);
	vertList[svert-1]->outList.push_back(tempedge);
	vertList[evert-1]->inList.push_back(tempedge);
}

vector<Vertex*> Graph::getVertices() const 
{
	return vertList;
}

void Graph::PrintGraph() // print out all the edges and associated vertices in the entire graph
{
	for(unsigned int i=0;i<vertList.size();++i)
	{
		vector<Edge*> ej_list=vertList.at(i)->getOutEdges();
		cout<<vertList.at(i)->getID()<<" ";
		for(unsigned int j=0;j<ej_list.size();++j)
		{
			cout<<ej_list.at(j)->getWeight()<<" "<<ej_list.at(j)->geteVertP()->getID()<<" ";
		}
		cout<<"#\n";
	}
}

bool Graph::are_adjacent(Vertex * a, Vertex * b)
{
	vector<Edge*> c=a->getOutEdges();
	vector<Edge*> d=a->getInEdges();
	for(unsigned int i=0;i<c.size();++i)
	{
		if(c.at(i)->geteVertP()==b)
			return true;
	}
	for(unsigned int i=0;i<d.size();++i)
	{
		if(d.at(i)->getsVertP()==b)
			return true;
	}	
	return false;
		
}

//Allows an easy way for a minimum priority queue
//to interface with the graph's edges.
void Graph::apply_locator(locator<Vertex*>* loc)
{
	vector<Edge*> ej_list = loc->get_location()->get_value()->getInEdges();
	for(unsigned int i=0;i<ej_list.size();++i)
	{
			ej_list.at(i)->set_out_locator(loc);
	}
}

//Removes the interfacing between the graph's edges
//and the minimum priority queue for a particular vertex.
void Graph::finalize_locator(locator<Vertex*>* loc) 
{
	vector<Edge*> ej_list = loc->get_location()->get_value()->getInEdges();
	for(unsigned int i=0;i<ej_list.size();++i)
	{
		ej_list.at(i)->terminate_out_locator();
	}	
}

//Return the number of vertices or edges in graph.
int Graph::get_num_vertices(){return vertList.size();}
int Graph::get_num_edges(){return edgeList.size();}

bool Graph::get_state(){return failed_input;};
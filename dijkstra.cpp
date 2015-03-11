#include "dijkstra.h"
#include  <iostream>
#define infinity INT_MAX
class distance_finder;

using namespace std;

dijkstra::dijkstra(Graph * g, int source)//Graph pointer, ID of source vertex.
{
	spec_compare=0;
	source-=1;//Changes source to represent index value.
	my_graph=g;
	comparisons=0;
	paired_int pi;
	vector<paired_int> finalized(my_graph->get_num_vertices(), pi);
	shortest_paths=finalized;
	vector<Vertex*> v_list= g->getVertices();
	locator<Vertex*>* l;
	unsigned int i=0;
	//Initialize all vertices not including source to inf.
	//Initialize source to 0. Use locators to interface MPQ to Graph edges.
	for(;i<source;++i)
	{
		l=MPQ.insert(infinity, v_list.at(i));
		g->apply_locator(l);
	}
	l=MPQ.insert(0, v_list.at(source));
	g->apply_locator(l);
	++i;
	for(;i<v_list.size();++i)
	{
		l=MPQ.insert(infinity, v_list.at(i));
		g->apply_locator(l);
	}
	cloud_phase();
	cout<<"Total compares to find all shortest paths from vertex "<<source+1<<": "<<comparisons<<".\n";
}

void dijkstra::cloud_phase()
{
	while(!MPQ.is_empty())
	{
		locator<Vertex *> * final_vertex = MPQ.min();//Get the vertex which will be finalized.
		if(!(D[final_vertex]==infinity))//Normality. That is, that the vertex was either the source or was relaxed by another connected vertex.
		{
			vector<Edge *> ej_list=final_vertex->get_location()->get_value()->getOutEdges(); //Get its neighbors.
			for(unsigned int i=0;i<ej_list.size();++i)
			{//If the edge is not a selfloop or has been discontinued from action, relax the edge.
				if(ej_list.at(i)->get_out_locator()!=0&&(ej_list.at(i)->getsVertP()!=ej_list.at(i)->geteVertP()))
					relax(final_vertex, ej_list.at(i)->get_out_locator(), ej_list.at(i));//Relax the the edge.
				comparisons+=2;
			}
			//Places final weight in shortest path.
			shortest_paths.at(final_vertex->get_location()->get_value()->getID()-1).final_weight=final_vertex->get_location()->get_key();
			my_graph->finalize_locator(final_vertex); //Eliminate edges that no longer need to be considered.
			comparisons+=MPQ.remove(final_vertex);
			comparisons++; //To find the minimum
		}
		else
		{
			//The path from source has dead-ended. All other vertices are isolated from source.
			shortest_paths.at(final_vertex->get_location()->get_value()->getID()-1).final_weight=infinity;
			comparisons+=MPQ.remove(final_vertex);
			comparisons++; //To find the minimum
			while(!MPQ.is_empty())
			{
				final_vertex = MPQ.min();
				shortest_paths.at(final_vertex->get_location()->get_value()->getID()-1).final_weight=infinity;
				comparisons+=MPQ.remove(final_vertex);
				comparisons++; //To find the minimum
			}
		}
		++comparisons;
	}
}

void dijkstra::relax(locator<Vertex *> * u, locator<Vertex *> * z, Edge * e) //finalizing locator, Relaxing Locator, Their edge
{
	//If a vertex's weight plus an outgoing edge's weight is less than
	//a destination vertex, set that destination's weight to that sum.
	if(D[u]+e->getWeight()<D[z])
	{
		comparisons+=MPQ.decrease_key(z, D[u]+e->getWeight());
		//Set z's predecessor that currently yields the shortest path.
		shortest_paths.at(z->get_location()->get_value()->getID()-1).predecessor_ID=u->get_location()->get_value()->getID();
	}
	++comparisons;
}

void dijkstra::print_shortest_path(int destination)
{
	if(shortest_paths.at(destination-1).final_weight==infinity)
	{
		cout<<destination<<" cannot be reached from the source.";
	}
	else
	{
		if(shortest_paths.at(destination-1).final_weight==0)
		{
			cout<<"The source and destination are the same.\nThe total weight of the path is 0.\n";
		}
		else
		{
			recurse_path(destination);
			cout<<"\n"<<"The total weight of the path is "<<shortest_paths.at(destination-1).final_weight<<".\n";
		}
	}
	spec_compare+=2;
	cout<<"The number of comparisons it took to get this shortest path from the completed algorithm was: "<<spec_compare<<".\n";
	spec_compare=0;
}

void dijkstra::recurse_path(int destination)
{
	int pred=shortest_paths.at(destination-1).predecessor_ID;
	if(!(pred==-1))
	{
		recurse_path(pred);
		cout<<"--"<<(shortest_paths.at(destination-1).final_weight-shortest_paths.at(pred-1).final_weight)<<"-->"<<destination;
	}
	else
	{
		cout<<destination;
	}
	++spec_compare;
}

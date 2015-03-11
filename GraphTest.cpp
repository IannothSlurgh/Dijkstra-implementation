#include <iostream>
#include <string>
#include "Graph.h"
#include "dijkstra.h"
#include "minimum_priority_queue.h"
using namespace std;

//Credits: Original test by Professor Leyk.

int main()
{
		cout<<"Please enter the name of a file for graph input.\n";
		string str;
		int source;
		int dest=0;
		cin>>str;
		Graph graph(str);
		if(!graph.get_state())
		{
			graph.PrintGraph();
			cout<<"There are "<<graph.get_num_vertices()<<" vertices. Which vertex do you want to be the the source of Dijkstra's Algorithm?\n";
			cin>>source;
			if(source<=graph.get_num_vertices() && source>0)
			{
				dijkstra d(&graph, source);
				cout<<"Please give a destination vertex to get the shortest path from the source to it.\nTerminate program by inputting invalid vertex.\n";
				cin>>dest;
				while(dest>0&&dest<=graph.getVertices().size())
				{
					d.print_shortest_path(dest);
					cin>>dest;
				}
			}
			else
				cout<<"Invalid vertex. Terminating.\n";
		}
		return 0;
}
#include "Edge.h"
#include "Vertex.h"
using namespace std;

Edge::Edge()
{
	sVertP=0;
	eVertP=0;
	weight=0;
	e_loc=0;
}

Edge::Edge(Vertex* sVert, Vertex* eVert, int weit)
{
	sVertP=sVert;
	eVertP=eVert;
	weight=weit;
	e_loc=0;
}

int Edge::getWeight(){return weight;}

Vertex* Edge::getsVertP(){return sVertP;}

Vertex* Edge::geteVertP(){return eVertP;}

//These three are additions to help handle dijkstra's algorithm.
//Each edge has a pointer to a locator associated with the MPQ
//allowing for affecting now non minimum values in the MPQ.

void Edge::set_out_locator(locator<Vertex*> * loc)
{
	e_loc=loc;
}

locator <Vertex*> * Edge::get_out_locator()
{
	return e_loc;
}

void Edge::terminate_out_locator()
{
	e_loc=0;
}
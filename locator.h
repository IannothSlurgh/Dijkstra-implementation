#ifndef LOCATOR_GUARD
#define LOCATOR_GUARD
#include "node.h"

//The sole purposes of locator are to occupy dynamic memory,
//keep an accurate pointer to their node, as well as the 
//index a node may have in a container. Locators do not shift 
//in memory, allowing pointers to them to remain accurate.

template <class T> class node;

template <class T>
class locator
{
	int index;
	node<T> * point;
	public:
	locator(node<T> * n=0)
	{
		point = n;
		index=-1;
	}
	void update(node<T> * n)
	{
		point=n;
	}
	void update(int i)
	{
		index=i;
	}
	void update(node<T> * n, int i)
	{
		point=n;
		index=i;
	}
	node<T> * get_location()
	{
		return point;
	}
	int get_index()
	{
		return index;
	}
};
#endif

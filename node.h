#ifndef NODE_GUARD
#define NODE_GUARD
#include "locator.h"
#include <iostream>

template <class T> class locator;

using namespace std;
template <class T>
class node
{
	T elem;
	locator<T> * my_loc;
	int key;
	public:
	node(T input, int k=0)
	{
		elem=input; 
		key=k;
		my_loc=new locator<T>(this);
	}
	int get_key() const
	{
		return key;
	}
	T get_value() const
	{
		return elem;
	}
	void change_key(int i)
	{
		key=i;
	}
	void swap_node(node<T> a, node<T> b)
	{
		T temp= b.elem;
		b.elem=a.elem;
		a.elem=temp;
		int k = b.key;
		b.key=a.key;
		a.key=k;
	}
	void dispose()
	{
		delete my_loc;
		my_loc=0;
	}
	locator<T> * get_locator()
	{
		return my_loc;
	}
	void update_locator()
	{
		my_loc->update(this);
	}
	void update_locator(int i)
	{
		my_loc->update(i);
	}
};

template <class T>
ostream& operator<<(ostream& out, const node<T>& n)
{
	out<<"("<<n.get_key()<<","<<n.get_value()<<")";
	return out;
}
#endif

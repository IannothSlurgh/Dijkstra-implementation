#ifndef MPQ_GUARD
#define MPQ_GUARD
#define ancestor minimum_priority_queue<T>
#include "node.h"
#include "locator.h"
#include "supp_exception.h"
#include <vector>
#include <climits>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cstdlib>

template <class T> class node;
template <class T> class locator;
using namespace std;

//Modified 4/29/13 to store the number of comparisons it makes.
template <class T>
class comparator: public std::binary_function< node<T>, node<T>, bool>     
{
	int comparisons;
	public:
	void reset_comparisons(){comparisons=0;}
	int get_comparisons(){return comparisons;}
	bool operator()(const node<T> a, const node<T> b)
	{
		++comparisons;
		return a.get_key()>b.get_key();
	}
};

template <class T>
class minimum_priority_queue
{
	protected:
	std::vector< node<T> > storage;
	public:
	virtual ~minimum_priority_queue()
	{
		for(unsigned int i=0;i<storage.size();++i)
		{
			storage.at(i).dispose();
		}
	}
	//Is this priority queue empty?
	bool is_empty()
	{
		return storage.size()==0;
	}
	node<T> get_data(int i) const
	{
		return storage.at(i);
	}
	unsigned int get_size() const
	{
		return storage.size();
	}
	//Modified 4/28/13 to return a locator.
	virtual locator<T>* insert(int key, T elem)
	{
		try
		{
			if(key<0)
				throw negative_key_exception();
			else
			{
				node<T> n(elem, key);
				bool update_all;
				update_all=storage.size()==storage.capacity();//Check to see if size will exceed capacity.
				storage.push_back(n);
				locator<T>* l = storage.at(storage.size()-1).get_locator();
				if(update_all)
					for(unsigned int i = 0;i<storage.size();++i)
					{
						storage.at(i).update_locator();//Fix all the locator's pointers.
					}
				storage.at(storage.size()-1).update_locator(storage.size()-1); //Give the new locator a valid index.
				return l;
			}
		}
		catch(negative_key_exception())
		{
			cerr<<negative_key_exception();
			return 0;
		}
	}
	
	virtual locator<T>* min()
	{
		if(!is_empty())//Terminate operations otherwise.
		{
			int min_key=INT_MAX;
			int loc=0;
			for(unsigned int i=0;i<storage.size();++i)
			{
				if(storage.at(i).get_key()<=min_key)
				{
					min_key=storage.at(i).get_key();
					loc=i;//Position of lowest key node.
				}
			}
			return storage.at(loc).get_locator();
		}
		else
		{
			throw empty_priority_queue_exception();
		}
		return 0;
	}
	//Modified 4/29/13 because of coredumps involving two attempted removes.
	virtual int remove(locator<T>* loc)//loc is assumed to be valid.
	{
		int index=loc->get_index();//Get index of node from locator.
		storage.at(index).dispose();
		storage.erase(storage.begin()+index);//Tell vector to delete node at that index.
		for(unsigned int i=index;i<storage.size();++i)
		{
			//Fix all locators of nodes following the removed node.
			storage.at(i).update_locator();
			storage.at(i).update_locator(i);
		}
		return 0;
	}
	//Modified 4/28/13 To be a "setter" and not a subtracter.
	virtual int decrease_key(locator<T>* loc, int i)
	{
		try
		{
			if(i<0)
			{
				throw negative_key_exception();
			}
			else
				loc->get_location()->change_key(i);
		}
		catch(negative_key_exception())
		{
			cerr<<negative_key_exception();
		}
		return 1;
	}
	
	//Fill the container with a text file's data.
	//Commented out 4/28/13 because I needed a priority queue of objects 
	//that would have no >> operator, and no required input mechanism like below.
	virtual void create_priority_queue(string s)//Where s is filename
	{
	/*	T temp;
		int key;
		ifstream i(s.c_str());
		try
		{
			if(i)
			{
				storage.empty(); //Clear out any old priority queue data.
				while(i)
				{
					i>>temp;
					i>>key;
					if(i)
						insert(key, temp);//If a pair is successfully gathered, insert.
				}
			}
			else
				throw invalid_file_exception(s);
		}
		catch(invalid_file_exception(s))
		{
			cerr<<invalid_file_exception(s);
		}*/
	}
};
//Derived class below.
template <class T>
class minimum_priority_queue_heap: public minimum_priority_queue<T> 
{
	public:
	/*minimum_priority_queue_heap():minimum_priority_queue<T>(){}*/
	locator<T>* min()
	{
		if(!ancestor::is_empty())//Atleast one node.
		{
			return ancestor::storage.at(0).get_locator();//That first node is min due to heap structuring.
		}
		else
			throw empty_priority_queue_exception();
		return 0;
	}
	//Modified 4/28/13 to return the locator of the added object.
	locator<T>* insert(int key, T elem)
	{
		try
		{
			if(key<0)
				throw negative_key_exception();
			else
			{
				node<T> n(elem, key);
				ancestor::storage.push_back(n);
				locator<T>* l=ancestor::storage.at(ancestor::storage.size()-1).get_locator();
				reorganize_heap_small();
					for(unsigned int i = 0;i<ancestor::storage.size();++i)
					{
						//Fix all the locator's pointers.
						//Must occur on every insert because the position
						//of the new node is uncertain after being put in heap.
						ancestor::storage.at(i).update_locator();
						ancestor::storage.at(i).update_locator(i);
					}
				return l;
			}
		}
		catch(negative_key_exception())
		{
			cerr<<negative_key_exception();
			return 0;
		}	
	}
	//Modified 4/29/13 for comparisons.
	int remove(locator<T>* loc)
	{
		int compares=0;
		compares+=ancestor::remove(loc);
		compares+=reorganize_heap();
		return compares;
	}
	bool compare(node<T> a, node<T> b) const
	{
		return a.get_key()>b.get_key();
	}
	void create_priority_queue(string s)
	{
		ancestor::create_priority_queue(s);
		reorganize_heap();
	}
	//Modified 4/29/13 for comparisons.
	int decrease_key(locator<T>* loc, int i)
	{
		int compares=0;
		int index=loc->get_index();
		compares+=ancestor::decrease_key(loc, i);
		compares+=reorganize_heap();
		return compares;
	}
	//Modified 4/29/13 for comparisons.
	int reorganize_heap()
	{
		comparator<T> c;
		c.reset_comparisons();
		make_heap(ancestor::storage.begin(), ancestor::storage.end(), c);
		for(unsigned int i = 0;i<ancestor::storage.size();++i)
		{
			ancestor::storage.at(i).update_locator();//Fix all the locator's pointers.
			ancestor::storage.at(i).update_locator(i);
		}
		return c.get_comparisons();
	}
	//Modified 4/29/13 for comparisons.
	int reorganize_heap_small()
	{
		comparator<T> c;
		c.reset_comparisons();
		push_heap(ancestor::storage.begin(), ancestor::storage.end(), c);
		return c.get_comparisons();
	}
};

template <class T>
ostream& operator<<(ostream& out, const minimum_priority_queue<T>& q)
{
	out<<"{";
	for(int i =0; i<q.get_size();++i)
	{
		out<<q.get_data(i);
	}
	out<<"}\n";
	return out;
}

template <class T>
ostream& operator<<(ostream& out, const minimum_priority_queue_heap<T>& q)
{
	out<<"{";
	for(unsigned int i =0; i<q.get_size();++i)
	{
		out<<q.get_data(i);
	}
	out<<"}\n";
	return out;
}

#undef ancestor
#endif

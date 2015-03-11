#ifndef SUPP_EXCEPTION_GUARD
#define SUPP_EXCEPTION_GUARD

#include "RuntimeException.h"
#include <iostream>
using namespace std;

class invalid_file_exception: public RuntimeException
{
	public:
	invalid_file_exception(string s) : RuntimeException(s.append(" could not open.\n")) {} //Report the filename that failed opening.
};

class negative_key_exception: public RuntimeException
{
	public:
	negative_key_exception(): RuntimeException("Negative keys are not valid.\n"){}
};

class empty_priority_queue_exception: public RuntimeException
{
	public:
	empty_priority_queue_exception(): RuntimeException("One find an object in an empty container.\n"){}
};
#endif

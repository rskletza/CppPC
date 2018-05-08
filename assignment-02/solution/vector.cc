#include "vector.h"
#include <stdexcept>
#include <iostream>

namespace cpppc 
{

Vector::Vector()
{
	_count = 0;
	_values = nullptr;
}

Vector::~Vector()
{
	delete[] _values;
}

Vector::Vector(const Vector & other)
: _count(other._count)
{
	_values = new VectorElement[_count];
	for (size_t i = 0; i < _count; i++)
	{
		_values[i] = other._values[i];
	}
}

void Vector::operator=(const Vector & other)
{
	if (this != &other)
	{
		_count = other._count;
		if (_count > 0)
		{
			for (size_t i = 0; i < _count; i++)
			{
				_values[i] = other._values[i];
			}
		}
	}
}

bool Vector::operator==(const Vector & other) const
{
	if (this == &other)
	  return 1; 
	if (_count != other.size())
		return 0;
	else if (_count == 0)
		return 1;
	else
		for (size_t i = 0; i<_count; i++)
		{
			if (this->_values[i] != other[i])
				return 0;
		}
	return 1;
}

size_t Vector::size() const
{
	return _count;
}

bool Vector::empty() const
{
	return (_count == 0);
}

VectorIterator Vector::begin() const
{
	return &_values[0];
}

VectorIterator Vector::end() const
{
	return &_values[_count];
}

VectorElement & Vector::operator[](size_t index) const
{
	if (index >= _count)
		throw std::out_of_range ("index out of range");
	return _values[index];
}

void Vector::push_back(const VectorElement val)
{
	VectorElement * newvalues = new VectorElement[_count + 1];
	for (size_t i = 0; i < _count; i++)
	{
		newvalues[i] = _values[i];
	}
	newvalues[_count] = val;
	_values = newvalues;
	++_count;
}

VectorElement Vector::pop_back()
{
	if (empty())
		return 0;
	VectorElement val = _values[_count-1];
	VectorElement * newvalues = new VectorElement[_count - 1];
	_count--;
	for (size_t i = 0; i < _count; i++)
	{
		newvalues[i] = _values[i];
	}
	_values = newvalues;
	return val;
}


void Vector::push_front(VectorElement val)
{
	VectorElement * newvalues = new VectorElement[_count + 1];
	for(size_t i = 0; i<_count ;i++)
	{
		newvalues[i+1] = _values[i];
	}
	_values = newvalues;
	*(begin()) = (VectorElement) val;
	++_count;
}

VectorElement Vector::pop_front()
{
	if (empty())
		return 0;
	VectorElement val = *(begin());
	*(begin()) = 0;
	VectorElement * newvalues = new VectorElement[_count - 1];
	--_count;
	for(size_t i=0;i<_count;i++)
	{
		newvalues[i] = _values[i+1];
	}
	_values = newvalues;
	return val;
}

void Vector::reverse()
{
	if (empty())
		return;
	Vector newv = Vector();
	for(size_t i = 0; i<_count; i++)
	{
		newv.push_front((*this)[i]);
	}
	*this = newv;
}
}

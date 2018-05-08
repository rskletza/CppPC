#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "deque.h"

Deque * deque__new()
{
	Deque * d = (Deque*) malloc(sizeof(int)+sizeof(DequeValue *)); 
	d->_count = 0;
	d->_values = NULL;
	return d;
}
Deque * deque__copy(Deque * orig)
{
	Deque * newd = deque__new();
	newd = deque__assign(newd, orig);
	return newd;
}

void deque__delete(Deque * _this)
{
	free(_this->_values);
	free(_this);
	_this = NULL;
} 

Deque * deque__assign(Deque * _this, Deque * other)
{
	if (_this->_count != other->_count)
	{
		_this->_values = (DequeValue*) realloc(_this->_values, sizeof(DequeValue)*other->_count);
		_this->_count = other->_count;
	}
	memcpy(_this->_values, other->_values, sizeof(DequeValue)*_this->_count);
	return _this;
}

int deque__equals(Deque * d1, Deque * d2)
{
	if (d1->_count != d2->_count)
		return 0;
	else if (d1->_count == 0)
		return 1;
	else
		return (0 == memcmp(d1->_values, d2->_values, sizeof(DequeValue)*d1->_count));
} 

int deque__size(Deque * _this)
{
	return _this->_count;
}

int deque__empty(Deque * _this)
{
	return (_this->_count == 0);
}

void deque__push_back(Deque * _this, DequeValue val)
{
	_this->_values = (DequeValue *) realloc(_this->_values, sizeof(DequeValue)*_this->_count+1);
	_this->_values[_this->_count] = (DequeValue) val;
	_this->_count++;
}

DequeValue deque__pop_back(Deque * _this)
{
	if (deque__empty(_this))
		return 0;
	_this->_count--;
	DequeValue val = _this->_values[_this->_count];
	_this->_values[_this->_count] = 0;
	_this->_values = (DequeValue *) realloc(_this->_values, sizeof(DequeValue)*_this->_count);
	return val;
}

void deque__push_front(Deque * _this, DequeValue val)
{
	_this->_count++;
	_this->_values = (DequeValue *) realloc(_this->_values, sizeof(DequeValue)*_this->_count);
	int i;
	for(i=_this->_count-1;i>0;i--)
	{
		_this->_values[i] = _this->_values[i-1];
	}
	_this->_values[0] = (DequeValue) val;
	

}

DequeValue deque__pop_front(Deque * _this)
{
	if (deque__empty(_this))
		return 0;
	DequeValue val = _this->_values[0];
	_this->_values[0] = 0;
	int i;
	for(i=0;i<_this->_count-1;i++)
	{
		_this->_values[i] = _this->_values[i+1];
	}
	_this->_count--;
	_this->_values = (DequeValue *) realloc(_this->_values, sizeof(DequeValue)*_this->_count);
	return val;
}

Deque * deque__reverse(Deque * d)
{
	if (d->_count == 0)
		return d;
	Deque * newd = deque__new();
	while(!deque__empty(d))
	{
		deque__push_front(newd, deque__pop_front(d));
	}
	deque__delete(d);
	return newd;
}

//void deque__init(Deque * _this, int count)
//{
//
//}
//
//void deque__print(Deque * _this)
//{
//
//}

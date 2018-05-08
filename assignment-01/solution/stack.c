#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

Stack * stack__new()
{
	Stack * v = (Stack*) malloc(sizeof(StackValue)+sizeof(StackValue *)); 
	v->_count = 0;
	v->_values = NULL;
	return v;
}

Stack * stack__copy(Stack * orig)
{
	Stack * news = stack__new();
	news = stack__assign(news, orig);
	return news;
	
}

void stack__delete(Stack * _this)
{
	free(_this->_values);
	free(_this);
	_this = NULL;

}

Stack * stack__assign(Stack * _this, Stack * other)
{
	if (_this->_count != other->_count)
	{
		_this->_values = (StackValue*) realloc(_this->_values, sizeof(StackValue)*other->_count);
		_this->_count = other->_count;
	}
	memcpy(_this->_values, other->_values, sizeof(StackValue)*_this->_count);
	return _this;

}

int stack__equals(Stack * s1, Stack * s2)
{
//  if (v1 == v2)
//	  return 1; 
//  return 0;
	if (s1->_count != s2->_count)
		return 0;
	else if (s1->_count == 0)
		return 1;
	else
		return (0 == memcmp(s1->_values, s2->_values, sizeof(StackValue)*s1->_count));
}

int stack__size(Stack * _this)
{

	return _this->_count;
}

int stack__empty(Stack * _this)
{
	
	return (_this->_count == 0);
}

void stack__push(Stack * _this, StackValue val)
{
	_this->_values = (StackValue *) realloc(_this->_values, sizeof(StackValue)*_this->_count+1);
	_this->_values[_this->_count] = (StackValue) val;
	_this->_count++;

}

StackValue stack__pop(Stack * _this)
{
	if (stack__empty(_this))
		return 0;
	_this->_count--;
	StackValue val = _this->_values[_this->_count];
	_this->_values[_this->_count] = 0;
	_this->_values = (StackValue *) realloc(_this->_values, sizeof(StackValue)*_this->_count);
	return val;

}

Stack * stack__reverse(Stack * _this)
{
	if (stack__empty(_this))
		return _this;
	Stack * news = stack__new();

	while(!stack__empty(_this))
	{
		stack__push(news, stack__pop(_this));
	}
	stack__delete(_this);
	return news;
}

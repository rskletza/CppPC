#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

//int main()
//{
//	Vector * v1 = vector__new();
//	vector__init(v1, 4);
//	vector__print(v1);
//	v1 = vector__reverse(v1);
//	vector__print(v1);
//	printf("size: %d\n", v1->_count);
//}

Vector * vector__new()
{
	Vector * v = (Vector*) malloc(sizeof(VectorValue)+sizeof(VectorValue *)); 
	v->_count = 0;
	v->_values = NULL;
	return v;
}

void vector__init(Vector * _this, int count)
{
	int i;
	_this->_values = (VectorValue*) malloc(sizeof(VectorValue)*count);
	for(i = 0; i<count; i++)
	{
		(_this->_values[i])= i;
	}
	_this->_count = count;
}

void vector__print(Vector * _this)
{
	int i;
	for(i = 0; i<_this->_count; i++)
	{
		printf("value %d: %d ", i, (_this->_values[i]));
	}
	printf("size: %d\n", _this->_count);

}

Vector * vector__copy(Vector * old)
{
	Vector * newv = vector__new();
	newv = vector__assign(newv, old);
	return newv;
}

void vector__delete(Vector * _this)
{
	free(_this->_values);
	free(_this);
	_this = NULL;
}


Vector * vector__assign(Vector * _this, Vector * other)
{
	if (_this->_count != other->_count)
	{
		_this->_values = (VectorValue*) realloc(_this->_values, sizeof(VectorValue)*other->_count);
		_this->_count = other->_count;
	}
	memcpy(_this->_values, other->_values, sizeof(VectorValue)*_this->_count);
	return _this;
}


int vector__equals(Vector * v1, Vector * v2)
{
  if (v1 == v2)
	  return 1; 
	if (v1->_count != v2->_count)
		return 0;
	else if (v1->_count == 0)
		return 1;
	else
		return (0 == memcmp(v1->_values, v2->_values, sizeof(VectorValue)*v1->_count));
}

int vector__size(Vector * _this)
{
	return _this->_count;
}

int vector__empty(Vector * _this)
{
	return (_this->_count == 0);
}

VectorIterator vector__begin(Vector * _this)
{
	return &_this->_values[0];
}

VectorIterator vector__end(Vector * _this)
{
	return &_this->_values[_this->_count];
}

void vector__push_back(Vector * _this, VectorValue val)
{
	_this->_values = (VectorValue *) realloc(_this->_values, sizeof(VectorValue)*_this->_count+1);
	*(vector__end(_this)) = (VectorValue) val;
	_this->_count++;
}

VectorValue vector__pop_back(Vector * _this)
{
	if (vector__empty(_this))
		return 0;
	_this->_count--;
	VectorValue val = *(vector__end(_this));
	*(vector__end(_this)) = 0;
	_this->_values = (VectorValue *) realloc(_this->_values, sizeof(VectorValue)*_this->_count);
	return val;
}


void vector__push_front(Vector * _this, VectorValue val)
{
	_this->_count++;
	_this->_values = (VectorValue *) realloc(_this->_values, sizeof(VectorValue)*_this->_count);
	int i;
	for(i=_this->_count-1;i>0;i--)
	{
		_this->_values[i] = _this->_values[i-1];
	}
	*(vector__begin(_this)) = (VectorValue) val;
	
}

VectorValue vector__pop_front(Vector * _this)
{
	if (vector__empty(_this))
		return 0;
	VectorValue val = *(vector__begin(_this));
	*(vector__begin(_this)) = 0;
	int i;
	for(i=0;i<_this->_count-1;i++)
	{
		_this->_values[i] = _this->_values[i+1];
	}
	_this->_count--;
	_this->_values = (VectorValue *) realloc(_this->_values, sizeof(VectorValue)*_this->_count);
	return val;
}

VectorValue vector__at(Vector * _this, VectorValue offset)
{
	if (offset >= _this->_count)
	{
		return 0.0;
	}
	else
	{
		return (VectorValue) _this->_values[(int)offset];
	}
}

Vector * vector__reverse(Vector * v)
{
	if (vector__empty(v))
		return v;
	Vector * newv = vector__new();
	int i;
	for(i = 0; i<v->_count; i++)
	{
		vector__push_front(newv, vector__at(v, i));
	}
	vector__delete(v);
	return newv;
}
//more memory efficient version of reverse
//Vector * vector__reverse(Vector * v)
//{
//	if (v->_count == 0)
//		return v;
//	Vector * newv = vector__new();
//	newv->_values = (VectorValue*) malloc(sizeof(VectorValue)*v->_count);
//	newv->_count = v->_count;
//
//	int i;
//	for(i = 0; i<newv->_count; i++)
//	{
//		newv->_values[i] = v->_values[v->_count - i - 1];
//	}
//	vector__delete(v);
//	return newv;
//}

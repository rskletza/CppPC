#ifndef CPPPC__02__VECTOR_H__INCLUDED
#define CPPPC__02__VECTOR_H__INCLUDED

#include <string>

namespace cpppc 
{

typedef int             VectorElement;
typedef VectorElement *   VectorIterator;


class Vector
{
public:

	Vector();
	Vector(const Vector & other);

	~Vector();

	void operator=(const Vector & other);
	
	bool operator==(const Vector & other) const;

/////////// Interface of Vector concept: //////////////////////

	size_t size() const;
	bool empty() const;
	
	VectorIterator begin() const;
	VectorIterator end() const;

	//VectorElement & operator[](int index);
	//const VectorElement & operator[](int index) const;

	VectorElement & operator[](size_t index) const;

	void push_back(const VectorElement value);
	VectorElement pop_back();

	void push_front(VectorElement value);
	VectorElement pop_front();

	void		reverse();

private:
	size_t			_count;
	//TODO This doesn't seem to be cpp style, would we normally use a reference? and then an iterator instead of a pointer?
	VectorElement * _values = nullptr;

}; //class Vector

} //namespace cpppc

#endif // CPPPC__01__VECTOR_H__INCLUDED

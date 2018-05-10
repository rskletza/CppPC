#ifndef CPPPC__A03__FORWARD_LIST_H__INCLUDED
#define CPPPC__A03__FORWARD_LIST_H__INCLUDED

#include <iterator>
#include <iostream>

namespace cpppc {

  template <typename ValueT, ValueT default_value = ValueT()>
  class forward_list;

  // forward_list<int32_t, -1>
  template <typename ValueT, ValueT default_value>
 //   ValueT   default_value = ValueT()>
  class forward_list {
    typedef forward_list<ValueT, default_value> self_t;

  public:
    struct forward_list_node {
       forward_list_node * next;
       ValueT      value;
    };
    // forward_list<T>::iterator
    class iterator {
       typedef forward_list<ValueT, default_value> forward_list_t;
       typedef typename forward_list_t::forward_list_node forward_list_node_t;
       typedef typename forward_list_t::iterator self_t;

    public:
       using iterator_category = std::forward_iterator_tag;
       using value_type = ValueT;
       using difference_type = std::ptrdiff_t;
       using pointer = value_type *;
       using reference = value_type &;

       iterator() = delete;

       iterator(forward_list_node & _node)
       : _forward_list_node(&_node)
       { }


       iterator & operator++() {
          _forward_list_node = _forward_list_node->next;
          return *this;
       }

       iterator operator++(int) {
          iterator old = *this;
          _forward_list_node = _forward_list_node->next;
          return old;
       }

       const ValueT & operator*() const {
         return _forward_list_node->value;
       }

       ValueT & operator*() {
         return _forward_list_node->value;
       }

       bool operator==(const iterator rhs) const
       {
	   return (this == &rhs || _forward_list_node == rhs._forward_list_node);
       }

       bool operator!=(const iterator rhs) const
       {
         return  !(*this == rhs);
       }

    private:
       forward_list_node * _forward_list_node;

    };

    
  public:
    forward_list()
    : _begin(iterator((*this)._tail))
    , _end(iterator((*this)._tail))
    { }

    forward_list(const self_t & other) = default;
    self_t & operator=(const self_t & rhs) = default;

    bool operator==(const self_t & other) const
    {
	//TODO compare begin and end
	if (this == &other) //identity
	    return true;

	else if ((*this).size() != other.size())
	    return false;

	else if ((*this).size() == 0) //hacky
	    return true;

	iterator ithis = begin();
	iterator iother  = other.begin();

	while (ithis != (*this).end() && iother != other.end())
	{
	    if (*ithis != *iother)
		return false;
	    ++ithis;
	    ++iother;
	}

	return true; 
    }

    iterator begin() const 
    { 
	return _begin; 
    }

    iterator end() const 
    { 
	return _end; 
    }

    size_t size() const
    {
	return _size;
//	size_t count = 0;
//	for(iterator i = *this.begin(); i!=*this.end(); ++i)
//	{
//		++count;	
//	}
//	return count;
    }

    bool empty() const
    {
//	return (_head == _tail);
	return (_size == 0);
    }

    const ValueT & front() const
    {
	return _head.value;
    }

    void push_front(const ValueT value)
    {
	_head = new forward_list_node{_head, value};
	_begin = iterator(*_head);
	++_size;
    }

    ValueT pop_front()
    {
	if (size() == 0)
	    return default_value;

	forward_list_node * tmp = _head;
	ValueT val = tmp->value;
	_head = _head->next;
	delete tmp;

	_begin = iterator(*_head);
	--_size;
	return val;
    }

    void print_list()
    {
	iterator i = begin();
	int stop = 10;

	std::cout << "list: ";
	while (i != end() && stop != 0)
	{
	    std::cout << *i << " ";
	    ++i;
	    --stop;
	}
	    std::cout << "\n";
    }
	
  private:
    // same as = { }
    forward_list_node _tail = { nullptr, default_value };
    forward_list_node * _head = &_tail;
    size_t _size = 0;


    iterator  _begin;
    iterator  _end;
  };

}
#endif // CPPPC__A03__FORWARD_LIST_H__INCLUDED

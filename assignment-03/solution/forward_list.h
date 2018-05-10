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
       iterator() = delete;

       iterator(forward_list_node & _node)
       : _forward_list_node(&_node)
       { }

       // const my_container & c;
       // c[23] = "foo";
       // c.push_back("foo"); <-- 'nouh'

       //TODO WARUM INKREMENTIERT DER POINTER NICHT?!?!!?!
       iterator & operator++() {
//	  std::cout << "old address: " << &_forward_list_node << "\n";
//	  std::cout << "next address: " << _forward_list_node->next << "\n";
          _forward_list_node = _forward_list_node->next;
//	  std::cout << "new address: " << &_forward_list_node << "\n";
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

    // forward_list<uint32_t>(forward_list<int32_t>()) says 'nouh'
    forward_list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;

    bool operator==(const self_t & other) const
    {
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

    // forward_list<int> l;
    // l_begin = l.begin();
    // ++l_begin;
    iterator begin() const 
    { 
	return _begin; 
    }
    // forward_list<T> l;
    // *l.end();
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
	std::cout << "first value " << *_begin << "\n";
	forward_list_node new_node;
	std::cout << "head:\t" <<  &(_head) << "\n";
	std::cout << "tail:\t" << &(_tail) << "\n";
	std::cout << "new node address: " << &new_node << "\n";

       	new_node.next = &_head;
	std::cout << "new node next address (should be same as head): " << new_node.next << "\n";
	std::cout << "new node next value: " << (new_node.next)->value << "\n";
	new_node.value = value;
	_head = new_node;	
	std::cout << "head address (should be same as new node addr): " << &_head << "\n";
	std::cout << "head value: " << _head.value << "\n";
	std::cout << "second value " << (_head.next)->value << "\n";
	
	_begin = iterator(_head);
	++_size;
	print_list();
    }

    ValueT pop_front()
    {
	if (size() == 0)
	    return default_value;

	ValueT val = _head.value;
	_head = *(_head.next);
	_begin = iterator(_head);
	--_size;
	print_list();
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
	
    

//    iterator insert(iterator pos, const ValueT value);
    
  private:
    // same as = { }
    forward_list_node _tail = { nullptr, default_value };
    forward_list_node _head = _tail;
    size_t _size = 0;

    // self_t * this

    iterator  _begin; // = *this;
    iterator  _end;
  };

}
#endif // CPPPC__A03__FORWARD_LIST_H__INCLUDED

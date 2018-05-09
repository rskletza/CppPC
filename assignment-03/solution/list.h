#ifndef CPPPC__A03__LIST_H__INCLUDED
#define CPPPC__A03__LIST_H__INCLUDED

#include <iterator>
#include <iostream>

namespace cpppc {

  template <typename ValueT, ValueT default_value = ValueT()>
  class list;

  // list<int32_t, -1>
  template <typename ValueT, ValueT default_value>
 //   ValueT   default_value = ValueT()>
  class list {
    typedef list<ValueT, default_value> self_t;

  public:
    struct list_node {
       list_node * next;
       ValueT      value;
    };
    // list<T>::iterator
    class iterator {
       typedef list<ValueT, default_value> list_t;
       typedef typename list_t::list_node list_node_t;
       typedef typename list_t::iterator self_t;

    public:
       iterator() = delete;

       iterator(list_node & _node)
       : _list_node(&_node)
       { }

       // const my_container & c;
       // c[23] = "foo";
       // c.push_back("foo"); <-- 'nouh'

       iterator & operator++() {
          _list_node = _list_node->next;
          return *this;
       }

       iterator operator++(int) {
          iterator old = *this;
          _list_node = _list_node->next;
          return old;
       }

       const ValueT & operator*() const {
         return _list_node->value;
       }

       ValueT & operator*() {
         return _list_node->value;
       }

       bool operator==(const iterator rhs) const
       {
	   return (this == &rhs || _list_node == rhs._list_node);
       }

       bool operator!=(const iterator rhs) const
       {
         return  !(*this == rhs);
       }

    private:
       list_node * _list_node;

    };

    
  public:
    list()
	//here we define _begin and _end as iterators of this list object
    : _begin(iterator((*this)._head))
    , _end(iterator((*this)._tail))
    { }

    // list<uint32_t>(list<int32_t>()) says 'nouh'
    list(const self_t & other)             = default;
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
	    std::cout << "marker 1\n";
	    if (*ithis != *iother)
		return false;
	    ++ithis;
	    ++iother;
	    std::cout << "marker 2\n";
	}

	return true; 
    }

    // list<int> l;
    // l_begin = l.begin();
    // ++l_begin;
    iterator begin() const 
    { 
	return _begin; 
    }
    // list<T> l;
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

    const ValueT & front()
    {
	return _head._value;
    }

    const list_node & back()
    {
	return _tail.value;
    }

    //TODO: Ich muss ja auf das next-Feld des ehemaligen letzten Elements zugreifen, um es auf das neue letzte zu setzen. Dazu muss ich auf das letzte Element der Liste zugreifen können. Dafür ist wahrscheinlich _tail gedacht. Allerdings verwende ich _tail (bzw es war ja von dir ursprünglich auch als static definiert) als leeres abschließendes Element. Brauche ich ein bestimmtes Feld, dass den "Inhalt" dieses letzten Elements deklariert, oder kann ich das direkt in den Konstruktor von _end() einfügen? (Zeile 78ff). Eigentlich brauche ich ja schon ein bestimmtes Member-Element, dass das abschließende ist.
    void push_back(const ValueT value)
    {
	list_node new_node;
       	new_node.next = &_tail;
	new_node.value = value;
	iterator i = begin();
	while (i != back())
	{
	    ++i;
	}
	_ = &new_node;
	++_size;
    }

    ValueT pop_back()
    {
//	if (size() == 0)
//	    return default_value;
//
//	iterator i = begin();
//	while (i != back())
//	{
//		++i;
//	}
//	ValueT val = *i;
//	delete _tail;
//	_tail = new_tail;
//	return val;
    }

    void push_front(const ValueT value)
    {

    }

    ValueT pop_front()
    {

    }

//    iterator insert(iterator pos, const ValueT value);
    
  private:
    // same as = { }
    list_node _head = { nullptr, default_value };
    list_node _tail = { nullptr, default_value };
    size_t _size = 0;

    // self_t * this

    iterator  _begin; // = *this;
    iterator  _end;
  };

}
#endif // CPPPC__A03__LIST_H__INCLUDED

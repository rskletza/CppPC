#include <iterator>

namespace cpppc {

  // list<int32_t, -1>
  template <
    typename ValueT,
    ValueT   default_value = ValueT()>
  class list {
    typedef list<ValueT, default_value> self_t;

  public:
    // list<T>::iterator
    class iterator {
	//TODO I get an "expected nested-name-specifier" error here.. why?
       typedef typename list<ValueT, default_value> list_t;
       typedef typename list_t::list_node list_node_t;
       typedef typename list_t::iterator self_t;
    public:
       iterator() = delete;

       iterator(const list_t & list)
       : _list(list)
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

       bool operator==(const self_t & rhs) {
	   return (this == &rhs || _list_node == rhs._list_node);
       }

       bool operator!=(const self_t & rhs)
       {
         return  !(*this == rhs);
       }

    private:
       list_node_t * _list_node;
       //TODO: you didn't put list in here, but you define it in line 23. Am I right in thinking it needs to go here, too?
       list_t _list;
    };

    struct list_node {
       list_node * next;
       ValueT      value;
    };
    
  public:
    list()
	//here we define _begin and _end as iterators of this list object
    : _begin(iterator(*this))
    , _end(iterator(*this))
    { }

    // list<uint32_t>(list<int32_t>()) says 'nouh'
    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;

    bool operator==(const list & other)
    {
//	if (this == &other) //identity
//	    return true;
//	iterator i1 = *this.begin();
//	iterator i2 = other.begin();
//	TODO: Am I supposed to use _begin and _end to iterate? I would have to reset them at the end though wouldn't I?
//
//	while (i1 != *this.end() || i2 != other.end())
//	{
//	    if (*i1 != *i2)
//		return false;
//	    ++i1;
//	    ++i2;
//	}
//
//	return !(i1 == *this.end() && i2 == other.end());

    }

    // list<int> l;
    // l_begin = l.begin();
    // ++l_begin;
    iterator begin()  { _begin; }
    //TODO: is this the same as saying { return _begin; } ?
    // list<T> l;
    // *l.end();
    iterator end()    { _end; }

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

    const list_node & front()
    {
	return _head;
    }

    const list_node & back()
    {
	return _tail;
    }

    //here there be dragons
    void push_back(const ValueT value)
    {
//	list_node new_node = new list_node;
//	back().next = &new_node;
//	_tail = new_node;
//	new_node.value = value;
//	new_node.next = end();	
//	++_size;
    }

    ValueT pop_back()
    {
//	ValueT val = back().value;
//	iterator(*this) i = begin();
//	while (i != back())
//	{
//		++i;
//	}
//	list_node new_tail = *i;
//	delete back();
//	_tail = new_tail;
//	return val;
    }

    void push_front(const ValueT value);
    ValueT pop_front();

//    iterator insert(iterator pos, const ValueT value);
    
  private:
    // same as = { }
    list_node _head        = { nullptr, default_value };
    static list_node _tail = { nullptr, default_value };
    size_t _size = 0;

    // self_t * this

    iterator  _begin = *this;
    iterator  _end;
  };

}


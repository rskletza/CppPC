#ifndef CPPPC__A06__FORWARD_LIST_H__INCLUDED
#define CPPPC__A06__FORWARD_LIST_H__INCLUDED

#include "forward_iterator_base.h"
#include <iostream>
#include <iterator>

namespace cpppc {

template <typename ValueT, ValueT default_value = ValueT()>
class forward_list;

// template <class ListType> class iterator;

template <typename ValueT, ValueT default_value>
class forward_list {
  //    typedef forward_list<ValueT, default_value> self_t;
  //    typedef typename forward_list<const ValueT, default_value>::iterator
  //    const_iterator;
  // typedef forward_list_t::iterator iterator;
  using self_t     = forward_list<ValueT, default_value>;
  using value_type = ValueT;
public:
  struct forward_list_node {
    forward_list_node *next;
    ValueT value;
  };

  // forward_list<T>::iterator
  template <class ListType>
      class flist_iterator
      : public forward_iterator_base<
                  forward_list<ValueT, default_value>::flist_iterator<ListType>,
                  std::ptrdiff_t,
                  ValueT,
                  ValueT *,
                  ValueT &,
                  const ValueT & >
  {
    using forward_list_t      = forward_list<ValueT, default_value>;
    using forward_list_node_t = forward_list_t::forward_list_node;
    using self_t              = forward_list_t::flist_iterator<ListType>;
    using base_t              = forward_iterator_base<
                                   self_t,
                                   std::ptrdiff_t,
                                   ValueT,
                                   ValueT *,
                                   ValueT &,
                                   const ValueT &
                                >;

    friend forward_list_t; // for insert_after

  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename ListType::value_type;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type *;
    using reference         = value_type &;
    using const_reference   = const value_type &;

    flist_iterator() = default;
    flist_iterator(self_t &&) = default;
    flist_iterator(const self_t &) = default;
    ~flist_iterator() = default;
    self_t &operator=(self_t &&) = default;
    self_t &operator=(const self_t &) = default;

    flist_iterator(forward_list_node *_node)
      : _forward_list_node(_node) {}

    void increment() {
      _forward_list_node = _forward_list_node->next;
    }

    const_reference dereference() const {
      return _forward_list_node->value;
    }

    reference dereference() {
      return _forward_list_node->value;
    }

    bool operator==(const self_t & rhs) const {
        return base_t::operator==(rhs) && 
               ( _forward_list_node == rhs._forward_list_node );
    }
    
    bool operator!=(const self_t & rhs) const {
      return  !(*this == rhs);
    }

  private:
    forward_list_node * _forward_list_node;
  };

public:
  using iterator = flist_iterator<self_t>;

public:
  forward_list() {}

  // copy constructor
  forward_list(const self_t &other) = default;

  // move constructor
  forward_list(self_t &&other) : _head(other._head), _size(other._size) {
    other._size = 0;
    other._head = NULL;
  }

  // copy assignment
  self_t &operator=(const self_t &rhs) {
    // free old list elements
    while (!empty()) {
      pop_front();
    }

    auto lastelem = begin();
    for (auto i = rhs.begin(); i != rhs.end(); ++i) {
      lastelem = insert_after(lastelem, *i);
    }

    return *this;
  }

  // move assignment
  self_t &operator=(self_t &&other) {
    // free old list elements
    while (!empty()) {
      pop_front();
    }

    _size = other._size;
    other._size = 0;

    _head = other._head;
    other._head = nullptr;

    return *this;
  }

  bool operator==(const self_t &other) const {
    if (this == &other) // identity
      return true;

    else if ((*this).size() != other.size())
      return false;

    else if ((*this).size() == 0) // hacky
      return true;

    iterator ithis = begin();
    iterator iother = other.begin();

    while (ithis != (*this).end() && iother != other.end()) {
      // std::cout << "value of this: " << *ithis << "\n";
      if (*ithis != *iother)
        return false;
      ++ithis;
      ++iother;
    }

    return true;
  }

  iterator begin() const { return iterator(_head); }

  iterator end() const { return iterator(NULL); }

  //    const_iterator begin() const
  //    {
  //        return iterator(_head);
  //    }
  //
  //    const_iterator end() const
  //    {
  //        return iterator(NULL);
  //    }

  size_t size() const { return _size; }

  bool empty() const { return (_size == 0); }

  const ValueT &front() const { return _head->value; }

  void push_front(const ValueT value) {
    _head = new forward_list_node{_head, value};
    ++_size;
  }

  ValueT pop_front() {
    if (size() == 0)
      return default_value;

    forward_list_node *tmp = _head;
    ValueT val = tmp->value;
    //	_head = _head->next;
    _head = tmp->next;
    //    std::cout << "tmp next: " << tmp->next << "\n";
    //    std::cout << "tmp value: " << tmp->value << "\n";
    //    std::cout << "head value: " << _head->value << "\n";
    delete tmp;

    --_size;
    return val;
  }

  iterator insert_after(iterator pos, const ValueT value) {
    //        if (*pos == nullptr && size() != 0) //tail
    //        throw exception

    if (size() == 0) //--> empty list
    {
      push_front(value);
      return _head;
    }

    auto tmp = pos._forward_list_node->next;
    auto ret = pos._forward_list_node->next
             = new forward_list_node{tmp, value};
    ++_size;
    return iterator(ret);
  }

private:
  forward_list_node *_head = NULL; // = &_tail;
  size_t _size = 0;
};

} // namespace cpppc

#endif // CPPPC__A03__FORWARD_LIST_H__INCLUDED

#ifndef CPPPC__A03__FORWARD_LIST_H__INCLUDED
#define CPPPC__A03__FORWARD_LIST_H__INCLUDED

#include <iterator>

namespace cpppc {

template <
    class IteratorType,
//    class ValueType = typename IteratorType::value_type, 
    class IndexType,
//    class Pointer = ValueType *,
//    class Reference = ValueType & >
class forward_iterator_base
{

//    typedef forward_list<ValueT, default_value> forward_list_t;
//    typedef forward_list_node forward_list_node_t;
    using self_t = forward_iterator_base<IteratorType, IndexType>;
    using index_t = IndexType;
    using derived_t = IteratorType;
 
//    friend forward_list; //I need this for insert_after 
//
  private:
      derived_t & derived()
      {
          return static_cast<IteratorType &>(*this);
      }

      const derived_t & derived() const
      {
          return static_cast<const derived_t &>(*this);
      }

  public:
//     using iterator_category = std::forward_iterator_tag;
//     using value_type = ValueType;
//     using difference_type = std::ptrdiff_t;
//     using pointer = Pointer;
//     using const_pointer = const Pointer;
//     using reference = value_type &;
//     using const_reference = const Reference;
  
     forward_iterator_base() = delete;
     forward_iterator_base(self_t &&) = default;
     forward_iterator_base(const self_t &) = default;
     ~forward_iterator_base() = default;
     self_t & operator=(self_t &&) = default;
     self_t & operator=(const self_t &) = default;
  
     forward_iterator_base(index_type pos) 
     : _pos(pos)
     { }

     const_reference operator*() const {
       return derived().dereference(_pos);
     }
  
     reference operator*() {
       return derived().dereference(_pos);
     }
  
  
     derived_t & operator++() {
        derived().increment();
        return derived();
     }
  
     derived_t & operator++(int) {
        derived_t old = derived();
        derived().increment();
        return old;
     }
  
     bool operator==(const derived_t & rhs) const
     {
         return (this == &rhs || _pos == rhs._pos);
     }
  
     bool operator!=(const derived_t & rhs) const
     {
       return  !(*this == rhs);
     }
  
  private:
     index_t _pos;
  
    };
} //namespace cpppc

#endif

#ifndef CPPPC__A06__FORWARD_ITERATOR_BASE_H__INCLUDED
#define CPPPC__A06__FORWARD_ITERATOR_BASE_H__INCLUDED

#include <iterator>

namespace cpppc {

template <class IteratorType,
          class difference_type,
          class value_type,
          class pointer,
          class reference,
          class const_reference
>
class forward_iterator_base {
  using self_t    = forward_iterator_base<
                      IteratorType,
                      difference_type,
                      value_type,
                      pointer,
                      reference,
                      const_reference >;
  using derived_t = IteratorType;

  //    friend forward_list; //I need this for insert_after
  //
private:
  derived_t &derived() { return static_cast<IteratorType &>(*this); }

  const derived_t &derived() const {
    return static_cast<const derived_t &>(*this);
  }

public:
  using iterator_category = std::forward_iterator_tag;

protected:
  forward_iterator_base()               = default;

public:
  forward_iterator_base(self_t &&)      = default;
  forward_iterator_base(const self_t &) = default;
  ~forward_iterator_base()              = default;
  self_t &operator=(self_t &&)          = default;
  self_t &operator=(const self_t &)     = default;

  const_reference operator*() const { return derived().dereference(); }

  reference operator*() { return derived().dereference(); }

  derived_t &operator++() {
    derived().increment();
    return derived();
  }

  derived_t &operator++(int) {
    derived_t old = derived();
    derived().increment();
    return old;
  }

  bool operator==(const derived_t &rhs) const {
    return (this == &rhs);
  }

  bool operator!=(const derived_t &rhs) const { return !(*this == rhs); }
};

} // namespace cpppc

#endif // CPPPC__A06__FORWARD_ITERATOR_BASE_H__INCLUDED

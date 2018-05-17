#ifndef CPPPC__LAZY_SEQUENCE_H__INCLUDED
#define CPPPC__LAZY_SEQUENCE_H__INCLUDED

#include <iostream>
#include <iterator>
#include <functional>

namespace cpppc {

template<typename T>
class lazy_sequence
{
  public:
    typedef lazy_sequence<T>     self_t;

  public:
    class iterator {
        typedef lazy_sequence<T> lazy_seq_t;
        typedef typename lazy_seq_t::iterator self_t;

      public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

        iterator() = delete;

        iterator(lazy_seq_t & seq, size_t index)
        : _lseq(seq)
        , _index(index)
        { }

        iterator(const self_t & other)
        : _lseq(other._lseq)
        , _index(other._index)
        { }

        self_t & operator=(const self_t & other)
        {
            _index = other._index;
            _lseq = other._lseq;
            return (*this);
        }

        const value_type operator*() const
        {
            value_type res = (_lseq._F(_index));
            return res;
        }

//        reference operator*()
//        {
//            return (_lseq._F(_index));
//        }

        reference operator[](int offset) const
        {
            return *(*this + offset);
        }

        self_t & operator++()
        {
            ++_index;
            return *this;
        }

        self_t & operator++(int) const 
        {
        //post increment, return old value
        //TODO bad style.. because we copy the whole element? But only in the function's scope. Idk
            self_t old = *this;
            ++old;
            return old;
        }

        self_t & operator--()
        {
            --_index;
            return *this;
        }

        self_t & operator--(int) const 
        {
        //post decrement, return old value
            self_t old = *this;
            --old;
            return old;
        }

        self_t & operator+=(int offset)
        {
            _index += offset;
            return *this;
        }

        self_t operator+(int offset) const 
        {
            //TODO also bad style. The implementation or if you use it in code?
            self_t result = *this;
            result += offset;
            return result;
        }

        self_t operator-=(int offset)
        {
            _index -=offset; 
            return *this;
        }

        self_t operator-(int offset) const
        {
            //TODO Sorry. Early optimization is the root of all evil. -Knuth
            self_t result = *this;
            result += offset;
            return result;
        }

        difference_type operator-(self_t other) 
        {
            return (other._index - _index);
        }

        bool operator==(const self_t & other) const
        {

            return (&_lseq == &(other._lseq) && _index == other._index);
        }

        bool operator!=(const self_t & other) const
        {
            return !(*this == other);
        }

        bool operator<(const self_t & other) const
        {
            return (other._index - (*this)._index > 0);            
        }
        
        bool operator>(const self_t & other) const
        {
            return (other<(*this));
        }

        bool operator<=(const self_t & other) const
        {
            return !((*this)>other);
        }
        
        bool operator>=(const self_t & other) const
        {
            return !((*this)<other);
        }

      private:
        lazy_seq_t &    _lseq;  
        size_t          _index;
    }; //class iterator

  public:
    lazy_sequence() = delete;

    lazy_sequence(size_t sz, std::function<T(T)> func)
    : _size(sz)
    , _F(func)
    , _end((*this), sz)
    , _rbegin((*this), sz-1)
    { }

//    lazy_sequence(self_t & other);
//    : _size(other.size())
//    , _F(other._F)
//    , _end((*this), other.size())
//    , _rbegin((*this), other.size()-1)
//    { }
//
//    self_t & operator=(const self_t & other)
//    {
//        _size = other.size();
//        _F = other._F;
//        _end = iterator((*this), other.size());
//        _rbegin = iterator((*this), other.size()-1);
//    }

    T operator[](size_t index)
    {
        return _F(index);
    }

    //    cannot compare functions!!
//    bool operator==(const self_t & other) const
//    {
//        return (this == &other || (size() == other.size() && _F == other._F));
//    }

//    bool operator!=(const self_t & other) const
//    {
//        return !(*this == other);
//    }

    T & front() const
    {
        return *_begin;
    }

    T & back() const
    {
        return *_rbegin;
    }

    iterator begin() const
    {
        return _begin;
    }

    iterator end() const
    {
        return _end;
    }

    iterator rbegin() const
    {
        return _rbegin;
    }

    iterator rend() const
    {
        return _rend;
    }

    bool empty() const
    {
        return (_size == 0);
    }

    std::size_t size() const
    {
        return _size;
    }

  private:
      size_t    _size;
//      T (self_t::*pt2Member)(T) = NULL;
      std::function<T(T)> _F;

    iterator                              _begin  = iterator(*this, 0);
    iterator                              _end; //   = iterator(*this, _size);
    iterator                              _rbegin; //  = iterator(*this, _size-1);
    iterator                              _rend    = iterator(*this, -1);
};

} //namespace cpppc

#endif

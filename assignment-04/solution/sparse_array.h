#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

// Might come in handy:
#include <unordered_map>
#include <iterator>
#include <stdexcept>

namespace cpppc {

namespace detail {

template <class T, std::size_t N>
class sparse_array;

//template <typename T>
template <class SparseArrayT>
class sparse_array_iterator
{

    private:
        typedef sparse_array_iterator<SparseArrayT> self_t;
        typedef typename SparseArrayT::T value_t;
        typedef std::size_t index_t;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = value_t;
        using pointer = value_type *;
        using reference = value_type &;

    public:
        sparse_array_iterator(SparseArrayT & array, index_t index)
            : _array(array)
            , _index(index)
        { }

        reference operator*() const
        {
            auto it = _array._map.find();
            if (it  == _array._map.end())
                return (_array._default); 
            else
                return *it;
        }

        reference operator[](int offset) const
        {
            return *(*this + offset);
        }

        self_t & operator++()
        {

        }

        self_t & operator++(int) const 
        {
        //post increment, return old value
        }

        self_t & operator--()
        {

        }

        self_t & operator--(int) const 
        {
        //post decrement, return old value
        }

        self_t & operator+=(int offset)
        {

        }

        self_t operator+(int offset) const 
        {

        }

        self_t operator-=(int offset)
        {
    
        }

        self_t operator-(int offset) const
        {
            
        }

        bool operator==(const self_t & other) const
        {

        }

        bool operator!=(const self_t & other) const
        {
            return !(*this == other);
        }

        //TODO comparison > >= < <=
        //
        
    private:
        SparseArrayT & _array;
        index_t _index;
};

template <class SparseArrayT>
class sparse_array_proxy_ref
{
  // Just a suggestion
};

} // namespace detail


template <class T, std::size_t N>
class sparse_array
{
      // Just a suggestion:
    
    typedef sparse_array<T, N>                      self_t;
    typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
    typedef int                                     index_t;

  public:

    typedef detail::sparse_array_iterator<self_t>   iterator;
    typedef index_t                                 difference_type;

    friend iterator;

  public:

    sparse_array(T def_val)
    : _size(N)
    , _begin(iterator((*this)._end))
    , _end(iterator((*this)._end))
    , _default(def_val)
    { }

    sparse_array(const self_t & other);

    self_t & operator=(const self_t & other);

    bool operator==(const self_t & rhs)
    {

    }

    T & operator[](index_t index)
    {
        if (index >= _size || index < 0)
            throw std::out_of_range("out of range");

        return _begin[index];
    }

    const T & operator[](index_t index)
    {
        if (index >= _size || index < 0)
            throw std::out_of_range("out of range");

        return _begin[index];
    }

    T front() const
    {
        return *_begin;
    }

    T back() const
    {
        return (*this)[--size()];
    }

    iterator begin() const
    {
        return _begin;
    }

    iterator end() const
    {
        return _end;
    }

    bool empty() const
    {
        return (_size == 0);
    }

    std::size_t size() const
    {
        return _size;
    }

    std::size_t max_size() const
    {
        return _size;
    }

  private:
    size_t                                _size;
    std::unordered_map<std::size_t, T>    _map;
    T                                     _default;

    iterator                              _begin  = iterator(*this, 1);
    iterator                              _end    = iterator(*this, 1);
    
//    forward_list_node _tail = { nullptr, default_value };
//    forward_list_node * _head = &_tail;
//    size_t _size = 0;

};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

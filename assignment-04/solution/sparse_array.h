#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

// Might come in handy:
#include <unordered_map>
#include <iterator>
#include <stdexcept>
#include <algorithm>

namespace cpppc {

namespace detail {

template <class T, std::size_t N>
class sparse_array;

template <class SparseArrayT>
class sparse_array_proxy_ref;

//template <typename T>
template <class SparseArrayT>
class sparse_array_iterator
{

    private:
        typedef sparse_array_iterator<SparseArrayT> self_t;
        typedef typename SparseArrayT::value_t value_t;
        typedef std::size_t index_t;
        typedef sparse_array_proxy_ref<SparseArrayT>  proxy_reference;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = value_t;
        using pointer = value_t *;
        using reference = value_t &;

    public:
        sparse_array_iterator(SparseArrayT & array, index_t index)
            : _array(array)
            , _index(index)
        { }

        sparse_array_iterator(const self_t & other)
            : _array(other._array)
            , _index(other._index)
        { }

        ~sparse_array_iterator() = default;

        self_t & operator=(const self_t & other)
        {
            _index = other._index;
            _array = other._array;
            return (*this);
        }

        reference operator*() const
        {
            auto it = _array._map.find(_index);
            if (it  == _array._map.end())
                return (_array._default); 
            else
                return it->second;
        }

        proxy_reference operator*()
        {
            return proxy_reference(_array, _index);
//            auto it = _array._map.find(_index);
//            if (it  == _array._map.end())
//                return (_array._default); 
//            else
//                return it->second;
        }

//        proxy_reference operator*(const value_t val)
//        {
//            return proxy_reference(_array, _index);
//        }

        reference operator[](int offset) const
        {
            return *(*this + offset);
        }

        self_t & operator++()
        {
            ++_index;
            std::cout<< "++: new index: " << _index << ", value here: " << *(*this) << "\n";
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

            return (&_array == &(other._array) && _index == other._index);
        }

        bool operator!=(const self_t & other) const
        {
            return !(*this == other);
        }

        bool operator<(const self_t & other) const
        {
//            return (other-(*this) > 0);
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

        index_t getindex()
        {
            return _index;
        }

    private:
        SparseArrayT & _array;
        index_t _index;
};

template <class SparseArrayT>
class sparse_array_proxy_ref
{
    typedef sparse_array_proxy_ref<SparseArrayT>    self_t;
    typedef typename SparseArrayT::value_t          value_t;

  public:
    sparse_array_proxy_ref(SparseArrayT & array, size_t index)
        : _array(array)
        , _index(index)
    {}

    sparse_array_proxy_ref(const self_t & other)
        : _array(other._array)
        , _index(other._index)
    {}

    void operator=(const value_t & val)
    {
//        std::cout << val <<  " inserted at " << _index << "\n";
        auto it = _array._map.find(_index);
        if (it  == _array._map.end())
            _array._map.insert({_index, val});
        else
            it->second = val;
    }

    self_t & operator=(const self_t & other)
    {
        if (&other != this)
        {
            _array = other._array;
            _index = other._index;
        }

        return *this;
    }

    operator const value_t & () const
    {
//        std::cout << "read at " << _index << "\n";
        auto it = _array._map.find(_index);
        if (it  == _array._map.end())
            return (_array._default); 
        else
            return it->second;
    }

  private:
    SparseArrayT & _array;
    size_t _index;
};

} // namespace detail


template <class T, std::size_t N>
class sparse_array
{
    typedef sparse_array<T, N>                      self_t;
    typedef T   value_t;
    typedef detail::sparse_array_proxy_ref<self_t>  proxy_reference;
    typedef int                                     index_t;

  public:

    typedef detail::sparse_array_iterator<self_t>   iterator;
    typedef index_t                                 difference_type;

    friend iterator;
    friend proxy_reference;

  public:

    sparse_array()//T def_val)
    : _size(N)
    , _end((*this), N)
    , _rbegin((*this), N-1)
//    , _begin(iterator((*this)._end))
//    , _end(iterator((*this)._end))
//    , _default(def_val)
    { }

    ~sparse_array()=default;

    sparse_array(const self_t & other)=default;

    self_t & operator=(const self_t & other)
    {
        if((this) != &other)
        {
           _map = other._map;
           _size = other.size(); 
           
           _end = iterator(*this, _size);
           _rbegin = iterator(*this, _size-1);
        }
       return (*this);
    }

    proxy_reference operator[](index_t index)
    {
        if (index >= _size || index < 0)
            throw std::out_of_range("out of range");

        return proxy_reference(*this, index);
    }

    const T & operator[](index_t index) const
    {
        if (index >= _size || index < 0)
            throw std::out_of_range("out of range");

        return _begin[index];
    }

    bool operator==(const self_t & rhs) const
    {
        if ((*this).size() != rhs.size())
            return false;
        else if (this == &rhs || empty())
            return true;
        else
            return (_map == rhs._map);
//            return std::equal(begin(), end(), rhs.begin());
    }

    bool operator!=(const self_t & rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const self_t & rhs) const
    {
//        if((*this) == rhs)
//            return false;
//
        return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
    }

    bool operator>(const self_t & rhs) const
    {
        return (rhs<(*this));
    }

    bool operator<=(const self_t & rhs) const
    {
        return !((*this)>rhs);
    }

    bool operator>=(const self_t & rhs) const
    {
        return !((*this)<rhs);
    }


    T & front() const
    {
        return *_begin;
    }

    T & back() const
    {
        return *_rbegin;
    }

    proxy_reference front() 
    {
        return proxy_reference((*this), _begin.getindex()); 
    }

    proxy_reference back() 
    {
        return proxy_reference((*this),_rbegin.getindex());
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

    std::size_t max_size() const
    {
        return _size;
    }

    void fill(const T& value)
    {
        std::fill(begin(), end(), value);
    }

    void swap(self_t & other)
    {
        std::swap_ranges(_map.begin(), _map.end(), other._map.begin(), other._map.end());
    }

    void printmap()
    {
        std::cout << "printing map \n";
        std::cout << "begin index: " << _begin.getindex() << ", end index: " << _end.getindex() << "\n";
        for (const auto & n : _map)
        {
            std::cout << "index:" << n.first << ", value:" << n.second << "\n";
        }
    }

        void printarray()
        {
            for (auto i = begin(); i!=end(); ++i)
            {
                std::cout << i.getindex() << ":" << *i << " of " << _size <<  "\n";
            }
        }


  private:
    size_t                                _size;
    std::unordered_map<std::size_t, T>    _map;
    T                                     _default = {};

    iterator                              _begin  = iterator(*this, 0);
    iterator                              _end; //   = iterator(*this, _size);
    iterator                              _rbegin; //  = iterator(*this, _size-1);
    iterator                              _rend    = iterator(*this, -1);
    
//    forward_list_node _tail = { nullptr, default_value };
//    forward_list_node * _head = &_tail;
//    size_t _size = 0;

};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

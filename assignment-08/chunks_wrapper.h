#ifndef CPPPC_CHUNKS_INCLUDED
#define CPPPC_CHUNKS_INCLUDED

#include <iterator>


namespace cpppc{

    template <std::size_t B, class T, class Container> //limit to contiguous containers?
    class chunks
    {
        class iterator
        {
          public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

            iterator() = delete;

            iterator(size_t index, Container & con)
              : _index(index)
              , _container(con)
              , _chunksize(B);
            {   }

            bool operator==(const iterator rhs) const
            {
                return (this == &rhs || _index == rhs._index);
            }

            bool operator!=(const iterator rhs) const
            {
                return !(*this == rhs);
            }

            const T & operator*() const
            {
                return _container[_index];
            }

            T & operator*() 
            {
                return _container[_index];
            }

            iterator & operator++()
            {
                _index += _chunksize;
                return *this;
            }

            iterator & operator--()
            {
                _index -= _chunksize;
                return *this;
            }

            //random access accordingly

          private:
            size_t _index;
            T & _container;
            size_t _chunksize ;
        };

        using self_t = chunks<T,B,Container>;

      public:
        chunk() = delete;

        chunk(Container & con)
          :_container(con)
          ,_chunksize(B)
        {   }

        iterator begin() const
        {
            return iterator(0, _container);
        }

        iterator end() const
        {
            return iterator(size(), _container);
        }

        size_t size() const
        {
            return _container.size()/B; //returns number of chunks, works because decimal points are cut off
        }

      private:
        Container * _container;
        std::size_t _chunksize;

    }

} //namespace cpppc

#endif

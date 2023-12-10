#pragma once

#include <stdexcept>
#include <utility>
#include "utils.h"

namespace containers
{
    template<typename VECTOR>
    struct vector_iterator
    {
        using val_t = typename VECTOR::val_t;
        using ref_t = val_t&;
        using ptr_t = val_t*;

    private:
        ptr_t _ptr;

    public:
        vector_iterator(const ptr_t p) :
            _ptr(p)
        {}

        ptr_t operator->()
        {
            return _ptr;
        }

        ref_t operator*()
        {
            return *_ptr;
        }

        vector_iterator& operator++()
        {
            _ptr++;
            return *this;
        }

        vector_iterator& operator--()
        {
            _ptr--;
            return *this;
        }
    };
}

namespace containers
{
    template<typename T>
    struct vector
    {
        using val_t = T;
        using iterator = vector_iterator<vector<T>>;

    private:
        std::size_t _size;
        std::size_t _capacity;
        T* _data;
    
    public:
        vector() :
            _size( 0 ),
            _capacity( 8 ),
            _data(allocate(_capacity))
        {}

        vector( const std::size_t& cap ) :
            _size( 0 ),
            _capacity( cap ),
            _data(allocate(_capacity))
        {}

        vector( const std::size_t& cap, T def ) :
            _size( cap ),
            _capacity( cap ),
            _data(allocate(_capacity))
        {
            set_range(def, 0, _capacity);
        }

        ~vector() noexcept
        {
            wipe_memory();
        }

        /* ACCESS */

        T& front()
        {
            return _data[0];
        }

        T& back()
        {
            return _data[_size-1];
        }

        T& operator[](const std::size_t& ix)
        {
            check_bounds(ix, _capacity);
            return _data[ix];
        }

        iterator begin()
        {
            return iterator(&front());
        }

        iterator end()
        {
            return iterator(&back());
        }

        /* MODIFY */

        void push_back(const T& t)
        {
            inc_size();
            back() = t;
        }

        void push_back(const T&& t)
        {
            inc_size();
            back() = std::move(t);
        }

        template<typename... Args>
        void emplace_back(Args... args)
        {
            inc_size();
            back() = T(std::forward<Args>(args)...);
        }

        void pop_back()
        {
            back().~T();
            --_size;
        }

        void clear()
        {
            destruct_all();
            _size = 0;
        }

        void set_range(T val, std::size_t ix0, std::size_t ix1)
        {
            for (std::size_t ix = ix0; ix < std::min(ix1, _size); ++ix) {
                _data[ix] = val;
            }
        }

        /* QUERY */

        const std::size_t& size() const
        {
            return _size;
        }

        const std::size_t& capacity() const
        {
            return _capacity;
        }

    private:
        void inc_size()
        {
            if (++_size > _capacity) {
                reallocate(_capacity * 2);
            }
        }

        T* allocate(const std::size_t& cap)
        {
            return static_cast<T*>(::operator new(cap * sizeof(T)));
        }

        void destruct_all() noexcept
        {
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
        }

        void wipe_memory() noexcept
        {
            destruct_all();
            ::operator delete(_data, _capacity * sizeof(T));
        }

        void reallocate(const std::size_t& new_cap)
        {
            T* new_data = allocate(new_cap);

            for (std::size_t i = 0; i < _size - 1; ++i) {
                new_data[i] = std::move(_data[i]);
            }

            wipe_memory();
            _data = new_data;
            _capacity = new_cap;
        }
    };
}
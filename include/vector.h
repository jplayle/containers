#pragma once

#include <stdexcept>
#include <utility>

namespace containers
{
    template<typename T>
    struct vector
    {
    private:
        std::size_t _size;
        std::size_t _capacity;
        T _data[];
    
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

        ~vector() noexcept
        {
            dtor_all();
            ::operator delete(_data, _capacity * sizeof(T));
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
            if (ix >= _size) { throw std::runtime_error("out of bounds"); }

            return _data[ix];
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
            dtor_all();
            _size = 0;
        }

        /* QUERY */

        const std::size_t& size() const
        {
            return _size;
        }

        const bool contains(const T& val) const
        {
            std::size_t r = size - 1;
            std::size_t l = 0;

            while (l <= r)
            {
                std::size_t ix = l + ((r - l) / 2);

                if (_data[ix] == val) return true;
                
                if (_data[ix] > val) {
                    r = ix - 1;
                }
                else {
                    l = ix + 1;
                }
            }

            return false;
        }

    private:

        void dtor_all()
        {
            for (std::size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
        }

        T* allocate(const std::size_t& cap)
        {
            return static_cast<T*>(::operator new(cap * sizeof(T)));
        }

        void reallocate(const std::size_t& new_cap)
        {
            T* new_data = allocate(new_cap);

            for (std::size_t i = 0; i < _size - 1; ++i) {
                new_data[i] = _data[i];
            }

            ~vector();

            _data = new_data;
            _capacity = new_cap;
        }

        void inc_size()
        {
            if (++_size > _capacity) {
                reallocate(_capacity * 2);
            }
        }
    };
}
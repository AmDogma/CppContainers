#pragma once
#include <sys/types.h>
#include <iostream>
#include "iterator_vector.hpp"

namespace ft {
    template<class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T   value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::iterator_vector<pointer>	    iterator;
        typedef ft::iterator_vector<const_pointer>	const_iterator;
//        typedef ft::reverse_iterator<iterator>	reverse_iterator;
//        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type	difference_type;
        typedef size_t	size_type;
    private:
        size_type       _size;
        size_type       _capacity;
        allocator_type	_alloc;
        pointer         _pointer;
    public:
        /* Constructors and destructor */
        explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _pointer(NULL), _size(0), _capacity(0) {
        }
//        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _pointer(_alloc.allocate(_capacity)) {
//            this->insert(begin(), _capacity, val);
//        }

        // 2 more constr
        // range (3)
        //template <class InputIterator>
        //         vector (InputIterator first, InputIterator last,
        //                 const allocator_type& alloc = allocator_type());
        //copy (4)
        //vector (const vector& x);

        ~vector() {
            clear();
            _alloc.deallocate(_pointer, _capacity);
        }
        /* Operator=  */
        vector& operator= (const vector& x) {
           if (*this == x)
               return *this;
           clear();// need to insert and think about capacity and size
           _alloc.deallocate(_pointer, _capacity);// need to insert and think about capacity and size
           _capacity = x.capacity();// need to insert and think about capacity and size
           _size = x.size();// need to insert and think about capacity and size
           _pointer = _alloc.allocate(_capacity);// need to insert and think about capacity and size
           for (size_t i = 0; i < _size; i++)  // need to insert and think about capacity and size
               _pointer[i] = x[i]; // it is ok?
        }
        /* Iterators */
        iterator begin() {
            return iterator(_pointer);
        }
        iterator end() {
            return iterator(_pointer + _size);
        }
        const_iterator begin() const {
            return iterator(_pointer);
        }
        const_iterator end() const {
            return iterator(_pointer + _size);
        }
        /* Capacity */
        size_type size() const {
           return (_size);
        }
        size_type max_size() const {
           return (_alloc.max_size());
        }
        size_t capacity() const {
          return (_capacity);
        }
        bool        empty () const {
           return (size() == 0);
        }
        /*	Element access	*/
        reference operator[](size_type n) {
           return (*(_pointer + n));
        }
        const_reference operator[](size_type n) const {
           return (*(_pointer + n));
        }
        reference at (size_type n) {
           if (n > _size)
               throw std::out_of_range("N > SIZE");
           return _pointer[n];
        }
        const_reference at (size_type n) const {
           if (n > _size)
               throw std::out_of_range("N > SIZE");
           return _pointer[n];
        }
        reference front () {
           return _pointer[0];
        }
        const_reference front () const {
           return _pointer[0];
        }
        reference back () {
          return _pointer[_size - 1];
        }
        const_reference back () const {
           return _pointer[_size - 1];
        }
        /* Modifiers */
        template <class InputIterator>
            void assign (InputIterator first, InputIterator last) {
            std::cout << "Need to fill\n";
            }
        void assign (size_type n, const value_type& val) {
          std::cout << "Need to fill\n";
        }
        void reserve(size_type newCapacity) {
            if (newCapacity > max_size())
                throw std::length_error("Vector capacity out of max_size!");
            else if (_capacity < newCapacity) {
                size_type sizeTwice = _size * 2;
                if (newCapacity < sizeTwice && sizeTwice < max_size())
                    newCapacity = sizeTwice;
                pointer temp = _pointer;
                _pointer = _alloc.allocate(newCapacity);
                for (size_type i = 0; i < _size; ++i) { // просто перенести указатели разве нельзя?
                    _alloc.construct(_pointer + i, temp[i]);
                    _alloc.destroy(temp + i);
                }
                _alloc.deallocate(temp, _capacity);
                _capacity = newCapacity;
            }
        }
        void resize (size_type n, value_type val = value_type()) {
            if (n > _size)
                insert(end(), n - _size, val);
            else if (n < _size)
                for (_size; _size > n; --_size)
                    _alloc.destroy(_pointer + (_size - 1));
        }
        void push_back (const value_type& val) {
            reserve(_size + 1);
            _alloc.construct(_pointer + _size, val);
            _size++;
        }
        iterator insert (iterator position, const value_type& val) {
            size_type dis = static_cast<size_type>(ft::distance(begin(), position));
//            if (position > end() && position < begin())
//                throw std::logic_error("Insert position fail!"); // do we need care this?
            reserve(_size + 1);
//            if (position == end())
//                push_back(val);
//            else {
                for (size_type i = 0; _size - i != dis; ++i)
                    _pointer[_size - i] = _pointer[_size - i - 1];
                _alloc.construct(_pointer + dis, val);
                _size++;
//            }
            return iterator(begin() + dis);
        }
        void insert (iterator position, size_type n, const value_type& val) {
            size_type dis = static_cast<size_type>(ft::distance(begin(), position));
            if (position > end() && position < begin())
                throw std::logic_error("Insert position fail!"); // do we need care this?
            reserve(_size + n);
            for (size_type i = 0; _size - i != dis; ++i)
                _pointer[_size - i + n] = _pointer[_size - i - 1 + n];
            for (size_type i = 0; i < n; i++) {
                std::cout << "Need to fill\n";
            }
        }
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last) {
            std::cout << "Need to fill\n";
        }
        void clear() {
            for (; _size; --_size)
                _alloc.destroy(_pointer + (_size - 1));
        }
     };
}


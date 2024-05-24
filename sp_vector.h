#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class sparse_vector
{
    struct vect_elem
    {
        size_t idx;
        T value;

        bool operator<(const vect_elem &other) const
        {
            return idx < other.idx;
        }
    };

    size_t n_elem = 0;
    std::vector<vect_elem> elements;

public:
    // creates n_elements vector with all elements of value T()
    explicit sparse_vector(size_t n_elements = 10u) : n_elem(n_elements)
    {
    }

    // returns number of elments in the vector
    size_t size() const
    {
        return n_elem;
    }

    // returns number of non-default values in the vector
    size_t nd_count() const
    {
        return elements.size();
    }

    // sets all non-default values to T() (size() is not changed)
    void clear()
    {
        elements.clear();
    }

    // returns const reference to element in the vector or T()
    // if element with given idx has default value
    // invalid idx results in invalid_argument exception
    T operator[](int idx) const
    {
        if (idx < 0 || size() <= (size_t)idx)
        {
            throw std::invalid_argument("Const index out of bounds.");
        }

        auto it = std::lower_bound(elements.cbegin(), elements.cend(), vect_elem{(size_t)idx, T()});
        if (it == elements.cend() || it->idx != (size_t)idx)
        {
            return T();
        }
        return it->value;
    }

    // returns const reference to element in the vector
    // if element with given idx has default value new element is inserted
    // invalid idx results in invalid_argument exception
    T &operator[](int idx)
    {
        if (idx < 0 || size() <= (size_t)idx)
        {
            throw std::invalid_argument("Index out of bounds.");
        }

auto it = std::lower_bound(elements.begin(), elements.end(), vect_elem{(size_t)idx, T()});
        if (it == elements.end() || it->idx != (size_t)idx) {
            it = elements.insert(it, {(size_t)idx, T()});
        }
        return it->value;
    }
    class const_iterator
    {
        typename std::vector<vect_elem>::const_iterator it;

    public:
        const_iterator(typename std::vector<vect_elem>::const_iterator it) : it(it) {}

        const_iterator &operator++()
        {
            ++it;
            return *this;
        }
        bool operator!=(const const_iterator &other)
        {
            return it != other.it;
        }
        T operator*() const
        {
            return it->value;
        }
    };

    const_iterator cbegin() const
    {
        return const_iterator(elements.cbegin());
    }
    const_iterator cend() const
    {
        return const_iterator(elements.cend());
    }
    const_iterator begin() const
    {
        return cbegin();
    }
    const_iterator end() const
    {
        return cend();
    }

    friend std::ostream &operator<<(std::ostream &os, const sparse_vector &vec)
    {
       os << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            os << vec[i] << " ";
        }
        return os << "]";
    }
};

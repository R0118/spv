#pragma once
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class sparse_vector
{
    struct vect_elem {
        size_t  idx;
        T       value;
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
        if (idx < 0 || size() <= (size_t) idx)
            throw std::invalid_argument("Const index out of bounds.");

        auto it = std::find_if(elements.cbegin(), elements.cend(), [idx](const vect_elem& ve) { return ve.idx == (size_t) idx; });
        if (it == elements.cend())
            return T();
        return it->value;
    }

    // returns const reference to element in the vector
    // if element with given idx has default value new element is inserted
    // invalid idx results in invalid_argument exception
    T& operator[](int idx)
    {
        if (idx < 0 || size() <= (size_t) idx)
            throw std::invalid_argument("Index out of bounds.");

        auto it = std::find_if(elements.begin(), elements.end(), [idx](const vect_elem& ve) { return ve.idx == (size_t) idx; });
        if (it == elements.cend())
        {
            elements.push_back({(size_t) idx, T()});
            return elements.back().value;
        }
        return it->value;
    }

    class const_iterator
    {
        const sparse_vector& container;
        size_t current_idx = 0;

        const_iterator(const sparse_vector& container, size_t index) :
            container(container), current_idx(index)
        {}
        friend sparse_vector;
    public:
        // Please define minimal interface for forward iterator
        const_iterator& operator++()
        {
            ++current_idx;
            return *this;
        }
        bool operator!=(const const_iterator& other)
        {
            return &container != &other.container || current_idx != other.current_idx;
        }
        T operator*() const
        {
            return container[current_idx];
        }
    };

    const_iterator cbegin() const
    {
        return const_iterator(*this, 0);
    }
    const_iterator cend() const
    {
        return const_iterator(*this, size());
    }

    const_iterator begin() const
    {
        return cbegin();
    }
    const_iterator end() const
    {
        return cend();
    }

    friend std::ostream& operator<<(std::ostream& os, const sparse_vector& vec)
    {
        os << '[';
        for (auto val : vec)
            os << val << ' ';
        return os << ']';
    }
};

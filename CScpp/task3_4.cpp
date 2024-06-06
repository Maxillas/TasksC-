#include <iostream>
#include <vector>
#include <iterator>
#include <list>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    // определите const_iterator
    struct const_iterator : std::iterator<
                                std::bidirectional_iterator_tag,
                                const T>
    {
        const_iterator(const ListT* inputData)
            : m_data(inputData),
            m_ListIt(m_data->cbegin()),
            m_VectorIt(m_ListIt->cbegin()){};

        const_iterator(const const_iterator & it) = default;
        const_iterator() = default;
        ~const_iterator() = default;
        const_iterator& operator=(const const_iterator&) = default;

        const_iterator& in_end()
        {
            m_ListIt = --(m_data->cend());
            m_VectorIt = m_ListIt->cend();
            return *this;
        }

        const T& operator * () const {
            return *m_VectorIt;
        };

        const T * operator->() const {
            return &(*m_VectorIt);
        }

        const_iterator operator++(int)  {
            auto tmp = *this;
            ++(*this);
            return tmp;
        };

        const_iterator& operator++() {

            if (m_VectorIt == std::prev((*m_ListIt).cend()))
            {
                ++m_ListIt;
                if (m_ListIt != m_data->cend()) {
                    m_VectorIt = m_ListIt->cbegin();
                } else {++m_VectorIt; --m_ListIt; }
            }
            else
            {
                ++m_VectorIt;
            }
            return *this;
        }

        const_iterator operator--(int) {
            auto tmp = *this;
            --(*this);
            return tmp;
        };

        const_iterator& operator--() {

            if (m_VectorIt == (*m_ListIt).cbegin())
            {
                if (m_ListIt != m_data->cbegin())
                {
                    --m_ListIt;
                    m_VectorIt = std::prev((*m_ListIt).cend());
                }
            }
            else
            {
                --m_VectorIt;
            }
            return *this;
        };

        bool operator != (const const_iterator& it) const {
            return !(m_ListIt==it.m_ListIt && m_VectorIt==it.m_VectorIt);
        };

        bool operator == (const const_iterator& it) const {
            return (m_ListIt==it.m_ListIt && m_VectorIt==it.m_VectorIt);
        };

    //private:
        const ListT * m_data;
        typename ListT::const_iterator m_ListIt;
        typename VectT::const_iterator m_VectorIt;
    };

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q) {
        if (p != q) {
            data_.push_back(VectT(p,q));
        }
    }; // определена снаружи

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t fullSize = 0;
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            fullSize += (*it).size();
        }
        return fullSize;
    }

    // определите методы begin / end
    const_iterator begin() const {        
        return !data_.empty() ? const_iterator(&data_) : const_iterator();
    }
    const_iterator end() const {
        if (!data_.empty())
        {
            auto a = const_iterator(&data_).in_end();
            return a;
        }
        return const_iterator();
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const {
        return !data_.empty() ? const_reverse_iterator(end()) : const_reverse_iterator();
    }
    const_reverse_iterator rend() const {
        return !data_.empty() ? const_reverse_iterator(begin()) : const_reverse_iterator();
    }

private:
    ListT data_;
};

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
                                const T,
                                int,
                                T*,
                                const T&
                                >
    {
        const_iterator(ListT const &inputData,
                       typename ListT::const_iterator listIt,
                       typename VectT::const_iterator vectIt)
        {
            m_data = &inputData;
            m_ListIt = listIt;
            m_VectorIt = vectIt;
            //std::cout << "size = " <<  (*m_ListIt).size() << std::endl;
        }
        const_iterator(const const_iterator & it){};
        const_iterator(){};

        T const & operator * () const {
            return *m_VectorIt;
        };

        const_iterator operator ++ (int)  {
            //const_iterator newIt();

            //typename VectT::const_iterator new_VectorIt = m_VectorIt;
            //typename ListT::const_iterator new_ListIt = m_ListIt;
            const_iterator output_It;
            //m_VectorIt++;
        // каждый раз создает новый объект и поэтому бесконечный цикл
            m_VectorIt++;
            if (m_VectorIt == (*m_ListIt).end()) { // если это был последний элемент в векторе
                m_ListIt++; // переход на следующий вектор в списке
                if (m_ListIt == m_data->end()) { //если это был последний вектор в списке
                    output_It = const_iterator(*m_data, m_ListIt, m_VectorIt);
                    return output_It;
                }
                m_VectorIt = (*m_ListIt).begin();
            }
            output_It = const_iterator(*m_data, m_ListIt, m_VectorIt);
            std::cout << "asssa = " << *output_It << std::endl;
            return output_It;
        };

        const_iterator operator -- (int) const {
            // if (m_VectorIt == m_ListIt.begin()) {
            //     m_VectorIt =
            // }
            m_VectorIt--;
            return this;
        };

        const_iterator& operator--() {
            // if (m_VectorIt == m_ListIt.begin()) {
            //     m_VectorIt =
            // }
            m_VectorIt--;
            return this;
        };

        bool operator != (const const_iterator& it) const {
            if (m_VectorIt == it.m_VectorIt) {
                return false;
            }
            return true;
        };

        bool operator == (const const_iterator& it) const {
            if (m_VectorIt == it.m_VectorIt) {
                return true;
            }
            return false;
        };

    private:
        ListT const * m_data;
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
        const_iterator begin_it(data_, data_.begin(), (*(data_.begin())).begin());
        return begin_it;
    }
    const_iterator end() const {
        auto lastIt = data_.end();
        lastIt--;
        auto lastElemIt = (*lastIt).end();
        lastElemIt--;
        const_iterator end_it(data_, lastIt, lastElemIt);
        return end_it;
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const {
        const_reverse_iterator rBeginIt(begin());
        return rBeginIt;
    }
    // const_reverse_iterator rend()   const { return ... ; }

private:
    ListT data_;
};

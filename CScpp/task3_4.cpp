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
                                const T*,
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

        T const& operator * () const {
            std::cout << "ESSSSS??????????" << std::endl;
            auto it = m_data->begin();
            for (it; it != m_data->end(); it++) {
                if (it == m_ListIt) {
                    break;
                }
            }
            for (auto it_vect = (*it).cbegin(); it_vect != (*it).cend(); ++it_vect) {
                if (it_vect == m_VectorIt) {
                    return *it_vect;
                }
            }
        };

        T const* operator->() const {
            auto it = m_data->begin();
            for (it; it != m_data->end(); it++) {
                if (it == m_ListIt) {
                    break;
                }
            }
            for (auto it_vect = (*it).cbegin(); it_vect != (*it).cend(); ++it_vect) {
                if (it_vect == m_VectorIt) {
                    return &(*it_vect);
                }
            }
        }

        const_iterator operator++(int)  {
            auto copy = *this;
            m_VectorIt++;
            if (m_VectorIt == (*m_ListIt).end()) { // если это был последний элемент в векторе
                m_ListIt++; // переход на следующий вектор в списке
                if (m_ListIt == m_data->end()) { //если это был последний вектор в списке
                    return copy;
                }
                m_VectorIt = (*m_ListIt).begin();
            }
            return copy;
        };

        const_iterator& operator++() {

            m_VectorIt++;
            if (m_VectorIt == (*m_ListIt).end()) { // если это был последний элемент в векторе
                m_ListIt++; // переход на следующий вектор в списке
                if (m_ListIt == m_data->end()) { //если это был последний вектор в списке
                    return *this;
                }
                m_VectorIt = (*m_ListIt).begin();
            }
            return *this;
        }

        const_iterator operator--(int) {
            auto copy = *this;

            if (m_VectorIt == (*m_ListIt).begin()) { // если это был первый элемент в векторе
                if (m_ListIt == m_data->begin()) { //если это был первый вектор в списке
                    return copy;
                }
                m_ListIt--; // переход на следующий вектор в списке
                m_VectorIt = (*m_ListIt).end();
            }
            m_VectorIt--;
            return copy;
        };

        const_iterator& operator--() {

            if (m_VectorIt == (*m_ListIt).begin()) { // если это был первый элемент в векторе
                if (m_ListIt == m_data->begin()) { //если это был первый вектор в списке
                    return *this;
                }
                m_ListIt--; // переход на следующий вектор в списке
                m_VectorIt = (*m_ListIt).end();
            }
            m_VectorIt--;
            return *this;
        };

        bool operator != (const const_iterator& it) const {
            if (m_VectorIt == it.m_VectorIt) { //возможно неверно, нельзя сравнивать из разных векторов
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

    //private:
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
        //for (const auto &it : data_) {
            fullSize += (*it).size();
        }
        return fullSize;
    }

    // определите методы begin / end
    const_iterator begin() const {
        const_iterator begin_it(data_, data_.begin(), (*(data_.begin())).begin());
        return begin_it;

        // 2. Надо обязательно проверить, что begin и end для emptyVectorList равны, т.е.
        // VectorList<int> emptyVectorList;
        // emptyVectorList.begin() == emptyVectorList.end()
    }
    const_iterator end() const {
        auto lastIt = data_.end();
        auto lastElemIt = (*(--lastIt)).end();
        const_iterator end_it(data_, lastIt, lastElemIt);
        return end_it;
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    //using const_reverse_iterator = std::reverse_iterator<VectorList<int>::const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(--end());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(--begin());
    }
    // const_reverse_iterator rend()   const { return ... ; }

private:
    ListT data_;
};

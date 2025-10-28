#include <vector>
#include <cstddef>

namespace std {

    template <typename T>
    vector<T>::vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    template <typename T>
    vector<T>::~vector() {
        delete[] m_data;
    }

    template <typename T>
    void vector<T>::push_back(const T& value) {
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            T *new_data = new T[new_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_data[m_size++] = value;
    }

    template <typename T>
    void vector<T>::pop_back() {
        if (m_size > 0) {
            m_size--;
        }

        if (m_size < m_capacity / 4) {
            size_t new_capacity = m_capacity / 2;
            T *new_data = new T[new_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
    }

    template <typename T>
    T& vector<T>::operator[](size_t index) {
        return m_data[index];
    }

    template <typename T>
    size_t vector<T>::size() const {
        return m_size;
    }

} // namespace std

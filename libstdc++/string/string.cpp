#include <string>
#include <cstring>
#include <cstddef>
#include <algorithm>

// Macro to handle unimplemented exceptions
#define todo_exception(exception) return
#define todo_exception_return(exception, dval) return dval

namespace std {

    string::string() {
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    string::string(const char *str) {
        if (str) {
            m_size = strlen(str);
            m_capacity = m_size + 1;
            m_data = new char[m_capacity];
            strcpy(m_data, str);
        } else {
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
    }

    string::string(const string& other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        if (m_capacity > 0) {
            m_data = new char[m_capacity];
            strcpy(m_data, other.m_data);
        } else {
            m_data = nullptr;
        }
    }

    string::string(size_t n, char c) {
        if (n > 0) {
            m_capacity = n + 1;
            m_data = new char[m_capacity];
            memset(m_data, c, n);
            m_data[n] = '\0';
            m_size = n;
        } else {
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
    }

    string::~string() {
        delete[] m_data;
    }

    string& string::operator=(const string& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            if (m_capacity > 0) {
                m_data = new char[m_capacity];
                strcpy(m_data, other.m_data);
            } else {
                m_data = nullptr;
            }
        }
        return *this;
    }

    char& string::operator[](size_t index) {
        return m_data[index];
    }

    const char& string::operator[](size_t index) const {
        return m_data[index];
    }

    void string::push_back(char c) {
        if (m_size + 1 >= m_capacity) {
            reserve(m_capacity == 0 ? 2 : m_capacity * 2);
        }
        m_data[m_size++] = c;
        m_data[m_size] = '\0';
    }

    void string::pop_back() {
        if (m_size > 0) {
            m_size--;
            m_data[m_size] = '\0';
        }
    }

    void string::clear() {
        m_size = 0;
        if (m_data) {
            m_data[0] = '\0';
        }
    }

    void string::reserve(size_t new_capacity) {
        if (new_capacity > m_capacity) {
            char *new_data = new char[new_capacity];
            if (m_data) {
                strcpy(new_data, m_data);
                delete[] m_data;
            }
            m_data = new_data;
            m_capacity = new_capacity;
        }
    }

    void string::resize(size_t n, char c) {
        if (n < m_size) {
            m_size = n;
            m_data[m_size] = '\0';
        } else if (n > m_size) {
            if (n >= m_capacity) {
                reserve(n + 1);
            }
            memset(m_data + m_size, c, n - m_size);
            m_size = n;
            m_data[m_size] = '\0';
        }
    }

    size_t string::length() const {
        return m_size;
    }

    size_t string::size() const {
        return m_size;
    }

    size_t string::capacity() const {
        return m_capacity;
    }

    size_t string::max_size() const {
        return (size_t)-1;
    }

    bool string::empty() const {
        return m_size == 0;
    }

    void string::shrink_to_fit() {
        if (m_size < m_capacity) {
            char *new_data = new char[m_size + 1];
            if (m_data) {
                strcpy(new_data, m_data);
                delete[] m_data;
            }
            m_data = new_data;
            m_capacity = m_size + 1;
        }
    }

    void *string::get_allocator() const {
        return nullptr;
    }

    const char *string::c_str() const {
        return m_data ? m_data : "";
    }

    const char* string::data() const {
        return m_data ? m_data : "";
    }

    char& string::at(size_t index) {
        if (index >= m_size) {
            todo_exception_return(std::out_of_range("Index out of range"), m_data[0]);
        }
        return m_data[index];
    }

    const char& string::at(size_t index) const {
        if (index >= m_size) {
            todo_exception_return(std::out_of_range("Index out of range"), m_data[0]);
        }
        return m_data[index];
    }

    char& string::back() {
        return m_data[m_size - 1];
    }

    const char& string::back() const {
        return m_data[m_size - 1];
    }

    char& string::front() {
        return m_data[0];
    }

    const char& string::front() const {
        return m_data[0];
    }

    void string::insert(size_t index, const string& other) {
        if (index > m_size) {
            todo_exception(std::out_of_range("Index out of range"));
        }
        size_t new_size = m_size + other.m_size;
        if (new_size >= m_capacity) {
            reserve(new_size + 1);
        }
        memmove(m_data + index + other.m_size, m_data + index, m_size - index + 1);
        memcpy(m_data + index, other.m_data, other.m_size);
        m_size = new_size;
    }

    void string::erase(size_t index, size_t count) {
        if (index >= m_size) {
            todo_exception(std::out_of_range("Index out of range"));
        }
        if (index + count > m_size) {
            count = m_size - index;
        }
        memmove(m_data + index, m_data + index + count, m_size - index - count + 1);
        m_size -= count;
    }

    void string::replace(size_t index, size_t count, const string& other) {
        if (index > m_size) {
            todo_exception(std::out_of_range("Index out of range"));
        }
        if (index + count > m_size) {
            count = m_size - index;
        }
        size_t new_size = m_size - count + other.m_size;
        if (new_size >= m_capacity) {
            reserve(new_size + 1);
        }
        memmove(m_data + index + other.m_size, m_data + index + count, m_size - index - count + 1);
        memcpy(m_data + index, other.m_data, other.m_size);
        m_size = new_size;
    }

    int string::compare(const string& other) const {
        return strcmp(m_data ? m_data : "", other.m_data ? other.m_data : "");
    }

    void string::append(const string& other) {
        size_t new_size = m_size + other.m_size;
        if (new_size >= m_capacity) {
            reserve(new_size + 1);
        }

        if (other.m_data != nullptr) {
            strcpy(m_data + m_size, other.m_data);
        }

        m_size = new_size;
    }

    string& string::operator+=(const string& other) {
        append(other);
        return *this;
    }

    string& string::assign(const string& str) {
        if (this != &str) {
            delete[] m_data;
            m_size = str.m_size;
            m_capacity = str.m_capacity;
            if (m_capacity > 0) {
                m_data = new char[m_capacity];
                strcpy(m_data, str.m_data);
            } else {
                m_data = nullptr;
            }
        }
        return *this;
    }

    size_t string::copy(char* s, size_t len, size_t pos) const {
        if (pos >= m_size) {
            return 0;
        }
        size_t to_copy = (len < m_size - pos) ? len : m_size - pos;
        memcpy(s, m_data + pos, to_copy);
        return to_copy;
    }

    size_t string::find(const string& str, size_t pos) const {
        if (pos >= m_size || str.m_size == 0) {
            return npos;
        }
        const char* found = strstr(m_data + pos, str.m_data);
        if (found) {
            return found - m_data;
        }
        return npos;
    }

    size_t string::rfind(const string& str, size_t pos) const {
        if (m_size == 0 || str.m_size == 0) {
            return npos;
        }
        if (pos >= m_size) {
            pos = m_size - 1;
        }
        for (size_t i = pos; i >= str.m_size - 1; --i) {
            if (memcmp(m_data + i - (str.m_size - 1), str.m_data, str.m_size) == 0) {
                return i - (str.m_size - 1);
            }
        }
        return npos;
    }

    size_t string::find_first_of(char c, size_t pos) const {
        if (pos >= m_size) {
            return npos;
        }
        for (size_t i = pos; i < m_size; ++i) {
            if (m_data[i] == c) {
                return i;
            }
        }
        return npos;
    }

    size_t string::find_last_of(char c, size_t pos) const {
        if (m_size == 0) {
            return npos;
        }
        if (pos >= m_size) {
            pos = m_size - 1;
        }
        for (size_t i = pos; i != (size_t)-1; --i) {
            if (m_data[i] == c) {
                return i;
            }
        }
        return npos;
    }

    size_t string::find_first_not_of(char c, size_t pos) const {
        if (pos >= m_size) {
            return npos;
        }
        for (size_t i = pos; i < m_size; ++i) {
            if (m_data[i] != c) {
                return i;
            }
        }
        return npos;
    }

    size_t string::find_last_not_of(char c, size_t pos) const {
        if (m_size == 0) {
            return npos;
        }
        if (pos >= m_size) {
            pos = m_size - 1;
        }
        for (size_t i = pos; i != (size_t)-1; --i) {
            if (m_data[i] != c) {
                return i;
            }
        }
        return npos;
    }

    string string::substr(size_t pos, size_t len) const {
        if (pos >= m_size) {
            return string();
        }
        
        if (len > m_size - pos) {
            len = m_size - pos;
        }

        string result(len, '\0');

        if (len > 0) {
            memcpy(result.m_data, m_data + pos, len);
            result.m_data[len] = '\0';
            result.m_size = len;
        }
        
        return result;
    }
    
    void string::swap(string& other) {
        std::swap(m_data, other.m_data);
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
    }

} // namespace std

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector{
private:
    size_t dim;
    size_t cap;
    T* array;
public:
    Vector();
    Vector(size_t);
    Vector(const Vector&);
    ~Vector();
    Vector& operator=(const Vector&);
    void assign(size_t, const T&);
    T at(size_t) const;
    T operator[](size_t) const;
    T front() const;
    T back() const;
    const T* data() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void shrink_to_fit();
    void clear();
    void push_back(const T&);
    void pop_back();
    void resize(size_t);
};

int main() {
    return 0;
}

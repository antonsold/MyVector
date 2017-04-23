#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector{
private:
    size_t dim;
    size_t cap;
    T* array;
    void new_memory(size_t);
    void free_memory();
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

template <typename T>
void Vector<T>::new_memory(size_t capacity) {
    array = new T[capacity];
    cap = capacity;
}

template <typename T>
void Vector<T>::free_memory() {
    delete[] array;
}

template <typename T>
Vector<T>::Vector(){
    dim = 0;
    new_memory(1);
}

template <typename T>
Vector<T>::Vector(size_t size){
    dim = 0;
    new_memory(size);
}

template <typename T>
Vector<T>::Vector(const Vector &vector) {
    new_memory(vector.dim);
    this->dim = vector.dim;
    for (int i = 0; i < dim; i++)
        this->array[i] = vector.array[i];
}

template <typename T>
Vector<T>::~Vector(){
    free_memory();
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vector) {
    if (this->array != vector.array){
        free_memory();
        new_memory(vector.dim);
        this->dim = vector.dim;
        for (int i = 0; i < dim; i++)
            this->array[i] = vector.array[i];
    }
    return *this;
}

template <typename T>
void Vector<T>::assign(size_t pos, const T &value) {
    array[pos] = value;
}

template <typename T>
T Vector<T>::at(size_t pos) const{
    if (pos > dim)
        throw out_of_range("Index out of range!");
    else
        return array[pos];
}

template <typename T>
T Vector<T>::operator[](size_t pos) const {
    return array[pos];
}

template <typename T>
T Vector<T>::front() const {
    return array[0];
}

template <typename T>
T Vector<T>::back() const {
    return array[dim - 1];
}

template <typename T>
const T* Vector<T>::data() const {
    return &front();
}

template <typename T>
bool Vector<T>::empty() const {
    return dim == 0;
}

template <typename T>
size_t Vector<T>::size() const{
    return dim;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return cap;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    resize(dim);
}

template <typename T>
void Vector<T>::clear() {
    free_memory();
    new_memory(cap);
}

template <typename T>
void Vector<T>::push_back(const T &value) {
    if (cap == dim)
        resize(cap * 2);
    array[dim] = value;
    dim++;
}

template <typename T>
void Vector<T>::pop_back(){
    if (dim == 0)
        throw underflow_error("Stack underflow!");
    else
        dim--;
}

template <typename T>
void Vector<T>::resize(size_t size){
    T* tmp = new T[size];
    for (int i = 0; i < min(size, dim); i++)
        tmp[i] = array[i];
    free_memory();
    if (size < dim)
        dim = size;
    cap = size;
    array = tmp;
}

int main() {
    Vector<int> a;
    a.push_back(4);
    a.push_back(7);
    a.pop_back();
    cout << a.front() << endl;
    cout << a.back() << endl;
    a.push_back(85);
    a.push_back(47);
    a.push_back(41);
    a.push_back(44);
    a.push_back(-5);
    a.pop_back();
    cout << a.size() << endl;
    cout << a.capacity() << endl;
    a.pop_back();
    a.resize(152);
    cout << a.front() << endl;
    a.shrink_to_fit();
    cout << a.size() << endl;
    cout << a.capacity() << endl;
    cout << a.back();
    return 0;
}

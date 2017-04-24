//
// Created by anton on 23.04.2017.
//

#ifndef MYVECTOR_VECTOR_H
#define MYVECTOR_VECTOR_H

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
    template <typename T1, typename T2, typename T3, bool R>
    class v_iterator{
    private:
        T2 startptr; //указатель на T1
        int dim_, pos;
        bool reversed;
        void copy_fields(const v_iterator<T1, T2, T3, R>&);
        void move(int step);
        T2 getptr() const;
    public:
        v_iterator(){};
        v_iterator(T2, int, int);
        v_iterator(const v_iterator<T1, T2, T3, R>&);
        v_iterator<T1, T2, T3, R>& operator=(const v_iterator<T1, T2, T3, R>&);
        T3 operator*();
        v_iterator<T1, T2, T3, R>& operator++();
        v_iterator<T1, T2, T3, R>& operator--();
        const v_iterator<T1, T2, T3, R> operator++(int);
        const v_iterator<T1, T2, T3, R> operator--(int);
        v_iterator<T1, T2, T3, R> operator+(const int) const;
        v_iterator<T1, T2, T3, R> operator-(const int) const;
        int operator-(const v_iterator<T1, T2, T3, R>&) const;
        v_iterator<T1, T2, T3, R>& operator+=(const int);
        v_iterator<T1, T2, T3, R>& operator-=(const int);
        T3 operator[](const int);
        bool operator==(const v_iterator<T1, T2, T3, R>&) const;
        bool operator!=(const v_iterator<T1, T2, T3, R>&) const;
        bool operator>(const v_iterator<T1, T2, T3, R>&) const;
        bool operator<(const v_iterator<T1, T2, T3, R>&) const;
        bool operator>=(const v_iterator<T1, T2, T3, R>&) const;
        bool operator<=(const v_iterator<T1, T2, T3, R>&) const;
    };
    typedef v_iterator<T, T*, T&, true> iterator;
    typedef v_iterator<const T, const T*, const T&, true> const_iterator;
    typedef v_iterator<T, T*, T&, false> reverse_iterator;
    typedef v_iterator<const T, const T*, const T&, false> const_reverse_iterator;
    iterator begin();
    const_iterator cbegin() const;
    reverse_iterator rbegin();
    const_reverse_iterator crbegin() const;
    iterator end();
    const_iterator cend() const;
    reverse_iterator rend();
    const_reverse_iterator crend() const;
};

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
T2 Vector<T>::v_iterator<T1, T2, T3, R>::getptr() const{
    return startptr + pos;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
void Vector<T>::v_iterator<T1, T2, T3, R>::move(int step) {
    if (dim_ == 0) {
        pos = 0;
        return;
    }
    if (R)
        pos += step;
    else
        pos -= step;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>::v_iterator(T2 start_ptr, int dim, int position) {
    startptr = start_ptr;
    dim_ = dim;
    if (R)
        pos = position;
    else
        pos = -position;
    reversed = R;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
void Vector<T>::v_iterator<T1, T2, T3, R>::copy_fields(const Vector<T>::v_iterator<T1, T2, T3, R> &it) {
    this->startptr = it.startptr;
    this->dim_ = it.dim_;
    this->pos = it.pos;
    this->reversed = it.reversed;
}


template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>::v_iterator(const Vector<T>::v_iterator<T1, T2, T3, R> &it) {
    copy_fields(it);
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>& Vector<T>::v_iterator<T1, T2, T3, R>::operator=(const Vector<T>::v_iterator<T1, T2, T3, R> &it) {
    copy_fields(it);
    return *this;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
T3 Vector<T>::v_iterator<T1, T2, T3, R>::operator*() {
    return *getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>& Vector<T>::v_iterator<T1, T2, T3, R>::operator++() {
    move(1);
    return *this;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>& Vector<T>::v_iterator<T1, T2, T3, R>::operator--() {
    move(-1);
    return *this;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
const Vector<T>::v_iterator<T1, T2, T3, R> Vector<T>::v_iterator<T1, T2, T3, R>::operator++(int) {
    v_iterator<T1, T2, T3, R> tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
const Vector<T>::v_iterator<T1, T2, T3, R> Vector<T>::v_iterator<T1, T2, T3, R>::operator--(int) {
    v_iterator<T1, T2, T3, R> tmp = *this;
    --(*this);
    return tmp;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R> Vector<T>::v_iterator<T1, T2, T3, R>::operator+(const int a) const{
    v_iterator<T1, T2, T3, R> tmp = *this;
    tmp.move(a);
    return tmp;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R> Vector<T>::v_iterator<T1, T2, T3, R>::operator-(const int a) const{
    v_iterator<T1, T2, T3, R> tmp = *this;
    tmp.move(-a);
    return tmp;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
int Vector<T>::v_iterator<T1, T2, T3, R>::operator-(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() - it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>& Vector<T>::v_iterator<T1, T2, T3, R>::operator+=(const int a) {
    move(a);
    return *this;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
Vector<T>::v_iterator<T1, T2, T3, R>& Vector<T>::v_iterator<T1, T2, T3, R>::operator-=(const int a) {
    move(-a);
    return *this;
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
T3 Vector<T>::v_iterator<T1, T2, T3, R>::operator[](const int a) {
    return *(*this + a);
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator==(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() == it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator!=(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() != it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator>(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() > it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator<(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() < it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator>=(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() >= it.getptr();
}

template <typename T>
template <typename T1, typename T2, typename T3, bool R>
bool Vector<T>::v_iterator<T1, T2, T3, R>::operator<=(const Vector<T>::v_iterator<T1, T2, T3, R> &it) const{
    return this->getptr() <= it.getptr();
}

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
        throw underflow_error("Vector underflow!");
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

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(&array[0], dim, 0);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const{
    return const_iterator(&array[0], dim, 0);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
    return reverse_iterator(&array[dim - 1], dim, 0);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const{
    return const_reverse_iterator(&array[dim - 1], dim, 0);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(&array[0], dim, dim);
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const{
    return const_iterator(&array[0], dim, dim);
}

template <typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() {
    return reverse_iterator(&array[dim - 1], dim, dim);
}

template <typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const{
    return const_reverse_iterator(&array[dim - 1], dim, dim);
}

#endif //MYVECTOR_VECTOR_H

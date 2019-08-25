#ifndef QONTAINER_H
#define QONTAINER_H

#include <iostream>
#include <vector>

template <class T>
class Qontainer{
private:
    unsigned int size; //num elementi
    unsigned int capacity; //capacità qontainer
    T* buffer;
    void recapacity(); //crea un clone del qontainer corrente raddoppiandone la capacità
public:
    class iterator{
        friend class Qontainer<T>;
    private:
        T* punt;
        iterator(T*);
    public:
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;

        T& operator*() const;
        T* operator->() const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+(unsigned int);
        iterator& operator-(unsigned int);
    };

    class const_iterator{
        friend class Qontainer<T>;
    private:
        const T* cpunt;
        const_iterator(T*);
    public:
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;

        const T& operator*()const;
        const T* operator->()const;

        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const_iterator& operator+(unsigned int);
        const_iterator& operator-(unsigned int);
    };

    Qontainer(unsigned int =4);
    Qontainer(const T&, unsigned int =4);
    Qontainer(const Qontainer<T>&);
    ~Qontainer();
    Qontainer<T>& operator=(const Qontainer<T>&);
    T& operator[](unsigned int);
    T& front();
    T& back();

    bool operator==(const Qontainer<T>&) const;

    unsigned int getSize() const; //ritorna size = num elementi
    unsigned int getCapacity() const; //ritorna capacity = capacità container
    bool isEmpty() const;
    void push_back(T*);
    void push_back(const T&); //aggiunge un elemento in coda
    void pop_back(); //elimina ultimo elemento
    void erase(unsigned int =0);
    void erase(unsigned int, unsigned int);
    void erase(T);
    void clear();
    T& element(unsigned int);
    std::vector<T> search(T);

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    void print() const;
};

//*********************QONTAINER************************

template <typename T>
Qontainer<T>::Qontainer(unsigned int g) : size(0), capacity(g), buffer(new T[g]) {}

template <typename T>
Qontainer<T>::Qontainer(const T& t, unsigned int g) : size(0), capacity(g), buffer(new T[g]) {
    for(unsigned int i=0; i < capacity; ++i)
        buffer[i] = t;
}

template <typename T>
Qontainer<T>::Qontainer(const Qontainer<T>& q) : size(q.size), capacity(q.capacity), buffer(new T[q.capacity]){
    for(unsigned int i = 0; i < size; ++i)
        buffer[i] = q.buffer[i];
}

template <typename T>
Qontainer<T>::~Qontainer<T>(){
    if(buffer)  delete[] buffer;
}

template <typename T>
Qontainer<T>& Qontainer<T>::operator=(const Qontainer<T>& q){
    if(this != &q){
        delete[] buffer;
        size = q.size;
        capacity = q.capacity;
        buffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i)
            buffer[i] = q.buffer[i];
    }
    return *this;
}

template <typename T>
T& Qontainer<T>::operator[](unsigned int index){
    return buffer[index];
}

template <typename T>
T& Qontainer<T>::front(){
    return buffer[0];
}

template <typename T>
T& Qontainer<T>::back(){
    return buffer[size-1];
}

template <typename T>
bool Qontainer<T>::operator==(const Qontainer<T>& q) const{
    bool uguale = (q.size == size && q.capacity == capacity);
    for(auto it = cbegin(), it2 = q.cbegin(); it != cend() && uguale; ++it, ++it2)
        if(*it != *it2)     uguale = false;
    return uguale;
}

template <typename T>
unsigned int Qontainer<T>::getSize() const{
    return size;
}

template <typename T>
unsigned int Qontainer<T>::getCapacity() const{
    return capacity;
}

template <typename T>
bool Qontainer<T>::isEmpty() const{
    return size == 0;
}

template <typename T>
void Qontainer<T>::recapacity(){
    unsigned int newCapacity = capacity*2;
    T* newBuffer = new T[newCapacity];
    for(unsigned int i = 0; i < size; ++i)
        newBuffer[i] = buffer[i];
    capacity = newCapacity;
    delete[] buffer;
    buffer = newBuffer;
}

template <typename T>
void Qontainer<T>::push_back(T *q) {
    if(!(size < capacity))
        recapacity();
    buffer[size++] = *q;
}
template <typename T>
void Qontainer<T>::push_back(const T& q) {
    Qontainer<T>::push_back(new T(q));
}

template <typename T>
void Qontainer<T>::pop_back(){
    if(size > 0)
        --size;
}

template <typename T>
void Qontainer<T>::erase(unsigned int index){
    if(index > size-1)
        throw std::out_of_range("Index out of range.");
    for(unsigned int i = index; i < size-1; i++)
        buffer[i] = buffer[i+1];
    size--;
}

template <typename T>
void Qontainer<T>::erase(unsigned int start, unsigned int end){
    if(start<0 || end<0 || start > size-1 || end > size-1 || start > end)
        throw std::out_of_range("Indexes out of bounds.");
    for(unsigned int i=start, j=1; i < size; ++i, ++j)
        buffer[i] = buffer[end+j];
    size = size - (end-start)+1;
}

template <typename T>
void Qontainer<T>::erase(T t) {
    unsigned int index = 0U;
    for(auto it = begin();  (*it) != t && it != end(); index++, ++it);
    return erase(index);
}

template <typename T>
void Qontainer<T>::clear(){
    delete[] buffer;
    buffer = new T[4];
    capacity = 4;
    size = 0;
}

template <typename T>
T& Qontainer<T>::element(unsigned int index){
    if(index < 0 || index > size-1)
        throw std::out_of_range("Index out of range.");
    return buffer[index];
}

template <typename T>
std::vector<T> Qontainer<T>::search(T el) {
    std::vector<T> search;
    T aux;
    for(auto it = begin(); it != end(); ++it)
        if(el == *it) {
            aux = *it;
            search.push_back(aux);
        }
    return search;
}

template <typename T>
typename Qontainer<T>::iterator Qontainer<T>::begin() const{
    return iterator(buffer);
}

template <typename T>
typename Qontainer<T>::iterator Qontainer<T>::end() const{
    return iterator(buffer + size);
}

template <typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::cbegin() const{
    return const_iterator(buffer);
}

template <typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::cend() const{
    return const_iterator(buffer + size);
}

template <typename T>
void Qontainer<T>::print() const{
    if(!size)
        std::cout<<"Qontainer vuoto." << std::endl;
    for(unsigned int i=0; i < size; ++i)
        std::cout<<buffer[i]<<" ";
    std::cout<<std::endl;
}

//*********************ITERATOR************************

template <class T>
Qontainer<T>::iterator::iterator(T* q) : punt(q) {}

template <typename T>
bool Qontainer<T>::iterator::operator==(const iterator& iter) const{
    return punt == iter.punt;
}

template <typename T>
bool Qontainer<T>::iterator::operator!=(const iterator& iter) const{
    return punt != iter.punt;
}

template <typename T>
T& Qontainer<T>::iterator::operator*() const {
    return *punt;
}

template <typename T>
T* Qontainer<T>::iterator::operator->() const {
    return punt;
}

template <typename T>
typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator++() {
    if(punt)
        punt++;
    return *this;
}

template <typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator++(int) {
    iterator aux = *this;
    if(punt)
        punt++;
    return aux;
}

template <typename T>
typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator--() {
    if(punt)
        punt--;
    return *this;
}

template <typename T>
typename Qontainer<T>::iterator Qontainer<T>::iterator::operator--(int) {
    iterator aux(punt);
    if(punt)
        punt--;
    return aux;
}

template <typename T>
typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator+(unsigned int i) {
    if(punt)
        punt = punt + i;
    return *this;
}

template <typename T>
typename Qontainer<T>::iterator& Qontainer<T>::iterator::operator-(unsigned int i) {
    if(punt)
        punt = punt - i;
    return *this;
}

//*********************CONST_ITERATOR************************

template <class T>
Qontainer<T>::const_iterator::const_iterator(T* q) : cpunt(q) {}

template <typename T>
bool Qontainer<T>::const_iterator::operator==(const const_iterator& iter) const{
    return cpunt == iter.cpunt;
}

template <typename T>
bool Qontainer<T>::const_iterator::operator!=(const const_iterator& iter) const{
    return cpunt != iter.cpunt;
}

template <typename T>
const T& Qontainer<T>::const_iterator::operator*() const{
    return *cpunt;
}

template <typename T>
const T* Qontainer<T>::const_iterator::operator->() const{
    return cpunt;
}

template <typename T>
typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator++() {
    if(cpunt)
        cpunt++;
    return *this;
}

template <typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator++(int) {
    const_iterator aux = *this;
    if(cpunt)
        cpunt++;
    return aux;
}

template <typename T>
typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator--() {
    if(cpunt)
        cpunt--;
    return *this;
}

template <typename T>
typename Qontainer<T>::const_iterator Qontainer<T>::const_iterator::operator--(int) {
    const_iterator aux(cpunt);
    if(cpunt)
        cpunt--;
    return aux;
}

template <typename T>
typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator+(unsigned int i) {
    if(cpunt)
        cpunt = cpunt + i;
    return *this;
}

template <typename T>
typename Qontainer<T>::const_iterator& Qontainer<T>::const_iterator::operator-(unsigned int i) {
    if(cpunt)
        cpunt = cpunt - i;
    return *this;
}


#endif // QONTAINER_H

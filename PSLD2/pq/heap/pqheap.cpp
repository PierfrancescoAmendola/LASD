//
//  pqheap.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//

namespace lasd {

/* ************************************************************************** */

// Specific constructor from TraversableContainer
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& cont) : HeapVec<Data>(cont){}

// Specific constructor from MappableContainer
template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& cont) : HeapVec<Data>(std::move(cont)){}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {}

/* ************************************************************************** */

/* ************************************************************************** */

// Copy assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
    HeapVec<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
    HeapVec<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */

// Tip: Returns the maximum element (throws length_error if empty)
template <typename Data>
Data PQHeap<Data>::Tip() const {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    return (*this)[0]; // Assuming this->elements[0] is the maximum element
}

// RemoveTip: Removes the maximum element (throws length_error if empty)
template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    std::swap(this->elements[0], this->elements[size - 1]);
    --size;
    if (size > 0) {
        HeapifyDown(0);
    }
}

// TipNRemove: Returns and removes the maximum element (throws length_error if empty)
template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
    }
    Data result = std::move(this->elements[0]);
    std::swap(this->elements[0], this->elements[size - 1]);
    --size;
    if (size > 0) {
        HeapifyDown(0);
    }
    return result;
}

// Insert (copy): Inserts a copy of the value
template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
    // Double the capacity if needed
    unsigned long newCapacity = (size == 0) ? 1 : size * 2;
    Data* newelements = new Data[newCapacity];
    for (unsigned long i = 0; i < size; ++i) {
        newelements[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newelements;
    this->elements[size] = value;
    ++size;
    HeapifyUp(size - 1);
}

// Insert (move): Inserts by moving the value
template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
    // Double the capacity if needed
    unsigned long newCapacity = (size == 0) ? 1 : size * 2;
    Data* newelements = new Data[newCapacity];
    for (unsigned long i = 0; i < size; ++i) {
        newelements[i] = std::move(this->elements[i]);
    }
    delete[] this->elements;
    this->elements = newelements;
    this->elements[size] = std::move(value);
    ++size;
    HeapifyUp(size - 1);
}

// Change (copy): Changes priority at given index
template <typename Data>
void PQHeap<Data>::Change(unsigned long index, const Data& value)
{
    if (index >= size) 
    {
        return;
    }
    Data oldValue = this->elements[index];
    this->elements[index] = value;
    if (value > oldValue) 
    {
        HeapifyUp(index);
    } else if (value < oldValue) 
    {
        HeapifyDown(index);
    }
}

// Change (move): Changes priority at given index by moving
template <typename Data>
void PQHeap<Data>::Change(unsigned long index, Data&& value) 
{
    if (index >= size) 
    {
        return;
    }
    Data oldValue = this->elements[index];
    this->elements[index] = std::move(value);
    if (this->elements[index] > oldValue) 
    {
        HeapifyUp(index);
    }
    else if (this->elements[index] < oldValue) 
    {
        HeapifyDown(index);
    }
}

template <typename Data>
void PQHeap<Data>::Clear() noexcept {
    // Libero l'array e resetto tutto
    delete[] this->elements;
    this->elements = nullptr;
    size = 0;
    capacity = 0;
    // Creo un nuovo array vuoto
    this->elements = new Data[4]();
    capacity = 4;
    // Perché: resetto tutto e mantengo la capacità iniziale di 4 // Delegate to Vector<Data>::Clear
}

/* ************************************************************************** */

// HeapifyUp: Restores max-heap property upward
template <typename Data>
void PQHeap<Data>::HeapifyUp(unsigned long index) {
    while (index > 0) {
        unsigned long parent = (index - 1) / 2;
        if (this->elements[index] > this->elements[parent]) {
            std::swap(this->elements[index], this->elements[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// HeapifyDown: Restores max-heap property downward
template <typename Data>
void PQHeap<Data>::HeapifyDown(unsigned long index) {
    while (true) {
        unsigned long largest = index;
        unsigned long left = 2 * index + 1;
        unsigned long right = 2 * index + 2;

        if (left < size && this->elements[left] > this->elements[largest]) {
            largest = left;
        }
        if (right < size && this->elements[right] > this->elements[largest]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        std::swap(this->elements[index], this->elements[largest]);
        index = largest;
    }
}

/* ************************************************************************** */

}
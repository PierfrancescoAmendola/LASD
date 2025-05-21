//
//  setlst.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

namespace lasd {

/* ************************************************************************** */

// Specific Constructors
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& tc) {
    tc.Traverse([this](const Data& data) { Insert(data); });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& mc) {
    mc.Map([this](Data& data) { Insert(std::move(data)); });
}

// Copy Constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst& other) {
    List<Data>::CopyList(other);
}

// Move Constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst&& other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

// Destructor
template <typename Data>
SetLst<Data>::~SetLst() {
    Clear();
}

/* ************************************************************************** */

// Copy Assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst& other) {
    if (this != &other) {
        Clear();
        List<Data>::CopyList(other);
    }
    return *this;
}

// Move Assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst&& other) noexcept {
    if (this != &other) {
        Clear();
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }
    return *this;
}

/* ************************************************************************** */

// Comparison Operators
template <typename Data>
bool SetLst<Data>::operator==(const SetLst& other) const noexcept {
    return List<Data>::operator==(other);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// OrderedDictionaryContainer
template <typename Data>
const Data& SetLst<Data>::Min() const {
    return List<Data>::Front();
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
    return List<Data>::FrontNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
    List<Data>::RemoveFromFront();
}

template <typename Data>
const Data& SetLst<Data>::Max() const {
    return List<Data>::Back();
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
    return List<Data>::BackNRemove();
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
    List<Data>::RemoveFromBack();
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
    if (head == nullptr || head->element >= data)
        throw std::length_error("Predecessore non trovato");

    Node** pos = BinarySearch(data);
    Node* pred = nullptr;
    for (Node* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->next == *pos) {
            pred = curr;
            break;
        }
    }

    if (pred == nullptr)
        throw std::length_error("Predecessore non trovato");

    return pred->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& data) {
    Data val = Predecessor(data);
    Remove(val);
    return val;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& data) {
    Data val = Predecessor(data);
    Remove(val);
}

template <typename Data>
const Data& SetLst<Data>::Successor(const Data& data) const {
    if (head == nullptr || tail->element <= data)
        throw std::length_error("Successore non trovato");

    Node** pos = BinarySearch(data);
    Node* succ = (*pos != nullptr && (*pos)->element == data)
                 ? (*pos)->next
                 : *pos;

    if (succ == nullptr)
        throw std::length_error("Successore non trovato");

    return succ->element;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    Data val = Successor(data);
    Remove(val);
    return val;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
    Data val = Successor(data);
    Remove(val);
}

/* ************************************************************************** */

// DictionaryContainer
template <typename Data>
bool SetLst<Data>::Insert(const Data& data) {
    Node** pos = BinarySearch(data);
    if (*pos != nullptr && (*pos)->element == data) return false;
    Node* newNode = new Node(data);
    newNode->next = *pos;
    *pos = newNode;
    if (newNode->next == nullptr) tail = newNode;
    size++;
    return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data&& data) {
    Node** pos = BinarySearch(data);
    if (*pos != nullptr && (*pos)->element == data) return false;
    Node* newNode = new Node(std::move(data));
    newNode->next = *pos;
    *pos = newNode;
    if (newNode->next == nullptr) tail = newNode;
    size++;
    return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& data) {
    Node** pos = BinarySearch(data);
    if (*pos == nullptr || (*pos)->element != data) return false;
    
    Node* toRemove = *pos;
    *pos = toRemove->next;
    
    if (toRemove == tail) {
        if (head == nullptr) {
            tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            tail = current;
        }
    }
    
    toRemove->next = nullptr;
    delete toRemove;
    size--;
    return true;
}

/* ************************************************************************** */

// LinearContainer
template <typename Data>
const Data& SetLst<Data>::operator[](unsigned long index) const {
    return List<Data>::operator[](index);
}

/* ************************************************************************** */

// TestableContainer
template <typename Data>
bool SetLst<Data>::Exists(const Data& data) const noexcept {
    Node** pos = BinarySearch(data);
    return (*pos != nullptr && (*pos)->element == data);
}

/* ************************************************************************** */

// ClearableContainer
template <typename Data>
void SetLst<Data>::Clear() {
    List<Data>::Clear();
}

/* ************************************************************************** */

// Auxiliary function: Binary search for ordered list
template <typename Data>
typename SetLst<Data>::Node** SetLst<Data>::BinarySearch(const Data& dat) const {
    if (size == 0) {
        return const_cast<Node**>(&head);
    }

    long left = 0;
    long right = size - 1;

    Node* leftNode = head;
    Node** leftPtr = const_cast<Node**>(&head);
    Node** resultPtr = leftPtr;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        
        long steps = mid - left;
        
        Node* midNode = leftNode;
        Node** midPtr = leftPtr;
        for (long i = 0; i < steps && midNode != nullptr; ++i) {
            midPtr = &((*midPtr)->next);
            midNode = *midPtr;
        }

        if (midNode == nullptr) {
            return resultPtr;
        }

        if (midNode->element == dat) {
            return midPtr;
        } else if (midNode->element < dat) {
            resultPtr = &(midNode->next);
            left = mid + 1;
            leftNode = midNode->next;
            leftPtr = &((*midPtr)->next);
        } else {
            right = mid - 1;
            resultPtr = midPtr;
        }
    }

    return resultPtr;
}

/* ************************************************************************** */

}






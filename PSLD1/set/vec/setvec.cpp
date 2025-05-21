//
//  setvec.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//



// namespace lasd {

// /* ************************************************************************** */

// /* Auxiliary function for circular indexing */
// template <typename Data>
// unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
//     return (head + index) % vec.Size();
// }

// //size: Indica quanti elementi sono effettivamente presenti nel set (cardinalità logica). 
// //È sempre minore o uguale a vec.Size().
// //vec.Size(): Indica la capacità totale del vettore (dimensione fisica), 
// //cioè lo spazio allocato per contenere gli elementi, 
// //che può essere maggiore di size per evitare riallocazioni frequenti.


// /* Binary search to find insertion point (returns absolute index) */
// template <typename Data>
// unsigned long SetVec<Data>::BinarySearch(const Data& data) const noexcept  {
//     if (size == 0) {
//         return head;
//     }
//     unsigned long left = 0;
//     unsigned long right = size;
//     while (left < right) {
//         unsigned long mid = left + (right - left) / 2;
//         if (vec[(head + mid) % vec.Size()] < data) {
//             left = mid + 1;
//         } else {
//             right = mid;
//         }
//     }
//     return (head + left) % vec.Size();
// }

// /* Default constructor */
// template <typename Data>
// SetVec<Data>::SetVec() {
//     vec.Resize(4); // Capacità iniziale arbitraria
//     size = 0;
//     head = 0;
// }

// /* Specific constructors */
// template <typename Data>
// SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec() {
//     container.Traverse([this](const Data& dato) {
//         Insert(dato);
//     });
// }

// template <typename Data>
// SetVec<Data>::SetVec(MappableContainer<Data>& container) : SetVec() {
//     container.Map([this](const Data& val) {
//         Insert(val);
//     });
// }

// /* Copy constructor */
// template <typename Data>
// SetVec<Data>::SetVec(const SetVec& other) : vec(other.vec), head(other.head) {
//     size = other.size;
// }

// /* Move constructor */
// template <typename Data>
// SetVec<Data>::SetVec(SetVec&& other) noexcept {
//     std::swap(vec, other.vec);
//     std::swap(size, other.size);
//     std::swap(head, other.head);
// }

// /* Destructor */
// template <typename Data>
// SetVec<Data>::~SetVec() {
//     Clear();
// }

// /* Copy assignment */
// template <typename Data>
// SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
//     if (this != &other) {
//         Clear();
//         vec = other.vec;
//         size = other.size;
//         head = other.head;
//     }
//     return *this;
// }

// /* Move assignment */
// template <typename Data>
// SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) noexcept {
//     if (this != &other) {
//         std::swap(vec, other.vec);
//         std::swap(size, other.size);
//         std::swap(head, other.head);
//     }
//     return *this;
// }

// /* Comparison operators */
// template <typename Data>
// bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
//     if (size != other.size) return false;
//     for (unsigned long i = 0; i < size; ++i) {
//         if (vec[CircularIndex(i)] != other.vec[other.CircularIndex(i)]) return false;
//     }
//     return true;
// }

// template <typename Data>
// bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
//     return !(*this == other);
// }

// /* Specific member functions (OrderedDictionaryContainer) */
// template <typename Data>
// const Data& SetVec<Data>::Min() const {
//     if (size == 0) throw std::length_error("Set is empty");
//     return vec[head];
// }

// template <typename Data>
// Data SetVec<Data>::MinNRemove() {
//     if (size == 0) throw std::length_error("Set is empty");
//     Data result = std::move(vec[head]);
//     head = (head + 1) % vec.Size();
//     --size;
//     return result;
// }

// template <typename Data>
// void SetVec<Data>::RemoveMin() {
//     if (size == 0) throw std::length_error("Set is empty");
//     head = (head + 1) % vec.Size();
//     --size;
// }

// template <typename Data>
// const Data& SetVec<Data>::Max() const {
//     if (size == 0) throw std::length_error("Set is empty");
//     return vec[CircularIndex(size - 1)];
// }

// template <typename Data>
// Data SetVec<Data>::MaxNRemove() {
//     if (size == 0) throw std::length_error("Set is empty");
//     Data result = std::move(vec[CircularIndex(size - 1)]);
//     --size;
//     return result;
// }

// template <typename Data>
// void SetVec<Data>::RemoveMax() {
//     if (size == 0) throw std::length_error("Set is empty");
//     --size;
// }

// template <typename Data>
// const Data& SetVec<Data>::Predecessor(const Data& value) const {
//     if (size == 0) throw std::length_error("Set is empty");

//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

//     if (pos == 0)
//         throw std::length_error("No predecessor found");

//     return vec[CircularIndex(pos - 1)];
// }


// template <typename Data>
// void SetVec<Data>::RemovePredecessor(const Data& value) {
//     if (size == 0) throw std::length_error("Set is empty");
//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
//     if (pos == 0) throw std::length_error("No predecessor found");
//     pos--;
//     if (pos <= size / 2) {
//         // Shift right towards head
//         for (unsigned long i = pos; i > 0; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[head] = Data{}; // Clear old head position
//         head = (head + 1) % vec.Size();
//     } else {
//         // Shift left towards tail
//         for (unsigned long i = pos; i < size - 1; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//     }
//     --size;
//     if (size < vec.Size() / 4 && vec.Size() > 10) Resize(vec.Size() / 2);
// }

// template <typename Data>
// Data SetVec<Data>::PredecessorNRemove(const Data& value) {
//     if (size == 0) throw std::length_error("Set is empty");
//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
//     if (pos == 0) throw std::length_error("No predecessor found");
//     pos--;
//     Data result = std::move(vec[CircularIndex(pos)]);
//     if (pos <= size / 2) {
//         // Shift right towards head
//         for (unsigned long i = pos; i > 0; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[head] = Data{}; // Clear old head position
//         head = (head + 1) % vec.Size();
//     } else {
//         // Shift left towards tail
//         for (unsigned long i = pos; i < size - 1; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//     }
//     --size;
//     if (size < vec.Size() / 4 && vec.Size() > 10) Resize(vec.Size() / 2);
//     return result;
// }
// template <typename Data>
// const Data& SetVec<Data>::Successor(const Data& value) const {
//     if (size == 0) throw std::length_error("Set is empty");

//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

//     // Se il valore è uguale a quello trovato, il successore è il successivo
//     if (pos < size && vec[CircularIndex(pos)] == value) {
//         if (pos + 1 >= size)
//             throw std::length_error("No successor found");
//         return vec[CircularIndex(pos + 1)];
//     }

//     // Altrimenti il successore è il valore trovato in BinarySearch
//     if (pos >= size)
//         throw std::length_error("No successor found");
//     return vec[CircularIndex(pos)];
// }


// template <typename Data>
// Data SetVec<Data>::SuccessorNRemove(const Data& value) {
//     if (size == 0) throw std::length_error("Set is empty");

//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

//     // Se il valore è presente, il successore è l'elemento successivo
//     if (pos < size && vec[CircularIndex(pos)] == value) {
//         pos++;
//     }

//     // Verifica se esiste un successore
//     if (pos >= size) throw std::length_error("No successor found");

//     // Rimuovi il successore
//     Data result = std::move(vec[CircularIndex(pos)]);

//     // Shift efficiente
//     if (pos <= size / 2) {
//         // Shift verso destra (verso head)
//         for (unsigned long i = pos; i > 0; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[head] = Data{}; // Pulisce la vecchia posizione di head
//         head = (head + 1) % vec.Size();
//     } else {
//         // Shift verso sinistra (verso tail)
//         for (unsigned long i = pos; i < size - 1; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//     }

//     --size;

//     // Ridimensiona se necessario
//     if (size < vec.Size() / 4 && vec.Size() > 10) {
//         Resize(vec.Size() / 2);
//     }

//     return result;
// }

// /* RemoveSuccessor */
// template <typename Data>
// void SetVec<Data>::RemoveSuccessor(const Data& value) {
//     if (size == 0) throw std::length_error("Set is empty");

//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

//     // Se il valore è presente, il successore è l'elemento successivo
//     if (pos < size && vec[CircularIndex(pos)] == value) {
//         pos++;
//     }

//     // Verifica se esiste un successore
//     if (pos >= size) throw std::length_error("No successor found");

//     // Shift efficiente
//     if (pos <= size / 2) {
//         // Shift verso destra (verso head)
//         for (unsigned long i = pos; i > 0; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[head] = Data{}; // Pulisce la vecchia posizione di head
//         head = (head + 1) % vec.Size();
//     } else {
//         // Shift verso sinistra (verso tail)
//         for (unsigned long i = pos; i < size - 1; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//     }

//     --size;

//     // Ridimensiona se necessario
//     if (size < vec.Size() / 4 && vec.Size() > 10) {
//         Resize(vec.Size() / 2);
//     }
// }


// /* Specific member functions (DictionaryContainer) */
// template <typename Data>
// bool SetVec<Data>::Insert(const Data& value) {
//     if (size == vec.Size()) Resize(vec.Size() * 2);
//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
//     if (pos < size && vec[CircularIndex(pos)] == value) return false; // Duplicate
//     if (size == 0) {
//         vec[head] = value;
//         ++size;
//         return true;
//     }
//     if (pos <= size / 2) {
//         // Shift left towards head
//         head = (head == 0) ? vec.Size() - 1 : head - 1;
//         for (unsigned long i = 0; i < pos; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//         vec[CircularIndex(pos)] = value;
//     } else {
//         // Shift right towards tail
//         for (unsigned long i = size; i > pos; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[CircularIndex(pos)] = value;
//     }
//     ++size;
//     return true;
// }

// template <typename Data>
// bool SetVec<Data>::Insert(Data&& value) {
//     if (size == vec.Size()) Resize(vec.Size() * 2);
//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
//     if (pos < size && vec[CircularIndex(pos)] == value) return false; // Duplicate
//     if (size == 0) {
//         vec[head] = std::move(value);
//         ++size;
//         return true;
//     }
//     if (pos <= size / 2) {
//         // Shift left towards head
//         head = (head == 0) ? vec.Size() - 1 : head - 1;
//         for (unsigned long i = 0; i < pos; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//         vec[CircularIndex(pos)] = std::move(value);
//     } else {
//         // Shift right towards tail
//         for (unsigned long i = size; i > pos; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[CircularIndex(pos)] = std::move(value);
//     }
//     ++size;
//     return true;
// }
// template <typename Data>
// bool SetVec<Data>::Remove(const Data& value) {
//     if (size == 0) return false; // Nothing to remove

//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size(); // Correct calculation

//     // Check if the value is at the position
//     if (vec[CircularIndex(pos)] != value) return false;

//     // Shift elements depending on the position
//     if (pos <= size / 2) {
//         // Shift right towards head
//         for (unsigned long i = pos; i > 0; --i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
//         }
//         vec[head] = Data{}; // Clear old head position
//         head = (head + 1) % vec.Size(); // Update head
//     } else {
//         // Shift left towards tail
//         for (unsigned long i = pos; i < size - 1; ++i) {
//             vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
//         }
//     }
//     --size;

//     // Shrink the vector if necessary
//     if (size < vec.Size() / 4 && vec.Size() > 10) Resize(vec.Size() / 2);

//     return true;
// }


// /* Specific member functions (LinearContainer) */
// template <typename Data>
// const Data& SetVec<Data>::operator[](unsigned long index) const {
//     if (index >= size) throw std::out_of_range("Index out of range");
//     return vec[CircularIndex(index)];
// }  

// /* Specific member function (TestableContainer) */
// template <typename Data>
// bool SetVec<Data>::Exists(const Data& value) const noexcept {
//     unsigned long abs_pos = BinarySearch(value);
//     unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
//     return (pos < size && vec[CircularIndex(pos)] == value);
// }

// /* Specific member function (ClearableContainer) */
// template <typename Data>
// void SetVec<Data>::Clear() {
//     vec.Clear();
//     size = 0;
//     head = 0;
//     vec.Resize(4); // Coerente con il costruttore di default
// }

// /* Auxiliary function for resizing */
// template <typename Data>
// void SetVec<Data>::Resize(unsigned long newSize) {
//     Vector<Data> newVec(newSize);
//     unsigned long newHead = 0;
//     for (unsigned long i = 0; i < size; ++i) {
//         newVec[newHead + i] = std::move(vec[CircularIndex(i)]);
//     }
//     vec = std::move(newVec);
//     head = newHead;
// }

// /* ************************************************************************** */

// }

namespace lasd {

/* ************************************************************************** */

/* Auxiliary function for circular indexing */
template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
    return (head + index) % capacity;
}

/* Binary search to find insertion point (returns absolute index) */
template <typename Data>
unsigned long SetVec<Data>::BinarySearch(const Data& data) const noexcept {
    if (size == 0) {
        return head;
    }
    unsigned long left = 0;
    unsigned long right = size;
    while (left < right) {
        unsigned long mid = left + (right - left) / 2;
        if (elements[CircularIndex(mid)] < data) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return (head + left) % capacity;
}

/* Default constructor */
template <typename Data>
SetVec<Data>::SetVec() {
    capacity = 4; // Capacità iniziale arbitraria
    elements = new Data[capacity]();
    size = 0;
    head = 0;
}

/* Specific constructors */
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec() {
    container.Traverse([this](const Data& dato) {
        Insert(dato);
    });
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>& container) : SetVec() {
    container.Map([this](const Data& val) {
        Insert(val);
    });
}

/* Copy constructor */
template <typename Data>
SetVec<Data>::SetVec(const SetVec& other) {
    capacity = other.capacity;
    elements = new Data[capacity]();
    size = other.size;
    head = other.head;
    for (unsigned long i = 0; i < size; ++i) {
        elements[CircularIndex(i)] = other.elements[other.CircularIndex(i)];
    }
}

/* Move constructor */
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
    std::swap(elements, other.elements);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(head, other.head);
}

/* Destructor */
template <typename Data>
SetVec<Data>::~SetVec() {
    delete[] elements;
    elements = nullptr;
    size = 0;
    capacity = 0;
    head = 0;
}

/* Copy assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
    if (this != &other) {
        delete[] elements;
        capacity = other.capacity;
        elements = new Data[capacity]();
        size = other.size;
        head = other.head;
        for (unsigned long i = 0; i < size; ++i) {
            elements[CircularIndex(i)] = other.elements[other.CircularIndex(i)];
        }
    }
    return *this;
}

/* Move assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) noexcept {
    if (this != &other) {
        // Delete current resources
        delete[] elements;
        // Move resources from other
        elements = other.elements;
        size = other.size;
        capacity = other.capacity;
        head = other.head;
        // Reset other to empty state
        other.elements = new Data[4]();
        other.size = 0;
        other.capacity = 4;
        other.head = 0;
    }
    return *this;
}

/* Comparison operators */
template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
    if (size != other.size) return false;
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[CircularIndex(i)] != other.elements[other.CircularIndex(i)]) return false;
    }
    return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
    return !(*this == other);
}

/* Specific member functions (OrderedDictionaryContainer) */
template <typename Data>
const Data& SetVec<Data>::Min() const {
    if (size == 0) throw std::length_error("Set is empty");
    return elements[head];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
    if (size == 0) throw std::length_error("Set is empty");
    Data result = std::move(elements[head]);
    elements[head] = Data{}; // Clear old head position
    head = (head + 1) % capacity;
    --size;
    return result;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
    if (size == 0) throw std::length_error("Set is empty");
    elements[head] = Data{}; // Clear old head position
    head = (head + 1) % capacity;
    --size;
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
    if (size == 0) throw std::length_error("Set is empty");
    return elements[CircularIndex(size - 1)];
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    if (size == 0) throw std::length_error("Set is empty");
    Data result = std::move(elements[CircularIndex(size - 1)]);
    --size;
    return result;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
    if (size == 0) throw std::length_error("Set is empty");
    --size;
}

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& value) const {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos == 0) throw std::length_error("No predecessor found");
    return elements[CircularIndex(pos - 1)];
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    Data result = std::move(elements[CircularIndex(pos)]);
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return result;
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& value) const {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos < size && elements[CircularIndex(pos)] == value) {
        if (pos + 1 >= size) throw std::length_error("No successor found");
        return elements[CircularIndex(pos + 1)];
    }
    if (pos >= size) throw std::length_error("No successor found");
    return elements[CircularIndex(pos)];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos < size && elements[CircularIndex(pos)] == value) {
        pos++;
    }
    if (pos >= size) throw std::length_error("No successor found");
    Data result = std::move(elements[CircularIndex(pos)]);
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return result;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos < size && elements[CircularIndex(pos)] == value) {
        pos++;
    }
    if (pos >= size) throw std::length_error("No successor found");
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
}

/* Specific member functions (DictionaryContainer) */
template <typename Data>
bool SetVec<Data>::Insert(const Data& value) {
    if (size == capacity) Resize(capacity * 2);
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos < size && elements[CircularIndex(pos)] == value) return false; // Duplicate
    if (size == 0) {
        elements[head] = value;
        ++size;
        return true;
    }
    if (pos <= size / 2) {
        // Shift left towards head
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
        elements[CircularIndex(pos)] = value;
    } else {
        // Shift right towards tail
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[CircularIndex(pos)] = value;
    }
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& value) {
    if (size == capacity) Resize(capacity * 2);
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos < size && elements[CircularIndex(pos)] == value) return false; // Duplicate
    if (size == 0) {
        elements[head] = std::move(value);
        ++size;
        return true;
    }
    if (pos <= size / 2) {
        // Shift left towards head
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
        elements[CircularIndex(pos)] = std::move(value);
    } else {
        // Shift right towards tail
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[CircularIndex(pos)] = std::move(value);
    }
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& value) {
    if (size == 0) return false; // Nothing to remove
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    if (pos >= size || elements[CircularIndex(pos)] != value) return false;
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return true;
}

/* Specific member functions (LinearContainer) */
template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return elements[CircularIndex(index)];
}

/* Specific member function (TestableContainer) */
template <typename Data>
bool SetVec<Data>::Exists(const Data& value) const noexcept {
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    return (pos < size && elements[CircularIndex(pos)] == value);
}

/* Specific member function (ClearableContainer) */
template <typename Data>
void SetVec<Data>::Clear() {
    delete[] elements;
    elements = nullptr;
    size = 0;
    capacity = 0;
    head = 0;
    elements = new Data[4](); // Coerente con il costruttore di default
    capacity = 4;
}

/* Auxiliary function for resizing */
template <typename Data>
void SetVec<Data>::Resize(unsigned long newCapacity) {
    if (newCapacity == 0) newCapacity = 4; // Capacità minima
    Data* newElements = new Data[newCapacity]();
    unsigned long newHead = 0;
    for (unsigned long i = 0; i < size; ++i) {
        newElements[newHead + i] = std::move(elements[CircularIndex(i)]);
    }
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
    head = newHead;
}

/* Auxiliary functions */
template <typename Data>
void SetVec<Data>::MakeSpaceAt(unsigned long pos) noexcept {
    if (size == capacity) Resize(capacity * 2);
    if (size == 0) return;
    if (pos <= size / 2) {
        // Shift left towards head
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    } else {
        // Shift right towards tail
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
    }
}

template <typename Data>
void SetVec<Data>::FillGapAt(unsigned long pos) noexcept {
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Clear old head position
        head = (head + 1) % capacity;
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
}

template <typename Data>
Data SetVec<Data>::RemoveAt(unsigned long pos) {
    Data result = std::move(elements[CircularIndex(pos)]);
    FillGapAt(pos);
    --size;
    return result;
}

/* ************************************************************************** */

}
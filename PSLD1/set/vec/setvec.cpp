// namespace lasd {

// /* ************************************************************************** */

// // Funzione ausiliaria per calcolare l'indice circolare
// template <typename Data>
// unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
//     return (head + index) % vec.Size();
// }

// /* ************************************************************************** */

// // Default constructor
// template <typename Data>
// SetVec<Data>::SetVec() {
//     vec.Resize(4); // Capacità iniziale arbitraria
//     size = 0;
//     head = 0;
// }

// // Costruttore da TraversableContainer
// template <typename Data>
// SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec() {
//     container.Traverse([this](const Data& dato) {
//         Insert(dato);
//     });
// }

// // Costruttore da MappableContainer (move)
// template <typename Data>
// SetVec<Data>::SetVec(MappableContainer<Data>& container) : SetVec() {
//     container.Map([this](const Data& val) {
//         Insert(val);
//     });
// }

// // Copy constructor
// template <typename Data>
// SetVec<Data>::SetVec(const SetVec& other) : vec(other.vec), head(other.head) {
//     size = other.size; // Assegno size nel corpo del costruttore
// }

// // Move constructor
// template <typename Data>
// SetVec<Data>::SetVec(SetVec&& other) noexcept {
//     std::swap(vec, other.vec);
//     std::swap(size, other.size);
//     std::swap(head, other.head);
// }

// /* ************************************************************************** */

// // Distruttore
// template <typename Data>
// SetVec<Data>::~SetVec() {
//     Clear();
// }

// /* ************************************************************************** */

// // Copy assignment
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

// // Move assignment
// template <typename Data>
// SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) {
//     if (this != &other) {
//         std::swap(vec, other.vec);
//         std::swap(size, other.size);
//         std::swap(head, other.head);
//     }
//     return *this;
// }

// /* ************************************************************************** */

// // Comparison operators
// template <typename Data>
// bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
//     if (size != other.size) return false;
//     for (unsigned long i = 0; i < size; ++i) {
//         if (!other.Exists(vec[CircularIndex(i)])) return false;
//     }
//     return true;
// }

// template <typename Data>
// bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
//     return !(*this == other);
// }

// /* ************************************************************************** */

// // Specific member functions (inherited from OrderedDictionaryContainer)

// // Min
// template <typename Data>
// const Data& SetVec<Data>::Min() const {
//     if (size == 0) throw std::length_error("Min on empty set");
//     unsigned long minIndex = 0;
//     for (unsigned long i = 1; i < size; ++i) {
//         if (vec[CircularIndex(i)] < vec[CircularIndex(minIndex)]) {
//             minIndex = i;
//         }
//     }
//     return const_cast<Data&>(vec[CircularIndex(minIndex)]);
// }

// // MinNRemove
// template <typename Data>
// Data SetVec<Data>::MinNRemove() {
//     const Data min = Min();
//     Data temp = min;
//     Remove(min);
//     return temp;
// }

// // RemoveMin
// template <typename Data>
// void SetVec<Data>::RemoveMin() {
//     Remove(Min());
// }

// // Max
// template <typename Data>
// const Data& SetVec<Data>::Max() const {
//     if (size == 0) throw std::length_error("Max on empty set");
//     unsigned long maxIndex = 0;
//     for (unsigned long i = 1; i < size; ++i) {
//         if (vec[CircularIndex(i)] > vec[CircularIndex(maxIndex)]) {
//             maxIndex = i;
//         }
//     }
//     return const_cast<Data&>(vec[CircularIndex(maxIndex)]);
// }

// // MaxNRemove
// template <typename Data>
// Data SetVec<Data>::MaxNRemove() {
//     const Data max = Max();
//     Data temp = max;
//     Remove(max);
//     return temp;
// }

// // RemoveMax
// template <typename Data>
// void SetVec<Data>::RemoveMax() {
//     Remove(Max());
// }

// // Predecessor
// template <typename Data>
// const Data& SetVec<Data>::Predecessor(const Data& val) const {
//     auto [found, pos] = BinarySearch(val);
//     if (pos == 0) throw std::length_error("Predecessor not found");
//     return const_cast<Data&>(vec[CircularIndex(pos - 1)]);
// }


// // PredecessorNRemove
// template <typename Data>
// Data SetVec<Data>::PredecessorNRemove(const Data& valore) {
//     const Data& pred = Predecessor(valore);
//     Data temp = pred;
//     Remove(pred);
//     return temp;
// }

// // RemovePredecessor
// template <typename Data>
// void SetVec<Data>::RemovePredecessor(const Data& valore) {
//     Remove(Predecessor(valore));
// }

// // Successor
// template <typename Data>
// const Data& SetVec<Data>::Successor(const Data& val) const {
//     auto [found, pos] = BinarySearch(val);
//     if (pos == size || (found && pos == size - 1)) throw std::length_error("Successor not found");
//     return const_cast<Data&>(vec[CircularIndex(found ? pos + 1 : pos)]);
// }


// // SuccessorNRemove
// template <typename Data>
// Data SetVec<Data>::SuccessorNRemove(const Data& valore) {
//     const Data& succ = Successor(valore);
//     Data temp = succ;
//     Remove(succ);
//     return temp;
// }

// // RemoveSuccessor
// template <typename Data>
// void SetVec<Data>::RemoveSuccessor(const Data& valore) {
//     Remove(Successor(valore));
// }

// /* ************************************************************************** */

// // Specific member functions (inherited from DictionaryContainer)

// // Insert (copy)
// /* ************************************************************************** */
// // Insert (copy)
// template <typename Data>
// bool SetVec<Data>::Insert(const Data& value) {

//   auto [found,pos] = BinarySearch(value);
//   if (found) return false;

//   if (size == vec.Size()) {
//     vec.Resize(vec.Size() * 2);
//   }

//   Unwrap();                                  // 1. srotola

//   /* shift lineare classico */
//   for (unsigned long i = size; i > pos; --i)
//     vec[i] = std::move(vec[i - 1]);

//   vec[pos] = value;
//   ++size;

//   Rewrap();                                  // 3. riavvolgi (opzionale ma utile)

//   return true;
// }


// /* ************************************************************************** */
// // Insert (move)
// template <typename Data>
// bool SetVec<Data>::Insert(Data&& value) {
//   auto [found, pos] = BinarySearch(value);
//   if (found)
//     return false;

//   if (size == vec.Size()) {
//     vec.Resize(vec.Size() * 2);
//   }

//   Unwrap(); // porta head a 0, array lineare

//   // Shift a destra per fare spazio a value
//   for (unsigned long i = size; i > pos; --i)
//     vec[i] = std::move(vec[i - 1]);

//   // Inserimento con move
//   vec[pos] = std::move(value);
//   ++size;

//   Rewrap(); // opzionale: per mantenere bilanciamento e coerenza del buffer

//   return true;
// }




// template <typename Data>
// bool SetVec<Data>::Remove(const Data& value) {

//   auto [found,pos] = BinarySearch(value);
//   if (!found) return false;

//   Unwrap();                                  // 1. srotola

//   /* shift lineare per chiudere il buco */
//   for (unsigned long i = pos + 1; i < size; ++i)
//     vec[i - 1] = std::move(vec[i]);

//   --size;

//   Rewrap();                                  // 3. riavvolgi

//   return true;
// }


// /* ************************************************************************** */

// // Specific member functions (inherited from LinearContainer)

// template <typename Data>
// const Data& SetVec<Data>::operator[](unsigned long i) const {
//     if (i >= size) throw std::out_of_range("Index out of range");
//     return vec[CircularIndex(i)];
// }

// /* ************************************************************************** */

// // Specific member function (inherited from TestableContainer)

// template <typename Data>
// bool SetVec<Data>::Exists(const Data& valore) const noexcept {
//     for (unsigned long i = 0; i < size; ++i) {
//         if (vec[CircularIndex(i)] == valore) return true;
//     }
//     return false;
// }

// /* ************************************************************************** */

// // Specific member function (inherited from ClearableContainer)

// template <typename Data>
// void SetVec<Data>::Clear() {
//     vec.Clear();
//     vec.Resize(4); // Reimposta capacità iniziale
//     size = 0;
//     head = 0;
// }

// /* ************************************************************************** */

// // Specific member function (inherited from ResizableContainer)

// template <typename Data>
// void SetVec<Data>::Resize(unsigned long newSize) {
//     if (newSize == 0) {
//         Clear();
//         return;
//     }
//     if (newSize < size) {
//         size = newSize; // Tronca gli elementi
//     }
//     Vector<Data> newVec(newSize);
//     unsigned long copySize = std::min(size, newSize);
//     for (unsigned long i = 0; i < copySize; ++i) {
//         newVec[i] = std::move(vec[CircularIndex(i)]);
//     }
//     vec = std::move(newVec);
//     head = 0;
//     size = copySize;
// }

// /* ************************************************************************** */
// /* ************************************************************************** */

// // Funzione ausiliaria per ricerca binaria
// template <typename Data>
// std::pair<bool, unsigned long> SetVec<Data>::BinarySearch(const Data& value) const noexcept {
//     if (size == 0) return {false, 0};

//     long left = 0;
//     long right = size - 1;

//     while (left <= right) {
//         long mid = (left + right) / 2;
//         const Data& elem = vec[CircularIndex(mid)];

//         if (elem == value) {
//             return {true, static_cast<unsigned long>(mid)};
//         } else if (elem < value) {
//             left = mid + 1;
//         } else {
//             right = mid - 1;
//         }
//     }

//     return {false, static_cast<unsigned long>(left)};
// }

// template <typename Data>
// void SetVec<Data>::Unwrap() {
//   if (head == 0 || size == 0) return;

//   Vector<Data> tmp(vec.Size());
//   for (unsigned long i = 0; i < size; ++i)
//     tmp[i] = std::move(vec[CircularIndex(i)]);

//   vec  = std::move(tmp);
//   head = 0;
// }

// template <typename Data>
// void SetVec<Data>::Rewrap() {
//   const unsigned long cap = vec.Size();
//   if (size == 0 || cap == 0) { head = 0; return; }

//   unsigned long tailFree = cap - size;
//   unsigned long headFree = head;

//   // Se ci sono più spazi liberi prima della testa che dopo la coda
//   if (headFree > tailFree) {
//     // Sposta solo gli 'tailFree' elementi che stanno dopo la coda logica
//     for (unsigned long i = 0; i < tailFree; ++i) {
//       unsigned long from = (head + size + i) % cap;
//       unsigned long to   = (headFree + i) % cap;
//       vec[to] = std::move(vec[from]);
//     }
//     head = (head + tailFree) % cap;
//   }
//   // Altrimenti non serve fare nulla
// }




// }


namespace lasd {

/* ************************************************************************** */

/* Auxiliary function for circular indexing */
template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
    return (head + index) % vec.Size();
}

/* Binary search to find insertion point (returns absolute index) */
template <typename Data>
unsigned long SetVec<Data>::BinarySearch(const Data& data) const noexcept  {
    if (size == 0) {
        return head;
    }
    unsigned long left = 0;
    unsigned long right = size;
    while (left < right) {
        unsigned long mid = left + (right - left) / 2;
        if (vec[(head + mid) % vec.Size()] < data) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return (head + left) % vec.Size();
}

/* Default constructor */
template <typename Data>
SetVec<Data>::SetVec() {
    vec.Resize(4); // Capacità iniziale arbitraria
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
SetVec<Data>::SetVec(const SetVec& other) : vec(other.vec), head(other.head) {
    size = other.size;
}

/* Move constructor */
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
    std::swap(vec, other.vec);
    std::swap(size, other.size);
    std::swap(head, other.head);
}

/* Destructor */
template <typename Data>
SetVec<Data>::~SetVec() {
    Clear();
}

/* Copy assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
    if (this != &other) {
        Clear();
        vec = other.vec;
        size = other.size;
        head = other.head;
    }
    return *this;
}

/* Move assignment */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) {
    if (this != &other) {
        std::swap(vec, other.vec);
        std::swap(size, other.size);
        std::swap(head, other.head);
    }
    return *this;
}

/* Comparison operators */
template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
    if (size != other.size) return false;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] != other.vec[other.CircularIndex(i)]) return false;
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
    return vec[head];
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
    if (size == 0) throw std::length_error("Set is empty");
    Data result = std::move(vec[head]);
    head = (head + 1) % vec.Size();
    --size;
    return result;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
    if (size == 0) throw std::length_error("Set is empty");
    head = (head + 1) % vec.Size();
    --size;
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
    if (size == 0) throw std::length_error("Set is empty");
    return vec[CircularIndex(size - 1)];
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    if (size == 0) throw std::length_error("Set is empty");
    Data result = std::move(vec[CircularIndex(size - 1)]);
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
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

    if (pos == 0)
        throw std::length_error("No predecessor found");

    return vec[CircularIndex(pos - 1)];
}


template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    Data result = std::move(vec[CircularIndex(pos)]);
    for (unsigned long i = pos; i < size - 1; ++i) {
        vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
    }
    --size;
    return result;
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    for (unsigned long i = pos; i < size - 1; ++i) {
        vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
    }
    --size;
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& value) const {
    if (size == 0) throw std::length_error("Set is empty");

    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

    // Se il valore è uguale a quello trovato, il successore è il successivo
    if (pos < size && vec[CircularIndex(pos)] == value) {
        if (pos + 1 >= size)
            throw std::length_error("No successor found");
        return vec[CircularIndex(pos + 1)];
    }

    // Altrimenti il successore è il valore trovato in BinarySearch
    if (pos >= size)
        throw std::length_error("No successor found");
    return vec[CircularIndex(pos)];
}


template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");

    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

    // Se il valore è presente, il successore è l'elemento successivo
    if (pos < size && vec[CircularIndex(pos)] == value) {
        pos++;
    }

    // Verifica se esiste un successore
    if (pos >= size) throw std::length_error("No successor found");

    // Rimuovi il successore
    Data result = std::move(vec[CircularIndex(pos)]);

    // Shift efficiente
    if (pos <= size / 2) {
        // Shift verso destra (verso head)
        for (unsigned long i = pos; i > 0; --i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        }
        vec[head] = Data{}; // Pulisce la vecchia posizione di head
        head = (head + 1) % vec.Size();
    } else {
        // Shift verso sinistra (verso tail)
        for (unsigned long i = pos; i < size - 1; ++i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        }
    }

    --size;

    // Ridimensiona se necessario
    if (size < vec.Size() / 4 && vec.Size() > 10) {
        Resize(vec.Size() / 2);
    }

    return result;
}

/* RemoveSuccessor */
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
    if (size == 0) throw std::length_error("Set is empty");

    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();

    // Se il valore è presente, il successore è l'elemento successivo
    if (pos < size && vec[CircularIndex(pos)] == value) {
        pos++;
    }

    // Verifica se esiste un successore
    if (pos >= size) throw std::length_error("No successor found");

    // Shift efficiente
    if (pos <= size / 2) {
        // Shift verso destra (verso head)
        for (unsigned long i = pos; i > 0; --i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        }
        vec[head] = Data{}; // Pulisce la vecchia posizione di head
        head = (head + 1) % vec.Size();
    } else {
        // Shift verso sinistra (verso tail)
        for (unsigned long i = pos; i < size - 1; ++i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        }
    }

    --size;

    // Ridimensiona se necessario
    if (size < vec.Size() / 4 && vec.Size() > 10) {
        Resize(vec.Size() / 2);
    }
}


/* Specific member functions (DictionaryContainer) */
template <typename Data>
bool SetVec<Data>::Insert(const Data& value) {
    if (size == vec.Size()) Resize(vec.Size() * 2);
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
    if (pos > 0 && vec[CircularIndex(pos - 1)] == value) return false; // Duplicate

    if (size == 0) {
        vec[head] = value;
        ++size;
        return true;
    }

    if (pos <= size / 2) {
        // Shift left towards head
        head = (head == 0) ? vec.Size() - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        }
        vec[CircularIndex(pos)] = value;
    } else {
        // Shift right towards tail
        for (unsigned long i = size; i > pos; --i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        }
        vec[CircularIndex(pos)] = value;
    }
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& value) {
    if (size == vec.Size()) Resize(vec.Size() * 2);
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
    if (pos > 0 && vec[CircularIndex(pos - 1)] == value) return false; // Duplicate

    if (size == 0) {
        vec[head] = std::move(value);
        ++size;
        return true;
    }

    if (pos <= size / 2) {
        // Shift left towards head
        head = (head == 0) ? vec.Size() - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        }
        vec[CircularIndex(pos)] = std::move(value);
    } else {
        // Shift right towards tail
        for (unsigned long i = size; i > pos; --i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        }
        vec[CircularIndex(pos)] = std::move(value);
    }
    ++size;
    return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& value) {
    if (size == 0) return false; // Nothing to remove

    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size(); // Correct calculation

    // Check if the value is at the position
    if (vec[CircularIndex(pos)] != value) return false;

    // Shift elements depending on the position
    if (pos <= size / 2) {
        // Shift right towards head
        for (unsigned long i = pos; i > 0; --i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        }
        vec[head] = Data{}; // Clear old head position
        head = (head + 1) % vec.Size(); // Update head
    } else {
        // Shift left towards tail
        for (unsigned long i = pos; i < size - 1; ++i) {
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        }
    }
    --size;

    // Shrink the vector if necessary
    if (size < vec.Size() / 4 && vec.Size() > 10) Resize(vec.Size() / 2);

    return true;
}


/* Specific member functions (LinearContainer) */
template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
    if (index >= size) throw std::out_of_range("Index out of range");
    return vec[CircularIndex(index)];
}

/* Specific member function (TestableContainer) */
template <typename Data>
bool SetVec<Data>::Exists(const Data& value) const noexcept {
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + vec.Size()) % vec.Size();
    return (pos < size && vec[CircularIndex(pos)] == value);
}

/* Specific member function (ClearableContainer) */
template <typename Data>
void SetVec<Data>::Clear() {
    vec.Clear();
    size = 0;
    head = 0;
    vec.Resize(4); // Coerente con il costruttore di default
}

/* Auxiliary function for resizing */
template <typename Data>
void SetVec<Data>::Resize(unsigned long newSize) {
    Vector<Data> newVec(newSize);
    unsigned long newHead = 0;
    for (unsigned long i = 0; i < size; ++i) {
        newVec[newHead + i] = std::move(vec[CircularIndex(i)]);
    }
    vec = std::move(newVec);
    head = newHead;
}

/* ************************************************************************** */

}
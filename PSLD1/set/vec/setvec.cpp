namespace lasd {

/* ************************************************************************** */

// Funzione ausiliaria per calcolare l'indice circolare
template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
    return (head + index) % vec.Size();
}

/* ************************************************************************** */

// Default constructor
template <typename Data>
SetVec<Data>::SetVec() {
    vec.Resize(4); // Capacità iniziale arbitraria
    size = 0;
    head = 0;
}

// Costruttore da TraversableContainer
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec() {
    container.Traverse([this](const Data& dato) {
        Insert(dato);
    });
}

// Costruttore da MappableContainer (move)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>& container) : SetVec() {
    container.Map([this](const Data& val) {
        Insert(val);
    });
}

// Copy constructor
template <typename Data>
SetVec<Data>::SetVec(const SetVec& other) : vec(other.vec), head(other.head) {
    size = other.size; // Assegno size nel corpo del costruttore
}

// Move constructor
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
    std::swap(vec, other.vec);
    std::swap(size, other.size);
    std::swap(head, other.head);
}

/* ************************************************************************** */

// Distruttore
template <typename Data>
SetVec<Data>::~SetVec() {
    Clear();
}

/* ************************************************************************** */

// Copy assignment
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

// Move assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) {
    if (this != &other) {
        std::swap(vec, other.vec);
        std::swap(size, other.size);
        std::swap(head, other.head);
    }
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
    if (size != other.size) return false;
    for (unsigned long i = 0; i < size; ++i) {
        if (!other.Exists(vec[CircularIndex(i)])) return false;
    }
    return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (inherited from OrderedDictionaryContainer)

// Min
template <typename Data>
Data& SetVec<Data>::Min() const {
    if (size == 0) throw std::length_error("Min on empty set");
    unsigned long minIndex = 0;
    for (unsigned long i = 1; i < size; ++i) {
        if (vec[CircularIndex(i)] < vec[CircularIndex(minIndex)]) {
            minIndex = i;
        }
    }
    return const_cast<Data&>(vec[CircularIndex(minIndex)]);
}

// MinNRemove
template <typename Data>
Data SetVec<Data>::MinNRemove() {
    Data min = Min();
    Data temp = min;
    Remove(min);
    return temp;
}

// RemoveMin
template <typename Data>
void SetVec<Data>::RemoveMin() {
    Remove(Min());
}

// Max
template <typename Data>
Data& SetVec<Data>::Max() const {
    if (size == 0) throw std::length_error("Max on empty set");
    unsigned long maxIndex = 0;
    for (unsigned long i = 1; i < size; ++i) {
        if (vec[CircularIndex(i)] > vec[CircularIndex(maxIndex)]) {
            maxIndex = i;
        }
    }
    return const_cast<Data&>(vec[CircularIndex(maxIndex)]);
}

// MaxNRemove
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    Data max = Max();
    Data temp = max;
    Remove(max);
    return temp;
}

// RemoveMax
template <typename Data>
void SetVec<Data>::RemoveMax() {
    Remove(Max());
}

// Predecessor
template <typename Data>
Data& SetVec<Data>::Predecessor(const Data& val) const {
    const Data* pred = nullptr;
    unsigned long predIndex = 0;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] < val && (!pred || vec[CircularIndex(i)] > *pred)) {
            pred = &vec[CircularIndex(i)];
            predIndex = i;
        }
    }
    if (!pred) throw std::length_error("Predecessor not found");
    return const_cast<Data&>(vec[CircularIndex(predIndex)]);
}

// PredecessorNRemove
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& valore) {
    Data& pred = Predecessor(valore);
    Data temp = pred;
    Remove(pred);
    return temp;
}

// RemovePredecessor
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& valore) {
    Remove(Predecessor(valore));
}

// Successor
template <typename Data>
Data& SetVec<Data>::Successor(const Data& val) const {
    const Data* succ = nullptr;
    unsigned long succIndex = 0;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] > val && (!succ || vec[CircularIndex(i)] < *succ)) {
            succ = &vec[CircularIndex(i)];
            succIndex = i;
        }
    }
    if (!succ) throw std::length_error("Successor not found");
    return const_cast<Data&>(vec[CircularIndex(succIndex)]);
}

// SuccessorNRemove
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& valore) {
    Data& succ = Successor(valore);
    Data temp = succ;
    Remove(succ);
    return temp;
}

// RemoveSuccessor
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& valore) {
    Remove(Successor(valore));
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

// Insert (copy)
template <typename Data>
bool SetVec<Data>::Insert(const Data& valore) {
    if (Exists(valore)) return false;

    // Ridimensiona se necessario
    if (size == vec.Size()) {
        Vector<Data> newVec(vec.Size() * 2);
        for (unsigned long i = 0; i < size; ++i) {
            newVec[i] = std::move(vec[CircularIndex(i)]);
        }
        vec = std::move(newVec);
        head = 0;
    }

    // Trova la posizione per l'inserimento ordinato
    unsigned long insertPos = size;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] > valore) {
            insertPos = i;
            break;
        }
    }

    // Sposta gli elementi a destra
    for (unsigned long i = size; i > insertPos; --i) {
        vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
    }

    // Inserisci il nuovo elemento
    vec[CircularIndex(insertPos)] = valore;
    ++size;
    return true;
}

// Insert (move)
template <typename Data>
bool SetVec<Data>::Insert(Data&& valore) {
    if (Exists(valore)) return false;

    if (size == vec.Size()) {
        Vector<Data> newVec(vec.Size() * 2);
        for (unsigned long i = 0; i < size; ++i) {
            newVec[i] = std::move(vec[CircularIndex(i)]);
        }
        vec = std::move(newVec);
        head = 0;
    }

    unsigned long insertPos = size;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] > valore) {
            insertPos = i;
            break;
        }
    }

    for (unsigned long i = size; i > insertPos; --i) {
        vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
    }

    vec[CircularIndex(insertPos)] = std::move(valore);
    ++size;
    return true;
}

// Remove
template <typename Data>
bool SetVec<Data>::Remove(const Data& valore) {
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] == valore) {
            // Sposta gli elementi a sinistra
            for (unsigned long j = i; j < size - 1; ++j) {
                vec[CircularIndex(j)] = std::move(vec[CircularIndex(j + 1)]);
            }
            --size;
            // Normalizza head
            head = CircularIndex(0);
            return true;
        }
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long i) const {
    if (i >= size) throw std::out_of_range("Index out of range");
    return vec[CircularIndex(i)];
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)

template <typename Data>
bool SetVec<Data>::Exists(const Data& valore) const noexcept {
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] == valore) return true;
    }
    return false;
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

template <typename Data>
void SetVec<Data>::Clear() {
    vec.Clear();
    vec.Resize(4); // Reimposta capacità iniziale
    size = 0;
    head = 0;
}

/* ************************************************************************** */

// Specific member function (inherited from ResizableContainer)

template <typename Data>
void SetVec<Data>::Resize(unsigned long newSize) {
    if (newSize == 0) {
        Clear();
        return;
    }
    if (newSize < size) {
        size = newSize; // Tronca gli elementi
    }
    Vector<Data> newVec(newSize);
    unsigned long copySize = std::min(size, newSize);
    for (unsigned long i = 0; i < copySize; ++i) {
        newVec[i] = std::move(vec[CircularIndex(i)]);
    }
    vec = std::move(newVec);
    head = 0;
    size = copySize;
}

/* ************************************************************************** */

}
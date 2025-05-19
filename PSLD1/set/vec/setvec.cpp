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
template<typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0)
    throw std::length_error("Min on empty set");
  // perché il vettore è sempre ordinato
  return const_cast<Data&>(vec[CircularIndex(0)]);
}



// MinNRemove
template <typename Data>
Data SetVec<Data>::MinNRemove() {
    const Data min = Min();
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
template<typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0)
    throw std::length_error("Max on empty set");
  // ultimo elemento logico
  return const_cast<Data&>(vec[CircularIndex(size - 1)]);
}


// MaxNRemove
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    const Data max = Max();
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
template<typename Data>
const Data& SetVec<Data>::Predecessor(const Data& val) const {
  if (size == 0)
    throw std::length_error("Predecessor on empty set");

  auto [found, pos] = BinarySearch(val);
  // se l’hai trovato in pos == 0, non ha predecessore
  // se non l’hai trovato, pos è il punto d’inserimento: il predecessore è in pos-1,
  // ma se pos==0 allora non c’è
  if (pos == 0)
    throw std::length_error("Predecessor not found");

  return const_cast<Data&>( vec[CircularIndex(pos - 1)] );
}


// PredecessorNRemove
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& valore) {
    const Data& pred = Predecessor(valore);
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
template<typename Data>
const Data& SetVec<Data>::Successor(const Data& val) const {
  if (size == 0)
    throw std::length_error("Successor on empty set");

  auto [found, pos] = BinarySearch(val);
  // se trovato, il successore è in pos+1; altrimenti è in pos
  unsigned long succPos = found ? pos + 1 : pos;
  if (succPos >= size)
    throw std::length_error("Successor not found");

  return const_cast<Data&>( vec[CircularIndex(succPos)] );
}

// SuccessorNRemove
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& valore) {
    const Data& succ = Successor(valore);
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

template <typename Data>
bool SetVec<Data>::Insert(const Data& valore) {
  if (Exists(valore)) return false;

  // Ridimensiona se necessario (come prima)…
  if (size == vec.Size()) {
    Vector<Data> newVec(vec.Size() * 2);
    for (unsigned long i = 0; i < size; ++i)
      newVec[i] = std::move(vec[CircularIndex(i)]);
    vec = std::move(newVec);
    head = 0;
  }

  // Trova la posizione ordinata di inserimento
  unsigned long pos = size;
  for (unsigned long i = 0; i < size; ++i)
    if (vec[CircularIndex(i)] > valore) { pos = i; break; }

  // Calcola quanti elementi spostare a sinistra o a destra
  unsigned long distLeft  = pos;           // quante posizioni prima di pos
  unsigned long distRight = size - pos;    // quante dopo

  if (distRight <= distLeft) {
    // SHIFT A DESTRA come prima, ma senza toccare head
    for (unsigned long i = size; i > pos; --i)
      vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
    vec[CircularIndex(pos)] = valore;
  }
  else {
    // SHIFT A SINISTRA: sposto head indietro di 1 e incollo tutti tra 0 e pos-1
    head = (head + vec.Size() - 1) % vec.Size();
    for (unsigned long i = 0; i < pos; ++i)
      vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
    vec[CircularIndex(pos)] = valore;
  }

  ++size;
  return true;
}


template <typename Data>
bool SetVec<Data>::Insert(Data&& valore) {
    if (Exists(valore)) return false;

    // Ridimensiona se necessario
    if (size == vec.Size()) {
        Vector<Data> newVec(vec.Size() * 2);
        for (unsigned long i = 0; i < size; ++i)
            newVec[i] = std::move(vec[CircularIndex(i)]);
        vec = std::move(newVec);
        head = 0;
    }

    // Trova la posizione ordinata di inserimento
    unsigned long pos = size;
    for (unsigned long i = 0; i < size; ++i) {
        if (vec[CircularIndex(i)] > valore) { pos = i; break; }
    }

    // Calcola spostamenti
    unsigned long distLeft  = pos;
    unsigned long distRight = size - pos;

    if (distRight <= distLeft) {
        // sposto a destra
        for (unsigned long i = size; i > pos; --i)
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i - 1)]);
        vec[CircularIndex(pos)] = std::move(valore);
    }
    else {
        // sposto a sinistra ruotando head
        head = (head + vec.Size() - 1) % vec.Size();
        for (unsigned long i = 0; i < pos; ++i)
            vec[CircularIndex(i)] = std::move(vec[CircularIndex(i + 1)]);
        vec[CircularIndex(pos)] = std::move(valore);
    }

    ++size;
    return true;
}




template <typename Data>
bool SetVec<Data>::Remove(const Data& valore) {
  // Trova l’indice logico i
  unsigned long i;
  for (i = 0; i < size; ++i)
    if (vec[CircularIndex(i)] == valore)
      break;
  if (i == size) return false;

  unsigned long distLeft  = i;           // spostare a sinistra di i
  unsigned long distRight = size - 1 - i; // spostare a destra di (size-1-i)

  if (distRight <= distLeft) {
    // SHIFT A SINISTRA verso la posizione i
    for (unsigned long j = i; j < size - 1; ++j)
      vec[CircularIndex(j)] = std::move(vec[CircularIndex(j + 1)]);
    // head non cambia
  }
  else {
    // SHIFT A DESTRA: sposto head in avanti di 1, e copro il vuoto
    head = (head + 1) % vec.Size();
    for (long j = i; j > 0; --j)
      vec[CircularIndex(j)] = std::move(vec[CircularIndex(j - 1)]);
  }

  --size;
  // Normalizza head in modo che il primo elemento logico sia a index 0
  head = CircularIndex(0);
  return true;
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
    auto [found, pos] = BinarySearch(valore);
    return found;
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

template <typename Data>
std::pair<bool, unsigned long> SetVec<Data>::BinarySearch(const Data& valore) const noexcept{
    if (size == 0) return {false, 0};

    long left = 0;
    long right = static_cast<long>(size) - 1;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        const Data& midVal = vec[CircularIndex(mid)];

        if (midVal == valore) {
            return {true, static_cast<unsigned long>(mid)};
        }
        else if (midVal < valore) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    // Non trovato: left è la posizione dove si dovrebbe inserire
    return {false, static_cast<unsigned long>(left)};
}



}

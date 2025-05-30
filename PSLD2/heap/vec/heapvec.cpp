
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : SortableVector<Data>(container) {
    Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : SortableVector<Data>(std::move(container)) {
    Heapify();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& heap) : SortableVector<Data>(heap) {}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& heap) noexcept : SortableVector<Data>(std::move(heap)) {}

/* ************************************************************************ */

// // Destructor
// template <typename Data>
// HeapVec<Data>::~HeapVec() {
//     // Il distruttore di Vector<Data> viene chiamato automaticamente
// }

/* ************************************************************************ */

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heap) {
    SortableVector<Data>::operator=(heap);
    return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heap)  {
    SortableVector<Data>::operator=(std::move(heap));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& heap) const noexcept {
    return SortableVector<Data>::operator==(heap);
    
}

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& heap) const noexcept {
    return !(*this == heap);
}

/* ************************************************************************ */

// Specific member functions (inherited from Heap)

template <typename Data>
bool HeapVec<Data>::IsHeap() const {
    if (size == 0) return true;  // Un heap vuoto è valido
    return IsHeapRecursive(0);
}

template <typename Data>
bool HeapVec<Data>::IsHeapRecursive(unsigned long  index) const {
    if (index >= size) return true;
    
    unsigned long  left = 2 * index + 1;
    unsigned long  right = 2 * index + 2;
    
    // Verifica che il nodo sia >= dei suoi figli
    if (left < size && this->elements[index] < this->elements[left]) return false;
    if (right < size && this->elements[index] < this->elements[right]) return false;
    
    // Verifica ricorsivamente i sottoalberi
    return IsHeapRecursive(left) && IsHeapRecursive(right);
}
template <typename Data>
void HeapVec<Data>::Heapify() {
    // Partiamo dal penultimo livello (primo nodo non foglia)
    for (long i = static_cast<long>(size / 2) - 1; i >= 0; --i) {
        HeapDown(static_cast<unsigned long >(i));
    }
}



/* ************************************************************************ */

// Specific member function (inherited from SortableLinearContainer)

// template <typename Data>
// void HeapVec<Data>::Sort() noexcept {
//     // HeapSort: prima costruiamo l'heap, poi estraiamo gli elementi in ordine
//     Heapify();
    
//     // Salviamo la dimensione originale
//     unsigned long  originalSize = size;
    
//     for (unsigned long  i = size - 1; i > 0; --i) {
//         std::swap(this->elements[0], this->elements[i]);
//         size--; // Riduciamo temporaneamente la dimensione per escludere l'elemento massimo
//         HeapDown(0);
//     }
    
//     // Ripristiniamo la dimensione originale
//     size = originalSize;
    
//     // NON riformiamo l'heap alla fine dell'ordinamento
//     // Rimuovi la chiamata a Heapify() qui
// }

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    if (size == 0) {
        return; // Nessuna operazione necessaria per un heap vuoto
    }

    Heapify();
    
    unsigned long originalSize = size;
    
    for (unsigned long i = size - 1; i > 0; --i) {
        std::swap(this->elements[0], this->elements[i]);
        size--;
        HeapDown(0);
    }
    
    size = originalSize;
}

/* ************************************************************************ */

// Auxiliary protected functions

template <typename Data>
void HeapVec<Data>::HeapDown(unsigned long  index) {
    unsigned long  largest = index;
    unsigned long  left = 2 * index + 1;
    unsigned long  right = 2 * index + 2;

    // Confronto con il figlio sinistro
    if (left < size && this->elements[left] > this->elements[largest]) 
    {
        largest = left;
    }
    // Confronto con il figlio destro
    if (right < size && this->elements[right] > this->elements[largest])
    {
        largest = right;
    }
    // Se necessario, scambia e continua a scendere
    if (largest != index) 
    {
        std::swap(this->elements[index], this->elements[largest]);
        HeapDown(largest);
    }
}

/* ************************************************************************** */

}



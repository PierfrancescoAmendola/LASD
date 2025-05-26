
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : Vector<Data>(container) {
    Heapify();
}

template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {
    Heapify();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& heap) : Vector<Data>(heap) {}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& heap) noexcept : Vector<Data>(std::move(heap)) {}

/* ************************************************************************ */

// Destructor
template <typename Data>
HeapVec<Data>::~HeapVec() {
    // Il distruttore di Vector<Data> viene chiamato automaticamente
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heap) {
    Vector<Data>::operator=(heap);
    return *this;
}

// Move assignment
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heap)  {
    Vector<Data>::operator=(std::move(heap));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& heap) const noexcept {
    if (size != heap.size) return false;
    
    // Confronto elemento per elemento
    for (ulong i = 0; i < size; ++i) {
        if (elements[i] != heap.elements[i]) {
            return false;
        }
    }
    return true;
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
bool HeapVec<Data>::IsHeapRecursive(ulong index) const {
    if (index >= size) return true;
    
    ulong left = 2 * index + 1;
    ulong right = 2 * index + 2;
    
    // Verifica che il nodo sia >= dei suoi figli
    if (left < size && elements[index] < elements[left]) return false;
    if (right < size && elements[index] < elements[right]) return false;
    
    // Verifica ricorsivamente i sottoalberi
    return IsHeapRecursive(left) && IsHeapRecursive(right);
}
template <typename Data>
void HeapVec<Data>::Heapify() {
    // Partiamo dal penultimo livello (primo nodo non foglia)
    for (long i = static_cast<long>(size / 2) - 1; i >= 0; --i) {
        HeapDown(static_cast<ulong>(i));
    }
}

/* ************************************************************************ */

// Specific member function (inherited from SortableLinearContainer)

template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    // HeapSort: prima costruiamo l'heap, poi estraiamo gli elementi in ordine
    Heapify();
    
    // Salviamo la dimensione originale
    ulong originalSize = size;
    
    for (ulong i = size - 1; i > 0; --i) {
        std::swap(elements[0], elements[i]);
        size--; // Riduciamo temporaneamente la dimensione per escludere l'elemento massimo
        HeapDown(0);
    }
    
    // Ripristiniamo la dimensione originale
    size = originalSize;
    
    // NON riformiamo l'heap alla fine dell'ordinamento
    // Rimuovi la chiamata a Heapify() qui
}

/* ************************************************************************ */

// Auxiliary protected functions

template <typename Data>
void HeapVec<Data>::HeapDown(ulong index) {
    ulong largest = index;
    ulong left = 2 * index + 1;
    ulong right = 2 * index + 2;

    // Confronto con il figlio sinistro
    if (left < size && elements[left] > elements[largest]) {
        largest = left;
    }

    // Confronto con il figlio destro
    if (right < size && elements[right] > elements[largest]) {
        largest = right;
    }

    // Se necessario, scambia e continua a scendere
    if (largest != index) {
        std::swap(elements[index], elements[largest]);
        HeapDown(largest);
    }
}

/* ************************************************************************** */

}

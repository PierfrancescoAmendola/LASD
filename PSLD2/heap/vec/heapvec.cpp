//  heapvec.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//

namespace lasd 
{

/* ************************************************************************** */

// Specific constructors
// Costruttore che inizializza l'heap da un contenitore traversabile, costruendo prima il vettore e poi l'heap
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data>& container) : SortableVector<Data>(container) {
    Heapify(); // Trasforma il vettore in un heap
}

// Costruttore che inizializza l'heap da un contenitore mappabile, spostando i dati e poi costruendo l'heap
template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data>&& container) : SortableVector<Data>(std::move(container)) {
    Heapify(); // Trasforma il vettore in un heap
}

/* ************************************************************************ */

// Copy constructor
// Costruttore di copia: crea un nuovo heap copiando i dati da un altro heap
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data>& heap) : SortableVector<Data>(heap) {}

// Move constructor
// Costruttore di spostamento: trasferisce i dati da un heap esistente a un nuovo heap
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data>&& heap) noexcept : SortableVector<Data>(std::move(heap)) {}

/* ************************************************************************ */

// // Destructor
// // Distruttore: non è necessario implementarlo esplicitamente, il distruttore di Vector<Data> gestisce tutto
// template <typename Data>
// HeapVec<Data>::~HeapVec() {
//     // Il distruttore di Vector<Data> viene chiamato automaticamente
// }

/* ************************************************************************ */

// Copy assignment
// Operatore di assegnazione per copia: copia i dati da un altro heap e restituisce il riferimento a questo
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec<Data>& heap) {
    SortableVector<Data>::operator=(heap);
    return *this;
}

// Move assignment
// Operatore di assegnazione per spostamento: trasferisce i dati da un altro heap e restituisce il riferimento a questo
template <typename Data>
HeapVec<Data>& HeapVec<Data>::operator=(HeapVec<Data>&& heap) {
    SortableVector<Data>::operator=(std::move(heap));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
// Operatore di uguaglianza: confronta due heap per verificare se sono identici
template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data>& heap) const noexcept {
    return SortableVector<Data>::operator==(heap);
}

// Operatore di disuguaglianza: verifica se due heap sono diversi
template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data>& heap) const noexcept {
    return !(*this == heap);
}

/* ************************************************************************ */

// Specific member functions (inherited from Heap)
// Verifica se la struttura è un heap valido: restituisce true se vuota o se rispetta la proprietà dell'heap
template <typename Data>
bool HeapVec<Data>::IsHeap() const {
    if (size == 0) return true;  // Un heap vuoto è valido
    return IsHeapRecursive(0);   // Controlla ricorsivamente la proprietà dell'heap
}

// Funzione ricorsiva ausiliaria per verificare la proprietà dell'heap a partire da un indice
template <typename Data>
bool HeapVec<Data>::IsHeapRecursive(unsigned long index) const {
    if (index >= size) return true; // Base: indice oltre la dimensione, valido
    
    unsigned long left = 2 * index + 1;  // Indice del figlio sinistro
    unsigned long right = 2 * index + 2; // Indice del figlio destro
    
    // Verifica che il nodo sia >= dei suoi figli
    if (left < size && this->elements[index] < this->elements[left]) return false;
    if (right < size && this->elements[index] < this->elements[right]) return false;
    
    // Verifica ricorsivamente i sottoalberi sinistro e destro
    return IsHeapRecursive(left) && IsHeapRecursive(right);
}

// Trasforma il vettore in un heap, partendo dai nodi non foglia e applicando HeapDown
template <typename Data>
void HeapVec<Data>::Heapify() {
    // Partiamo dal penultimo livello (primo nodo non foglia)
    for (long i = static_cast<long>(size / 2) - 1; i >= 0; --i) {
        HeapDown(static_cast<unsigned long>(i)); // Ripristina la proprietà dell'heap verso il basso
    }
}

/* ************************************************************************ */

// Specific member function (inherited from SortableLinearContainer)
// Ordina gli elementi usando l'algoritmo HeapSort: costruisce l'heap, poi estrae gli elementi in ordine
template <typename Data>
void HeapVec<Data>::Sort() noexcept {
    if (size == 0) {
        return; // Nessuna operazione necessaria per un heap vuoto
    }

    Heapify(); // Costruisce l'heap
    
    unsigned long originalSize = size; // Salva la dimensione originale
    
    for (unsigned long i = size - 1; i > 0; --i) {
        std::swap(this->elements[0], this->elements[i]); // Scambia la radice (massimo) con l'ultimo elemento
        size--; // Riduce temporaneamente la dimensione per escludere l'elemento massimo
        HeapDown(0); // Ripristina la proprietà dell'heap verso il basso
    }
    
    size = originalSize; // Ripristina la dimensione originale
}

/* ************************************************************************ */

// Auxiliary protected functions
// Ripristina la proprietà dell'heap spostando un elemento verso il basso, confrontandolo con i figli
template <typename Data>
void HeapVec<Data>::HeapDown(unsigned long index) {
    unsigned long largest = index; // Assume che il nodo corrente sia il più grande
    unsigned long left = 2 * index + 1; // Indice del figlio sinistro
    unsigned long right = 2 * index + 2; // Indice del figlio destro

    // Confronto con il figlio sinistro
    if (left < size && this->elements[left] > this->elements[largest]) 
    {
        largest = left; // Aggiorna il più grande se il figlio sinistro è maggiore
    }
    // Confronto con il figlio destro
    if (right < size && this->elements[right] > this->elements[largest])
    {
        largest = right; // Aggiorna il più grande se il figlio destro è maggiore
    }
    // Se necessario, scambia e continua a scendere
    if (largest != index) 
    {
        std::swap(this->elements[index], this->elements[largest]); // Scambia con il figlio più grande
        HeapDown(largest); // Continua ricorsivamente verso il basso
    }
}

/* ************************************************************************** */

}

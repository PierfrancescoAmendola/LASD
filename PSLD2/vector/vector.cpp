//
//  vector.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 02/05/25.
//

namespace lasd {

/* ************************************************************************** */
// Private Helper Functions (Vector)

template <typename Data>
void Vector<Data>::AllocateMemory(unsigned long newSize) {
    // Alloca dinamicamente memoria per il vettore con dimensione newSize.
    // Se newSize è 0, il puntatore viene impostato a nullptr.
    size = newSize;
    if (size > 0) {
        elements = new Data[size]{};
    } else {
        elements = nullptr;
    }
}

template <typename Data>
void Vector<Data>::CopyElements(Data* dest, const Data* src, unsigned long count) {
    // Copia i primi 'count' elementi da src a dest.
    for (unsigned long i = 0; i < count; ++i) {
        dest[i] = src[i];
    }
}

template <typename Data>
void Vector<Data>::ThrowIfEmpty() const {
    // Lancia un'eccezione se il vettore è vuoto.
    if (size == 0) {
        throw std::length_error("Accesso a vettore vuoto");
    }
}

/* ************************************************************************** */
// Constructors (Vector)

template <typename Data>
Vector<Data>::Vector(const unsigned long newSize) {
    // Costruttore che crea un vettore con 'newSize' elementi inizializzati di default.
    AllocateMemory(newSize);
}

// Costruttore da container traversabile (copia)
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container) {
    // Costruttore che inizializza il vettore copiando tutti gli elementi da un container traversabile.
    AllocateMemory(container.Size());
    unsigned long i = 0;
    container.Traverse(
        [this, &i](const Data& dato) {
            elements[i++] = dato;
        }
    );
}

// Costruttore da container mappabile (move)
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container) {
    // Costruttore che inizializza il vettore spostando gli elementi da un container mappabile.
    AllocateMemory(container.Size());
    unsigned long posizione = 0;
    container.Map(
        [this, &posizione](Data& dato) {
            elements[posizione++] = std::move(dato);
        }
    );
}

/* ************************************************************************** */

// Copy Constructor (Vector)
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vettore) {
    // Costruttore di copia: crea una copia profonda del vettore passato.
    AllocateMemory(vettore.size);
    if (size > 0) {
        CopyElements(elements, vettore.elements, size);
    }
}

// Move Constructor (Vector)
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vettore) noexcept {
    // Costruttore di move: trasferisce la proprietà delle risorse senza copiare gli elementi.
    size = vettore.size;
    elements = vettore.elements;
    vettore.size = 0;
    vettore.elements = nullptr;
}

// Destructor (Vector)
template<typename Data>
Vector<Data>::~Vector() {
    // Distruttore: dealloca la memoria del vettore.
    delete[] elements;
}

// Copy Assignment (Vector)
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vettore) {
    // Operatore di assegnazione per copia: usa l'idioma copy-and-swap per garantire sicurezza.
    if (this != &vettore) {
        Vector<Data> tmpVettore(vettore);
        std::swap(size, tmpVettore.size);
        std::swap(elements, tmpVettore.elements);
    }
    return *this;
}

// Move Assignment (Vector)
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
    // Operatore di assegnazione per move: scambia le risorse con il vettore passato.
    std::swap(size, vec.size);
    std::swap(elements, vec.elements);
    return *this;
}

/* ************************************************************************** */

// Comparison Operators (Vector)
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& uguale) const noexcept {
    // Operatore di uguaglianza: confronta due vettori elemento per elemento.
    if (size != uguale.size) return false;
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] != uguale.elements[i]) return false;
    }
    return true;
}

template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& diverso) const noexcept {
    // Operatore di disuguaglianza: definito come negazione di ==
    return !(*this == diverso);
}

// Specific Member Functions (Vector) (inherited from MutableLinearContainer)
template <typename Data>
Data& Vector<Data>::operator[](const unsigned long i) {
    // Accesso in scrittura all’i-esimo elemento.
    // Usa cast per riutilizzare l’implementazione const.
    return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->operator[](i));
}

template<typename Data>
Data& Vector<Data>::Front() {
    // Ritorna il primo elemento del vettore (in scrittura).
    ThrowIfEmpty();
    return elements[0];
}

template<typename Data>
Data& Vector<Data>::Back() {
    // Ritorna l'ultimo elemento del vettore (in scrittura).
    ThrowIfEmpty();
    return elements[size - 1];
}

// Specific Member Function (Vector) (inherited from ClearableContainer)
template <typename Data>
void Vector<Data>::Clear() noexcept {
    // Rimuove tutti gli elementi del vettore e libera la memoria.
    if (elements != nullptr) {
        delete[] elements;
        elements = nullptr;
    }
    size = 0;
}

// Specific Member Function (Vector) (inherited from ResizableContainer)
template<typename Data>
void Vector<Data>::Resize(const unsigned long newSize) {
    // Ridimensiona il vettore alla nuova dimensione specificata.
    // Mantiene gli elementi esistenti se possibile.
    if (newSize == 0) return Clear();
    if (newSize == size) return;

    Data* newElements = new Data[newSize]{};
    const unsigned long copySize = std::min(size, newSize);
    for (unsigned long i = 0; i < copySize; ++i) {
        newElements[i] = std::move(elements[i]);
    }
    
    delete[] elements;
    elements = newElements;
    size = newSize;
}

/* ************************************************************************** */

// Specific Member Functions (Vector) (inherited from LinearContainer)
template<typename Data>
const Data& Vector<Data>::operator[](const unsigned long i) const {
    // Accesso in sola lettura all’i-esimo elemento.
    // Lancia eccezione se l'indice è fuori range.
    if (i >= size) {
        throw std::out_of_range("Indice " + std::to_string(i) + " supera la dimensione del vettore (" + std::to_string(size) + ")");
    }
    return elements[i];
}

template<typename Data>
const Data& Vector<Data>::Front() const {
    // Ritorna il primo elemento del vettore (in lettura).
    ThrowIfEmpty();
    return elements[0];
}

template<typename Data>
const Data& Vector<Data>::Back() const {
    // Ritorna l'ultimo elemento del vettore (in lettura).
    ThrowIfEmpty();
    return elements[size - 1];
}

/* ****************************************************** */
// Specific Constructors (SortableVector)

template<typename Data>
SortableVector<Data>::SortableVector(const unsigned long newsize) : Vector<Data>(newsize) {
    // Costruttore che inizializza un SortableVector con dimensione specifica.
}

template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data>& con) : Vector<Data>(con) {
    // Costruttore che inizializza un SortableVector da un container traversabile.
}

template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data>&& con) : Vector<Data>(std::move(con)) {
    // Costruttore che inizializza un SortableVector spostando i dati da un container mappabile.
}

/* ************************************************************************** */

// Copy Constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data>& vec) : Vector<Data>(vec) {
    // Costruttore di copia: costruisce un SortableVector copiando da un altro.
}

// Move Constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data>&& vec) noexcept : Vector<Data>(std::move(vec)) {
    // Costruttore di move: costruisce un SortableVector spostando risorse da un altro.
}

/* ************************************************************************** */

// Copy Assignment (SortableVector)
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec) {
    // Operatore di assegnazione per copia: delega all'operatore della classe base.
    Vector<Data>::operator=(vec);
    return *this;
}

// Move Assignment (SortableVector)
template<typename Data>
SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec) noexcept {
    // Operatore di assegnazione per move: delega all'operatore della classe base.
    Vector<Data>::operator=(std::move(vec));
    return *this;
}

}

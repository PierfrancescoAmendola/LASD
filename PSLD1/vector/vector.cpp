//
//  vector.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 02/05/25.
//


namespace lasd {

/* ************************************************************************** */
//Costruttori per (Vector)

template <typename Data>
Vector<Data>::Vector(const unsigned long newSize)
{
    size = newSize; // Imposta la dimensione
    if (size > 0)
    {
        elements = new Data[size]{}; // Alloca memoria e inizializza
    }
    else
    {
        elements = nullptr; // Caso dimensione zero
    }
}

// Costruttore da TraversableContainer (copia)
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container) : Vector(container.Size())
{
    unsigned long i = 0; // Indice per l'inserimento
    container.Traverse(
        [this, &i](const Data& dato)
        {
            elements[i++] = dato; // Copia i dati
        }
    );
}

// Costruttore da MappableContainer (move)
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container) : Vector(container.Size())
{
    unsigned long posizione = 0; // Posizione corrente
    container.Map(
        [this, &posizione](Data& dato)
        {
            elements[posizione++] = std::move(dato); // Sposta i dati
        }
    );
}

/* ************************************************************************** */

//Copy Constructor (Vector)
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& vettore)
{
    size = vettore.size; // Copia la dimensione
    
    if (size > 0) // Se il vettore non è vuoto
    {
        elements = new Data[size]; // Alloca nuovo spazio
        
        for (unsigned long  i = 0 ; i < size; ++i) // Copia elemento per elemento
        {
            elements[i] = vettore.elements[i]; // Copia il valore
        }
    }
    else // Se il vettore è vuoto
    {
        elements = nullptr; // Imposta a nullptr
    }
}

//Move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vettore) noexcept
{
    // Scambia i membri con il vettore sorgente
    size = vettore.size;
    elements = vettore.elements;
    
    // Mette il vettore sorgente in uno stato valido ma "vuoto"
    vettore.size = 0;
    vettore.elements = nullptr;
}

//Destructor (Vector)
template<typename Data>
Vector<Data>::~Vector()
{
  delete[] elements;
}

//Copy assignement (Vector)
template<typename Data>
Vector<Data>& Vector<Data>::operator = (const Vector<Data>& vettore)
{
    if (this != &vettore) // Protezione contro l'auto-assegnazione
    {
        Vector<Data> tmpVettore(vettore);  // Costruzione temporanea (sullo stack)
        std::swap(size, tmpVettore.size); //size.swap(tmpVettore.size); meglio non usare questa versione perchè potrebbe recare problemi nella compilazione in base al tipo che andiamo ad usare
        std::swap(elements, tmpVettore.elements);
        
        // tmpVettore viene distrutto qui, liberando le vecchie risorse
    }
    return *this;
}


// Move assignment (Vector)
template<typename Data>
Vector<Data> & Vector<Data>::operator = (Vector<Data> && vec) noexcept {
  std::swap(size, vec.size);
  std::swap(elements, vec.elements);
  return *this;
}



/* ************************************************************************** */



//Comparison Operator
// Operator == (Vector)
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& uguale) const noexcept
{
    if (size != uguale.size) return false; // Confronta le dimensioni
    for (unsigned long i = 0 ; i < size; ++i)
    {
        if (elements[i] != uguale.elements[i]) return false; // Accede direttamente agli elements
    }
    return true;
}

// Operator != (Vector)
template <typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& diverso) const noexcept
{
    return !(*this == diverso); // Negazione dell'operatore ==
}

// Specific member functions (Vector) (inherited from MutableLinearC)

template <typename Data>
Data& Vector<Data>::operator[](const unsigned long i)
{
    return const_cast<Data&>(static_cast<const Vector<Data> *>(this)->operator[](i));
}

template<typename Data>
Data& Vector<Data>::Front() 
{
    if (size == 0) {
        throw std::length_error("Accesso a vettore vuoto");
    }
    return elements[0];
}

template<typename Data>
Data& Vector<Data>::Back() {
    if (size == 0) {
        throw std::length_error("Accesso a vettore vuoto");
    }
    return elements[size - 1];
}



//Specific member function (Vector) (inhereted from ClerableC)
template <typename Data>
void Vector<Data>::Clear() noexcept
{
    if (elements != nullptr) // Se esiste già un array
    {
        delete[] elements;     // Lo distrugge
        elements = nullptr;    // Annulla il puntatore
    }
    size = 0 ; // Dimensione a zero
}

//Specific member function (Vector) (inherited from ResizableC)
template<typename Data>
void Vector<Data>::Resize(const unsigned long newSize)
{
    if (newSize == 0) return Clear();
    if (newSize == size) return;

    Data* newElements = new Data[newSize]{};
    const unsigned long copySize = std::min(size, newSize);
    
    for (unsigned long  i = 0; i < copySize; ++i)
    {
        newElements[i] = std::move(elements[i]);

    }
    
    delete[] elements;
    elements = newElements;
    size = newSize;
}


/* ************************************************************************** */

// Specific member functions (Vector) (inherited from LinearC)

template<typename Data>
const Data& Vector<Data>::operator[](const unsigned long i) const {
    if (i >= size) {
        throw std::out_of_range("Indice " + std::to_string(i) + 
                              " supera la dimensione del vettore (" + 
                              std::to_string(size) + ")");
    }
    return elements[i];
}

template<typename Data>
const Data & Vector<Data>::Front() const {
  if (size != 0) 
  {
    return elements[0];
  } else 
  {
    throw std::length_error("Accesso a vettore vuoto");
  }
}

template<typename Data>
const Data& Vector<Data>::Back() const
{
    if (elements == nullptr || size == 0)
    {
        throw std::length_error("Accesso a vettore vuoto");
    }
    
    return *(elements + size - 1);
}

/* ****************************************************** */
// Specific constructors (SortableVector)


template<typename Data>
SortableVector<Data>::SortableVector(const unsigned long newsize) : Vector<Data>(newsize) {}

template<typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & con) : Vector<Data>(con) {}

template<typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && con) : Vector<Data>(std::move(con)) {}

/* ************************************************************************** */

// Copy constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & vec) : Vector<Data>(vec) {}

// Move constructor (SortableVector)
template<typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && vec) noexcept : Vector<Data>(std::move(vec)) {}

/* ************************************************************************** */

// Copy assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & vec) {
  Vector<Data>::operator=(vec);
  return *this;
}

// Move assignment (SortableVector)
template<typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && vec) noexcept {
  Vector<Data>::operator=(std::move(vec));
  return *this;
}

}

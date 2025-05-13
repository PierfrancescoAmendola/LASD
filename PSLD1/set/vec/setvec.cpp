
namespace lasd {

/* ************************************************************************** */
// Default constructor

template <typename Data>
SetVec<Data>::SetVec() {
  vec.Resize(1);
  size = 0;
}

//Costruttori per (SetVec)
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : Set<Data>(), Vector<Data>(container.Size()) {
    unsigned long i = 0; // Indice per l'inserimento
    container.Traverse(
        [this, &i](const Data& dato)
        {
            Insert(dato); // Inserisce i dati
        }
    );
}
// Costruttore da MappableContainer (move)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>& container) {
  container.Map([this](const Data& val) {
    Insert(val);
  });
}

// Copy constructor
template <typename Data>
SetVec<Data>::SetVec(const SetVec& other)
 {
  vec = other.vec;
  size = other.size;
}

// Move constructor
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
  std::swap(vec, other.vec);
  std::swap(size, other.size);
}
/* ************************************************************************** */

// Distruttore
template <typename Data>
SetVec<Data>::~SetVec() 
{
    Clear();
}

/* ************************************************************************** */

//Copy assignement
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
  if (this != &other) 
  {
    Clear();
    for (unsigned long i = 0; i < other.vec.Size(); ++i) 
    {
      Insert(other.vec[i]);
    }
  }
  return *this;
}
//Move assignement
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) {
  if (this != &other) 
  {
    // Scambio manuale di vec e size
    Vector<Data> tmpVec = std::move(vec);
    vec = std::move(other.vec);
    other.vec = std::move(tmpVec);
    unsigned long tmpSize = size;
    size = other.size;
    other.size = tmpSize;
  }
  return *this;
}

/* ************************************************************************** */
//Comparison Operator

template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
  if (size != other.size) return false;
  for (unsigned long i = 0; i < size; ++i) 
  {
    if (!other.Exists(vec[i])) return false;
  }
  return true;
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
  return !(*this == other);
}
/* ************************************************************************** */
// Specific member functions (inherited from OrderedDictionaryContainer)

//Funzioni di Min

//Funzione Min
template <typename Data>
Data& SetVec<Data>::Min() const {
  if (size == 0) throw std::length_error("Min on empty set");
  unsigned long j = 0;
  for (unsigned long i = 1; i < size; ++i) 
  {
    if (vec[i] < vec[j]) j = i;
  }
  return const_cast<Data&>(vec[j]); 
}


//Funzione MinREmove
template <typename Data>
Data SetVec<Data>::MinNRemove() 
{
  Data& min = Min();
  Data temp = min;
  Remove(min);
  return temp;
}

//Funzione REmovemin
template <typename Data>
void SetVec<Data>::RemoveMin()
{
  Remove(Min());
}

//Funzioni di Max

//Funzione Max
template <typename Data>
Data& SetVec<Data>::Max() const 
{
  if (size == 0) throw std::length_error("SetVec::Max su insieme vuoto");
  unsigned long jMax = 0;
  for (unsigned long i = 1; i < size; ++i) 
  {
    if (vec[i] > vec[jMax]) 
    {
      jMax = i;
    }
  }
  return const_cast<Data&>(vec[jMax]);
}

//Funzione MaxREmove
template <typename Data>
Data SetVec<Data>::MaxNRemove() 
{
  Data& max = Max();
  Data temp = max;
  Remove(max);
  return temp;
}

//Funzione REmoveMax

template <typename Data>
void SetVec<Data>::RemoveMax() 
{
  Remove(Max());
}


//Funzoini di predecessore e successore

//Funzione Predecessor
template <typename Data>
Data& SetVec<Data>::Predecessor(const Data& val) const 
{
  const Data* pred = nullptr;
  for (unsigned long i = 0; i < size; ++i) {
    if (vec[i] < val && (!pred || vec[i] > *pred)) 
    {
      pred = &vec[i];
    }
  }
  if (!pred) throw std::length_error("Predecessor not found");
  return const_cast<Data&>(*pred);
}

//Funzione PredecessorNRemove
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& valore) 
{
  Data& predecessore = Predecessor(valore);
  Data temp = predecessore;
  Remove(predecessore);
  return temp;
}

//Funzione RemovePredecessor
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& valore)
{
  Remove(Predecessor(valore));
}

//Funzione Successor
template <typename Data>
Data& SetVec<Data>::Successor(const Data& val) const {
  const Data* succ = nullptr;
  for (unsigned long i = 0; i < size; ++i) {
    if (vec[i] > val && (!succ || vec[i] < *succ)) {
      succ = &vec[i];
    }
  }
  if (!succ) throw std::length_error("Successor not found");
  return const_cast<Data&>(*succ);
}


//Funzione SuccessorNRemove
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& valore) 
{
  Data& successore = Successor(valore);
  Data temp = successore;
  Remove(successore);
  return temp;
}


//Funzione RemoveSuccessor
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& valore) 
{
  Remove(Successor(valore));
}


/* ************************************************************************ */
// Specific member functions (inherited from DictionaryContainer)

//Funzione Insert (copia) restituisce false se esiste già
// Inserimento ordinato per copia
template <typename Data>
bool SetVec<Data>::Insert(const Data& valore) {
  if (Exists(valore)) return false;

  if (vec.Size() == 0) vec.Resize(1);
  else if (size == vec.Size()) vec.Resize(vec.Size() * 2);

  // Trova posizione per inserimento ordinato
  unsigned long i = 0;
  while (i < size && vec[i] < valore) ++i;

  // Sposta gli elementi a destra
  for (unsigned long j = size; j > i; --j) {
    vec[j] = std::move(vec[j - 1]);
  }

  vec[i] = valore;
  ++size;
  return true;
}

// Inserimento ordinato per move
template <typename Data>
bool SetVec<Data>::Insert(Data&& valore) {
  if (Exists(valore)) return false;

  if (vec.Size() == 0) vec.Resize(1);
  else if (size == vec.Size()) vec.Resize(vec.Size() * 2);

  unsigned long i = 0;
  while (i < size && vec[i] < valore) ++i;

  for (unsigned long j = size; j > i; --j) {
    vec[j] = std::move(vec[j - 1]);
  }

  vec[i] = std::move(valore);
  ++size;
  return true;
}

//Funzione Remove restituisce true se trovato e rimosso
template <typename Data>
bool SetVec<Data>::Remove(const Data& valore) {
  for (unsigned long i = 0; i < size; ++i) {
    if (vec[i] == valore) {
      // Sposta a sinistra gli elementi rimanenti
      for (unsigned long j = i; j < size - 1; ++j) {
        vec[j] = std::move(vec[j + 1]);
      }
      --size;
      return true;
    }
  }
  return false;
}


  
/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)

template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long i) const 
{
  if (i >= size) throw std::out_of_range("SetVec::operator[] index out of range");
  return vec[i];
}

// template <typename Data>
// Data& SetVec<Data>::operator[](unsigned long index) {
//   if (index >= size) throw std::out_of_range("Index out of range");
//   return vec[index];
// }


// Specific member function (inherited from TestableContainer)

template <typename Data>
bool SetVec<Data>::Exists(const Data& valore) const noexcept 
{
  for (unsigned long i = 0; i < size; ++i) {
    if (vec[i] == valore) return true;
  }
  return false;
}


// Specific member function (inherited from ClearableContainer)
template <typename Data>
void SetVec<Data>::Clear()
{
  vec.Clear();     // Reset al vettore vuoto
  size = 0;        // Dimensione logica a zero
}


// ResizableContainer
template <typename Data>
void SetVec<Data>::Resize(unsigned long newSize) 
{
  vec.Resize(newSize);
}

/* ************************************************************************** */

}

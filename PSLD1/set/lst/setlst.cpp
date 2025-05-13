// setlst.cpp
// Progetto LASD 2025 - Implementazione di SetLst
// Corretto secondo la traccia ed errori segnalati


namespace lasd {

/* ************************************************************************** */

// Costruttore di default
template <typename Data>
SetLst<Data>::SetLst() : List<Data>() {}

// Costruttore da TraversableContainer
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& container) : List<Data>() {
  container.Traverse([this](const Data& val) { Insert(val); });
}

// Costruttore da MappableContainer
template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& container) : List<Data>() {
  container.Map([this](Data& val) { Insert(std::move(val)); });
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst& other) : List<Data>(other) {}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst&& other) noexcept : List<Data>(std::move(other)) {}

// Destructor
template <typename Data>
SetLst<Data>::~SetLst() {
  Clear();
}

// Copy assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst& other) {
  List<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst&& other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

// Comparison
template <typename Data>
bool SetLst<Data>::operator==(const SetLst& other) const noexcept {
  return List<Data>::operator==(other);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Min
template <typename Data>
Data& SetLst<Data>::Min() const {
  if (this->head == nullptr) throw std::length_error("SetLst::Min su insieme vuoto");
  return this->head->element;
}

// MinNRemove
template <typename Data>
Data SetLst<Data>::MinNRemove() {
  return this->FrontNRemove();
}

// RemoveMin
template <typename Data>
void SetLst<Data>::RemoveMin() {
  Remove(Min());
}

// Max
template <typename Data>
Data& SetLst<Data>::Max() const {
  if (this->tail == nullptr) throw std::length_error("SetLst::Max su insieme vuoto");
  return this->tail->element;
}

// MaxNRemove
template <typename Data>
Data SetLst<Data>::MaxNRemove() {
  return this->BackNRemove();
}

// RemoveMax
template <typename Data>
void SetLst<Data>::RemoveMax() {
  Remove(Max());
}

// Predecessor
template <typename Data>
Data& SetLst<Data>::Predecessor(const Data& val) const {
  typename List<Data>::Node* pred = nullptr;
  for (typename List<Data>::Node* curr = this->head; curr != nullptr; curr = curr->next) {
    if (curr->element < val && (!pred || curr->element > pred->element)) {
      pred = curr;
    }
  }
  if (!pred) throw std::length_error("SetLst::Predecessor non trovato");
  return pred->element;
}

// PredecessorNRemove
template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& val) {
  Data tmp = Predecessor(val);
  Remove(tmp);
  return tmp;
}

// RemovePredecessor
template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& val) {
  Remove(Predecessor(val));
}

// Successor
template <typename Data>
Data& SetLst<Data>::Successor(const Data& val) const {
  typename List<Data>::Node* succ = nullptr;
  for (typename List<Data>::Node* curr = this->head; curr != nullptr; curr = curr->next) {
    if (curr->element > val && (!succ || curr->element < succ->element)) {
      succ = curr;
    }
  }
  if (!succ) throw std::length_error("SetLst::Successor non trovato");
  return succ->element;
}

// SuccessorNRemove
template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& val) {
  Data tmp = Successor(val);
  Remove(tmp);
  return tmp;
}

// RemoveSuccessor
template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& val) {
  Remove(Successor(val));
}

/* ************************************************************************** */

// Insert (copy)
template <typename Data>
bool SetLst<Data>::Insert(const Data& val) {
  if (Exists(val)) return false;
  typename List<Data>::Node* node = new typename List<Data>::Node(val);
  if (this->head == nullptr || val < this->head->element) {
    node->next = this->head;
    this->head = node;
    if (this->tail == nullptr) this->tail = node;
  } else {
    typename List<Data>::Node* curr = this->head;
    while (curr->next != nullptr && curr->next->element < val) {
      curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
    if (node->next == nullptr) this->tail = node;
  }
  ++this->size;
  return true;
}

// Insert (move)
template <typename Data>
bool SetLst<Data>::Insert(Data&& val) {
  if (Exists(val)) return false;
  typename List<Data>::Node* node = new typename List<Data>::Node(std::move(val));
  if (this->head == nullptr || node->element < this->head->element) {
    node->next = this->head;
    this->head = node;
    if (this->tail == nullptr) this->tail = node;
  } else {
    typename List<Data>::Node* curr = this->head;
    while (curr->next != nullptr && curr->next->element < node->element) {
      curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
    if (node->next == nullptr) this->tail = node;
  }
  ++this->size;
  return true;
}

// Remove
template <typename Data>
bool SetLst<Data>::Remove(const Data& val) {
  if (this->head == nullptr) throw std::length_error("SetLst::Remove - Elemento non trovato (lista vuota).");
  if (this->head->element == val) {
    typename List<Data>::Node* tmp = this->head;
    this->head = this->head->next;
    if (tmp == this->tail) this->tail = nullptr;
    tmp->next = nullptr;
    delete tmp;
    --this->size;
    return true;
  }
  typename List<Data>::Node* prev = this->head;
  while (prev->next != nullptr && prev->next->element != val) {
    prev = prev->next;
  }
  if (prev->next == nullptr) throw std::length_error("SetLst::Remove - Elemento non trovato.");;
  typename List<Data>::Node* target = prev->next;
  prev->next = target->next;
  if (target == this->tail) this->tail = prev;
  target->next = nullptr;
  delete target;
  --this->size;
  return true;
}

/* ************************************************************************** */

template <typename Data>
const Data& SetLst<Data>::operator[](unsigned long index) const {
  return List<Data>::operator[](index);
}

/* ************************************************************************** */

template <typename Data>
bool SetLst<Data>::Exists(const Data& val) const noexcept {
  for (typename List<Data>::Node* curr = this->head; curr != nullptr; curr = curr->next) {
    if (curr->element == val) return true;
  }
  return false;
}

/* ************************************************************************** */

template <typename Data>
void SetLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************** */

} // namespace lasd

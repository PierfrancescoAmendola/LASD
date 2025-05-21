//
//  container.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

namespace lasd {

/* ************************************************************************** */

// Costruttori specifici
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& tc) {
    tc.Traverse([this](const Data& data) { Insert(data); });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& mc) {
    mc.Map([this](Data& data) { Insert(std::move(data)); });
}

// Costruttore di copia
template <typename Data>
SetLst<Data>::SetLst(const SetLst& other) {
    other.Traverse([this](const Data& data) { Insert(data); });
}

// Costruttore di spostamento
template <typename Data>
SetLst<Data>::SetLst(SetLst&& other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

// Distruttore
template <typename Data>
SetLst<Data>::~SetLst() {
    Clear();
    //delete head;
}

/* ************************************************************************** */

// Assegnamento per copia
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst& other) {
    if (this != &other) {
        Clear();
        other.Traverse([this](const Data& data) { Insert(data); });
    }
    return *this;
}

// Assegnamento per spostamento
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst&& other) noexcept {
    if (this != &other) {
        Clear();
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }
    return *this;
}

/* ************************************************************************** */

// Operatori di confronto
template <typename Data>
bool SetLst<Data>::operator==(const SetLst& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    
    Node* curr1 = head;
    Node* curr2 = other.head;
    
    while (curr1 != nullptr && curr2 != nullptr) {
        if (curr1->element != curr2->element) {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    return curr1 == nullptr && curr2 == nullptr;
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// OrderedDictionaryContainer
template <typename Data>
const Data& SetLst<Data>::Min() const {
    if (head == nullptr) throw std::length_error("Set is empty");
    return head->element;
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
    if (head == nullptr) throw std::length_error("Set is empty");
    Node* oldHead = head;
    Data result = oldHead->element;  // Copia il valore
    head = oldHead->next;            // Aggiorna head
    if (head == nullptr) {
        tail = nullptr;
    }
    oldHead->next = nullptr;         // Disconnetti il nodo
    size--;
    delete oldHead;                  // Elimina il nodo DOPO aver copiato e aggiornato tutto
    return result;
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
    if (head == nullptr) throw std::length_error("Set is empty");
    Node* oldHead = head;
    head = oldHead->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    oldHead->next = nullptr;
    size--;
    delete oldHead;
}
template <typename Data>
const Data& SetLst<Data>::Max() const {
    if (tail == nullptr) throw std::length_error("Set vuoto");
    return tail->element;
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
    if (tail == nullptr) throw std::length_error("Set vuoto");
    Data data = tail->element; // copia PRIMA di rimuovere
    RemoveMax();
    return data;
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
    if (tail == nullptr) throw std::length_error("Set vuoto");
    
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        size--;
        return;
    }

    Node* current = head;
    while (current->next != tail) {
        current = current->next;
    }

    delete tail;
    tail = current;
    tail->next = nullptr;
    size--;
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
    // caso base: lista vuota o primo elemento >= data → niente predecessore
    if (head == nullptr || head->element >= data)
        throw std::length_error("Predecessore non trovato");

    // BinarySearch restituisce il puntatore al puntatore del primo nodo >= data
    Node** pos = BinarySearch(data);

    // se pos punta ad head, allora *pos == head, ma abbiamo già escluso head->element >= data
    // *** predPtr deve sempre esistere ***
    Node* pred = nullptr;
    // scorriamo fino a trovare il nodo che punta a *pos
    for (Node* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->next == *pos) {
            pred = curr;
            break;
        }
    }

    if (pred == nullptr)
        throw std::length_error("Predecessore non trovato");

    return pred->element;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& data) {
    Data val = Predecessor(data); // copia PRIMA di rimuovere
    Remove(val);
    return val;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& data) {
    Data val = Predecessor(data);
    Remove(val);
}

template <typename Data>
const Data& SetLst<Data>::Successor(const Data& data) const {
    // caso base: lista vuota o ultimo elemento <= data → niente successore
    if (head == nullptr || tail->element <= data)
        throw std::length_error("Successore non trovato");

    // BinarySearch restituisce il puntatore al puntatore del primo nodo >= data
    Node** pos = BinarySearch(data);

    // se *pos esiste ed è esattamente == data, il successore è il nodo successivo
    Node* succ = (*pos != nullptr && (*pos)->element == data)
                 ? (*pos)->next
                 : *pos;

    if (succ == nullptr)
        throw std::length_error("Successore non trovato");

    return succ->element;
}



template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    Data val = Successor(data); // copia PRIMA di rimuovere
    Remove(val);
    return val;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
    Data val = Successor(data);
    Remove(val);
}



/* ************************************************************************** */

// DictionaryContainer
template <typename Data>
bool SetLst<Data>::Insert(const Data& data) {
    Node** pos = BinarySearch(data);
    if (*pos != nullptr && (*pos)->element == data) return false;
    Node* newNode = new Node(data);
    newNode->next = *pos;
    *pos = newNode;
    if (newNode->next == nullptr) tail = newNode;
    size++;
    return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data&& data) {
    Node** pos = BinarySearch(data);
    if (*pos != nullptr && (*pos)->element == data) return false;
    Node* newNode = new Node(std::move(data));
    newNode->next = *pos;
    *pos = newNode;
    if (newNode->next == nullptr) tail = newNode;
    size++;
    return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& data) {
    Node** pos = BinarySearch(data);
    if (*pos == nullptr || (*pos)->element != data) return false;
    
    Node* toRemove = *pos;
    *pos = toRemove->next;
    
    // Aggiorna tail se necessario
    if (toRemove == tail) {
        if (head == nullptr) {
            tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            tail = current;
        }
    }
    
    toRemove->next = nullptr; // Importante: disconnetti il nodo
    delete toRemove;
    size--;
    return true;
}

/* ************************************************************************** */

// LinearContainer
template <typename Data>
const Data& SetLst<Data>::operator[](unsigned long index) const {
    if (index >= size) throw std::out_of_range("Indice fuori dal range");
    Node* current = head;
    for (unsigned long i = 0; i < index; ++i) current = current->next;
    return current->element;
}

/* ************************************************************************** */

// TestableContainer
template <typename Data>
bool SetLst<Data>::Exists(const Data& data) const noexcept {
    Node** pos = BinarySearch(data);
    return (*pos != nullptr && (*pos)->element == data);
}

/* ************************************************************************** */

// ClearableContainer
template <typename Data>
void SetLst<Data>::Clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        temp->next = nullptr; // Importante: disconnetti il nodo
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */

// Funzione ausiliaria: ricerca per lista ordinata
template <typename Data>
typename SetLst<Data>::Node** SetLst<Data>::BinarySearch(const Data& dat) const {
    if (size == 0) {
        return const_cast<Node**>(&head);
    }

    long left = 0;
    long right = size - 1;

    Node* leftNode = head;
    Node** leftPtr = const_cast<Node**>(&head);
    Node** resultPtr = leftPtr;

    while (left <= right) {
        long mid = left + (right - left) / 2;
        
        // Calcola la distanza da sinistra
        long steps = mid - left;
        
        Node* midNode = leftNode;
        Node** midPtr = leftPtr;
        for (long i = 0; i < steps && midNode != nullptr; ++i) {
            midPtr = &((*midPtr)->next);
            midNode = *midPtr;
        }

        if (midNode == nullptr) {
            return resultPtr;
        }

        if (midNode->element == dat) {
            return midPtr;
        } else if (midNode->element < dat) {
            // Aggiorna il puntatore risultato
            resultPtr = &(midNode->next);
            
            // Sposta "sinistra" avanti
            left = mid + 1;
            leftNode = midNode->next;
            leftPtr = &((*midPtr)->next);
        } else {
            right = mid - 1;
            resultPtr = midPtr;
        }
    }

    return resultPtr;
}
/* ************************************************************************** */




}
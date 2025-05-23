//  setlst.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//
//  Implementazione di un insieme ordinato basato su una lista concatenata.
//  Ho scelto una lista concatenata per mantenere gli elementi ordinati e
//  garantire operazioni efficienti per il minimo e il massimo (O(1)).
//  Ho aggiunto funzioni ausiliarie per ridurre la duplicazione del codice.

namespace lasd {

/* ************************************************************************** */

// Costruttori Specifici

// Costruttore da TraversableContainer: crea un insieme ordinato da un contenitore qualsiasi
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& tc) {
    // Scorro tutti gli elementi del contenitore e li inserisco in ordine
    // Perché: uso Insert per mantenere l'ordine e funziona con qualsiasi contenitore attraversabile
    tc.Traverse([this](const Data& data) { Insert(data); });
}

// Costruttore da MappableContainer: crea un insieme ordinato spostando gli elementi
template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& mc) {
    // Sposto gli elementi uno a uno usando std::move per essere più veloce
    // Perché: evito copie inutili e mantengo l'ordine con Insert
    mc.Map([this](Data& data) { Insert(std::move(data)); });
}

// Costruttore di Copia
template <typename Data>
SetLst<Data>::SetLst(const SetLst& other) {
    // Creo una copia completa della lista, elemento per elemento
    // Perché: riutilizzo la funzione CopyList della classe base per fare tutto in modo sicuro
    List<Data>::CopyList(other);
}

// Costruttore di Movimento
template <typename Data>
SetLst<Data>::SetLst(SetLst&& other) noexcept {
    // Scambio i puntatori (head, tail, size) con quelli dell'altro insieme
    // Perché: è un'operazione veloce (O(1)) e non rischia errori, perfetta per spostare risorse
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

// Distruttore
template <typename Data>
SetLst<Data>::~SetLst() {
    // Libero tutta la memoria cancellando i nodi della lista
    // Perché: uso Clear della classe base per fare il lavoro sporco in modo corretto
    Clear();
}

/* ************************************************************************** */

// Operatore di Assegnamento per Copia
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst& other) {
    // Controllo se sto assegnando a me stesso per evitare operazioni inutili
    if (this != &other) {
        // Svuoto l'insieme corrente e copio tutto dall'altro
        // Perché: Clear e CopyList fanno il lavoro in modo pulito e sicuro
        Clear();
        List<Data>::CopyList(other);
    }
    return *this;
}

// Operatore di Assegnamento per Movimento
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst&& other) noexcept {
    // Evito di assegnare a me stesso per prevenire errori
    if (this != &other) {
        // Svuoto l'insieme e scambio i puntatori con l'altro
        // Perché: è veloce (O(1)) e non rischio perdite di memoria
        Clear();
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
    }
    return *this;
}

/* ************************************************************************** */

// Operatori di Confronto

// Operatore di uguaglianza: controllo se due insiemi sono identici
template <typename Data>
bool SetLst<Data>::operator==(const SetLst& other) const noexcept {
    // Uso la funzione di confronto della classe base List
    // Perché: è già pronta e confronta gli elementi uno per uno in modo affidabile
    return List<Data>::operator==(other);
}

// Operatore di disuguaglianza: controllo se due insiemi sono diversi
template <typename Data>
bool SetLst<Data>::operator!=(const SetLst& other) const noexcept {
    // Nego il risultato di operator==, semplice e veloce
    // Perché: è il modo standard per definire !=, evitando codice ridondante
    return !(*this == other);
}

/* ************************************************************************** */

// Funzioni di OrderedDictionaryContainer

// Trovo il valore minimo
template <typename Data>
const Data& SetLst<Data>::Min() const {
    // Prendo il primo elemento della lista
    // Perché: in una lista ordinata, il primo è sempre il minimo, ed è veloce (O(1))
    return List<Data>::Front();
}

// Rimuovo e restituisco il valore minimo
template <typename Data>
Data SetLst<Data>::MinNRemove() {
    // Uso la funzione della classe base per rimuovere il primo elemento
    // Perché: è veloce (O(1)) e già testata, garantendo correttezza
    return List<Data>::FrontNRemove();
}

// Rimuovo il valore minimo
template <typename Data>
void SetLst<Data>::RemoveMin() {
    // Rimuovo il primo elemento senza restituirlo
    // Perché: simile a MinNRemove, ma più semplice se non mi serve il valore
    List<Data>::RemoveFromFront();
}

// Trovo il valore massimo
template <typename Data>
const Data& SetLst<Data>::Max() const {
    // Prendo l'ultimo elemento della lista
    // Perché: in una lista ordinata, l'ultimo è il massimo, ed è veloce (O(1))
    return List<Data>::Back();
}

// Rimuovo e restituisco il valore massimo
template <typename Data>
Data SetLst<Data>::MaxNRemove() {
    // Rimuovo l'ultimo elemento e lo restituisco
    // Perché: è veloce (O(1)) grazie alla struttura della lista con puntatore tail
    return List<Data>::BackNRemove();
}

// Rimuovo il valore massimo
template <typename Data>
void SetLst<Data>::RemoveMax() {
    // Rimuovo l'ultimo elemento senza restituirlo
    // Perché: come MaxNRemove, ma senza bisogno del valore
    List<Data>::RemoveFromBack();
}

// Trovo il predecessore di un elemento
template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
    // Controllo se la lista è vuota o se il primo elemento è troppo grande
    if (head == nullptr || head->element >= data)
        throw std::length_error("Predecessore non trovato");

    // Cerco la posizione di data con la ricerca binaria
    Node** pos = BinarySearch(data);
    Node* pred = nullptr;
    // Scorro la lista per trovare il nodo precedente
    for (Node* curr = head; curr != nullptr; curr = curr->next) {
        if (curr->next == *pos) {
            pred = curr;
            break;
        }
    }

    // Se non trovo il predecessore, lancio un errore
    if (pred == nullptr)
        throw std::length_error("Predecessore non trovato");

    // Perché: la ricerca binaria è più veloce (O(log n) confronti), ma scorrere la lista è O(n)
    return pred->element;
}

// Rimuovo e restituisco il predecessore
template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& data) {
    // Trovo il predecessore e lo rimuovo, restituendo il valore
    // Perché: riutilizzo Predecessor e Remove per modularità
    Data val = Predecessor(data);
    Remove(val);
    return val;
}

// Rimuovo il predecessore
template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& data) {
    // Trovo il predecessore e lo rimuovo senza restituirlo
    // Perché: simile a PredecessorNRemove, ma più semplice
    Data val = Predecessor(data);
    Remove(val);
}

// Trovo il successore di un elemento
template <typename Data>
const Data& SetLst<Data>::Successor(const Data& data) const {
    // Controllo se la lista è vuota o se l'ultimo elemento è troppo piccolo
    if (head == nullptr || tail->element <= data)
        throw std::length_error("Successore non trovato");

    // Cerco la posizione di data con la ricerca binaria
    Node** pos = BinarySearch(data);
    // Il successore è il nodo dopo, se data esiste, altrimenti è *pos
    Node* succ = (*pos != nullptr && (*pos)->element == data)
                 ? (*pos)->next
                 : *pos;

    // Se non trovo il successore, lancio un errore
    if (succ == nullptr)
        throw std::length_error("Successore non trovato");

    // Perché: simile a Predecessor, usa la ricerca binaria per efficienza
    return succ->element;
}

// Rimuovo e restituisco il successore
template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
    // Trovo il successore e lo rimuovo, restituendo il valore
    // Perché: riutilizzo Successor e Remove per modularità
    Data val = Successor(data);
    Remove(val);
    return val;
}

// Rimuovo il successore
template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
    // Trovo il successore e lo rimuovo senza restituirlo
    // Perché: simile a SuccessorNRemove, ma più semplice
    Data val = Successor(data);
    Remove(val);
}

/* ************************************************************************** */

// Funzioni di DictionaryContainer

// Inserisco un elemento (copia)
template <typename Data>
bool SetLst<Data>::Insert(const Data& data) {
    // Creo un nuovo nodo con copia dell'elemento e lo inserisco usando DoInsert
    // Perché: DoInsert centralizza la logica di inserimento, riducendo duplicazione
    return DoInsert(new Node(data));
}

// Inserisco un elemento (movimento)
template <typename Data>
bool SetLst<Data>::Insert(Data&& data) {
    // Creo un nuovo nodo spostando l'elemento e lo inserisco usando DoInsert
    // Perché: std::move è più efficiente per tipi che supportano il movimento
    return DoInsert(new Node(std::move(data)));
}

// Rimuovo un elemento
template <typename Data>
bool SetLst<Data>::Remove(const Data& data) {
    // Cerco il nodo con la ricerca binaria
    Node** pos = BinarySearch(data);
    // Se non lo trovo o non corrisponde, restituisco false
    if (*pos == nullptr || (*pos)->element != data) return false;

    // Rimuovo il nodo aggiornando i puntatori
    Node* toRemove = *pos;
    *pos = toRemove->next;

    // Aggiorno tail se ho rimosso l'ultimo nodo
    if (toRemove == tail) {
        UpdateTail();
    }

    // Libero la memoria e decremento la dimensione
    // Perché: gestisco tail con cura e libero la memoria correttamente
    delete toRemove;
    size--;
    return true;
}

/* ************************************************************************** */

// Funzioni di LinearContainer

// Accedo all'elemento a un certo indice
template <typename Data>
const Data& SetLst<Data>::operator[](unsigned long index) const {
    // Uso la funzione della classe base per accedere all'elemento
    // Perché: è già pronta, anche se un po' lenta (O(n)) per liste concatenate
    return List<Data>::operator[](index);
}

/* ************************************************************************** */

// Funzioni di TestableContainer

// Controllo se un elemento esiste
template <typename Data>
bool SetLst<Data>::Exists(const Data& data) const noexcept {
    // Cerco il nodo con la ricerca binaria
    Node** pos = BinarySearch(data);
    // Restituisco true se lo trovo e corrisponde
    // Perché: la ricerca binaria è più veloce (O(log n) confronti)
    return (*pos != nullptr && (*pos)->element == data);
}

/* ************************************************************************** */

// Funzioni di ClearableContainer

// Svuoto l'insieme
template <typename Data>
void SetLst<Data>::Clear() {
    // Uso la funzione della classe base per liberare tutti i nodi
    // Perché: è già testata e fa tutto il lavoro al posto mio
    List<Data>::Clear();
}

/* ************************************************************************** */

// Funzione Ausiliaria: Ricerca binaria per lista ordinata
template <typename Data>
typename SetLst<Data>::Node** SetLst<Data>::BinarySearch(const Data& dat) const {
    // Se la lista è vuota, punto a head per consentire l'inserimento
    if (size == 0) {
        return const_cast<Node**>(&head);
    }

    // Preparo gli indici per la ricerca binaria
    long left = 0;
    long right = size - 1;

    Node* leftNode = head;
    Node** leftPtr = const_cast<Node**>(&head);
    Node** resultPtr = leftPtr;

    // Faccio la ricerca binaria
    while (left <= right) {
        long mid = left + (right - left) / 2;

        // Mi muovo al nodo centrale
        long steps = mid - left;

        Node* midNode = leftNode;
        Node** midPtr = leftPtr;
        // Scorro la lista per arrivare al nodo centrale
        for (long i = 0; i < steps && midNode != nullptr; ++i) {
            midPtr = &((*midPtr)->next);
            midNode = *midPtr;
        }

        // Se non trovo il nodo centrale, restituisco il risultato
        if (midNode == nullptr) {
            return resultPtr;
        }

        // Confronto l'elemento centrale con quello cercato
        if (midNode->element == dat) {
            return midPtr;
        } else if (midNode->element < dat) {
            // Cerco a destra e aggiorno il risultato
            resultPtr = &(midNode->next);
            left = mid + 1;
            leftNode = midNode->next;
            leftPtr = &((*midPtr)->next);
        } else {
            // Cerco a sinistra
            right = mid - 1;
            resultPtr = midPtr;
        }
    }

    // Perché: la ricerca binaria è veloce per i confronti (O(log n)), ma scorrere la lista è O(n)
    return resultPtr;
}

/* ************************************************************************** */

// Funzioni Ausiliarie Aggiunte

// Funzione Ausiliaria: Inserisce un nodo già creato nella posizione corretta
template <typename Data>
bool SetLst<Data>::DoInsert(Node* newNode) {
    // Cerco la posizione di inserimento con la ricerca binaria
    Node** pos = BinarySearch(newNode->element);
    // Se l'elemento esiste già, elimino il nuovo nodo e restituisco false
    if (*pos != nullptr && (*pos)->element == newNode->element) {
        delete newNode;
        return false;
    }
    // Inserisco il nuovo nodo mantenendo l'ordine
    newNode->next = *pos;
    *pos = newNode;
    // Aggiorno tail se il nuovo nodo è l'ultimo
    if (newNode->next == nullptr)
        tail = newNode;
    size++;
    // Perché: centralizzo la logica di inserimento per evitare duplicazione in Insert
    return true;
}

// Funzione Ausiliaria: Aggiorna il puntatore tail dopo la rimozione di un nodo
template <typename Data>
void SetLst<Data>::UpdateTail() {
    // Se la lista è vuota, imposto tail a nullptr
    if (head == nullptr)
        tail = nullptr;
    else {
        // Scorro la lista per trovare l'ultimo nodo
        Node* current = head;
        while (current->next != nullptr)
            current = current->next;
        tail = current;
    }
    // Perché: separo la logica di aggiornamento di tail per rendere Remove più leggibile
}

}
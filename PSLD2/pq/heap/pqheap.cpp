//  pqheap.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//



namespace lasd {

/* ************************************************************************** */

template <typename Data>
PQHeap<Data>::PQHeap() {
    capacity = 4;
    this->elements = new Data[capacity]();
    size = 0;
    // Perché: 4 è una dimensione iniziale ragionevole, e inizializzo tutto a zero per sicurezza
}

template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data>& cont) : HeapVec<Data>(cont) {
    // Perché: eredita da HeapVec per costruire un heap valido dai dati del contenitore
}

template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data>&& cont) : HeapVec<Data>(std::move(cont)) {
    // Perché: usa std::move per trasferire i dati efficientemente, poi costruisce l'heap
}

/* ************************************************************************** */

template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {
    // Dopo aver chiamato il costruttore di copia di HeapVec, assicurati che capacity sia sufficiente
    if (capacity <= size) {
        unsigned long newCapacity = (size == 0) ? 4 : size * 2;
        Resize(newCapacity);
    }
    // Perché: garantisce spazio extra per inserimenti futuri, evitando overflow immediato
}

template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {
    // Perché: usa std::move per evitare copie inutili, preservando lo stato
}

/* ************************************************************************** */

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
    HeapVec<Data>::operator=(other);
    if (capacity <= size) {
        Resize((size == 0) ? 4 : size * 2);
    }
    return *this;
    // Perché: delega a HeapVec per la copia, assicura capacità sufficiente, restituisce this
}

template <typename Data>
PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
    HeapVec<Data>::operator=(std::move(other));
    return *this;
    // Perché: usa std::move per efficienza, restituisce il riferimento a this
}

/* ************************************************************************** */

template <typename Data>
Data PQHeap<Data>::Tip() const {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
        // Perché: impedisce l'accesso a una coda vuota, segnalando l'errore
    }
    return (*this)[0]; // Restituisce la radice (massimo in un max-heap)
    // Perché: la radice dell'heap contiene l'elemento con priorità più alta
}

template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
        // Perché: protegge da operazioni su una coda vuota
    }
    std::swap(this->elements[0], this->elements[size - 1]); // Scambia la radice con l'ultimo elemento
    --size; // Riduce la dimensione, escludendo l'elemento rimosso
    if (size > 0) {
        HeapifyDown(0); // Ripristina la proprietà del max-heap verso il basso
        // Perché: mantiene la struttura dell'heap dopo la rimozione
    }
    if (size < capacity / 4 && capacity > 4) {
        Resize(capacity / 2); // Riduce la capacità se la dimensione è meno di un quarto della capacità
        // Perché: ottimizza l'uso della memoria riducendo la capacità quando l'array è troppo vuoto
    }
}

template <typename Data>
Data PQHeap<Data>::TipNRemove() {
    if (size == 0) {
        throw std::length_error("Priority queue is empty");
        // Perché: impedisce operazioni su una coda vuota
    }
    Data result = std::move(this->elements[0]); // Salva la radice per restituirla
    std::swap(this->elements[0], this->elements[size - 1]); // Scambia la radice con l'ultimo elemento
    --size; // Riduce la dimensione
    if (size > 0) {
        HeapifyDown(0); // Ripristina la proprietà del max-heap
        // Perché: mantiene l'heap valido dopo la rimozione
    }
    if (size < capacity / 4 && capacity > 4) {
        Resize(capacity / 2); // Riduce la capacità se la dimensione è meno di un quarto della capacità
        // Perché: ottimizza l'uso della memoria riducendo la capacità quando l'array è troppo vuoto
    }
    return result; // Restituisce l'elemento rimosso
}

template <typename Data>
void PQHeap<Data>::Insert(const Data& value) {
    if (size >= capacity) { // Usa >= per sicurezza
        Resize((size == 0) ? 4 : size * 2); // Raddoppia la capacità o usa 4 se vuota
    }
    this->elements[size] = value; // Aggiunge il nuovo valore
    ++size; // Incrementa la dimensione
    HeapifyUp(size - 1); // Ripristina la proprietà del max-heap verso l'alto
    // Perché: usa Resize per gestire la capacità dinamicamente e mantiene l'heap valido
}

template <typename Data>
void PQHeap<Data>::Insert(Data&& value) {
    if (size >= capacity) { // Usa >= per sicurezza
        Resize((size == 0) ? 4 : size * 2); // Raddoppia la capacità o usa 4 se vuota
    }
    this->elements[size] = std::move(value); // Aggiunge il valore spostandolo
    ++size; // Incrementa la dimensione
    HeapifyUp(size - 1); // Ripristina la proprietà del max-heap verso l'alto
    // Perché: usa Resize per efficienza e mantiene l'heap valido
}

template <typename Data>
void PQHeap<Data>::Change(unsigned long index, const Data& value) {
    if (index >= size) {
        //throw std::length_error("Index out of bound"); // Esce se l'indice è fuori dai limiti
        return;
        // Perché: evita accessi non validi
    }
    Data oldValue = this->elements[index]; // Salva il vecchio valore
    this->elements[index] = value; // Sostituisce con il nuovo valore
    if (value > oldValue) {
        HeapifyUp(index); // Ripristina l'heap verso l'alto se il valore è aumentato
    } else if (value < oldValue) {
        HeapifyDown(index); // Ripristina l'heap verso il basso se il valore è diminuito
    }
    // Perché: regola la posizione dell'elemento per mantenere la proprietà del max-heap
}

template <typename Data>
void PQHeap<Data>::Change(unsigned long index, Data&& value) {
    if (index >= size) {
        //throw std::length_error("Index out of bound"); // Esce se l'indice è fuori dai limiti
        return;
        // Perché: protegge da indici non validi
    }
    Data oldValue = this->elements[index]; // Salva il vecchio valore
    this->elements[index] = std::move(value); // Sostituisce spostando il nuovo valore
    if (this->elements[index] > oldValue) {
        HeapifyUp(index); // Ripristina l'heap verso l'alto se il valore è aumentato
    } else if (this->elements[index] < oldValue) {
        HeapifyDown(index); // Ripristina l'heap verso il basso se il valore è diminuito
    }
    // Perché: usa lo spostamento per efficienza e mantiene la proprietà del max-heap
}


template <typename Data>
void PQHeap<Data>::Clear() noexcept {
    delete[] this->elements; // Libera l'array corrente
    this->elements = nullptr; // Imposta il puntatore a null
    size = 0; // Resetta la dimensione
    capacity = 0; // Resetta la capacità
    this->elements = new Data[4]();
    capacity = 4;
    // Perché: libera la memoria, resetta lo stato e prepara un nuovo array per futuri inserimenti
}

template <typename Data>
void PQHeap<Data>::Resize(unsigned long newCapacity) {
    if (newCapacity == 0) {
        newCapacity = 4; // Capacità minima
    }
    if (newCapacity < size) {
        newCapacity = size; // Non ridurre sotto la dimensione corrente
    }
    Data* newElements = new Data[newCapacity](); // Alloca nuovo array
    for (unsigned long i = 0; i < size; ++i) {
        newElements[i] = std::move(this->elements[i]); // Sposta gli elementi esistenti
    }
    delete[] this->elements; // Libera la memoria del vecchio array
    this->elements = newElements; // Aggiorna il puntatore
    capacity = newCapacity; // Aggiorna la capacità
    // Perché: ridimensiona l'array per ottimizzare la memoria, garantendo spazio per gli elementi esistenti
}

/* ************************************************************************** */

template <typename Data>
void PQHeap<Data>::HeapifyUp(unsigned long index) {
    while (index > 0) {
        unsigned long parent = (index - 1) / 2; // Calcola l'indice del genitore
        if (this->elements[index] > this->elements[parent]) {
            std::swap(this->elements[index], this->elements[parent]); // Scambia se il figlio è maggiore
            index = parent; // Continua verso l'alto
        } else {
            break; // Esce se la proprietà dell'heap è rispettata
        }
    }
    // Perché: sposta un elemento verso l'alto per mantenere il max-heap
}

template <typename Data>
void PQHeap<Data>::HeapifyDown(unsigned long index) {
    while (true) {
        unsigned long largest = index; // Assume che il nodo corrente sia il più grande
        unsigned long left = 2 * index + 1; // Indice del figlio sinistro
        unsigned long right = 2 * index + 2; // Indice del figlio destro
        if (left < size && this->elements[left] > this->elements[largest]) {
            largest = left; // Aggiorna se il figlio sinistro è maggiore
        }
        if (right < size && this->elements[right] > this->elements[largest]) {
            largest = right; // Aggiorna se il figlio destro è maggiore
        }
        if (largest == index) {
            break; // Esce se non ci sono figli maggiori
        }
        std::swap(this->elements[index], this->elements[largest]); // Scambia con il figlio più grande
        index = largest; // Continua verso il basso
    }
    // Perché: sposta un elemento verso il basso per mantenere la proprietà del max-heap
}

}

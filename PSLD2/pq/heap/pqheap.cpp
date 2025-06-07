// //  pqheap.cpp
// //  Progetto LASD 2025
// //
// //  Created by Pierfrancesco on 21/05/25.
// //

// namespace lasd {

// /* ************************************************************************** */

// template <typename Data>
// PQHeap<Data>::PQHeap() {
//     // Creo un array con una capacità iniziale di 4
//     capacity = 4;
//     this-> elements = new Data[capacity]();
//     size = 0;
//     // Perché: 4 è una dimensione iniziale ragionevole, e inizializzo tutto a zero per sicurezza
// }

// // Costruttore specifico da TraversableContainer
// // Inizializza la coda a priorità copiando i dati da un contenitore traversabile, sfruttando la costruzione di HeapVec
// template <typename Data>
// PQHeap<Data>::PQHeap(const TraversableContainer<Data>& cont) : HeapVec<Data>(cont) {
//     // Perché: eredita da HeapVec per costruire un heap valido dai dati del contenitore
// }

// // Costruttore specifico da MappableContainer
// // Inizializza la coda a priorità spostando i dati da un contenitore mappabile, ottimizzando con lo spostamento
// template <typename Data>
// PQHeap<Data>::PQHeap(MappableContainer<Data>&& cont) : HeapVec<Data>(std::move(cont)) {
//     // Perché: usa std::move per trasferire i dati efficientemente, poi costruisce l'heap
// }

// /* ************************************************************************** */

// // Costruttore di copia
// // Crea una nuova coda a priorità copiando i dati da un'altra PQHeap
// template <typename Data>
// PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {
//     // Perché: duplica l'intera struttura, mantenendo la proprietà dell'heap
// }

// // Costruttore di spostamento
// // Trasferisce i dati da un'altra PQHeap a questa, in modo efficiente
// template <typename Data>
// PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {
//     // Perché: usa std::move per evitare copie inutili, preservando lo stato
// }

// /* ************************************************************************** */

// // Operatore di assegnazione per copia
// // Copia i dati da un'altra PQHeap, sovrascrivendo il contenuto attuale
// template <typename Data>
// PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
//     HeapVec<Data>::operator=(other);
//     return *this;
//     // Perché: delega a HeapVec per la copia, restituisce il riferimento a this per concatenazione
// }

// // Operatore di assegnazione per spostamento
// // Trasferisce i dati da un'altra PQHeap, ottimizzando l'operazione
// template <typename Data>
// PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
//     HeapVec<Data>::operator=(std::move(other));
//     return *this;
//     // Perché: usa std::move per efficienza, restituisce il riferimento a this
// }

// /* ************************************************************************** */

// // Tip: Restituisce l'elemento con priorità massima
// // Lancia un'eccezione se la coda è vuota
// template <typename Data>
// Data PQHeap<Data>::Tip() const {
//     if (size == 0) {
//         throw std::length_error("Priority queue is empty");
//         // Perché: impedisce l'accesso a una coda vuota, segnalando l'errore
//     }
//     return (*this)[0]; // Restituisce la radice (massimo in un max-heap)
//     // Perché: la radice dell'heap contiene l'elemento con priorità più alta
// }

// // RemoveTip: Rimuove l'elemento con priorità massima
// // Lancia un'eccezione se la coda è vuota
// template <typename Data>
// void PQHeap<Data>::RemoveTip() {
//     if (size == 0) {
//         throw std::length_error("Priority queue is empty");
//         // Perché: protegge da operazioni su una coda vuota
//     }
//     std::swap(this->elements[0], this->elements[size - 1]); // Scambia la radice con l'ultimo elemento
//     --size; // Riduce la dimensione, escludendo l'elemento rimosso
//     if (size > 0) {
//         HeapifyDown(0); // Ripristina la proprietà del max-heap verso il basso
//         // Perché: mantiene la struttura dell'heap dopo la rimozione
//     }
// }

// // TipNRemove: Restituisce e rimuove l'elemento con priorità massima
// // Lancia un'eccezione se la coda è vuota
// template <typename Data>
// Data PQHeap<Data>::TipNRemove() {
//     if (size == 0) {
//         throw std::length_error("Priority queue is empty");
//         // Perché: impedisce operazioni su una coda vuota
//     }
//     Data result = std::move(this->elements[0]); // Salva la radice per restituirla
//     std::swap(this->elements[0], this->elements[size - 1]); // Scambia la radice con l'ultimo elemento
//     --size; // Riduce la dimensione
//     if (size > 0) {
//         HeapifyDown(0); // Ripristina la proprietà del max-heap
//         // Perché: mantiene l'heap valido dopo la rimozione
//     }
//     return result; // Restituisce l'elemento rimosso
// }

// // Insert (copia): Inserisce una copia del valore nella coda
// template <typename Data>
// void PQHeap<Data>::Insert(const Data& value) {
//     // Raddoppia la capacità se necessario
//     unsigned long newCapacity = (size == 0) ? 1 : size * 2;
//     Data* newelements = new Data[newCapacity]; // Alloca un nuovo array
//     for (unsigned long i = 0; i < size; ++i) {
//         newelements[i] = this->elements[i]; // Copia gli elementi esistenti
//     }
//     delete[] this->elements; // Libera la memoria vecchia
//     this->elements = newelements; // Aggiorna il puntatore
//     this->elements[size] = value; // Aggiunge il nuovo valore
//     ++size; // Incrementa la dimensione
//     HeapifyUp(size - 1); // Ripristina la proprietà del max-heap verso l'alto
//     // Perché: espande la capacità dinamicamente e mantiene l'heap valido
// }

// // Insert (spostamento): Inserisce un valore spostandolo nella coda
// template <typename Data>
// void PQHeap<Data>::Insert(Data&& value) {
//     // Raddoppia la capacità se necessario
//     unsigned long newCapacity = (size == 0) ? 1 : size * 2;
//     Data* newelements = new Data[newCapacity]; // Alloca un nuovo array
//     for (unsigned long i = 0; i < size; ++i) {
//         newelements[i] = std::move(this->elements[i]); // Sposta gli elementi esistenti
//     }
//     delete[] this->elements; // Libera la memoria vecchia
//     this->elements = newelements; // Aggiorna il puntatore
//     this->elements[size] = std::move(value); // Aggiunge il valore spostandolo
//     ++size; // Incrementa la dimensione
//     HeapifyUp(size - 1); // Ripristina la proprietà del max-heap verso l'alto
//     // Perché: usa lo spostamento per efficienza e mantiene l'heap valido
// }

// // Change (copia): Modifica la priorità di un elemento a un dato indice
// template <typename Data>
// void PQHeap<Data>::Change(unsigned long index, const Data& value) {
//     if (index >= size) {
//         //throw std::length_error("Index out of bound"); // Esce se l'indice è fuori dai limiti
//         return;
//         // Perché: evita accessi non validi
//     }

//     Data oldValue = this->elements[index]; // Salva il vecchio valore
//     this->elements[index] = value; // Sostituisce con il nuovo valore
//     if (value > oldValue) {
//         HeapifyUp(index); // Ripristina l'heap verso l'alto se il valore è aumentato
//     } else if (value < oldValue) {
//         HeapifyDown(index); // Ripristina l'heap verso il basso se il valore è diminuito
//     }
//     // Perché: regola la posizione dell'elemento per mantenere la proprietà del max-heap
// }

// // Change (spostamento): Modifica la priorità di un elemento a un dato indice spostando il valore
// template <typename Data>
// void PQHeap<Data>::Change(unsigned long index, Data&& value) {
//     if (index >= size) {
//         //throw std::length_error("Index out of bound"); // Esce se l'indice è fuori dai limiti
//         return;
//         // Perché: protegge da indici non validi
//     }
//     Data oldValue = this->elements[index]; // Salva il vecchio valore
//     this->elements[index] = std::move(value); // Sostituisce spostando il nuovo valore
//     if (this->elements[index] > oldValue) {
//         HeapifyUp(index); // Ripristina l'heap verso l'alto se il valore è aumentato
//     } else if (this->elements[index] < oldValue) {
//         HeapifyDown(index); // Ripristina l'heap verso il basso se il valore è diminuito
//     }
//     // Perché: usa lo spostamento per efficienza e mantiene la proprietà del max-heap
// }

// // Clear: Pulisce la coda, liberando la memoria e resettando lo stato
// template <typename Data>
// void PQHeap<Data>::Clear() noexcept {
//     delete[] this->elements; // Libera l'array corrente
//     this->elements = nullptr; // Imposta il puntatore a null
//     size = 0; // Resetta la dimensione
//     capacity = 0; // Resetta la capacità
//     // Crea un nuovo array vuoto con capacità iniziale
//     this->elements = new Data[4]();
//     capacity = 4;
//     // Perché: libera la memoria, resetta lo stato e prepara un nuovo array per futuri inserimenti
// }

// template <typename Data>
// void PQHeap<Data>::Resize(unsigned long newCapacity) {
//     // Se la nuova capacità è 0, uso la minima (4)
//     if (newCapacity == 0) {
//         newCapacity = 4;
//     }
//     // Assicurati che la nuova capacità sia almeno pari alla dimensione corrente
//     if (newCapacity < size) {
//         newCapacity = size; // Non ridurre la capacità sotto il numero di elementi attuali
//     }
//     // Creo un nuovo array
//     Data* newElements = new Data[newCapacity]();
//     // Copio gli elementi nel nuovo array
//     for (unsigned long i = 0; i < size; ++i) {
//         newElements[i] = std::move(this->elements[i]); // Sposto gli elementi esistenti
//     }
//     // Libero il vecchio array
//     delete[] this->elements; // Libera la memoria del vecchio array
//     this->elements = newElements; // Aggiorna il puntatore
//     capacity = newCapacity; // Aggiorna la capacità
//     // Perché: ridimensiono l'array per ottimizzare la memoria, garantendo spazio per gli elementi esistenti
// }


// /* ************************************************************************** */

// // HeapifyUp: Ripristina la proprietà del max-heap spostando un elemento verso l'alto
// template <typename Data>
// void PQHeap<Data>::HeapifyUp(unsigned long index) {
//     while (index > 0) {
//         unsigned long parent = (index - 1) / 2; // Calcola l'indice del genitore
//         if (this->elements[index] > this->elements[parent]) {
//             std::swap(this->elements[index], this->elements[parent]); // Scambia se il figlio è maggiore
//             index = parent; // Continua verso l'alto
//         } else {
//             break; // Esce se la proprietà dell'heap è rispettata
//         }
//     }
//     // Perché: sposta un elemento verso l'alto per mantenere il max-heap
// }

// // HeapifyDown: Ripristina la proprietà del max-heap spostando un elemento verso il basso
// template <typename Data>
// void PQHeap<Data>::HeapifyDown(unsigned long index) {
//     while (true) {
//         unsigned long largest = index; // Assume che il nodo corrente sia il più grande
//         unsigned long left = 2 * index + 1; // Indice del figlio sinistro
//         unsigned long right = 2 * index + 2; // Indice del figlio destro

//         if (left < size && this->elements[left] > this->elements[largest]) {
//             largest = left; // Aggiorna se il figlio sinistro è maggiore
//         }
//         if (right < size && this->elements[right] > this->elements[largest]) {
//             largest = right; // Aggiorna se il figlio destro è maggiore
//         }
//         if (largest == index) {
//             break; // Esce se non ci sono figli maggiori
//         }
//         std::swap(this->elements[index], this->elements[largest]); // Scambia con il figlio più grande
//         index = largest; // Continua verso il basso
//     }
//     // Perché: sposta un elemento verso il basso per mantenere la proprietà del max-heap
// }

// /* ************************************************************************** */

// }




// // // pqheap.cpp
// // // Progetto LASD 2025

// // // Created by Pierfrancesco on 21/05/25.

// // namespace lasd {

// // template <typename Data>
// // PQHeap<Data>::PQHeap() {
// //     capacity = 4;
// //     this->elements = new Data[capacity]();
// //     size = 0;
// // }

// // template <typename Data>
// // PQHeap<Data>::PQHeap(const TraversableContainer<Data>& cont) : HeapVec<Data>(cont) {
// // }

// // template <typename Data>
// // PQHeap<Data>::PQHeap(MappableContainer<Data>&& cont) : HeapVec<Data>(std::move(cont)) {
// // }

// // template <typename Data>
// // PQHeap<Data>::PQHeap(const PQHeap<Data>& other) : HeapVec<Data>(other) {
// // }

// // template <typename Data>
// // PQHeap<Data>::PQHeap(PQHeap<Data>&& other) noexcept : HeapVec<Data>(std::move(other)) {
// // }

// // template <typename Data>
// // PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap<Data>& other) {
// //     HeapVec<Data>::operator=(other);
// //     return *this;
// // }

// // template <typename Data>
// // PQHeap<Data>& PQHeap<Data>::operator=(PQHeap<Data>&& other) noexcept {
// //     HeapVec<Data>::operator=(std::move(other));
// //     return *this;
// // }

// // template <typename Data>
// // Data PQHeap<Data>::Tip() const {
// //     if (size == 0) {
// //         throw std::length_error("Priority queue is empty");
// //     }
// //     return this->elements[0];
// // }

// // template <typename Data>
// // void PQHeap<Data>::RemoveTip() {
// //     if (size == 0) {
// //         throw std::length_error("Priority queue is empty");
// //     }
// //     std::swap(this->elements[0], this->elements[size - 1]);
// //     --size;
// //     if (size > 0) {
// //         HeapifyDown(0);
// //     }
// // }

// // template <typename Data>
// // Data PQHeap<Data>::TipNRemove() {
// //     if (size == 0) {
// //         throw std::length_error("Priority queue is empty");
// //     }
// //     Data result = std::move(this->elements[0]);
// //     std::swap(this->elements[0], this->elements[size - 1]);
// //     --size;
// //     if (size > 0) {
// //         HeapifyDown(0);
// //     }
// //     return result;
// // }

// // template <typename Data>
// // void PQHeap<Data>::Insert(const Data& value) {
// //     if (size >= capacity) {
// //         Resize(capacity == 0 ? 4 : capacity * 2);
// //     }
// //     this->elements[size] = value;
// //     ++size;
// //     HeapifyUp(size - 1);
// // }

// // template <typename Data>
// // void PQHeap<Data>::Insert(Data&& value) {
// //     if (size >= capacity) {
// //         Resize(capacity == 0 ? 4 : capacity * 2);
// //     }
// //     this->elements[size] = std::move(value);
// //     ++size;
// //     HeapifyUp(size - 1);
// // }

// // template <typename Data>
// // void PQHeap<Data>::Change(unsigned long index, const Data& value) {
// //     if (index >= size) {
// //         //throw std::length_error("Index out of bounds");
// //         return; // Exit if index is out of bounds
// //     }
// //     Data oldValue = this->elements[index];
// //     this->elements[index] = value;
// //     if (value > oldValue) {
// //         HeapifyUp(index);
// //     } else if (value < oldValue) {
// //         HeapifyDown(index);
// //     }
// // }

// // template <typename Data>
// // void PQHeap<Data>::Change(unsigned long index, Data&& value) {
// //     if (index >= size) {
// //         //throw std::length_error("Index out of bounds");
// //         return; // Exit if index is out of bounds
// //     }
// //     Data oldValue = this->elements[index];
// //     this->elements[index] = std::move(value);
// //     if (this->elements[index] > oldValue) {
// //         HeapifyUp(index);
// //     } else if (this->elements[index] < oldValue) {
// //         HeapifyDown(index);
// //     }
// // }

// // template <typename Data>
// // void PQHeap<Data>::Clear() noexcept {
// //     delete[] this->elements;
// //     capacity = 4;
// //     this->elements = new Data[capacity]();
// //     size = 0;
// // }

// // template <typename Data>
// // void PQHeap<Data>::Resize(unsigned long newCapacity) {
// //     if (newCapacity < size) {
// //         newCapacity = size; // Ensure capacity is at least size
// //     }
// //     Data* newElements = new Data[newCapacity]();
// //     for (unsigned long i = 0; i < size; ++i) {
// //         newElements[i] = std::move(this->elements[i]);
// //     }
// //     delete[] this->elements;
// //     this->elements = newElements;
// //     capacity = newCapacity;
// // }

// // template <typename Data>
// // void PQHeap<Data>::HeapifyUp(unsigned long index) {
// //     while (index > 0) {
// //         unsigned long parent = (index - 1) / 2;
// //         if (this->elements[index] > this->elements[parent]) {
// //             std::swap(this->elements[index], this->elements[parent]);
// //             index = parent;
// //         } else {
// //             break;
// //         }
// //     }
// // }

// // template <typename Data>
// // void PQHeap<Data>::HeapifyDown(unsigned long index) {
// //     while (true) {
// //         unsigned long largest = index;
// //         unsigned long left = 2 * index + 1;
// //         unsigned long right = 2 * index + 2;

// //         if (left < size && this->elements[left] > this->elements[largest]) {
// //             largest = left;
// //         }
// //         if (right < size && this->elements[right] > this->elements[largest]) {
// //             largest = right;
// //         }
// //         if (largest == index) {
// //             break;
// //         }
// //         std::swap(this->elements[index], this->elements[largest]);
// //         index = largest;
// //     }
// // }

// // } // namespace lasd

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
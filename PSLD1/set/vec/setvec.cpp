//
//  setvec.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

namespace lasd {

/* ************************************************************************** */

/* Funzione per calcolare l'indice circolare */
template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long index) const noexcept {
    // Trasformo l'indice logico in un indice reale usando il modulo
    // Perché: gestisce il wrapping circolare dell'array, così non esco mai dai limiti
    return (head + index) % capacity;
}

/* Ricerca binaria per trovare il punto di inserimento */
template <typename Data>
unsigned long SetVec<Data>::BinarySearch(const Data& data) const noexcept {
    // Se l'insieme è vuoto, restituisco l'indice di head
    if (size == 0) {
        return head;
    }
    // Uso una ricerca binaria per trovare dove inserire il dato
    unsigned long left = 0;
    unsigned long right = size;
    while (left < right) {
        unsigned long mid = left + (right - left) / 2;
        if (elements[CircularIndex(mid)] < data) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    // Restituisco l'indice assoluto nel vettore
    // Perché: la ricerca binaria è veloce (O(log n)) e trova il punto giusto per mantenere l'ordine
    return (head + left) % capacity;
}

/* Costruttore di default */
template <typename Data>
SetVec<Data>::SetVec() {
    // Creo un array con una capacità iniziale di 4
    capacity = 4;
    elements = new Data[capacity]();
    size = 0;
    head = 0;
    // Perché: 4 è una dimensione iniziale ragionevole, e inizializzo tutto a zero per sicurezza
}

/* Costruttori specifici */
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : SetVec() {
    // Scorro il contenitore e inserisco ogni elemento
    container.Traverse([this](const Data& dato) {
        Insert(dato);
    });
    // Perché: riutilizzo Insert per mantenere l'ordine e funziona con qualsiasi contenitore attraversabile
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>& container) : SetVec() {
    // Scorro il contenitore e inserisco ogni elemento
    container.Map([this](const Data& val) {
        Insert(val);
    });
    // Perché: simile al costruttore sopra, ma usa Map per compatibilità con contenitori mappabili
}

/* Costruttore di copia */
template <typename Data>
SetVec<Data>::SetVec(const SetVec& other) {
    // Copio la capacità e creo un nuovo array
    capacity = other.capacity;
    elements = new Data[capacity]();
    size = other.size;
    head = other.head;
    // Copio gli elementi uno per uno usando l'indice circolare
    for (unsigned long i = 0; i < size; ++i) {
        elements[CircularIndex(i)] = other.elements[other.CircularIndex(i)];
    }
    // Perché: faccio una copia completa per avere un duplicato esatto
}

/* Costruttore di movimento */
template <typename Data>
SetVec<Data>::SetVec(SetVec&& other) noexcept {
    // Scambio gli array e le variabili con l'altro oggetto
    std::swap(elements, other.elements);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(head, other.head);
    // Perché: è veloce (O(1)) e sposta le risorse senza copiarle
}

/* Distruttore */
template <typename Data>
SetVec<Data>::~SetVec() {
    // Libero la memoria dell'array e resetto tutto
    delete[] elements;
    elements = nullptr;
    size = 0;
    capacity = 0;
    head = 0;
    // Perché: pulisco tutto per evitare perdite di memoria
}

/* Operatore di assegnamento per copia */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec& other) {
    // Evito l'auto-assegnamento
    if (this != &other) {
        // Libero l'array corrente e copio tutto dall'altro
        delete[] elements;
        capacity = other.capacity;
        elements = new Data[capacity]();
        size = other.size;
        head = other.head;
        for (unsigned long i = 0; i < size; ++i) {
            elements[CircularIndex(i)] = other.elements[other.CircularIndex(i)];
        }
    }
    // Perché: assicuro una copia completa e corretta, liberando prima le risorse
    return *this;
}

/* Operatore di assegnamento per movimento */
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec&& other) noexcept {
    // Evito l'auto-assegnamento
    if (this != &other) {
        // Libero l'array corrente
        delete[] elements;
        // Sposto le risorse dall'altro oggetto
        elements = other.elements;
        size = other.size;
        capacity = other.capacity;
        head = other.head;
        // Resetto l'altro oggetto a uno stato vuoto
        other.elements = new Data[4]();
        other.size = 0;
        other.capacity = 4;
        other.head = 0;
    }
    // Perché: è veloce (O(1)) e sposta le risorse senza copiarle
    return *this;
}

/* Operatori di confronto */
template <typename Data>
bool SetVec<Data>::operator==(const SetVec& other) const noexcept {
    // Controllo se le dimensioni sono diverse
    if (size != other.size) return false;
    // Confronto gli elementi uno per uno
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[CircularIndex(i)] != other.elements[other.CircularIndex(i)]) return false;
    }
    return true;
    // Perché: confronto elemento per elemento per verificare se gli insiemi sono uguali
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec& other) const noexcept {
    // Uso l'operatore == e lo nego
    return !(*this == other);
    // Perché: è il modo più semplice per definire !=
}

/* Funzioni specifiche (OrderedDictionaryContainer) */
template <typename Data>
const Data& SetVec<Data>::Min() const {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Restituisco il primo elemento
    return elements[head];
    // Perché: in un insieme ordinato, il primo elemento è il minimo (O(1))
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Sposto il minimo e lo restituisco
    Data result = std::move(elements[head]);
    elements[head] = Data{}; // Pulisco la posizione
    head = (head + 1) % capacity;
    --size;
    return result;
    // Perché: rimuovo il minimo (primo elemento) in modo efficiente (O(1))
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Pulisco la posizione del minimo e aggiorno head
    elements[head] = Data{};
    head = (head + 1) % capacity;
    --size;
    // Perché: simile a MinNRemove, ma non restituisco il valore
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Restituisco l'ultimo elemento
    return elements[CircularIndex(size - 1)];
    // Perché: in un insieme ordinato, l'ultimo elemento è il massimo (O(1))
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Sposto il massimo e lo restituisco
    Data result = std::move(elements[CircularIndex(size - 1)]);
    --size;
    return result;
    // Perché: rimuovo l'ultimo elemento in modo veloce (O(1))
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Riduco la dimensione, eliminando il massimo
    --size;
    // Perché: semplice e veloce, non serve spostare nulla
}

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& value) const {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se sono al primo elemento, non c'è predecessore
    if (pos == 0) throw std::length_error("No predecessor found");
    // Restituisco l'elemento precedente
    return elements[CircularIndex(pos - 1)];
    // Perché: uso la ricerca binaria per trovare il punto giusto in O(log n)
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& value) {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se sono al primo elemento, non c'è predecessore
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    // Decido se spostare verso sinistra o destra in base alla posizione
    if (pos <= size / 2) {
        // Sposto verso sinistra (verso head)
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione di head
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra (verso tail)
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    // Se l'array è troppo vuoto, lo ridimensiono
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    // Perché: scelgo il movimento più efficiente e ridimensiono per risparmiare memoria
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& value) {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se sono al primo elemento, non c'è predecessore
    if (pos == 0) throw std::length_error("No predecessor found");
    pos--;
    // Salvo il predecessore da restituire
    Data result = std::move(elements[CircularIndex(pos)]);
    // Sposto gli elementi per riempire il buco
    if (pos <= size / 2) {
        // Sposto verso sinistra (verso head)
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra (verso tail)
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    // Ridimensiono se necessario
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return result;
    // Perché: simile a RemovePredecessor, ma restituisco il valore rimosso
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& value) const {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore esiste, prendo il successivo
    if (pos < size && elements[CircularIndex(pos)] == value) {
        if (pos + 1 >= size) throw std::length_error("No successor found");
        return elements[CircularIndex(pos + 1)];
    }
    // Se non esiste, prendo l'elemento alla posizione trovata
    if (pos >= size) throw std::length_error("No successor found");
    return elements[CircularIndex(pos)];
    // Perché: la ricerca binaria trova il punto giusto in O(log n)
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& value) {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore esiste, passo al successivo
    if (pos < size && elements[CircularIndex(pos)] == value) {
        pos++;
    }
    // Se sono oltre la fine, non c'è successore
    if (pos >= size) throw std::length_error("No successor found");
    // Salvo il successore
    Data result = std::move(elements[CircularIndex(pos)]);
    // Sposto gli elementi per riempire il buco
    if (pos <= size / 2) {
        // Sposto verso sinistra
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    // Ridimensiono se necessario
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return result;
    // Perché: simile a RemoveSuccessor, ma restituisco il valore
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& value) {
    // Se l'insieme è vuoto, lancio un errore
    if (size == 0) throw std::length_error("Set is empty");
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore esiste, passo al successivo
    if (pos < size && elements[CircularIndex(pos)] == value) {
        pos++;
    }
    // Se sono oltre la fine, non c'è successore
    if (pos >= size) throw std::length_error("No successor found");
    // Sposto gli elementi per riempire il buco
    if (pos <= size / 2) {
        // Sposto verso sinistra
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    // Ridimensiono se necessario
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    // Perché: scelgo il movimento più efficiente per mantenere l'ordine
}

/* Funzioni specifiche (DictionaryContainer) */
template <typename Data>
bool SetVec<Data>::Insert(const Data& value) {
    // Se l'array è pieno, lo allargo
    if (size == capacity) Resize(capacity * 2);
    // Trovo dove inserire con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore esiste già, non lo inserisco
    if (pos < size && elements[CircularIndex(pos)] == value) return false;
    // Se l'insieme è vuoto, inserisco direttamente
    if (size == 0) {
        elements[head] = value;
        ++size;
        return true;
    }
    // Sposto gli elementi per fare spazio
    if (pos <= size / 2) {
        // Sposto verso sinistra
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
        elements[CircularIndex(pos)] = value;
    } else {
        // Sposto verso destra
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[CircularIndex(pos)] = value;
    }
    ++size;
    return true;
    // Perché: uso la ricerca binaria per mantenere l'ordine e scelgo il movimento più efficiente
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& value) {
    // Se l'array è pieno, lo allargo
    if (size == capacity) Resize(capacity * 2);
    // Trovo dove inserire con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore esiste già, non lo inserisco
    if (pos < size && elements[CircularIndex(pos)] == value) return false;
    // Se l'insieme è vuoto, inserisco direttamente
    if (size == 0) {
        elements[head] = std::move(value);
        ++size;
        return true;
    }
    // Sposto gli elementi per fare spazio
    if (pos <= size / 2) {
        // Sposto verso sinistra
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
        elements[CircularIndex(pos)] = std::move(value);
    } else {
        // Sposto verso destra
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[CircularIndex(pos)] = std::move(value);
    }
    ++size;
    return true;
    // Perché: simile a Insert per copia, ma uso std::move per essere più veloce
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& value) {
    // Se l'insieme è vuoto, non c'è nulla da rimuovere
    if (size == 0) return false;
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Se il valore non esiste, restituisco false
    if (pos >= size || elements[CircularIndex(pos)] != value) return false;
    // Sposto gli elementi per riempire il buco
    if (pos <= size / 2) {
        // Sposto verso sinistra
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    --size;
    // Ridimensiono se l'array è troppo vuoto
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    return true;
    // Perché: mantengo l'ordine e scelgo il movimento più efficiente
}

/* Funzioni specifiche (LinearContainer) */
template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
    // Controllo se l'indice è valido
    if (index >= size) throw std::out_of_range("Index out of range");
    // Restituisco l'elemento all'indice
    return elements[CircularIndex(index)];
    // Perché: l'indice circolare mi permette di accedere in O(1)
}

/* Funzione specifica (TestableContainer) */
template <typename Data>
bool SetVec<Data>::Exists(const Data& value) const noexcept {
    // Trovo la posizione con la ricerca binaria
    unsigned long abs_pos = BinarySearch(value);
    unsigned long pos = (abs_pos - head + capacity) % capacity;
    // Controllo se il valore esiste
    return (pos < size && elements[CircularIndex(pos)] == value);
    // Perché: la ricerca binaria è veloce (O(log n)) per verificare l'esistenza
}

/* Funzione specifica (ClearableContainer) */
template <typename Data>
void SetVec<Data>::Clear() {
    // Libero l'array e resetto tutto
    delete[] elements;
    elements = nullptr;
    size = 0;
    capacity = 0;
    head = 0;
    // Creo un nuovo array vuoto
    elements = new Data[4]();
    capacity = 4;
    // Perché: resetto tutto e mantengo la capacità iniziale di 4
}

/* Funzione ausiliaria per ridimensionare */
template <typename Data>
void SetVec<Data>::Resize(unsigned long newCapacity) {
    // Se la nuova capacità è 0, uso la minima (4)
    if (newCapacity == 0) newCapacity = 4;
    // Creo un nuovo array
    Data* newElements = new Data[newCapacity]();
    unsigned long newHead = 0;
    // Copio gli elementi nel nuovo array
    for (unsigned long i = 0; i < size; ++i) {
        newElements[newHead + i] = std::move(elements[CircularIndex(i)]);
    }
    // Libero il vecchio array
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
    head = newHead;
    // Perché: ridimensiono l'array per ottimizzare la memoria
}

/* Funzioni ausiliarie */
template <typename Data>
void SetVec<Data>::MakeSpaceAt(unsigned long pos) noexcept {
    // Se l'array è pieno, lo allargo
    if (size == capacity) Resize(capacity * 2);
    // Se l'insieme è vuoto, non faccio nulla
    if (size == 0) return;
    // Sposto gli elementi per fare spazio
    if (pos <= size / 2) {
        // Sposto verso sinistra
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    } else {
        // Sposto verso destra
        for (unsigned long i = size; i > pos; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
    }
    // Perché: scelgo il movimento più efficiente per fare spazio
}

template <typename Data>
void SetVec<Data>::FillGapAt(unsigned long pos) noexcept {
    // Sposto gli elementi per riempire il buco
    if (pos <= size / 2) {
        // Sposto verso sinistra
        for (unsigned long i = pos; i > 0; --i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i - 1)]);
        }
        elements[head] = Data{}; // Pulisco la vecchia posizione
        head = (head + 1) % capacity;
    } else {
        // Sposto verso destra
        for (unsigned long i = pos; i < size - 1; ++i) {
            elements[CircularIndex(i)] = std::move(elements[CircularIndex(i + 1)]);
        }
    }
    // Ridimensiono se necessario
    if (size < capacity / 4 && capacity > 10) Resize(capacity / 2);
    // Perché: mantengo l'ordine e ottimizzo la memoria
}

template <typename Data>
Data SetVec<Data>::RemoveAt(unsigned long pos) {
    // Sposto l'elemento e lo restituisco
    Data result = std::move(elements[CircularIndex(pos)]);
    FillGapAt(pos);
    --size;
    return result;
    // Perché: rimuovo l'elemento in modo efficiente e mantengo l'ordine
}

/* ************************************************************************** */

}
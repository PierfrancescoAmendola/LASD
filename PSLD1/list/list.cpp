
namespace lasd
{

/* ************************************************************************** */

// ...

// Specific constructor (Node)
template<typename Data>
List<Data>::Node::Node(Data && dat) noexcept
{
    std::swap(element, dat);
}

/* ************************************************************************** */

// Move constructor (Node)
template<typename Data>
List<Data>::Node::Node(Node && nod) noexcept
{
    std::swap(element, nod.element);
    std::swap(next, nod.next);
}

/* ************************************************************************** */

// Destructor (Node)
template<typename Data>
List<Data>::Node::~Node()
{
    delete next;
}

/* ************************************************************************** */

// Comparison operators (Node)
template<typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept
{
    if (element != nod.element) {return false;}
    
    bool thisNextNull = (next == nullptr);
    bool otherNextNull = (nod.next == nullptr);
    
    if (thisNextNull != otherNextNull){return false;}
    
    if (!thisNextNull && !otherNextNull){return (*next == *nod.next);}
    
    return true;
}

template<typename Data>
inline bool List<Data>::Node::operator!=(const Node& nod) const noexcept
{
    if (*this == nod)
    {
        return false;
    }
    return true;
}

/* ************************************************************************** */
// Specific member functions (Node)
template <typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail)
{
    if(next == nullptr)
    {
        return tail;
    } else
    {
        Node * node = new Node(element);
        node -> next = next -> Clone(tail);
        return node;
    }
}



/* ************************************************************************** */

// Specific constructors (List)
template<typename Data>
List<Data>::List(const TraversableContainer<Data> & con)
{
    con.Traverse(
                 [this](const Data & dat) {
                     InsertAtBack(dat);
                 }
                 );
}

template<typename Data>
List<Data>::List(MappableContainer<Data> && con)
{
    con.Map(
            [this](Data & dat) {
                InsertAtBack(std::move(dat));
            }
            );
}

/* ************************************************************************** */

// Copy constructor (List)
template<typename Data>
List<Data>::List(const List<Data> & lst)
{
    if (lst.tail != nullptr)
    {
        tail = new Node(*lst.tail);
        head = lst.head->Clone(tail);
        size = lst.size;
    }
}

// Move constructor (List)
template<typename Data>
List<Data>::List(List<Data> && lst) noexcept
{
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
}

/* ************************************************************************** */

// Destructor (List)
template<typename Data>
List<Data>::~List()
{
    delete head;
}

/* ************************************************************************** */

// Copy assignment (List)
template<typename Data>
List<Data> & List<Data>::operator=(const List<Data> & lst)
{
    if (size <= lst.size)
    {
        if (tail == nullptr)
        {
            List<Data> * tmplst = new List<Data>(lst);
            std::swap(*tmplst, *this);
            delete tmplst;
        } else
        {
            Node * ocur = lst.head;
            for (Node * ncur = head; ncur != nullptr; ncur = ncur->next, ocur = ocur->next)
            {
                ncur->element = ocur->element;
            }
            if (ocur != nullptr)
            {
                Node * newtail = new Node(*lst.tail);
                tail->next = ocur->Clone(newtail);
                tail = newtail;
            }
        }
    } else
    {
        if (lst.tail == nullptr)
        {
            delete head;
            head = tail = nullptr;
        } else
        {
            Node * ncur = head;
            for (Node * ocur = lst.head; ocur != nullptr; ocur = ocur->next, tail = ncur, ncur = ncur->next)
            {
                ncur->element = ocur->element;
            }
            delete ncur;
            tail->next = nullptr;
        }
    }
    size = lst.size;
    return *this;
}

// Move assignment (List)
template<typename Data>
List<Data> & List<Data>::operator=(List<Data> && lst) noexcept
{
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
    return *this;
}


/* ************************************************************************** */

// Comparison operators (List)

template<typename Data>
inline bool List<Data>::operator==(const List<Data>& lst) const noexcept
{
    // Controllo rapido sulla dimensione
    if (size != lst.size) {return false;}
    
    // Entrambe le liste sono vuote
    if (head == nullptr && lst.head == nullptr){return true;}
    
    // Una lista è vuota e l'altra no
    if (head == nullptr || lst.head == nullptr) {return false;}
    
    // Confronto ricorsivo dei nodi
    return *head == *lst.head;
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& lst) const noexcept
{
    if (*this == lst)
    {
        return false;
    }
    return true;
}
/* ************************************************************************** */

// Specific member functions (List)
template <typename Data>
void List<Data>::InsertAtFront(const Data &dato)
{
  Node *temp = new Node(dato);
  temp->next = head;
  head = temp;
  if (tail == nullptr)
    tail = head;
  ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data &&dato)
{
  Node *temp = new Node(std::move(dato));
  temp->next = head;
  head = temp;
  if (tail == nullptr)
    tail = head;
  ++size;
}

template<typename Data>
void List<Data>::RemoveFromFront()
{
    if (head == nullptr)
    {
        throw std::length_error("Access to an empty list.");
    }

    Node* toDelete = head;
    
    // Controlla se c'è un solo nodo usando next invece di head/tail
    if (head->next == nullptr)
    {
        tail = nullptr; // Resetta tail prima di head
        head = nullptr;
    } else
    {
        head = head->next;
    }

    // Isola il nodo prima della cancellazione
    toDelete->next = nullptr;
    delete toDelete;
    
    --size; // Spostato dopo la cancellazione per differenziare l'ordine
}

template<typename Data>
Data List<Data>::FrontNRemove()
{
    if (head == nullptr)
    {
        throw std::length_error("Access to an empty list.");
    }

    Node* victim = head;
    Data extracted_data = std::move(victim->element);  // Estrazione anticipata
    
    // Controllo elemento singolo tramite next invece di head/tail
    if (victim->next == nullptr)
    
    {
        tail = nullptr;  // Reset tail prima di head
        head = nullptr;
    } else {
        head = victim->next;
    }

    // Isolamento e pulizia
    victim->next = nullptr;
    delete victim;
    --size;  // Decremento post-eliminazione

    return extracted_data;  // Return per move semantics
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& dato)
{
    Node* newNode = new Node(dato);
    newNode->next = nullptr;  // Esplicita che è l'ultimo nodo
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    tail = newNode;
    size++;
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& dato)
{
    Node* new_node = new Node(std::move(dato));
    
    // Gestione caso lista vuota
    if (head == nullptr)
    {
        head = tail = new_node;
    }
    // Gestione caso lista non vuota
    else
    {
        tail->next = new_node;
        tail = new_node;
    }
    
    size++;
}

template<typename Data>
void List<Data>::RemoveFromBack()
{
    if (head == nullptr)
    {
        throw std::length_error("Access to an empty list.");
    }

    Node* toDelete = tail;

    // Caso con un solo nodo
    if (head == tail)
    {
        head = tail = nullptr;
    }
    // Caso con più nodi
    else
    {
        // Trova il penultimo nodo
        Node* prev = head;
        while (prev->next != tail)
        {
            prev = prev->next;
        }
        
        prev->next = nullptr;  // Isola l'ultimo nodo
        tail = prev;           // Aggiorna tail al penultimo
    }

    // Isola e cancella il nodo
    toDelete->next = nullptr;
    delete toDelete;
    
    --size;
}

template<typename Data>
Data List<Data>::BackNRemove()
{
    if (head == nullptr) {
        throw std::length_error("Access to an empty list.");
    }

    Node* victim = tail;
    Data extracted_data = std::move(victim->element);  // Estrazione dati prima della cancellazione

    // Caso con un solo nodo
    if (head == tail) {
        head = tail = nullptr;
    }
    // Caso con più nodi
    else {
        // Trova il penultimo nodo
        Node* prev = head;
        while (prev->next != tail) {
            prev = prev->next;
        }
        
        prev->next = nullptr;  // Isola l'ultimo nodo
        tail = prev;           // Aggiorna tail al penultimo
    }

    // Isolamento e pulizia
    victim->next = nullptr;
    delete victim;
    --size;

    return extracted_data;  // Return per move semantics
}

// Specific member functions (inherited from MutableLinearContainer)

template <typename Data>
Data & List<Data>::operator[](const unsigned long i)
{
    if(i < size)
    {
        Node * current = head;
        for (unsigned long j = 0; j < i; j++, current = current -> next) {}
        return current -> element;
    } else
    {
        throw std::out_of_range("Accesso all'indice " + std::to_string(i) + "ma la dimensione Lista = " + std::to_string(size));
    }
}


template <typename Data>
Data & List<Data>::Front()
{
    if(head != nullptr)
    {
        return head->element;
    } else
    {
        throw std::length_error("Accesso ad una lista vuota4");
    }
}


template <typename Data>
Data & List<Data>::Back()
{
    if(tail != nullptr)
    {
        return tail -> element;
    } else
    {
        throw std::length_error("Accesso ad una lista vuota6");
    }
}


/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)
template<typename Data>
const Data & List<Data>::operator[](const unsigned long i) const
{
    if(i < size)
    {
        Node * current = head;
        for (unsigned long j = 0; j < i; j++, current = current -> next) {}
        return current -> element;
    } else
    {
        throw std::out_of_range("Accesso all'indice " + std::to_string(i) + "ma la dimensione Lista = " + std::to_string(size));
    }
}

template <typename Data>
const Data & List<Data>::Front() const
{
    if(head != nullptr)
    {
        return head -> element;
    } else
    {
        throw std::length_error("Accesso ad una lista vuota");
    }
}

template <typename Data>
const Data & List<Data>::Back() const
{
    if(tail != nullptr)
    {
        return tail -> element;
    } else
    {
        throw std::length_error("Accesso ad una lista vuota");
    }
}


/* ************************************************************************ */

// Specific member function (inherited from MappableContainer)
template<typename Data>
inline void List<Data>::Map(MapFun fun)
{
  PreOrderMap(fun, head);
}



/* ************************************************************************ */

// Specific member function (inherited from PreOrderMappableContainer)
template<typename Data>
inline void List<Data>::PreOrderMap(MapFun fun)
{
  PreOrderMap(fun, head);
}
// Specific member functions (List) (inherited from PostOrderMappableContainer)

template<typename Data>
inline void List<Data>::PostOrderMap(MapFun fun)
{
  PostOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from TraversableContainer)

template<typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderTraversableContainer)

template<typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderTraversableContainer)

template<typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from ClearableContainer)

template<typename Data>
void List<Data>::Clear()
{
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for TraversableContainer)

template<typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node * current) const {
    //; inizializzazione vuota perchè già effettuata
  for (; current != nullptr; current = current->next)
  {
    fun(current->element);
  }
}

template<typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node * current) const
{
  if (current != nullptr) {
    PostOrderTraverse(fun, current->next);
    fun(current->element);
  }
}

/* ************************************************************************** */
// Auxiliary member functions (List) (for MappableContainer)

template<typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * current)
{
  for (; current != nullptr; current = current->next) {
    fun(current->element);
  }
}

template<typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * current)
{
  if (current != nullptr) {
    PostOrderMap(fun, current->next);
    fun(current->element);
  }
}

/* ************************************************************************** */






}

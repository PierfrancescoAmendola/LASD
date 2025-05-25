//
//  list.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//



namespace lasd {

/* ************************************************************************** */

// Specific constructor (Node)
template<typename Data>
List<Data>::Node::Node(Data&& dato) noexcept {
    std::swap(element, dato);
}

/* ************************************************************************** */

// Move constructor (Node)
template<typename Data>
List<Data>::Node::Node(Node&& nod) noexcept {
    std::swap(element, nod.element);
    std::swap(next, nod.next);
}

/* ************************************************************************** */

template<typename Data>
List<Data>::Node::~Node() {
    next = nullptr; // Prevent recursive deletion; List::DeleteList handles cleanup
}

/* ************************************************************************** */


template<typename Data>
bool List<Data>::Node::operator==(const Node& nod) const noexcept {
    return element == nod.element && (next == nullptr) == (nod.next == nullptr) && (next == nullptr || *next == *nod.next);
}

template<typename Data>
inline bool List<Data>::Node::operator!=(const Node& nod) const noexcept {
    return !(*this == nod);
}



/* ************************************************************************** */

template<typename Data>
typename List<Data>::Node* List<Data>::Node::Clone(Node* tailptr) {
    Node* newHead = new Node(element);
    Node* current = newHead;
    Node* nextNode = next;
    while (nextNode) {
        current->next = new Node(nextNode->element);
        current = current->next;
        nextNode = nextNode->next;
    }
    current->next = tailptr;
    return newHead;
}

/* ************************************************************************** */

// Specific constructors (List)
template<typename Data>
List<Data>::List(const TraversableContainer<Data>& con) {
    con.Traverse([this](const Data& dato) { InsertAtBack(dato); });
}

template<typename Data>
List<Data>::List(MappableContainer<Data>&& con) {
    con.Map([this](Data& dato) { InsertAtBack(std::move(dato)); });
}

/* ************************************************************************** */

// Copy constructor (List)
template <typename Data>
List<Data>::List(const List<Data>& other) {
    CopyList(other);
}

// Move constructor (List)
template<typename Data>
List<Data>::List(List<Data>&& lst) noexcept {
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
}

/* ************************************************************************** */

// Destructor (List)
template<typename Data>
List<Data>::~List() {
    DeleteList();
}

/* ************************************************************************** */

// Copy assignment (List)
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& other) {
    if (this != &other) {
        Clear();
        CopyList(other);
    }
    return *this;
}

// Move assignment (List)
template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& lst) noexcept {
    std::swap(head, lst.head);
    std::swap(tail, lst.tail);
    std::swap(size, lst.size);
    return *this;
}

/* ************************************************************************** */

// Comparison operators (List)
template <typename Data>
bool List<Data>::operator==(const List<Data>& other) const noexcept {
    if (size != other.size) return false;
    Node* a = head;
    Node* b = other.head;
    while (a && b) {
        if (!(a->element == b->element)) return false;
        a = a->next;
        b = b->next;
    }
    return true;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data>& other) const noexcept {
    return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (List)
template <typename Data>
void List<Data>::InsertAtFront(const Data& dato) {
    Node* nuovo = new Node(dato);
    nuovo->next = head;
    head = nuovo;
    if (!tail) tail = head;
    ++size;
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& dato) {
    Node* nuovo = new Node(std::move(dato));
    nuovo->next = head;
    head = nuovo;
    if (!tail) tail = head;
    ++size;
}

template<typename Data>
void List<Data>::RemoveFromFront() {
    CheckEmpty("Access to an empty list.");
    Node* toDelete = head;
    if (head->next == nullptr) {
        tail = nullptr;
        head = nullptr;
    } else {
        head = head->next;
    }
    toDelete->next = nullptr;
    delete toDelete;
    --size;
}

template<typename Data>
Data List<Data>::FrontNRemove() {
    CheckEmpty("Access to an empty list.");
    Node* victim = head;
    Data extracted_data = std::move(victim->element);
    if (victim->next == nullptr) {
        tail = nullptr;
        head = nullptr;
    } else {
        head = victim->next;
    }
    victim->next = nullptr;
    delete victim;
    --size;
    return extracted_data;
}

template<typename Data>
void List<Data>::InsertAtBack(const Data& dato) {
    Node* newNode = new Node(dato);
    AppendNode(newNode);
}

template<typename Data>
void List<Data>::InsertAtBack(Data&& dato) {
    Node* newNode = new Node(std::move(dato));
    AppendNode(newNode);
}

template<typename Data>
void List<Data>::RemoveFromBack() {
    CheckEmpty("Access to an empty list.");
    RemoveLastNode();
}

template<typename Data>
Data List<Data>::BackNRemove() {
    CheckEmpty("Access to an empty list.");
    Node* victim = tail;
    Data extracted_data = std::move(victim->element);
    RemoveLastNode();
    return extracted_data;
}

/* ************************************************************************** */

// Specific member functions (inherited from MutableLinearContainer)
template <typename Data>
Data& List<Data>::operator[](const unsigned long i) {
    Node* node = GetNodeAt(i);
    return node->element;
}

template <typename Data>
Data& List<Data>::Front() {
    CheckEmpty("Access to an empty list.");
    return head->element;
}

template <typename Data>
Data& List<Data>::Back() {
    CheckEmpty("Access to an empty list.");
    return tail->element;
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)
template<typename Data>
const Data& List<Data>::operator[](const unsigned long i) const {
    Node* node = GetNodeAt(i);
    return node->element;
}

template <typename Data>
const Data& List<Data>::Front() const {
    CheckEmpty("Access to an empty list.");
    return head->element;
}

template <typename Data>
const Data& List<Data>::Back() const {
    CheckEmpty("Access to an empty list.");
    return tail->element;
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)
template<typename Data>
inline void List<Data>::Map(MapFun fun) {
    PreOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)
template<typename Data>
inline void List<Data>::PreOrderMap(MapFun fun) {
    PreOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderMappableContainer)
template<typename Data>
inline void List<Data>::PostOrderMap(MapFun fun) {
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
template <typename Data>
void List<Data>::Clear() {
    DeleteList();
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for TraversableContainer)
template<typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* current) const {
    for (; current != nullptr; current = current->next) {
        fun(current->element);
    }
}

template<typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* current) const {
    if (current != nullptr) {
        PostOrderTraverse(fun, current->next);
        fun(current->element);
    }
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for MappableContainer)
template<typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node* current) {
    for (; current != nullptr; current = current->next) {
        fun(current->element);
    }
}

template<typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node* current) {
    if (current != nullptr) {
        PostOrderMap(fun, current->next);
        fun(current->element);
    }
}

/* ************************************************************************** */

// New Auxiliary member functions (List)
template<typename Data>
void List<Data>::CopyList(const List& other) {
    if (other.head) {
        Node* curr = other.head;
        head = new Node(curr->element);
        Node* thisCurr = head;
        curr = curr->next;
        while (curr) {
            thisCurr->next = new Node(curr->element);
            thisCurr = thisCurr->next;
            curr = curr->next;
        }
        tail = thisCurr;
        size = other.size;
    }
}

template<typename Data>
void List<Data>::DeleteList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template<typename Data>
void List<Data>::AppendNode(Node* newNode) {
    newNode->next = nullptr;
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template<typename Data>
void List<Data>::RemoveLastNode() {
    Node* toDelete = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        Node* prev = head;
        while (prev->next != tail) {
            prev = prev->next;
        }
        prev->next = nullptr;
        tail = prev;
    }
    toDelete->next = nullptr;
    delete toDelete;
    --size;
}

template<typename Data>
typename List<Data>::Node* List<Data>::GetNodeAt(unsigned long i) const {
    if (i >= size) {
        throw std::out_of_range("Accesso all'indice " + std::to_string(i) + " ma la dimensione Lista = " + std::to_string(size));
    }
    Node* current = head;
    for (unsigned long j = 0; j < i; j++, current = current->next) {}
    return current;
}

template<typename Data>
void List<Data>::CheckEmpty(const char* msg) const {
    if (head == nullptr) {
        throw std::length_error(msg);
    }
}

/* ************************************************************************** */

}

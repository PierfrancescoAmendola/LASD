#include "list.hpp"
#include <stdexcept>
namespace lasd
{
 
    /* ================================== COSTRUTTORI E DISTRUTTORE (Node) ================================== */
 
    template <typename Data>
    List<Data>::Node::Node(Data &&newElements) noexcept 
    {
        std::swap(elements, newElements);
    }
 
    template <typename Data>
    List<Data>::Node::Node(const Data &newElements)
    {
        elements = newElements;
    }
 
  
    template <typename Data>
    List<Data>::Node::Node(Node &&newNode) noexcept
    {
        std::swap(elements, newNode.elements);
        std::swap(next, newNode.next);
    }
 
    template <typename Data>
    List<Data>::Node::Node(const Node & newNode)
    {
        elements = newNode.elements;
        next = newNode.next;
    }
 
 
 
    template <typename Data>
    List<Data>::Node::~Node()
    {
        delete next;
    }
 
     /* ================================== OPERATORI DI COMPARAZIONE E ASSEGNAZIONE (Node)================================== */
 
    template <typename Data>
    inline bool List<Data>::Node::operator==(const Node &other) const noexcept
    {
        if(elements != other.elements)
            return false; 
 
        bool NextNull = (next == nullptr);
        bool OnextNull = (other.next == nullptr);
 
        if(NextNull != OnextNull)
            return false; 
 
        if(!NextNull && !OnextNull)
            return (*next == *other.next);
        
        return true;
    }
 
    template <typename Data>
    inline bool List<Data>::Node::operator!=(const Node &other) const noexcept
    {
        return !(other.elements == elements);
    }
 
     /* ================================== COSTRUTTORI E DISTRUTTORE (List) ================================== */
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data> &container)
    {
        container.Traverse(
            [this](const Data &val)
            { InsertAtBack(val); 
            });
    }
 
    template <typename Data>
    List<Data>::List(MappableContainer<Data> &&container) noexcept
    {
        container.Map(
            [this](Data &val)
            {
                InsertAtBack(std::move(val));
            });
    }
 
    template <typename Data>
    List<Data>::List(const List<Data> &other)
    {
        CopyFrom(other);
    }
 
    template <typename Data>
    List<Data>::List(List<Data> &&other) noexcept
    {
        MoveFrom(std::move(other));
    }
 
    template <typename Data>
    List<Data>::~List()
    {
        delete head;
    }
 
     /* ================================== OPERATORI DI CONFRONTO E ASSEGNAMENTO (List) ================================== */
    template <typename Data>
    List<Data> &List<Data>::operator=(const List &other)
    {
        if (this != &other)
        {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }
 
    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        MoveFrom(std::move(other));
        return *this;
    }
 
    template <typename Data>
    bool List<Data>::operator==(const List &other) const noexcept
    {
        if (size != other.size)
            return false;
 
        if(head == nullptr && other.head == nullptr)
            {
                return true;
            }
        
        if(head == nullptr || other.head == nullptr)
            return false;
        
        return *head == *other.head;
    }
 
    template <typename Data>
    bool List<Data>::operator!=(const List &other) const noexcept
    {
        return !(*this == other);
    }
 
    template <typename Data>
    void List<Data>::InsertAtFront(const Data &data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
            tail = head;
 
        size++;
    }
 
     /* ================================== FUNZIONI DI INSERIMENTO E RIMOZIONE ================================== */
 
    template <typename Data>
    void List<Data>::InsertAtFront(Data &&data)
    {
        Node *newNode = new Node(std::move(data));
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
            tail = head;
 
        size++;
    }
 
    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        Node *temp = head;
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
            head = head->next;
        size--;
        temp->next = nullptr;
        delete temp;
    }
 
    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        Node *temp = head;
        Data data = std::move(temp->elements);
        RemoveFromFront();
        return data;
    }
 
    template <typename Data>
    void List<Data>::InsertAtBack(const Data &data)
    {
 
        Node *newNode = new Node(data);
        if (tail != nullptr)
            tail->next = newNode;
        else
            head = newNode;
 
        tail = newNode;
        size++;
    }
 
    template <typename Data>
    void List<Data>::InsertAtBack(Data &&data) 
    {
        Node *newNode = new Node(std::move(data));
        if (tail != nullptr)
            tail->next = newNode;
        else
            head = newNode;
 
        tail = newNode;
        size++;
    }
 
    template <typename Data>
    void List<Data>::RemoveFromBack()
    {
        if (tail == nullptr)
        {
            throw std::length_error("La Lista e' vuota!");
        }
 
        Node *temp = head;
 
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            temp->next = nullptr;
            delete tail;
            tail = temp;
        }
 
        size--;
    }
 
    template <typename Data>
    Data List<Data>::BackNRemove()
    {
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        Data data = Back();
        RemoveFromBack();
        return data;
    }
 
     /* ================================== FUNZIONI DI ACCESSO ================================== */
 
    template <typename Data>
    Data &List<Data>::operator[](unsigned long int  i)
    {
        if (i >= size)
            throw std::out_of_range("Oltre la dimensione");
 
        Node *curr = head;
        unsigned long int  index = i;
        while (index-- > 0)
            curr = curr->next;
        return curr->elements;
    }
 
    template <typename Data>
    Data &List<Data>::Front()
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        return head->elements;
    }
 
    template <typename Data>
    Data &List<Data>::Back()
    {
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        return tail->elements;
    }
 
    template <typename Data>
    const Data &List<Data>::operator[](unsigned long int  i) const
    {
        if (i >= size)
            throw std::out_of_range("Oltre la dimensione");
 
        Node *curr = head;
        while (i-- > 0)
            curr = curr->next;
 
        return curr->elements;
    }
 
    template <typename Data>
    const Data &List<Data>::Front() const
    {
        if (head == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        return head->elements;
    }
 
    template <typename Data>
    const Data &List<Data>::Back() const
    {
        if (tail == nullptr)
            throw std::length_error("La Lista e' vuota!");
 
        return tail->elements;
    }
 
         /* ============================================================================== */
 
    template <typename Data>
    void List<Data>::Map(MapFun fun) noexcept
    {
        PreOrderMap(fun);
    }
 
    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun) noexcept
    {
      for(unsigned long int i =0; i<size; i++)
         fun( (*this)[i] );
    }
 
    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun) noexcept
    {
      for(unsigned long int i =size-1; i>=0; i--)
         fun( (*this)[i] );
    }
 
    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const
    {
         PreOrderTraverse(fun);
    }
 
    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const
    {
 
        Node *curr = head;
 
        while (curr != nullptr)
        {
            fun(curr->elements);
            curr = curr->next;
        }
    }
    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const
    {
 
        std::function<void(Node *)> helper = [&](Node *node)
        {
            if (node != nullptr)
            {
                helper(node->next);
                fun(node->elements);
            }
        };
        helper(head);
    }
    template <typename Data>
    void List<Data>::Clear() noexcept
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
 
    template <typename Data>
    void List<Data>::MoveFrom(List<Data> &&other) noexcept //metodo che scambia 2 liste
    {
        std::swap(size, other.size);
        std::swap(head, other.head);
        std::swap(tail, other.tail);
     }
 
    template <typename Data>
    void List<Data>::CopyFrom(const List &other) //metodo che copia 2 liste
    {
        Node *curr = other.head;
        while (curr != nullptr)
        {
            InsertAtBack(curr->elements);
            curr = curr->next;
        }
    }
 
 
    /* ************************************************************************ */
 
}
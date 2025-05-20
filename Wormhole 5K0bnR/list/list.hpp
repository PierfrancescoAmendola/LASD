
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */
 
#include "../container/linear.hpp"
 
/* ************************************************************************** */
 
namespace lasd
{
 
  /* ************************************************************************** */
 
  template <typename Data>
  class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer //ereditarietà
  {
    // Must extend MutableLinearContainer<Data>,
    //             ClearableContainer
 
  private:
    // ...
 
  protected:
    // using Container::???;
    using Container::size; //eredita da Container la var size
 
    struct Node
    {
      /*un nodo è composto da una parte contenente il dato (int, float, double, string .....) e da 
      una seconda parte contenente il linker al nodo successivo che di norma deve essere inizializzato
      a NULL (in c++: nullptr) visto che il primo nodo è sia quello di testa che di coda (quindi non ha successore)*/
 
      Data elements; //questo è l'elemento del nodo
 
      Node *next = nullptr; //link al successore
 
      /* ********************************************************************** */
 
      Node(Data &&) noexcept; //costruttore
 
      Node(const Data &); //costruttore
      
      /* ********************************************************************** */
 
      // Move constructor
      Node(Node &&) noexcept;
      
      // Copy constructor
      Node(const Node &);
 
      /* ********************************************************************** */
 
      virtual ~Node(); //distruttore
 
      /* ********************************************************************** */
 
      
      bool operator==(const Node &) const noexcept; //op. comparazione ==
 
      bool operator!=(const Node &) const noexcept; //op. comparazione !=
 
      /* ********************************************************************** */
 
      // Specific member functions
 
      // ...
    };
    Node *head = nullptr;
    Node *tail = nullptr;
 
    // ...
 
  public:
   
    List() = default; //costruttore di default 
 
    /* ************************************************************************ */
 
    // Specific constructor
    List(const TraversableContainer<Data> &); //costruttore di una lista ottenuta da un TraversableContainer
    
    List(MappableContainer<Data> &&) noexcept; //costruttore di una lista ottenuta da un Mappable
 
    /* ************************************************************************ */
 
    // Copy constructor
    List(const List &);
 
    // Move constructor
    List(List &&) noexcept;
 
    /* ************************************************************************ */
 
    // Destructor
    virtual ~List();
 
    /* ************************************************************************ */
 
    // Copy assignment
    List &operator=(const List &);
    // Move assignment
    List &operator=(List &&) noexcept;
    /* ************************************************************************ */
 
    // Comparison operators
    bool operator==(const List &) const noexcept;
    bool operator!=(const List &) const noexcept;
 
    /* ************************************************************************ */
 
    virtual void InsertAtFront(const Data &); //inserimento in testa per copia
  
    virtual void InsertAtFront(Data &&); //stessa cosa, per move
 
    virtual void RemoveFromFront(); //rimozione dalla testa
 
    virtual Data FrontNRemove(); //rimozione dalla testa restituendo il dato
 
    virtual void InsertAtBack(const Data &); //inserimento in coda per coda
 
    virtual void InsertAtBack(Data &&); //inserimento in coda per move
 
    virtual void RemoveFromBack(); //rimozione dalla coda
 
    virtual Data BackNRemove(); //rimozione dalla coda restituendo il dato
 
    // Specific member functions (inherited from MutableLinearContainer)
 
    Data &operator[](unsigned long) override; // Override MutableLinearContainer member. Accesso all'elemento per indice 
 
    Data &Front() override;  // Override MutableLinearContainer member. Accesso al primo elemento
 
    Data &Back() override; // Override MutableLinearContainer member. Accesso all'ultimo elemento
    /* ************************************************************************ */
 
    // Specific member functions (inherited from LinearContainer)
    /*per la descrizione del funzionamento vedi righe da 130 a 134*/
 
    const Data &operator[](unsigned long) const override; // Override LinearContainer member
    const Data &Front() const override; // Override LinearContainer member
    const Data &Back() const override; // Override LinearContainer member
    /* ************************************************************************ */
 
    // Specific member function (inherited from MappableContainer)
 
    using typename MappableContainer<Data>::MapFun;
 
    void Map(MapFun) noexcept override;  // Override MappableContainer member
 
    /* ************************************************************************ */
 
    // Specific member function (inherited from PreOrderMappableContainer)
 
    void PreOrderMap(MapFun) noexcept override; // Override PreOrderMappableContainer member
    /* ************************************************************************ */
 
    // Specific member function (inherited from PostOrderMappableContainer)
 
    void PostOrderMap(MapFun) noexcept override;  // Override PostOrderMappableContainer member
    /* ************************************************************************ */
 
    // Specific member function (inherited from TraversableContainer)
 
    using typename TraversableContainer<Data>::TraverseFun;
 
    void Traverse(TraverseFun) const override; // Override TraversableContainer member
 
    /* ************************************************************************ */
 
    // Specific member function (inherited from PreOrderTraversableContainer)
 
    void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member
 
    /* ************************************************************************ */
 
    // Specific member function (inherited from PostOrderTraversableContainer)
 
    void PostOrderTraverse(TraverseFun) const override;
 
    /* ************************************************************************ */
 
    // Specific member function (inherited from ClearableContainer)
 
    void Clear() noexcept override; // Override ClearableContainer member
 
    /* ************************************************************************ */
 
    
 
  protected:
  
    void CopyFrom(const List &);
    void MoveFrom(List &&) noexcept;
  };
 
  /* ************************************************************************** */
 
}
 
#include "list.cpp"

#endif

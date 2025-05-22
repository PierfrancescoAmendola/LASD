//
//  list.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//


#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>, virtual public ClearableContainer{
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;
    using Container :: size;



  struct Node {

    // Data
    // ...
      Data element;
      Node * next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    // ...
      inline Node () = default;
      inline Node(const Data & dat) : element(dat){};
      inline Node(Data&&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    // ...
      inline Node(const Node& nod): element(nod.element){}

    // Move constructor
    // ...
      inline Node(Node&& nod)noexcept;

    /* ********************************************************************** */

    // Destructor
    // ...
      virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    // ...
      bool operator==(const Node &) const noexcept;
      inline bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
      
    // ...
      virtual Node * Clone(Node *);


  };
    
    Node * head = nullptr;
    Node * tail = nullptr;

  // ...

public:

  // Default constructor
  // List() specifiers;
    List() = default; 

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
    List(const TraversableContainer<Data>&);
  // List(argument) specifiers; // A list obtained from a MappableContainer
    List (MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  // List(argument) specifiers;
    List(const List &);

  // Move constructor
  // List(argument) specifiers;
    List (List&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~List() specifiers;
    virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
    inline List& operator = (const List&);
  // Move assignment
  // type operator=(argument) specifiers;
    inline List& operator = (List&&) noexcept;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
    inline bool operator == (const List& ) const noexcept;
  // type operator!=(argument) specifiers;
    inline bool operator != (const List& ) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type InsertAtFront(argument) specifier; // Copy of the value
    void InsertAtFront (const Data&);
  // type InsertAtFront(argument) specifier; // Move of the value
    void InsertAtFront (Data&&);
  // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
    void RemoveFromFront();
  // type FrontNRemove() specifier; // (must throw std::length_error when empty)
    Data FrontNRemove();

  // type InsertAtBack(argument) specifier; // Copy of the value
    void InsertAtBack (const Data&);
  // type InsertAtBack(argument) specifier; // Move of the value
    void InsertAtBack (Data&&);
  // type RemoveFromBack() specifier; // (must throw std::length_error when empty)
    void RemoveFromBack();
  // type BackNRemove() specifier; // (must throw std::length_error when empty)
    Data BackNRemove();

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
    Data & operator[](const unsigned long ) override;

  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
    Data & Front() override;

  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
    Data & Back() override;


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
    const Data & operator[](const unsigned long ) const override;

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    const Data & Front() const override;

  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    const Data & Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;
    using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member
    void Map(MapFun) override;


  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
    void PreOrderMap(MapFun) override;


  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
    void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
    

  // using typename TraversableContainer<Data>::TraverseFun;
    using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
    void Traverse(TraverseFun) const override;


  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
    void PreOrderTraverse(TraverseFun) const override;


  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
    void PostOrderTraverse(TraverseFun) const override;


  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
    void Clear() override;


protected:

  // Auxiliary functions, if necessary! bisonga chiedere al prof
    inline void PreOrderTraverse(TraverseFun, const Node *) const;
    void PostOrderTraverse(TraverseFun, const Node *) const;

    /* ************************************************************************ */

    // Auxiliary member functions (for MappableContainer)

    void PreOrderMap(MapFun, Node *);
    void PostOrderMap(MapFun, Node *);

    //Funzioni ausiliarie per ridurre il codice duplicato
    
    // Copia tutti i nodi da un'altra lista, creando nuovi nodi (profondamente).
void CopyList(const List&);

// Cancella tutti i nodi della lista e libera la memoria.
void DeleteList();

// Aggiunge un nuovo nodo in fondo alla lista (append).
void AppendNode(Node*);

// Rimuove l'ultimo nodo dalla lista.
void RemoveLastNode();

// Restituisce il puntatore al nodo in posizione 'index' (0-based).
// Lancia eccezione se l'indice è fuori dal range.
Node* GetNodeAt(unsigned long) const;

// Controlla se la lista è vuota; se sì, lancia eccezione con il messaggio fornito.
void CheckEmpty(const char*) const;



};

/* ************************************************************************** */

}

#include "list.cpp"

#endif

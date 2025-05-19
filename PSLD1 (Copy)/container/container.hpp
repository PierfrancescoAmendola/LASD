//
//  container.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  // ...
    
  /* ************************************************************************ */

  // Default constructor
  Container() = default; //questo è il costruttore di default, che non fa nulla
  // Container() specifiers;
  unsigned long size = 0; //dimensione del container, inizialmente 0

public:

  // Destructor
  // ~Container() specifiers
  virtual ~Container() = default; //questo è il distruttore di default, che non fa nulla
  
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    Container& operator=(const Container&) = delete; //& riferimento a un oggetto esistente
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  //non uso const perchè si tratta di move quindi verrà modificato
    Container& operator = ( Container&& ) noexcept = delete; //&& riferimento a un oggetto temporaneo

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const Container&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const Container&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Empty() specifiers; // (concrete function should not throw exceptions)
    inline virtual bool Empty() const noexcept {return size==0;} //questo è il metodo Empty, che restituisce true se la dimensione è 0, altrimenti false
  // type Size() specifiers; // (concrete function should not throw exceptions)

   inline virtual unsigned long Size() const noexcept {return size;} //questo è il metodo Size, che restituisce la dimensione del container
};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~ClearableContainer() specifiers
    ~ClearableContainer() = default; //questo è il distruttore di default, che non fa nulla
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    ClearableContainer&  operator = (const ClearableContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    ClearableContainer& operator = (ClearableContainer &&) = delete;


  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const ClearableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const ClearableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Clear() specifiers;
    virtual void Clear() = 0 ;

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~ResizableContainer() specifiers
    
    virtual ~ResizableContainer () = default ;
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    ResizableContainer& operator = (const ResizableContainer&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    ResizableContainer& operator = (ResizableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const ResizableContainer&)  const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const ResizableContainer&)  const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
    
  // type Resize(argument) specifiers;
    virtual void Resize(unsigned long) = 0 ; //questo è il metodo Resize, che modifica la dimensione del container

    
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
//nel caso mettere exception in clear
    inline void Clear() override {Resize(0);} // Override ClearableContainer member
  // type Clear() specifiers; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#endif



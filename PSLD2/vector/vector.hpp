//
//  vector.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */
#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>, virtual public ResizableContainer
{
  // Must extend MutableLinearContainer<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  Data* elements = nullptr; // Puntatore a un array di Data
  //unsigned long i = 0;
  // ...

public:
  

  // Default constructor
  Vector () = default; //così definiamo il costruttore di default, che non fa nulla
  // Vector() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // Vector(argument) specifiers; // A vector with a given initial dimension
  
  Vector(const unsigned long);
  // Vector(argument) specifiers; // A vector obtained from a TraversableContainer

  Vector(const TraversableContainer<Data>&); //così creiamo un vettore a partire da un traversable container
    
  // Vector(argument) specifiers; // A vector obtained from a MappableContainer

  Vector( MappableContainer<Data>&&); //così creiamo un vettore a partire da un mappable container
    
  /* ************************************************************************ */

  // Copy constructor
  // Vector(argument) specifiers;
    Vector (const Vector<Data>&);
  // Move constructor
  // Vector(argument) specifiers;
    Vector (Vector<Data> &&) noexcept;
  /* ************************************************************************ */

  // Destructor
  // ~Vector() specifiers;
    virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
    Vector& operator = (const Vector&); //assegnamento di un vettore a un altro vettore
  // Move assignment
  // type operator=(argument) specifiers;
    Vector& operator = ( Vector&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
    bool operator == (const Vector &) const noexcept;
  // type operator!=(argument) specifiers;
    inline bool operator != (const Vector &) const noexcept;
  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
     Data & operator[](const unsigned long)  override;
  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
     Data& Front()  override;
  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
     Data& Back()  override;
  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
    const Data& operator[](const unsigned long) const override;
  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    const Data& Front() const override;
  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    const Data& Back() const override;
  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Override ResizableContainer member
    void Resize(const unsigned long) override;
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  // type Clear() specifiers; // Override ClearableContainer member
    void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!
  void AllocateMemory(const unsigned long); // Funzione ausiliaria per allocare memoria
  void CopyElements(Data* ,const Data*, const unsigned long); // Funzione ausiliaria per copiare gli elementi
  void ThrowIfEmpty() const; // Funzione ausiliaria per lanciare eccezioni se il vettore è vuoto

};

/* ************************************************************************** */

template <typename Data>
class SortableVector :  public  Vector<Data> , virtual public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;
    using Container:: size ;

  // ...

public:

  // Default constructor
  // SortableVector() specifiers;
     SortableVector () = default;
  /* ************************************************************************ */

  // Specific constructors
  // SortableVector(argument) specifiers; // A vector with a given initial dimension
    SortableVector(const unsigned long );
  // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
    SortableVector(const TraversableContainer<Data>&);
  // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer
    SortableVector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(argument) specifiers;
    SortableVector (const SortableVector<Data>&);
  // Move constructor
  // SortableVector(argument) specifiers;
    SortableVector(SortableVector<Data>&&) noexcept;
  /* ************************************************************************ */

  // Destructor
  // ~SortableVector() specifiers;
    virtual ~SortableVector() = default;
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
    SortableVector<Data>& operator = (const SortableVector<Data>&);
  // Move assignment
  // type operator=(argument) specifiers;
    SortableVector<Data>& operator = (SortableVector<Data>&&) noexcept;
    
protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif


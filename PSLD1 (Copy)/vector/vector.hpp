//
//  vector.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public MutableLinearContainer<Data>, virtual public ResizableContainer
  {

  private:
    //...

  protected:
    using Container::size;

    Data *elements = nullptr;

  public:
    // Default constructor
    Vector() = default;

    /* ************************************************************************ */
    // Specific constructors
    // Vector(argument) specifiers; // A vector with a given initial dimension

    Vector(const unsigned long);
    // Vector(argument) specifiers; // A vector obtained from a TraversableContainer

    Vector(const TraversableContainer<Data> &); // così creiamo un vettore a partire da un traversable container

    // Vector(argument) specifiers; // A vector obtained from a MappableContainer

    Vector(MappableContainer<Data> &&); // così creiamo un vettore a partire da un mappable container

    /* ************************************************************************ */

    // Copy constructor
    //  Vector(argument) specifiers;
    Vector(const Vector<Data> &);
    // Move constructor
    // Vector(argument) specifiers;
    Vector(Vector<Data> &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~Vector();

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    inline Vector<Data> &operator=(const Vector<Data> &);

    // Move assignment
    // type operator=(argument) specifiers;

    inline Vector<Data> &operator=(Vector<Data> &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const Vector<Data> &) const noexcept;
    inline bool operator!=(const Vector<Data> &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)

    // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
    inline Data &operator[](unsigned long) override;
    // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
    inline Data &Front() override;
    // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
    inline Data &Back() override;
    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    inline const Data &operator[](unsigned long) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

    inline const Data &Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

    inline const Data &Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member function (inherited from ResizableContainer)

    // type Resize(argument) specifiers; // Override ResizableContainer member

    inline void Resize(const unsigned long newSize) override; // Override ResizableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    inline void Clear() override; // Override ClearableContainer member

  protected:
    // Funzioni ausiliarie, se necessarie
  };

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data>
  {

  private:
    //....

  protected:
    using Container::size;

  public:
    // Default constructor
    // SortableVector() specifiers;

    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    // SortableVector(argument) specifiers; // A vector with a given initial dimension
    inline SortableVector(unsigned long initialSize) : Vector<Data>(initialSize) {};
    // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
    inline SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container) {};
    // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer
    inline SortableVector(MappableContainer<Data> &&container) : Vector<Data>(std::move(container)) {};
    /* ************************************************************************ */

    // Copy constructor
    // SortableVector(argument) specifiers;

    inline explicit SortableVector(const SortableVector<Data> &Svector) : Vector<Data>(Svector) {};

    // Move constructor
    // SortableVector(argument) specifiers;

    inline explicit SortableVector(SortableVector<Data> &&Svector) noexcept : Vector<Data>(std::move(Svector)) {};

    /* ************************************************************************ */

    // Destructor
    ~SortableVector() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    inline SortableVector<Data> &operator=(const SortableVector<Data> &);

    // Move assignment
    // type operator=(argument) specifiers;

    inline SortableVector<Data> &operator=(SortableVector<Data> &&) noexcept;

  protected:
    // Auxiliary functions, if necessary!
  };

  /* ************************************************************************** */

}

#include "vector.cpp"

#endif
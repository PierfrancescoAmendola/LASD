#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

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

  using Container::size;
	Data* elements = nullptr;

public:

  // Default constructor
  Vector() =default;

  /* ************************************************************************ */

  // Specific constructors
  inline Vector(unsigned long int) ; // A vector with a given initial dimension
  inline Vector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  inline Vector(MappableContainer<Data>&&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  inline Vector(const Vector<Data>&);

  // Move constructor
  inline Vector(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  inline Vector& operator=(const Vector<Data>&);

  // Move assignment
  inline Vector& operator=(Vector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const Vector<Data>&) const noexcept;
  inline bool operator!=(const Vector<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  inline Data& operator[](unsigned long int i) override ; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  inline Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  inline Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data& operator[](unsigned long int) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  inline const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  inline void Resize(unsigned long int) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : 
  virtual public Vector<Data>, 
  virtual public SortableLinearContainer<Data>
{
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:
  
  using Container::size;
  using Vector<Data>::elements;
  using Vector<Data>::Vector;
  // ...

public:

  // Default constructor
  SortableVector() =default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(unsigned long int); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data>&); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data>&&) noexcept; // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data>&);

  // Move constructor
  SortableVector(SortableVector<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() =default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector<Data>& operator=(const SortableVector<Data>&);

  // Move assignment
  SortableVector<Data>& operator=(SortableVector<Data>&&) noexcept;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif


#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */
#include "traversable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : 
  virtual public PreOrderTraversableContainer<Data>, 
  virtual public PostOrderTraversableContainer<Data>
{
  // Must extend PreOrderTraversableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  using Container::size;


public:

  using Container::Empty;
  // Destructor
  virtual ~LinearContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer&  operator=(LinearContainer&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const LinearContainer&)const noexcept; // Comparison of abstract types is possible.
  inline bool operator!=(const LinearContainer&)const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator[](unsigned long int i) const =0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual const Data& Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  inline virtual const Data& Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : 
  virtual public LinearContainer<Data>, 
  virtual public PreOrderMappableContainer<Data>, 
  virtual public PostOrderMappableContainer<Data>
{
  // Must extend LinearContainer<Data>,
  //             PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:
  using Container::size;
  // ...

public:

  // Destructor
  virtual ~MutableLinearContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer& operator=(const MutableLinearContainer&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer&  operator=(MutableLinearContainer&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  using Container::Empty;

  virtual Data& operator[](unsigned long int) =0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline virtual Data& Front(); // (mutable version; concrete function must throw std::length_error when empty)

  inline virtual Data& Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  inline void Map(MapFun) noexcept override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun) noexcept override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun) noexcept override; // Override PostOrderMappableContainer member

};

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data>
{
  // Must extend MutableLinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~SortableLinearContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer<Data>&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer<Data>&&)noexcept =delete; // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  // Specific member function
  using  MutableLinearContainer<Data>::operator[];
  virtual void Sort() noexcept;

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif

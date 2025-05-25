
#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SortableLinearContainer<Data>, virtual public ClearableContainer{
  // Must extend SortableLinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  // ~Heap() specifiers
  virtual ~Heap() = default; // Destructor of abstract types is not possible.

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  Heap& operator=(const Heap<Data>&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  Heap& operator =(Heap<Data>&&)= delete;

  /* ************************************************************************ */

  // Specific member functions

  // type IsHeap(argument) specifiers;

  // type Heapify(argument) specifiers;

};

/* ************************************************************************** */

}

#endif

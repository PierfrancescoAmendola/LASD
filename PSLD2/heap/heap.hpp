//
//  heap.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//


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
  virtual ~Heap() = default;
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  Heap& operator=(const Heap<Data>&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  Heap& operator =(Heap<Data>&&)= delete;

  /* ************************************************************************ */

  // Specific member functions

  // type IsHeap(argument) specifiers;
  virtual bool IsHeap() const = 0; // Check if the container is a heap

  // type Heapify(argument) specifiers;
  virtual void Heapify() = 0; // Transform the container into a heap

  /* 1)La funzione IsHeap() dovrebbe controllare se la struttura dati corrente soddisfa la proprietà di heap 
  (in base all'implementazione potrebbe essere un min-heap o un max-heap).
  2) La funzione Heapify() dovrebbe riorganizzare gli elementi nella struttura dati 
  per garantire che soddisfino la proprietà di heap.
  */ 

};

/* ************************************************************************** */

}

#endif

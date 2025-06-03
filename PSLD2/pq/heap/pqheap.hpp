//
//  pqheap.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//


#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, virtual public HeapVec<Data> {
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  unsigned long capacity=0; 


  // ...

public:

  // Default constructor
  // PQHeap() specifiers;
  PQHeap() = default;

  /* ************************************************************************ */

  // Specific constructors
  // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
  PQHeap(const TraversableContainer<Data>&);
  // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer
  PQHeap(MappableContainer<Data>&&);

  /* ************************************************************************ */

  // Copy constructor
  // PQHeap(argument) specifiers;
  PQHeap(const PQHeap<Data>&);

  // Move constructor
  // PQHeap(argument) specifiers;
  PQHeap(PQHeap<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~PQHeap() specifiers;
  virtual ~PQHeap()= default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  PQHeap& operator=(const PQHeap<Data>&) ;
  // Move assignment
  // type operator=(argument) specifiers;
  PQHeap& operator=(PQHeap<Data>&&) noexcept;


  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  Data Tip() const override;
  // type RemoveTip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override;
  // type TipNRemove(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override;

  // type Insert(argument) specifiers; // Override PQ member (Copy of the value)
  void Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override PQ member (Move of the value)
  void Insert(Data&&) override;

  // type Change(argument) specifiers; // Override PQ member (Copy of the value)
  void Change(unsigned long, const Data&) override; // Override PQ member (Change priority at index)
  // type Change(argument) specifiers; // Override PQ member (Move of the value)
  void Change(unsigned long, Data&&) override; // Override PQ member (Change priority at index)

  void Clear() noexcept override;

protected:

  // Auxiliary functions, if necessary!
  // type HeapifyUp(argument) specifiers; // Riorganizza l'heap verso l'alto
  void HeapifyUp(unsigned long );
  void HeapifyDown(unsigned long );


};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif


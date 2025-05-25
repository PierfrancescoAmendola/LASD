
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
  virtual ~PQHeap();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline PQHeap<Data>& operator=(const PQHeap<Data>&) ;
  // Move assignment
  // type operator=(argument) specifiers;
  inline PQHeap<Data>& operator=(PQHeap<Data>&&) noexcept;


  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  // type RemoveTip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  // type TipNRemove(argument) specifiers; // Override PQ member (must throw std::length_error when empty)

  // type Insert(argument) specifiers; // Override PQ member (Copy of the value)
  virtual bool Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override PQ member (Move of the value)
  virtual bool Insert(Data&&) override;

  // type Change(argument) specifiers; // Override PQ member (Copy of the value)
  // type Change(argument) specifiers; // Override PQ member (Move of the value)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif

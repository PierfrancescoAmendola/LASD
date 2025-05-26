
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>, virtual public Vector<Data> {
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container :: size;
  using Vector<Data>::elements; // Elements is the array of Data in Vector<Data>

  // ...

public:

  // Default constructor
  // HeapVec() specifiers;
  HeapVec() = default; // Default constructor of abstract types is not possible.

  /* ************************************************************************ */

  // Specific constructors
  // HeapVec(argument) specifiers; // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data>&);
  // HeapVec(argument) specifiers; // A heap obtained from a MappableContainer
  HeapVec (MappableContainer<Data>&&);
  /* ************************************************************************ */

  // Copy constructor
  // HeapVec(argument) specifiers;
  HeapVec(const HeapVec<Data>&);
  // Move constructor
  // HeapVec(argument) specifiers;
  HeapVec(HeapVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~HeapVec() specifiers;
  virtual ~HeapVec();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  inline HeapVec<Data>& operator=(const HeapVec<Data>&);

  // Move assignment
  // type operator=(argument) specifiers;
  inline HeapVec<Data>& operator=(HeapVec<Data>&&);


  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  inline bool operator == (const HeapVec<Data>&) const noexcept;
  // type operator!=(argument) specifiers;
  inline bool operator != (const HeapVec<Data>&) const noexcept;
  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // type IsHeap(argument) specifiers; // Override Heap member
  bool IsHeap() const override; 

  // type Heapify(argument) specifiers; // Override Heap member
  void Heapify() override;

  /* ************************************************************************ */

  
  /**********************************************************************++ */
  // Specific member function (inherited from SortableLinearContainer)

  // type Sort(argument) specifiers; // Override SortableLinearContainer member
  void Sort() noexcept override; 

protected:

  // Auxiliary functions, if necessary!
  void HeapDown(ulong );
  bool IsHeapRecursive(ulong index) const;

  
};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif

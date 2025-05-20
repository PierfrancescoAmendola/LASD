
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class DictionaryContainer : virtual public TestableContainer<Data>{
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~DictionaryContainer() noexcept =default;

  /* ************************************************************************ */

  // Copy assignment
  virtual bool operator=(const DictionaryContainer&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  virtual bool operator=(DictionaryContainer&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const DictionaryContainer&) =delete; // Comparison of abstract types is not possible.
  virtual bool operator!=(DictionaryContainer&&) noexcept =delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&)  =0; // Copy of the value
  virtual bool Insert(Data&&) noexcept =0; // Move of the value
  virtual bool Remove(const Data&) =0;

  virtual bool InsertAll(const TraversableContainer<Data>&); // Copy of the value; From TraversableContainer; True if all are inserted
  virtual bool InsertAll(MappableContainer<Data>&&) noexcept; // Move of the value; From MappableContainer; True if all are inserted
  virtual bool RemoveAll(const TraversableContainer<Data>&); // From TraversableContainer; True if all are removed

  virtual bool InsertSome(const TraversableContainer<Data>&) ; // Copy of the value; From TraversableContainer; True if some is inserted
  virtual bool InsertSome(MappableContainer<Data>&&); // Move of the value; From MappableContainer; True if some is inserted
  virtual bool RemoveSome(const TraversableContainer<Data>&); // From TraversableContainer; True if some is removed

};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>{
  // Must extend DictionaryContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~OrderedDictionaryContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  virtual bool operator=(const OrderedDictionaryContainer&) const =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  virtual bool operator=(OrderedDictionaryContainer&&) noexcept  =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const OrderedDictionaryContainer&) const =delete; // Comparison of abstract types is not possible.
  virtual bool operator!=(const OrderedDictionaryContainer&) noexcept =delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& Min() const =0; // (concrete function must throw std::length_error when empty)
  virtual Data MinNRemove() =0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMin() =0; // (concrete function must throw std::length_error when empty)

  virtual const Data& Max() const =0; // (concrete function must throw std::length_error when empty)
  virtual Data MaxNRemove()=0; // (concrete function must throw std::length_error when empty)
  virtual void RemoveMax() =0; // (concrete function must throw std::length_error when empty)

  virtual const Data& Predecessor(const Data&) const =0; // (concrete function must throw std::length_error when not found)
  virtual Data PredecessorNRemove(const Data&) =0; // (concrete function must throw std::length_error when not found)
  virtual void RemovePredecessor(const Data&) =0; // (concrete function must throw std::length_error when not found)

  virtual const Data& Successor(const Data&) const =0; // (concrete function must throw std::length_error when not found)
  virtual Data SuccessorNRemove(const Data&) =0; // (concrete function must throw std::length_error when not found)
  virtual void RemoveSuccessor(const Data&) =0; // (concrete function must throw std::length_error when not found)

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif

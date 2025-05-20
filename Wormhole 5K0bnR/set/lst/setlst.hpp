
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetLst : virtual  public Set<Data>, virtual public List<Data>
{
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  using Container::size;

  // ...

public:

  // Default constructor
  SetLst() =default;

  /* ************************************************************************ */

  // Specific constructors
  SetLst(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetLst(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetLst(const SetLst<Data>&);

  // Move constructor
  SetLst(SetLst<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetLst();

  /* ************************************************************************ */

  // Copy assignment
  SetLst<Data>& operator=(const SetLst<Data>&);

  // Move assignment
  SetLst<Data>& operator=(SetLst<Data>&& ls) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SetLst<Data>&) const noexcept;
  inline bool operator!=(const SetLst<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  inline const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  inline const Data6 Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  inline const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  inline const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
  inline void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  inline bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
  inline bool Insert(Data&&) noexcept override; // Override DictionaryContainer member (move of the value)
  inline bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data& operator[](unsigned long int) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(cons Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  inline Node<Data>* binSearch(const Data&);

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif

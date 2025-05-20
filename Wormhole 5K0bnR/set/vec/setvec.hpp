
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../container/mappable.hpp"
#include "../../vector/vector.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>, virtual public ResizableContainer
{
  // Must extend Set<Data>,
  //             ResizableContainer

private:

  // ...

protected:

  using Container::size;
  unsigned long int count;
  Data* elements;
  unsigned long int head;
  unsigned long int tail;

public:

  // Default constructor
  SetVec();

  /* ************************************************************************ */

  // Specific constructors
  SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
  SetVec(MappableContainer<Data>&&) noexcept; // A set obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SetVec(const SetVec<Data>&);

  // Move constructor
  SetVec(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~SetVec();

  /* ************************************************************************ */

  // Copy assignment
  inline SetVec& operator=(const SetVec&);

  // Move assignment
  inline SetVec& operator=(SetVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const SetVec<Data>&) const noexcept;
  inline bool operator!=(const SetVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  inline const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
  inline void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

  inline const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
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

  inline const Data& operator[](unsigned long int i) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  inline void Resize(unsigned long int) override;

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override; // Override ClearableContainer member

  // Specific member function (inherited from Container)
  inline inline unsigned long int Size() const noexcept override {return count;} 

protected:

  // Auxiliary functions, if necessary!
	inline unsigned long int binSearch(const Data&) const;
  inline Data& at(unsigned long int); 
};

/* ************************************************************************** */

}

#include "setvec.cpp"

#endif


#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class SetVec : virtual public Set<Data>, virtual public ResizableContainer{
  // Must extend Set<Data>,
  //             ResizableContainer

private:


protected:

  // using Container::???;
   using Container::size;
   Vector<Data> vec;
   unsigned long head= 0;


   unsigned long CircularIndex(unsigned long i) const noexcept;

  // ...

public:

  // Default constructor
  // SetVec() specifiers;
    SetVec();
  /* ************************************************************************ */

  // Specific constructors
  // SetVec(argument) specifiers; // A set obtained from a TraversableContainer
    SetVec (const TraversableContainer<Data>&);
  // SetVec(argument) specifiers; // A set obtained from a MappableContainer
    SetVec(MappableContainer<Data>&);
  /* ************************************************************************ */

  // Copy constructor
  // SetVec(argument) specifiers;
    SetVec(const SetVec&);


  // Move constructor
  // SetVec(argument) specifiers;
    SetVec(SetVec&&) noexcept;
  /* ************************************************************************ */

  // Destructor
  // ~SetVec() specifiers;
    virtual ~SetVec();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
    SetVec& operator = (const SetVec&);

  // Move assignment
  // type operator=(argument) specifiers;
    SetVec& operator = ( SetVec&&);

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
    bool operator == ( const SetVec&)  const noexcept;
  // type operator!=(argument) specifiers;
    bool operator != ( const SetVec&) const noexcept ;
  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // type Min(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     const Data& Min() const override;
  // type MinNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     Data MinNRemove() override;
  // type RemoveMin(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     void RemoveMin () override;
  
  // type Max(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     const Data& Max() const override;
  // type MaxNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     Data MaxNRemove() override;
  // type RemoveMax(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     void  RemoveMax() override;

  // type Predecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     const Data& Predecessor(const Data&) const override;
  // type PredecessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     Data PredecessorNRemove(const Data&)  override;
  // type RemovePredecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     void  RemovePredecessor(const Data&)  override ;
  // type Successor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     const Data& Successor(const Data&)  const override;

  // type SuccessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     Data SuccessorNRemove(const Data&)  override;

  // type RemoveSuccessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     void RemoveSuccessor(const Data&)  override;


  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  // type Insert(argument) specifiers; // Override DictionaryContainer member (copy of the value)
     bool Insert(const Data&) override;
  // type Insert(argument) specifiers; // Override DictionaryContainer member (move of the value)
     bool Insert(Data&&) override;
  // type Remove(argument) specifiers; // Override DictionaryContainer member
     bool Remove(const Data&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
     const Data& operator[](unsigned long ) const override;
     //Data& operator[](unsigned long) override;

   

  /* ************************************************************************** */

  // Specific member function (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member
     bool Exists(const Data&) const noexcept override;
  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
     void Clear() override;
protected:

  // Auxiliary functions, if necessary!

  void Resize(unsigned long) override;
  std::pair<bool, unsigned long> BinarySearch(const Data&) const noexcept;
  /* Utility: porta il buffer in forma lineare (head == 0) */
  void Unwrap();
  void Rewrap();
  unsigned long ShiftHole(unsigned long ) noexcept;

};

/* ************************************************************************** */



}

#include "setvec.cpp"

#endif



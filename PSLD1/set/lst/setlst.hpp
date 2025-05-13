
#ifndef SETLST_HPP
#define SETLST_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>

class SetLst : virtual public Set<Data>, virtual public  List<Data>{
  // Must extend Set<Data>,
  //             List<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  using List<Data>::head;
  using List<Data>::tail;
  using typename List<Data>::Node;

  // ...

public:

  // Default constructor
  // SetLst() specifiers;
    SetLst();

  /* ************************************************************************ */

  // Specific constructors
  // SetLst(argument) specifiers; // A set obtained from a TraversableContainer
    SetLst (const TraversableContainer<Data>&);
  // SetLst(argument) specifiers; // A set obtained from a MappableContainer
    SetLst(MappableContainer<Data>&&);
  /* ************************************************************************ */

  // Copy constructor
  // SetLst(argument) specifiers;
    SetLst(const SetLst &);

  // Move constructor
  // SetLst(argument) specifiers;
    SetLst(SetLst &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~SetLst() specifiers;
    virtual ~SetLst ();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
    SetLst & operator = (const SetLst & );

  // Move assignment
  // type operator=(argument) specifiers;
    SetLst & operator = (SetLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
    bool operator == (const SetLst&) const noexcept;
  // type operator!=(argument) specifiers;
    bool operator != (const SetLst&) const noexcept;


  /* ************************************************************************ */

  // Specific member functions (inherited from OrderedDictionaryContainer)

  // type Min(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      Data& Min() const override;

  // type MinNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      Data MinNRemove() override;

  // type RemoveMin(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     void RemoveMin() override;

  // type Max(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     Data& Max() const override;

  // type MaxNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     Data MaxNRemove() override ;

  // type RemoveMax(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
     void RemoveMax() override;


  // type Predecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
    Data& Predecessor(const Data&) const override;
  // type PredecessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     Data PredecessorNRemove(const Data&) override;
  // type RemovePredecessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     void RemovePredecessor(const Data&) override;
  // type Successor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     Data& Successor(const Data&) const override;
  // type SuccessorNRemove(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
      Data SuccessorNRemove(const Data&) override;

  // type RemoveSuccessor(argument) specifiers; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
     void RemoveSuccessor(const Data&) override;

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

};

/* ************************************************************************** */

}

#include "setlst.cpp"

#endif

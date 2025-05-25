
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQ : virtual public LinearContainer<Data>, virtual public ClearableContainer{
  // Must extend LinearContainer<Data>,
  //             ClearableContainer

private:

protected:

public:

  // Destructor
  // ~PQ() specifiers
  virtual ~PQ();

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  inline PQ<Data>& operator = (const PQ<Data>&) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  inline PQ<Data>& operator = (PQ<Data>&&) = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Tip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type RemoveTip(argument) specifiers; // (concrete function must throw std::length_error when empty)
  // type TipNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)

  // type Insert(argument) specifiers; // Copy of the value
  virtual bool Insert(const Data&) = 0; // Copy of the value
  // type Insert(argument) specifiers; // Move of the value
  virtual bool Insert(Data&&) = 0; // Move of the value

  // type Change(argument) specifiers; // Copy of the value
  // type Change(argument) specifiers; // Copy of the value

};

/* ************************************************************************** */

}

#endif

//
//  dictionary.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
// 


#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"
#include "traversable.hpp"

/* ************************************************************************** */

using namespace std;
namespace lasd {

/* ************************************************************************** */

template <typename Data>

class DictionaryContainer : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...


public:

  // Destructor
  // ~DictionaryContainer() specifiers
    virtual ~DictionaryContainer() = default; // Default destructor

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

    DictionaryContainer& operator= (const DictionaryContainer& ) = delete;
  
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    DictionaryContainer& operator = (DictionaryContainer&&) noexcept = delete;

  /* ************************************************************************ */
    
  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator==(const DictionaryContainer &) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator!=(const DictionaryContainer &) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member functions

  // type Insert(argument) specifiers; // Copy of the value
    virtual bool Insert(const Data&) = 0;
  // type Insert(argument) specifiers; // Move of the value
    virtual bool Insert(Data&&) = 0;
  // type Remove(argument) specifiers;
    virtual bool Remove(const Data&) = 0;

  // type InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
    virtual bool InsertAll(const TraversableContainer<Data>&);
  // type InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
    virtual bool InsertAll(MappableContainer<Data>&&);
  // type RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed
    virtual bool RemoveAll(const TraversableContainer<Data>&);
  // type InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
    virtual bool InsertSome(const TraversableContainer<Data>&);
  // type InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
    virtual bool InsertSome(MappableContainer<Data>&&);
  // type RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
    virtual bool RemoveSome(const TraversableContainer<Data>&);
};

/* ************************************************************************** */

template <typename Data>
class OrderedDictionaryContainer : public DictionaryContainer<Data> {
  // Must extend DictionaryContainer<Data>

private:

protected:

public:

  // Destructor
    virtual ~OrderedDictionaryContainer () = default; // virtual perchè è una classe astratta
  // ~OrderedDictionaryContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    OrderedDictionaryContainer& operator= (const OrderedDictionaryContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    OrderedDictionaryContainer& operator = (OrderedDictionaryContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const OrderedDictionaryContainer& ) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const OrderedDictionaryContainer&) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member functions

  // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual Data& Min() const = 0;
  // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual Data MinNRemove() = 0;
  // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual void RemoveMin() = 0 ;
  // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual Data& Max() const = 0;
  // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual Data MaxNRemove() = 0;
  // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)
    inline virtual void RemoveMax() = 0;
  // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual Data& Predecessor(const Data&) const = 0; //Restituire un riferimento consente di accedere direttamente all'oggetto originale senza creare una copia.
  // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual Data PredecessorNRemove(const Data&) = 0; //restuito un oggetto per valore significa che viene creata una copia dell'oggetto Data restituito.
  // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual void RemovePredecessor(const Data&) = 0;
  // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual Data& Successor(const Data&) const = 0;
  // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual Data SuccessorNRemove(const Data&) = 0;
  // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    inline virtual void RemoveSuccessor(const Data&) = 0;

};

/* ************************************************************************** */

}

#include "dictionary.cpp"

#endif

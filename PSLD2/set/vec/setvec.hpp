//
//  setvec.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//


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
   //Vector<Data> vec;
   Data *elements = nullptr;
  unsigned long capacity = 0;
  unsigned long head = 0;

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
    SetVec& operator = ( SetVec&&) noexcept ;

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

   //BinarySearch
   //Ricerca binaria per trovare la posizione di un elemento in un vettore ordinato.
   unsigned long BinarySearch(const Data&) const noexcept;

   
   //MakeSpaceAt
   //Centralizza lo spostamento degli elementi per creare spazio in Insert 
   //(entrambe le versioni), sostituendo i blocchi di codice che gestiscono lo 
   //spostamento a sinistra (verso head) o a destra (verso la coda).
   void MakeSpaceAt(unsigned long) noexcept;
   
   //FillGapAt
   //Centralizza lo spostamento degli elementi per colmare un vuoto in Remove, 
   //PredecessorNRemove, SuccessorNRemove, e RemoveSuccessor.
   void FillGapAt(unsigned long) noexcept;

   //RemoveAt
   //Unifica la logica di rimozione di un elemento a una posizione specifica, 
   //gestendo lo spostamento tramite FillGapAt e il ridimensionamento del vettore. 
   //È utilizzata in PredecessorNRemove, RemovePredecessor, SuccessorNRemove, e RemoveSuccessor.
   Data RemoveAt(unsigned long) ;

   /*Implemenatare queste funzioni ha portato a dei benefici come:
   1) Riduzione della Duplicazione: I blocchi di codice per lo spostamento degli elementi sono stati centralizzati in MakeSpaceAt e FillGapAt.
   2) Unificazione della Logica di Rimozione: RemoveAt elimina la duplicazione tra PredecessorNRemove/RemovePredecessor e SuccessorNRemove/RemoveSuccessor.*/
};

/* ************************************************************************** */



}

#include "setvec.cpp"

#endif



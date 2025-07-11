//
//  mappable.hpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 02/05/25.
//


#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~MappableContainer() specifiers
    virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    MappableContainer& operator = (const MappableContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    MappableContainer& operator = (MappableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const MappableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const MappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
    
  // using MapFun = std::function<void(Data &)>;
    using MapFun = std::function<void(Data &)>;
  // type Map(argument) specifiers;
    virtual void Map(MapFun) = 0; // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PreOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PreOrderMappableContainer() specifiers
    virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    PreOrderMappableContainer& operator = (const PreOrderMappableContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    PreOrderMappableContainer& operator = (PreOrderMappableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const PreOrderMappableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const PreOrderMappableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  // using typename MappableContainer<Data>::MapFun;
    using typename MappableContainer<Data>::MapFun;
  // type PreOrderMap(argument) specifiers;
    virtual void PreOrderMap(MapFun) = 0 ; // (concrete function should not throw exceptions)
  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
    
  // type Map(argument) specifiers; // Override MappableContainer member
    inline void Map(MapFun) override;
};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PostOrderMappableContainer() specifiers
    virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    PostOrderMappableContainer& operator = (const PostOrderMappableContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    PostOrderMappableContainer& operator = (PostOrderMappableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator == (const PostOrderMappableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
    bool operator != (const PostOrderMappableContainer&) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member function

  // using typename MappableContainer<Data>::MapFun;
    using typename MappableContainer<Data>::MapFun;
  // type PostOrderMap(argument) specifiers;
    virtual void PostOrderMap(MapFun) = 0; // (concrete function should not throw exceptions)
  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // type Map(argument) specifiers; // Override MappableContainer member
    void Map(MapFun) override;
};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif

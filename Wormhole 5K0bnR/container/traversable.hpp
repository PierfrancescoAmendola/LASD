
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer  : virtual public TestableContainer<Data> {
  // Must extend TestableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~TraversableContainer() specifiers
    virtual ~TraversableContainer() = default; // Default destructor

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    TraversableContainer& operator = (const TraversableContainer&) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    TraversableContainer& operator = (TraversableContainer&&) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const TraversableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator != (const TraversableContainer&) const noexcept = delete;
  /* ************************************************************************ */

  // Specific member function

  // using TraverseFun = std::function<void(const Data &)>;
  using TraverseFun = std::function<void(const Data &)>;
  // type Traverse(arguments) specifiers;
  virtual void Traverse(TraverseFun) const = 0;
  // template <typename Accumulator>
  template <typename Accumulator>
  // using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;
  // template <typename Accumulator>
  template <typename Accumulator>
  // type Fold(arguments) specifiers;
  inline Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;
    

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
    
  // type Exists(argument) specifiers; // Override TestableContainer member
    bool Exists(const Data&) const noexcept override;
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer  : virtual public TraversableContainer<Data>
{
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PreOrderTraversableContainer() specifiers
    virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    PreOrderTraversableContainer & operator = (const PreOrderTraversableContainer & ) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    PreOrderTraversableContainer & operator= (PreOrderTraversableContainer && ) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const PreOrderTraversableContainer&) const noexcept = delete;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator != (const PreOrderTraversableContainer&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;
    using typename TraversableContainer<Data>::TraverseFun;
  // type PreOrderTraverse(arguments) specifiers;
    virtual void PreOrderTraverse(TraverseFun) const = 0;
  // template <typename Accumulator>
    template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>; //#template_FoldFun
  // template <typename Accumulator>
    template <typename Accumulator>
  // type PreOrderFold(arguments) specifiers;
    Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  // type Traverse(arguments) specifiers; // Override TraversableContainer member
    inline void Traverse(TraverseFun) const override;

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer  : virtual public TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PostOrderTraversableContainer() specifiers
    virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
    PostOrderTraversableContainer & operator = (const PostOrderTraversableContainer & ) = delete;
  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
    PostOrderTraversableContainer & operator= (PostOrderTraversableContainer && ) noexcept = delete;
  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator == (const PostOrderTraversableContainer&) const noexcept;
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.
    bool operator != (const PostOrderTraversableContainer&) const noexcept ;
  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;
    using typename TraversableContainer<Data>::TraverseFun;
  // type PostOrderTraverse(arguments) specifiers;
    virtual void PostOrderTraverse(TraverseFun) const = 0;
  // template <typename Accumulator>
    template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>; //#template_FoldFun
  // template <typename Accumulator>
    template <typename Accumulator>
  // type PostOrderFold(arguments) specifiers;
    Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
    inline void Traverse(TraverseFun) const override;

    //i template non vengono compilati, ma solo quando vengono si istanzia un oggetto di quel tipo
};

/* ************************************************************************** */

}



#include "traversable.cpp"
#endif
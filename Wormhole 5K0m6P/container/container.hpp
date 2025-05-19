
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

  // ...

protected:

  unsigned long size = 0;

  /* ************************************************************************ */

  // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.
  Container & operator=(const Container &) = delete;

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.
  Container & operator=(Container &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator==(const Container &) const noexcept = delete;

  // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.
  bool operator!=(const Container &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions

  // type Empty() specifiers; // (concrete function should not throw exceptions)
  inline virtual bool Empty() const noexcept {
    return (size == 0);
  }

  // type Size() specifiers; // (concrete function should not throw exceptions)
  inline virtual unsigned long Size() const noexcept {
    return size;
  }
};

/* ************************************************************************** */

class ClearableContainer : virtual public Container {

private:


protected:

  using Container::size;

public:

  // Destructor
  virtual ~ClearableContainer()  = default;
  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer & operator=(const ClearableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer & operator=(ClearableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Clear() specifiers;
  virtual void Clear() = 0;

};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer {
  // Must extend ClearableContainer


private:

  // ...

protected:

  using Container::size;

public:

  // Destructor
  virtual ~ResizableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer & operator=(const ResizableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer & operator=(ResizableContainer &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResizableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResizableContainer &) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(unsigned long newSize) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override { // Override ClearableContainer member
    Resize(0);
  }

};

/* ************************************************************************** */

}

#endif

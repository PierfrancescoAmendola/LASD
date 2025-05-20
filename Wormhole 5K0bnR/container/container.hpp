
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */
namespace lasd {

/* ************************************************************************** */

class Container {

private:

  

protected:

  unsigned long int size;
  /* ************************************************************************ */

  // Default constructor
  Container() =default;

public:

  // Destructor
  virtual ~Container() =default;

  /* ************************************************************************ */

  // Copy assignment
  Container& operator=(const Container&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Container& operator=(Container&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&) const noexcept =delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&) const noexcept =delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const noexcept // (concrete function should not throw exceptions)
  {
    return size == 0; //Restituisce true se size == 0, ovvero e' vuoto
  }
  
  inline virtual unsigned long int Size() const noexcept // (concrete function should not throw exceptions)
  {
    return size;  //Restituisce la dimensione del container
  }

}; 

/* ************************************************************************** */

class ClearableContainer : virtual public Container {
  // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
    virtual ~ClearableContainer() =default;
  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer& operator=(const ClearableContainer&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer& operator=( ClearableContainer&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ClearableContainer&) const noexcept =delete; // Comparison of abstract types is not possible.
  bool operator!=(const ClearableContainer&) const noexcept =delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual void Clear() noexcept 
  { 
    size=0;  //imposta la dimensione a 0
  };  
};

/* ************************************************************************** */

class ResizableContainer : virtual public ClearableContainer{
  // Must extend ClearableContainer

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResizableContainer() =default;

  /* ************************************************************************ */

  // Copy assignment
  virtual ResizableContainer& operator=(const ResizableContainer&) =delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  virtual ResizableContainer& operator=(ResizableContainer&&) noexcept =delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Container&)const noexcept =delete; // Comparison of abstract types is not possible.
  bool operator!=(const Container&)const noexcept =delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  inline virtual void Resize(unsigned long int dim) 
  {
    size = dim;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline virtual void Clear() noexcept override // Override ClearableContainer member
  {
    Resize(0);
  }

};

/* ************************************************************************** */

}

#endif

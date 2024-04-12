
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
class TraversableContainer : public virtual TestableContainer<Data>{
  // Must extend TestableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer& operator=(const TraversableContainer& val) = delete;

  // Move assignment
  TraversableContainer& operator=(TraversableContainer&& val) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(cosnt TraversableContainer& val) const noexcept = delete;
  bool operator!=(cosnt TraversableContainer& val) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using TraverseFun = std::function<void(const Data &)>;

  virtual void Traverse(TraverseFun) = 0; // la funzione traverse verrà implementata in modo diverso in base a quale classe estende questa 

  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

  template <typename Accumulator>
  virtual inline Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : public virtual TraversableContainer<Data>{
  // Must extend TraversableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer& val) = delete;

  // Move assignment
  PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&& val) = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer& val) const noexcept = delete;
  bool operator!=(const PreOrderTraversableContainer& val) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  using typename TraversableContainer<Data>::TraverseFun;

  virtual void PreOrderTraverse(TraverseFun);

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  template <typename Accumulator>
  virtual inline Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator);

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  virtual void Traverse(TraverseFun fun) const override{ // Override TraversableContainer member
    PreOrderTraverse(fun);
  }

};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~PostOrderTraversableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;

  // type PostOrderTraverse(arguments) specifiers;

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type PostOrderFold(arguments) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~InOrderTraversableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;

  // type InOrderTraverse(arguments) specifiers;

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type InOrderFold(arguments) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...

public:

  // Destructor
  // ~BreadthTraversableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument); // Copy assignment of abstract types is not possible.

  // Move assignment
  // type operator=(argument); // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers; // Comparison of abstract types might be possible.
  // type operator!=(argument) specifiers; // Comparison of abstract types might be possible.

  /* ************************************************************************ */

  // Specific member function

  // using typename TraversableContainer<Data>::TraverseFun;

  // type BreadthTraverse(arguments) specifiers;

  // template <typename Accumulator>
  // using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

  // template <typename Accumulator>
  // type BreadthFold(arguments) specifiers;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif


#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST :
virtual public ClearableContainer,
virtual public DictionaryContainer<Data>,
virtual public BinaryTree<Data>,
virtual protected BinaryTreeLnk<Data>{
  // Must extend ClearableContainer,
  //             DictionaryContainer<Data>,
  //             BinaryTree<Data>,
  //             BinaryTreeLnk<Data>

private:

  // ...

protected:

  using Container::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data>&); // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data>&&) noexcept; // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST&);

  // Move assignment
  BST& operator=(BST&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST&) const noexcept;
  bool inline operator!=(const BST& bst) const noexcept {
    return !(operator==(bst));
  };

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found)

  const Data& Successor(const Data&) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const NodeLnk& Root() const override {
    if(this->Empty()) {
      throw std::length_error("Errore: albero vuoto.");
    }

    return *root;
  }; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

  Data DataNDelete(NodeLnk*);
  
  NodeLnk* Detach(NodeLnk*&) noexcept;

  NodeLnk* DetachMin(NodeLnk *&) noexcept;
  NodeLnk* DetachMax(NodeLnk *&) noexcept;

  NodeLnk* Skip2Left(NodeLnk *&) noexcept;
  NodeLnk* Skip2Right(NodeLnk *&) noexcept;

  NodeLnk* const &FindPointerToMin(NodeLnk *const &) const noexcept;
  NodeLnk* const &FindPointerToMax(NodeLnk *const &) const noexcept;

  NodeLnk*& FindPointerToMin(NodeLnk *&) noexcept;
  NodeLnk*& FindPointerToMax(NodeLnk *&) noexcept;

  NodeLnk*const& FindPointerTo(NodeLnk *const &, Data) const noexcept;
  NodeLnk*& FindPointerTo(NodeLnk *&, Data) noexcept;

  NodeLnk* const& FindPointerToPredecessor(NodeLnk *const &, Data) const noexcept;
  NodeLnk* const& FindPointerToSuccessor(NodeLnk *const &, Data) const noexcept;

  NodeLnk*& FindPointerToPredecessor(NodeLnk *&, Data) noexcept;
  NodeLnk*& FindPointerToSuccessor(NodeLnk *&, Data) noexcept;

};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif

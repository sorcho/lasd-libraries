
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>, virtual protected Vector<Data>{
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  // ...

  struct NodeVec : virtual MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  friend class BinaryTreeVec<Data>;

  private:

    // ...

  protected:

    // ...

  public:

    BinaryTreeVec<Data>* bt = nullptr;
    int index;

    NodeVec() {
      bt = nullptr;
      index = 0;
    }

    NodeVec(const Data&, int, BinaryTreeVec<Data>*);
    NodeVec(Data&&, int, BinaryTreeVec<Data>*);

    virtual ~NodeVec() = default;

    // Copy assignment
    NodeVec& operator=(const NodeVec& nv) { 
      bt = nv.bt;
      index = nv.index;
      return *this;
    };

    // Move assignment
    NodeVec& operator=(NodeVec&& nv) noexcept { 
      std::swap(bt, nv.bt);
      std::swap(index = nv.index); 
      return *this;
    };

    // Specific member functions
    virtual Data& Element() noexcept override { 
      return bt->elem[index]; 
    }

    virtual const Data& Element() const noexcept override { 
      return bt->elem[index]; 
    }

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;

    virtual NodeVec& RightChild() override;
    virtual const NodeVec& RightChild() const override;

  };

  using Container::size;
  using Vector<Data>::elem;
  NodeVec* nodes = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data>&&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() {
    delete[] nodes;
    nodes = nullptr;
  };

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeVec& right) const noexcept { 
    return Vector<Data>::operator==(right); 
  };
  inline bool operator!=(const BinaryTreeVec& right) const noexcept { 
    return Vector<Data>::operator!=(right); 
  };
  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeVec& Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override {
    Vector<Data>::Clear();
    delete[] nodes;
    nodes = nullptr;
  }; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  void BreadthTraverse(TraverseFun fun) const override {
    Vector<Data>::PreOrderTraverse(fun);
  }; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;
  inline virtual void BreadthMap(MapFun fun) override {
    Vector<Data>::PreOrderMap(fun);
  }; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif

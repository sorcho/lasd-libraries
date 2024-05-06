
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : public virtual MutableBinaryTree<Data>{
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  struct NodeLnk : virtual MutableBinaryTree<Data>::MutableNode{ // Must extend MutableNode

  friend class BinaryTreeLnk<Data>;

  private:

  protected:

  public:

    Data elem {};
    NodeLnk* LChild = nullptr;
    NodeLnk* RChild = nullptr;

    NodeLnk() = default;

    NodeLnk(const Data& data) : elem(data) {};
    NodeLnk(Data&& data) noexcept : elem(std::move(data)) {};

    //Copy Constructor
    NodeLnk(const NodeLnk&);

    //Move Constructor
    NodeLnk(NodeLnk&&) noexcept;

    virtual ~NodeLnk();

    //Copy Assignament
    NodeLnk& operator=(const NodeLnk&);

    //Move Assignament
    NodeLnk& operator=(NodeLnk&&) noexcept;

    // Specific member functions

    virtual bool inline IsLeaf() const noexcept override { 
      return (!(HasLeftChild() || HasRightChild())); 
    };

    virtual inline Data& Element() noexcept override {
      return elem;
    };

    virtual const inline Data& Element() const noexcept override {
      return elem;
    };

    virtual bool inline HasLeftChild() const noexcept override{
      return (LChild == nullptr ? false : true);
    };

    virtual bool inline HasRightChild() const noexcept override{
      return (RChild == nullptr ? false : true);
    };

    virtual inline NodeLnk& LeftChild() override {
      if(IsLeaf()) {
        throw std::out_of_range("Errore: figlio sinistro inesistente");
      }
      return *LChild;
    }; 

    virtual const inline NodeLnk& LeftChild() const override {
      if(IsLeaf()) {
        throw std::out_of_range("Errore: figlio sinistro inesistente");
      }
      return *LChild;
    }; 

    virtual inline NodeLnk& RightChild() override {
      if(IsLeaf()) {
        throw std::out_of_range("Errore: figlio destro inesistente.");
      }
      return *RChild;
    };

    virtual const inline NodeLnk& RightChild() const override {
      if(IsLeaf()) {
        throw std::out_of_range("Errore: figlio destro inesistente.");
      }
      return *RChild;
    };

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data>&); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data>&&); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk() {
    delete root;
  };

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk<Data>& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk<Data>& operator=(BinaryTreeLnk&&) noexcept;
  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BinaryTreeLnk& btl) const noexcept { 
    return BinaryTree<Data>::operator==(btl); 
  };

  inline bool operator!=(const BinaryTreeLnk& btl) const noexcept { 
    return BinaryTree<Data>::operator!=(btl); 
  };


  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual inline const NodeLnk& Root() const override {
    if(this->Empty()) {
      throw std::length_error("Errore: albero vuoto.");
    }
    return *root;
  }; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual inline NodeLnk& Root() override {
    if(this->Empty()) {
      throw std::length_error("Errore: albero vuoto.");
    }
    return *root;
  }; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual inline void Clear() override { 
    if (root != nullptr) { 
      delete root; 
      root=nullptr; 
    } 
    size = 0; 
  }; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif


namespace lasd {

/* ************************************************************************** */

    // -------------- BINARY TREE ------------------

    // Comparison operator

    template <typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const noexcept {
        if (size != bt.size) {
            return false;
        }

        BTPreOrderIterator i(*this);
        BTPreOrderIterator j(bt);

        while (!(i.Terminated())) {
            if ((*i) != (*j)) {
                return false;
            }

            ++i;
            ++j;
        }
    
        return true;
    }

    // --------------- TRAVERSE FUNCTIONS ----------------
    
    template <typename Data>
    void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const override {
        if(!this -> Empty()) {
            PreOrderTraverse(
                [this](const Data& data) {
                    fun(data);
            });
        }
    }

    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const override {
        if(!this -> Empty()) {
            PostOrderTraverse(
                [this](const Data& data) {
                    fun(data);
            });
        }
    }

    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const override {
        if(!this -> Empty()) {
            InOrderTraverse(
                [this](const Data& data) {
                    fun(data);
            });
        }
    }

    template <typename Data>
    void BinaryTree<Data>::BreadthOrderTraverse(TraverseFun fun) const override {
        if(!this -> Empty()) {
            BreadthOrderTraverse(
                [this](const Data& data) {
                    fun(data);
            });
        }
    }

    // ----------- MUTABLE BINARY TREE -------------

/* ************************************************************************** */

}

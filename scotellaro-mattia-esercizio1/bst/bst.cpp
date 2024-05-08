
namespace lasd {

/* ************************************************************************** */

    template <typename Data>
    BST<Data>::BST(const TraversableContainer<Data>& container) {
        container.Traverse(
            [this](const Data& value){
                Insert(value);
            });
    }

    template <typename Data>
    BST<Data>::BST(MappableContainer<Data>&& container) noexcept {
        container.Map(
            [this](Data& value){
                Insert(std::move(value));
            });
    }

    template<typename Data>
    BST<Data>::BST(const BST<Data>& bst): BinaryTreeLnk<Data>::BinaryTreeLnk(bst) {}

    template<typename Data>
    BST<Data>::BST(BST<Data>&& bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst)) {}

    template <typename Data>
    BST<Data>& BST<Data>::operator=(const BST<Data>& bst){
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    }
    template <typename Data>
    BST<Data>& BST<Data>::operator=(BST<Data>&& bst)noexcept{
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }

    template <typename Data>
    bool BST<Data>::operator==(const BST& bst) const noexcept {
        if (size == bst.Size()) {
            BTInOrderIterator<Data> IterThis(*this);
            BTInOrderIterator<Data> IterRight(bst);

            for (; !IterThis.Terminated(); ++IterThis, ++IterRight) {
                if((*IterThis) != (*IterRight)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    template <typename Data>
    const Data &BST<Data>::Min() const {
        if (root != nullptr) {
            return FindPointerToMin(root)->elem;
        } else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template <typename Data>
    Data BST<Data>::MinNRemove() {
        if (root != nullptr) {
            return DataNDelete(DetachMin(root));
        }
        else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template <typename Data>
    void BST<Data>::RemoveMin() {
        if (root != nullptr) {
            delete DetachMin(root);
        } else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Max() const {
        if (root != nullptr) {
            return FindPointerToMax(root)->elem;
        } else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template <typename Data>
    Data BST<Data>::MaxNRemove() {
        if (root != nullptr) {
            return DataNDelete(DetachMax(root));
        } else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template<typename Data>
    void BST<Data>::RemoveMax() {
        if (root != nullptr) {
            delete DetachMax(root);
        } else {
            throw std::length_error("L'albero è vuoto");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data& found) const {
        NodeLnk* const* ptr =& FindPointerToPredecessor(root, found);
        if (ptr != nullptr) {
            return (*ptr)->elem;
        } else {
            throw std::length_error("Errore: predecessore non trovato.");
        }
    }

    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data& found) {
        NodeLnk** ptr =& FindPointerToPredecessor(root, found);
        if (ptr != nullptr) {
            return DataNDelete(Detach(*ptr));
        } else {
            throw std::length_error("Errore: predecessore non trovato.");
        }
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data& found) {
        NodeLnk** ptr=& FindPointerToPredecessor(root, found);
        if (ptr != nullptr) {
            delete Detach(*ptr);
        } else {
            throw std::length_error("Errore: predecessore non trovato.");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data& found) const {
        NodeLnk* const* ptr =& FindPointerToSuccessor(root, found);
        if(ptr !=nullptr){
            return (*ptr)->elem;
        }
        else{
            throw std::length_error("Errore: successore non trovato.");
        }
    }

    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data& found) {
        NodeLnk** ptr =& FindPointerToSuccessor(root, found);
        if (ptr != nullptr) {
            return DataNDelete(Detach(*ptr));
        } else {
            throw std::length_error("Errore: successore non trovato.");
        }
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data& found) {
        NodeLnk **ptr =& FindPointerToSuccessor(root, found);
        if (ptr != nullptr) {
            delete Detach(*ptr);
        } else {
            throw std::length_error("Errore: successore non trovato.");
        }
    }

    template <typename Data>
    bool BST<Data>::Insert(const Data& value) {
        NodeLnk * & ptr = FindPointerTo(root, value); 
        if(ptr == nullptr){
            ptr = new NodeLnk(value);
            size++;
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::Insert(Data&& value){
    NodeLnk * & ptr = FindPointerTo(root, value); 
        if(ptr == nullptr){
            ptr = new NodeLnk(std::move(value));
            size++;
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::Remove(const Data& value){
        NodeLnk * & ptr = FindPointerTo(root, value);
        if(ptr != nullptr){
            delete Detach(ptr);
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data& value) const noexcept {
        return (FindPointerTo(root, value) !=nullptr);
    }

    template <typename Data>
    void BST<Data>::Clear() noexcept {
        BinaryTreeLnk<Data>::Clear();
    }

    template <typename Data>
    inline Data BST<Data>::DataNDelete(NodeLnk *node) {
        Data value;
        std::swap(value, node->elem);
        delete node;
        return value;
    }

    template <typename Data>
    typename lasd::BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(NodeLnk *&node) noexcept {
        if (node != nullptr) {
            if (node->LChild == nullptr) {
                return Skip2Right(node);
            }
            else if (node->RChild == nullptr) {
                return Skip2Left(node);
            }
            else {
                NodeLnk *max = DetachMax(node->LChild);
                std::swap(node->elem, max->elem);
                return max;
            }
        }
        return nullptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMax(typename BST<Data>::NodeLnk*& node) noexcept {
        return Skip2Left(FindPointerToMax(node));
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::DetachMin(typename BST<Data>::NodeLnk*& node) noexcept {
        return Skip2Right(FindPointerToMin(node));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(typename BST<Data>::NodeLnk*& node) noexcept {
        NodeLnk* new_LChild = nullptr;
        if (node != nullptr) {
            std::swap(new_LChild, node->LChild);
            std::swap(new_LChild, node);
            size--;
        }
        return new_LChild;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(typename BST<Data>::NodeLnk*& node) noexcept{
        NodeLnk *new_RChild = nullptr;
        if (node != nullptr) {
            std::swap(new_RChild, node->RChild);
            std::swap(new_RChild, node);
            size--;
        }
        return new_RChild;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk* const& node)const noexcept{
        NodeLnk* const* ptr=&node;
        NodeLnk* corrente=node;
        if(corrente != nullptr){
            while(corrente->LChild!=nullptr){
                ptr=&corrente->LChild;
                corrente=corrente->LChild;
            }
        }
        return *ptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* const& node)const noexcept{
    NodeLnk* const* ptr=&node;
    NodeLnk* corrente=node;
    if(corrente!=nullptr){
        while(corrente->RChild!=nullptr){
            ptr=&corrente->RChild;
            corrente=corrente->RChild;
        }
    }
    return *ptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk*& node) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(node));
    }

    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk*& node) noexcept {
        return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& node, Data found) const noexcept {
        NodeLnk *const *ptr = &node;
        NodeLnk *current = node;

        while (current != nullptr) {
            if (found > current->elem) {
                ptr = &current->RChild;
                current = current->RChild;
            } else if (found < current->elem) {
                ptr = &current->LChild;
                current = current->LChild;
            } else {
                break;
            }
        }
        return *ptr;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& node, Data found) noexcept {
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(node, found));
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToPredecessor(NodeLnk* const& node, Data found) const noexcept {
        NodeLnk *const *predecessor = nullptr;
        NodeLnk *const *current = &node;

        while ((*current) != nullptr && (*current)->elem != found) {
            if ((*current)->elem > found) {
                current = &(*current)->LChild;
            } else if ((*current)->elem < found) {
                predecessor = current;
                current = &(*current)->RChild;
            }
        }
        if ((*current) != nullptr && (*current)->LChild != nullptr) {
            predecessor = &FindPointerToMax((*current)->LChild);
        }

        return *predecessor;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToSuccessor(NodeLnk* const& node, Data found) const noexcept{
        NodeLnk *const *successor = nullptr;
        NodeLnk *const *current = &node;

        while ((*current) != nullptr && (*current)->elem != found) {
            if ((*current)->elem < found) current = &(*current)->RChild;
            else if ((*current)->elem > found) {
            successor = current;
            current = &(*current)->LChild;
            }
        }
        if ((*current) != nullptr && (*current)->RChild != nullptr) successor = &FindPointerToMin((*current)->RChild);

        return *successor;
    }

    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(NodeLnk*& node, Data found) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(node, found));
    }

    template<typename Data>
    typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(NodeLnk*& node, Data found) noexcept{
        return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(node, found));
    }

/* ************************************************************************** */

}

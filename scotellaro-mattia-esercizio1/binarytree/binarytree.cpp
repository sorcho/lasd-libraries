
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
    void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const {
        if(!this -> Empty()) {
            PreOrderTraverse(fun, &this -> Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const {
        if(!this -> Empty()) {
            PostOrderTraverse(fun, &this -> Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
        if(!this -> Empty()) {
            InOrderTraverse(fun, &this -> Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const {
        if(!this -> Empty()) {
            BreadthTraverse(fun, &this -> Root());
        }
    }

    // Auxiliary functions

    template <typename Data>
    void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node* node) const {
        fun(node->Element());  

        if(node->HasLeftChild()) {
            PreOrderTraverse(&node->LeftChild(), fun);
        } 

        if(node->HasRightChild()) {
            PreOrderTraverse(&node->RightChild(), fun);
        } 
    }

    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node* node) const {
        if(node->HasLeftChild()) {
            PostOrderTraverse(&node->LeftChild(), fun);
        }
        if(node->HasRightChild()) {
            PostOrderTraverse(&node->RightChild(), fun);
        }

        fun(node->Element());
    }

    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node* node) const {
        if(node->HasLeftChild()) {
            InOrderTraverse(&node->LeftChild(), fun);
        }

        fun(node->Element());

        if(node->HasRightChild()) {
            InOrderTraverse(&node->RightChild(), fun);
        }
    }

    template <typename Data>
    void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node* node) const {
        lasd::QueueVec<const BinaryTree<Data>::Node *> queue;
        if(node!=nullptr) {
            queue.Enqueue(node);
        }

        while (!queue.Empty()) {
            const BinaryTree<Data>::Node *currentNode = queue.HeadNDequeue();
            fun(currentNode->Element());

            if(currentNode->HasLeftChild()) {
                queue.Enqueue(&currentNode->LeftChild());
            }

            if(currentNode->HasRightChild()) {
                queue.Enqueue(&currentNode->RightChild());
            }
        }
    }

    // ----------- MUTABLE BINARY TREE -------------

    template <typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
        if(!this -> Empty()) {
            PreOrderMap(fun, &this -> Root());
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
        if(!this -> Empty()) {
            PostOrderMap(fun, &this -> Root());
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
        if(!this -> Empty()) {
            InOrderMap(fun, &this -> Root());
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
        if(!this -> Empty()) {
            BreadthMap(fun, &this -> Root());
        }
    }

    // Auxiliary functions

    template <typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode* node) {
        fun(node->Element());

        if(node->HasLeftChild()) {
            PreOrderMap(&node->LeftChild(), fun);
        }
        if(node->HasRightChild()) {
            PreOrderMap(&node->RightChild(), fun);
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode* node) {
        if(node->HasLeftChild()) {
            PostOrderMap(&node->LeftChild(), fun);
        }
        if(node->HasRightChild()) {
            PostOrderMap(&node->RightChild(), fun);
        }

        fun(node->Element());
    }

    template <typename Data>
    void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode* node) {
        if(node->HasLeftChild()) {
            InOrderMap(&node->LeftChild(), fun);
        }

        fun(node->Element());

        if(node->HasRightChild()) {
            InOrderMap(&node->RightChild(), fun);
    }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode* node) {
        lasd::QueueVec<MutableBinaryTree<Data>::MutableNode *> queue;
        if(node!=nullptr) {
            queue.Enqueue(node);
        }

        while (!queue.Empty()) {
            MutableBinaryTree<Data>::MutableNode *currentNode = queue.HeadNDequeue();
            fun(currentNode->Element());

            if(currentNode->HasLeftChild()) {
                queue.Enqueue(&currentNode->LeftChild());
            }

            if(currentNode->HasRightChild()) {
                queue.Enqueue(&currentNode->RightChild());
            }
        }
    }

    // --------- PRE ORDER ITERATOR ----------------

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
        if (!bt.Empty()) {
            root = &bt.Root();
            current = root;
        }
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& poi) : stack (poi.stack){
        root = poi.root;
        current = poi.current;
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& poi) noexcept : stack (std::move(poi.stack)){
        std::swap(root, poi.root);
        std::swap(current, poi.current);
    }

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& poi) {
        root = poi.root;
        stack = poi.stack;
        current = poi.current;
        return *this;
    }

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& poi) noexcept {
        std::swap(root, poi.root);
        std::swap(stack, poi.stack);
        std::swap(current, poi.current);
        return *this;
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& poi) const noexcept {
        return (current==poi.current && stack==poi.stack);
    }

    template <typename Data>
    const Data& BTPreOrderIterator<Data>::operator*() const {
        if (Terminated()) {
            throw std::out_of_range("Iteratore terminato.");
        } else {
            return current -> Element();
        }
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept {
        return (current == nullptr);
    }

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
        if(!Terminated()){
            if(current->HasLeftChild()){
                if(current->HasRightChild()) {
                    stack.Push(&current->RightChild());
                }
                current=&(current->LeftChild());
            }else if(current->HasRightChild()) { 
                current=&(current->RightChild());
            } else if (!stack.Empty()) {
                current=stack.TopNPop();
            } else {
                current=nullptr;
            }
        } else {
            throw std::out_of_range("Out of range iterator");
        }
        return *this;
    }

    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept {
        stack.Clear();
        current = root;
    }


/* ************************************************************************** */

}

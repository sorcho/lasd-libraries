
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

    // ---------------- PRE ORDER MUTABLE ITERATOR --------------
    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& pomi) {
        this->root=pomi.root;
        this->stack=pomi.stack;
        this->current=pomi.current;
        return *this;
    }

    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& pomi) noexcept {
        this->root = std::move(pomi.root);
        this->stack = std::move(pomi.stack);
        this->current = std::move(pomi.current); 
        return *this;
    }

    //  ------------ POST ORDER ITERATOR -------------
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt){
        if(bt.Empty()) {
            root = nullptr;
        } else {
            root = &bt.Root();
        }
        current = DeepestLeftLeaf(root);
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& poi) {
        stack = poi.stack;
        root = poi.root;
        current=poi.current;
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& poi) noexcept : stack(std::move(poi.stack)) {
        root = std::move(poi.root); 
        current = std::move(poi.current);
    }

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& poi) {
        root = poi.root;
        stack = poi.stack;
        current = poi.current;
        return *this;
    }

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& poi) noexcept {
        root = std::move(poi.root);
        stack = std::move(poi.stack); 
        current = std::move(poi.current);
        return *this;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& poi) const noexcept {
        return ((current == poi.current) && (stack == poi.stack));
    }

    template <typename Data>
    const Data& BTPostOrderIterator<Data>::operator*() const {
        if(Terminated()) {
            throw std::out_of_range("L'iteratore è terminato.");
        }
        else {
            return current->Element();
        }
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept {
        return (current==nullptr);
    }

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
        if(!Terminated()){
            if(!(stack.Empty())){
                if (stack.Top()->HasRightChild() && !(&(stack.Top()->RightChild()) == current)) {
                    current = &(stack.Top()->RightChild());
                    current = DeepestLeftLeaf(current);
                } else {
                    current = stack.TopNPop();
                }
            } else {
                current = nullptr;
            }
        }
        else {
            throw std::out_of_range("L'iteratore è terminato.");
        }

        return *this;
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept {
        stack.Clear();
        current = DeepestLeftLeaf(root);
    }

    template <typename Data>
    const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual){
        if(actual!=nullptr){
            while(actual->HasLeftChild()){
                stack.Push(actual);
                actual = &(actual->LeftChild());
            }
            if(actual->HasRightChild()){
                stack.Push(actual);
                actual = &(actual->RightChild());
                actual = DeepestLeftLeaf(actual);
            }
        }
        return actual;
    }

    // ----------- POST ORDER MUTABLE ITERATOR ---------
    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& pomi) {
        this->root = pomi.root;
        this->stack = pomi.stack;
        this->current = pomi.current;
        return *this;
    }

    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& pomi) noexcept {
        this->root = std::move(pomi.root);
        this->stack = std::move(pomi.stack);    
        this->current = std::move(pomi.current);
        return *this;
    }

    // ------------ IN ORDER ITERATOR -----------------
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& ioi) {
        if(ioi.Empty()) {
            root = nullptr;
        } else {
            root = &ioi.Root();
        }
        current = MostLeftNode(root);
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& ioi) {
        stack = ioi.stack;
        root = ioi.root;
        current=ioi.current;
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& ioi) noexcept : stack(std::move(ioi.stack)) {
        current = std::move(ioi.current);
        root = std::move(ioi.root); 
    }

    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& ioi) {
        root = ioi.root;
        stack = ioi.stack;
        current = ioi.current;
        return *this;
    }

    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& ioi) noexcept {
        root = std::move(ioi.root);
        stack = std::move(ioi.stack);
        current = std::move(ioi.current);
        return *this;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator& ioi) const noexcept {
        return ((current == ioi.current) && (stack == ioi.stack));
    }

    template <typename Data>
    const Data& BTInOrderIterator<Data>::operator*() const {
        if(Terminated()) {
            throw std::out_of_range("L'iteratore è terminato.");
        } else {
            return current->Element();
        }
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept {
        return (current == nullptr);
    }

    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
        if(!Terminated()) {
            if((stack.Empty()) && !(current->HasRightChild())) {
                current=nullptr;
            }
            else { 
                if(current->HasRightChild()){
                    current = MostLeftNode(&current->RightChild());
                } 
                else {
                    current = stack.TopNPop();
                }
            }
        } else {
            throw std::out_of_range("L'iteratore è terminato.");
        }

        return *this;
    }

    template <typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept {
        stack.Clear(); 
        current = MostLeftNode(root);
    }

    template <typename Data>
    const typename BinaryTree<Data>::Node *BTInOrderIterator<Data>::MostLeftNode(const typename BinaryTree<Data>::Node* actual) {
    while (actual != nullptr && (actual->HasLeftChild())) {
            stack.Push(actual);
            actual = &actual->LeftChild();
        }
        return actual;
    }

    // ---------- IN ORDER MUTABLE ITERATOR --------------
    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& iomi) {
        this->root = iomi.root;
        this->stack = iomi.stack;
        this->current = iomi.current;
        return *this;
    }

    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& iomi) noexcept {
        this->root = std::move(iomi.root);
        this->stack = std::move(iomi.stack);
        this->current = std::move(iomi.current);
        return *this;
    }

    // ---------- BREADTH ITERATOR -----------
    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bi) {
        if(bi.Empty()) {
            root = nullptr;
        } else {
            root = &bi.Root();
        }
        current = root;
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &bi) {
        queue = bi.queue;
        root = current = bi.current;
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& bi) noexcept : queue(std::move(bi.queue)) {
        root = std::move(bi.root);
        current = std::move(bi.current); 
    }

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& bi) {
        root = bi.root;
        queue = bi.queue;
        current = bi.current;
        return *this;
    }

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& bi) noexcept {
        root = std::move(bi.root);
        queue = std::move(bi.queue);
        current = std::move(bi.current);
        return *this;
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &bi) const noexcept {
        return (current == bi.current && queue == bi.queue);
    }

    template <typename Data>
    const Data& BTBreadthIterator<Data>::operator*() const {
        if(Terminated()) {
            throw std::out_of_range("L'iteratore è terminato.");
        } else {
            return current->Element();
        }
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept {
        return (current==nullptr);
    }

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
        if(!Terminated()) {
            if (current != nullptr) {
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild())); 
                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                
                if (!queue.Empty()) current = queue.HeadNDequeue();
                else current = nullptr;
            } 
        } else {
            throw std::out_of_range("L'iteratore è terminato.");
        }

        return *this;
    }

    template <typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept {
        queue.Clear();
        current = root;
    }
    
    // -------------- BREADTH MUTABLE ITERATOR ---------------
    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& bmi) {
        this->root=bmi.root;
        this->queue=bmi.queue;
        this->current=bmi.current;
        return *this;
    }

    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& bmi) noexcept {
        this->root = std::move(bmi.root);
        this->queue = std::move(bmi.queue);
        this->current = std::move(bmi.current);
        return *this;
    }
/* ************************************************************************** */

}

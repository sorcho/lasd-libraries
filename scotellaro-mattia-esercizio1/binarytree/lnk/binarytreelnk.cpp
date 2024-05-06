
namespace lasd {

/* ************************************************************************** */

    // ------------ NODE LNK -----------------

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk& nl) {
        elem = nl.elem;
        LChild = (nl.LChild != nullptr) ? new NodeLnk(*nl.LChild) : nullptr;
        RChild = (nl.RChild != nullptr) ? new NodeLnk(*nl.RChild) : nullptr;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk&& nl) noexcept {
        std::swap(elem, nl->elem);
        std::swap(LChild, nl->LChild);
        std::swap(RChild, nl->RChild);
    }

    template <typename Data>
    inline BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
        if (LChild != nullptr)
        {
            delete LChild;
            LChild = nullptr;
        }
        if (RChild != nullptr)
        {
            delete RChild;
            RChild = nullptr;
        }
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nl) {
        elem(nl->elem);
        return *this;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nl) noexcept {
        std::swap(elem, nl->elem);
        return *this;
    }

    // ----------- BINARY TREE LNK ------------------

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& cont) {
        size = cont.Size();
        QueueVec<NodeLnk **> queue;
        queue.Enqueue(&root);
        cont.Traverse(
            [&queue](const Data &data) {
                NodeLnk *&current = *queue.HeadNDequeue();
                current = new NodeLnk(data);
                queue.Enqueue(&current->LChild);
                queue.Enqueue(&current->RChild);
            });
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& cont) {
        size = cont.Size();
        QueueVec<NodeLnk **> queue;
        queue.Enqueue(&root);
        cont.Map(
            [&queue](Data &data) {
                NodeLnk *&current = *queue.HeadNDequeue();
                current = new NodeLnk(std::move(data));
                queue.Enqueue(&current->LChild);
                queue.Enqueue(&current->RChild);
            });
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& bt) {
        if(bt.root!=nullptr) {
            root = new NodeLnk(*bt.root);
            size = bt.Size();
        }     
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept {
        std::swap(root, bt.root);
        std::swap(size, bt.size);
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& bt) {
        Clear();
        if(bt.root!=nullptr) {
            root = new NodeLnk(*bt.root);
            size = bt.Size();
        }    
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& bt) noexcept {
        std::swap(root, bt.root);
        std::swap(size, bt.size);
        return *this;
    }

/* ************************************************************************** */

}

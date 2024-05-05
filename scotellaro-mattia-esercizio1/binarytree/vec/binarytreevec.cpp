
namespace lasd {

/* ************************************************************************** */

    // ------------ NODE VEC -------------

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &data, int i, BinaryTreeVec<Data>* bt) {
        this->bt = bt;
        this->index = i;
        bt->elem[i] = data;  
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data, int i, BinaryTreeVec<Data>* bt) {
        std::swap(this->bt, bt);
        std::swap(this->index, i);
        std::swap(bt->elem[i], data);  
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
    {
        if(index*2+1 < bt->size) {
            return true;
        }
        return false;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
        if(index*2+2 < bt->size) {
                return true;
        }
        return false;
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
        if(HasLeftChild()) {
            return (bt->Nodes[index*2+1]);
        }
        else throw std::out_of_range("Errore: figlio sinistro inesistente.");
    }

    template <typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
        if(HasLeftChild()) {
            return (bt->Nodes[index*2+1]);
        }
        else throw std::out_of_range("Errore: figlio sinistro inesistente.");
    }

    template <typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
        if(HasRightChild()) {
            return (bt->Nodes[index*2+2]);
        }
        else throw std::out_of_range("Errore: figlio destro inesistente.");
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
        if(HasRightChild()) {
            return (bt->Nodes[index*2+2]);
        }
        else throw std::out_of_range("Errore: figlio destro inesistente.");
    }

    // ----------- BINARY TREE VEC --------------

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& cont) {
        this->Resize(cont.Size());
        nodes = new NodeVec[cont.Size()];
        int i = 0;

        cont.Traverse(
            [this, &i](const Data& dat){
                this->nodes[i].index = i;
                elem[i] = dat;
                this->nodes[i].bt = this;
                i++;
            }
        );
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& cont) noexcept {
        this->Resize(cont.Size());
        nodes = new NodeVec[cont.Size()];
        int i = 0;
        cont.Map(
            [this, &i](Data& dat){
                this->nodes[i].index = i;
                elem[i] = std::move(dat);
                this->nodes[i].bt = this;
                i++;
            }
        );
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& btv) {
        this->Resize(btv.Size());
        nodes = new NodeVec[btv.Size()];
        std::copy(btv.elem, btv.elem + size, elem);
        std::copy(btv.nodes, btv.nodes + size, nodes);

        for(int i = 0; i < btv.Size(); i++) {
            nodes[i].btv = this;
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& btv) noexcept {
        std::swap(this->size, btv.size);
        std::swap(elem, btv.elem);
        std::swap(nodes, btv.nodes);

        for(int i = 0; i < size; i++) {
            nodes[i].btv = this;
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& btv) {
        this->Clear();
        this->Resize(btv.Size());
        nodes = new NodeVec[btv.Size()];
        std::copy(btv.elem, btv.elem + size, elem);
        std::copy(btv.nodes, btv.nodes + size, nodes);
        for(int i = 0; i < btv.Size(); i++) {
            nodes[i].bt = this;
        }
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& btv) noexcept {
        std::swap(this->size, btv.size);
        std::swap(elem, btv.elem);
        std::swap(nodes, btv.nodes);
        for(int i = 0; i < size; i++) {
            nodes[i].bt = this;
        }
        for(int i = 0; i < btv.size; i++) {
            btv.nodes[i].bt = &btv;
        }
        return *this;
    }

    template <typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
        if(!this->Empty()) {
            return nodes[0];
        }
        else {
            throw std::length_error("Errore: albero vuoto");
        }
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
        if(!this->Empty()) {
            return nodes[0];
        }
        else {
            throw std::length_error("Errore: albero vuoto");
        }
    }
/* ************************************************************************** */

}

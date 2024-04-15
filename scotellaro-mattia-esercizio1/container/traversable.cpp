
namespace lasd {

/* ************************************************************************** */

    //----------------- TRAVERSABLE -----------------------

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const {
        Traverse(
            [fun, &acc](const Data &dat)
            {
                acc = fun(dat, acc);
            });

            return acc;
    }

    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data &val) const noexcept {
        bool exist = false;

        Traverse(
            [val, &exist](const Data &dat){
                exist |= (val == dat);
            });

        return exist;
    }

    //----------------- PRE ORDER -----------------------

    template <typename Data>
    virtual void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
        PreOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        PreOrderTraverse(
            [fun, &acc](const Data &dat){
                acc = fun(dat, acc);
            });

        return acc;
    }

    //----------------- POST ORDER -----------------------

    template <typename Data>
    virtual void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
        PostOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        PostOrderTraverse(
            [fun, &acc](const Data &dat){
                acc = fun(dat, acc);
            });

        return acc;
    }

    //----------------- IN ORDER -----------------------

    template <typename Data>
    virtual void InOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
        InOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        InOrderTraverse(
            [fun, &acc](const Data &dat){
                acc = fun(dat, acc);
            });

        return acc;
    }

    //----------------- BREADTH ORDER -----------------------

    template <typename Data>
    virtual void BreadthOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
        BreadthOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator BreadthOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
        BreadthOrderTraverse(
            [fun, &acc](const Data &dat){
                acc = fun(dat, acc);
            });

        return acc;
    }

/* ************************************************************************** */

};

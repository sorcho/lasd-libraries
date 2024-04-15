namespace lasd {

/* ************************************************************************** */

    //------------- PRE ORDER ---------------------

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFun fun) const {
        PreOrderMap(fun);
    }

    //------------- POST ORDER ---------------------

    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFun fun) const {
        PostOrderMap(fun);
    }

    //------------- IN ORDER ---------------------

    template <typename Data>
    void InOrderMappableContainer<Data>::Map(MapFun fun) const {
        InOrderMap(fun);
    }

    //------------- BREADTH ORDER ---------------------

    template <typename Data>
    void BreadthMappableContainer<Data>::Map(MapFun fun) const {
        BreadthMap(fun);
    }

/* ************************************************************************** */

}

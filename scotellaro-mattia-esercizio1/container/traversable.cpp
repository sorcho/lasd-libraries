
namespace lasd {

/* ************************************************************************** */

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
    inline bool TraversableContainer<Data>::Exists(const Data &val) const noexcept{
        bool exist = false;

        Traverse(
            [val, &exist](const Data &val){
                exist |= (val == dat);
            });

        return exist;
    }

/* ************************************************************************** */

}

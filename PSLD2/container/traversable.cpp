//
//  traversable.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 01/05/25.
//


namespace lasd {

/* ************************************************************************** */
template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    Traverse(
        [foldFunction , &accumulator](const Data & dato){
            accumulator = foldFunction (dato ,accumulator);
        }
    );
    return accumulator;
}

template<typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& valore) const noexcept
{
    bool risultato = false;
    Traverse(
        [valore, &risultato](const Data& data)
        {
            if (data == valore)
            {
                risultato = true;
            }
        }
    );
    return risultato;
}
 
/* ************************************************************************** */


template<typename Data>
template<typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    PreOrderTraverse(
        [foldFunction , &accumulator](const Data & dato)
        {
            accumulator = foldFunction (dato, accumulator);
        }
    );
    return accumulator;
}

template <typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun tFun) const
{
    PreOrderTraverse(tFun);
    
}


template<typename Data>
template<typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFunction, Accumulator accumulator) const
{
    PostOrderTraverse(
        [foldFunction , &accumulator](const Data & dato)
        {
            accumulator = foldFunction (dato, accumulator);
        }
    );
    return accumulator;
}
template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
{
    PostOrderTraverse(fun);
}


}

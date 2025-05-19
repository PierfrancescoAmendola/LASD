//
//  mappable.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 02/05/25.
//

namespace lasd {

/* ************************************************************************** */

//Funzione PreOrder
template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

//Funzione PostOrder
template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun fun) {
    PostOrderMap(fun);
}

//Funzione
template <typename Data>
void PreOrderMappableContainer<Data>::PreOrderMap(MapFun fun)
{
    PreOrderMap (
        [fun](Data& data){
            fun(data);
        }
    );
}

template <typename Data>
void PostOrderMappableContainer<Data>::PostOrderMap(MapFun fun)
{
    PostOrderMap(
        [fun](Data& data){
            fun(data);
        }
    );
}

}

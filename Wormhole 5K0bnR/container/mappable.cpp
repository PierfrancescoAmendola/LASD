#include "mappable.hpp"

namespace lasd {

/* ************************************************************************** */
//PreOrderMappableContainer
    template<typename Data>
    inline void PreOrderMappableContainer<Data> :: Map(MapFun func) noexcept 
    {
        PreOrderMap(func);
    }

//PostOrderMappableContainer
    template<typename Data>
    inline void PostOrderMappableContainer<Data> :: Map(MapFun func) noexcept 
    {
        PostOrderMap(func);
    }
/* ************************************************************************** */

}

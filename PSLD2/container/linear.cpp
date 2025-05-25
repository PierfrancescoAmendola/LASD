//
//  linear.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 01/05/25.
//
namespace lasd{

/* ************************************************************************** */


//Comparison operators

//Operator ==
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& uguale) const noexcept
{
    if (size != uguale.size) return false; //Confronta le dimensioni con if (size != uguale.size)
    for (unsigned long  i = 0; i < size; ++i)
    {
        //scrivere this->operator[](i) è equivalente a (*this)[i]
        if ((*this)[i] != uguale[i]) return false; //(*this)[i] per accedere agli elementi
    }
    return true;
}

//Operator !=
template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& diverso) const noexcept
{
    return !(*this == diverso); //Se sono diversi, restituisce true
}

/* ************************************************************************** */

//Funzione Front LinearContainer
template <typename Data>
const Data& LinearContainer<Data>::Front() const
{
    if (size == 0) throw std::length_error("Container is empty"); //Controlla se il container è vuoto
    return (*this)[0]; //Restituisce il primo elemento
}

//Funzione Back
template <typename Data>
const Data& LinearContainer<Data>::Back() const
{
    if (size == 0) throw std::length_error("Container is empty"); //Controlla se il container è vuoto
    return (*this)[size - 1]; //Restituisce l'ultimo elemento
}

//Funzioni Traverse
template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun fun) const 
{
    PreOrderTraverse(fun); // Delega senza controlli aggiuntivi, non inseriramo un controllo di tipo Empty perchè potrebbe essre ridondante e creare piccoli overhead
}

//Funzioni PreOrderTraverse
template<typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const
{
    const unsigned long  dimensioneContainer = size;  // Cache size per ottimizzazione
    for (unsigned long  i = 0; i < dimensioneContainer ; ++i)
    {
        fun((*this)[i]);
    }
}

template<typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const
{
    for (unsigned long  i = size; i > 0; )
    {
        fun((*this)[--i]);
    }
}

template <typename Data>
inline Data& MutableLinearContainer<Data>::Front()
{
    if (size == 0) throw std::length_error("Container is empty"); //Controlla se il container è vuoto
    return (*this)[0]; //Restituisce il primo elemento
}

template <typename Data>
inline Data& MutableLinearContainer<Data>::Back()
{
    if (size == 0) throw std::length_error("Container is empty"); //Controlla se il container è vuoto
    return (*this)[size - 1]; //Restituisce l'ultimo elemento
}


//Funzione Mutable

template <typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun fun)
{
    PreOrderMap(fun); // Delega senza controlli aggiuntivi
    
}

//Funzione PreOrderMap
template <typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun)
{
    const unsigned long  dimensioneContainer = size;  // Cache size per ottimizzazione
    for (unsigned long  i = 0 ; i < dimensioneContainer ; i++)
    {
        fun((*this)[i]);
    }
}

//Funzione PostOrderMap
template <typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap (MapFun fun)
{
    const unsigned long  dimensioneContainer = size;
    for (unsigned long  i = dimensioneContainer ; i > 0 ; )
    {
        fun ((*this)[--i]);
    }
}

// #Sort

template<typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
    InsertionSort();
}

template<typename Data>
void SortableLinearContainer<Data>::InsertionSort() noexcept
{
    for (unsigned long i = 1; i < this->size; ++i)
    {
        Data key = (*this)[i];                // elemento da inserire
        long j = i - 1;

        // Sposta gli elementi più grandi del key in avanti di una posizione
        while (j >= 0 && (*this)[j] > key)
        {
            (*this)[j + 1] = (*this)[j];      // spostamento
            --j;
        }

        (*this)[j + 1] = key;                 // inserimento nella posizione corretta
    }
}


}
    



//
//  dictionary.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//
namespace lasd {

/* ************************************************************************** */

//Funzione InsertAll che inserisce tutti gli elementi di un TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container)
{
    bool inserimentoTutto = true;
    container.Traverse([this, &inserimentoTutto](const Data& value) {
        if (!Insert(value))
        {
            inserimentoTutto = false;
        }
    });
    return inserimentoTutto;
}

//Funzione InsertAll che inserisce tutti gli elementi di un MappableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container)
{
    bool  inserimentoTutto = true;
    container.Map([this, & inserimentoTutto](Data value){
        if (!Insert(value))
        {
             inserimentoTutto = false;
        }
    });
    return  inserimentoTutto;
}

//Funzione RemoveAll che rimuove tutti gli elementi di un TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container)
{
    bool rimozioneTutto = true;
    container.Traverse([this, &rimozioneTutto](const Data& value) {
        if (!Remove(value))
        {
            rimozioneTutto = false;
        }
    });
    return rimozioneTutto;
}

//Funzione InsertSome che inserisce qualche elemento di un TraversableContainer
// Deve restituire true se almeno UN elemento è stato inserito, false altrimenti
// (quindi va inizializzato a false e messo a true se almeno un Insert ha successo)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & container)
{
    bool qualcheInserimento = false;
    container.Traverse([this, &qualcheInserimento] (const Data& value) {
        if (Insert(value))
        {
            qualcheInserimento = true;
        }
    });
    return qualcheInserimento;
}

//Funzione InsertSome che inserisce qualche elemento di un MappableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container)
{
    bool qualcheInserimento = false;
    container.Map([this, &qualcheInserimento] (Data value) {
        if (Insert(value))
        {
            qualcheInserimento = true;
        }
    });
    return qualcheInserimento;
}

//Funzione RemoveSome che rimuove qualche elemento di un TraversableContainer
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container)
{
    bool qualcheRimozione = false;
    container.Traverse([this, &qualcheRimozione](const Data& value)
    {
        if (Remove(value))
        {
            qualcheRimozione = true;
        }
    });
    return qualcheRimozione;
}
/* ************************************************************************** */
}



#include "dictionary.hpp"
namespace lasd {

/* ************************************************************************** */

//OrderedDictionaryContainer
   template<typename Data>
   bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& con) 
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = all && Insert(dat);
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data> :: InsertAll(MappableContainer<Data>&& con) noexcept
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = all && Insert(std::move(dat));
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& con) 
   {
      bool all = true;
      con.Traverse
      (
         [this, &all](const Data& dat)
         {
            all = all && Remove(dat);
         }
      );
      return all;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = inserted && Insert(dat);
         }
      );
      return inserted; 
   }

   template<typename Data>
   bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = inserted && Insert( std::move(dat) );
         }
      );
      return inserted;
   }

   template<typename Data>
   bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& con) 
   {
      bool inserted = false;
      con.Traverse
      (
         [this, &inserted](const Data& dat)
         {
            inserted = inserted && Remove(dat);
         }
      );
      return inserted;
   }
/* ************************************************************************** */

}

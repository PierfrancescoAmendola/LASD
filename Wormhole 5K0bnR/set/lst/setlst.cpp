
namespace lasd {

/* ************************************************************************** */

   template<typename Data>
   SetLst<Data> :: SetLst(const TraversableContainer<Data>& con)
   {
      con.Traverse(
         [this](const Data& dat)
         {
            Insert(dat);
         }
      )
   }  

   template<typename Data>
   SetLst<Data> :: SetLst(MappableContainer<Data>&& con)
   {
      con.Map(
         [this](const Data& dat)
         {
            Insert(dat);
         }
      )
   }

   template<typename Data>
   SetLst<Data> :: SetLst(const SetLst<Data>& ls) 
      : List(ls) {}

   template<typename Data>
   SetLst<Data> :: SetLst(SetLst<Data>&& ls) noexcept
      : List(ls) {}

   template<typename Data>
   SetLst<Data> :: ~SetLst() 
   {
      while(head != nullptr)
      {
         Node<Data> *t = head;
         head = head->next;
         delete t;
      }
   }

   template<typename Data>
   inline SetLst<Data>& SetLst<Data> :: operator=(SetLst<Data>&& ls) noexcept
   {
      std::swap(size, ls.size);
      std::swap(head, ls.head);
      std::swap(tail, ls.tail); 
   }

   template<typename Data>
   inline SetLst<Data>& SetLst<Data> :: operator=(const SetLst<Data>& ls) 
   {
      while(head != nullptr)
      {
         Node<Data> *t = head;
         head = head->next;
         delete t;
      }
      size = ls.size;
      while(head != nullptr)
      tail = head
      Node<Data> *t = head, t2 = ls.head;

      for(unsigned long int i=0; i<size; i++)
      {
         t = new Node<Data>;
         t->elements = t2->elements;
         t->next = nullptr;
         tail = t;
         t2 = t2->next;
         t = t->next;
      }
   }

   template <typename Data>
   inline bool SetLst<Data> :: operator==(const SetLst<Data>& ls) const noexcept
   {
      return List::operator==(ls);
   }
   template <typename Data>
   inline bool SetLst<Data> :: operator!=(const SetLst<Data>& ls) const noexcept
   {
      return !((*this) == ls);
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Min() const  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
   {
      if(size==0)
         throw std::length_error("Lista vuota");
      return head->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::MinNRemove() noexcept
   {
      Data t = Min();
      RemoveMin();
   }

   template <typename Data>
   inline void SetLst<Data>::RemoveMin() noexcept
   {
      Data t = Min();
      Node<Data>* t = head;
      head = head->next;
      delete t;
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Max() const  // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
   {
      if(size==0)
         throw std::length_error("Lista vuota");
      return tail->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::MaxNRemove() noexcept
   {
      Data t = Max();
      RemoveMax();
   }

   template <typename Data>
   inline void SetLst<Data>::RemoveMax() noexcept
   {
      Data t = Max();
      Node<Data>* t = tail;
      tail = tail->next;
      delete t;
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Predecessor(const Data& dat) const 
   {
      if(size==0)
         throw std::length_error("Non esiste");

      Node<Data> *t2 = binSearch(dat), t = head;

      if(t == head)
         throw std::length_error("Non esiste");

      while(t2 != t)
      {
         if(t->next != nullptr)
            if(t->next != t2 )   //Si ferma al precednete
               t = t->next;
      }
      return t->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::PredecessorNRemove(const Data&)
   {
      Node<Data> *t = binSearch( Predecessor(dat));
      Data elem = t->elements;
      RemovePredecessor(dat);
   }

   template <typename Data>
   inline void SetLst<Data> :: RemovePredecessor(const Data&)
   {
      Node<Data> *t = binSearch( Predecessor(dat)), t2;
      if(head->next == t)
      {
         t = head;
         head = head->next;
      }else
      {
         t2 = binSearch(Predecessor(t->elements))
         t2 = t->next;
      }
      delete t;
   }

   template <typename Data>
   inline const Data& SetLst<Data>::Successor(const Data& dat) const 
   {
      if(size==0)
         throw std::length_error("Non esiste");

      Node<Data> *t2 = binSearch(dat), t = head;

      while(t2 != t)
      {
         t = t->next;
      }
      if(dat == nullptr)
         throw std::length_error("Non esiste");
      return t->elements;
   }

   template <typename Data>
   inline Data SetLst<Data>::SuccessorNRemove(const Data&)
   {
      Node<Data> *t = binSearch( Successor(dat));
      Data elem = t->elements;
      RemoveSuccessor(dat);
   }

   template <typename Data>
   inline void SetLst<Data> :: RemoveSuccessor(const Data&)
   {
      Node<Data> *t = binSearch(dat), t2;
      if( t->next == tail )
      {
         delete t->next;
         tail = t;
         tail->next = nullptr;
      }else
      {
         t2 = t;
         t2 = t2->next->next;
         delete t->next;
      }
   }

   template<typename Data>
   inline bool SetLst<Data>::Insert(const Data& dat)
   {
      if ( binSearch(dat) == nullptr )
         return false;
      Node<Data> *t = new Node<Data>(dat); 
      if(dat < head->elements)   // e minore del minimo
      {
         t->next = head;
         head = t;
      } else if(dat > tail->elements)
      {
         tail->next = t;
         tail = t;
      }else
      {
         Node<Data> *prev = head;
         while( dat < prev->next->elements )
            prev = prev->next;
         t->next = prev->next;
         prev->next = t;
      }
      return true;
   }
   
   template<typename Data>
   inline bool SetLst<Data>::Remove(const Data& dat)
   {
      Node<Data> *t = binSearch(dat);
      if ( t == nullptr )
         return false;
      if (t==head)
         head = head->next;
      else
      {
         Node<Data> *prev = head;
         while( prev->next != dat )
            prev = prev->next;
         if(t == tail)
         {
            tail = prev;
            t->next = null;
         }
         prev->next =  t->next;
      }
      delete t;
   }

   template<typename Data>
   inline const Data& SetLsr<Data> :: operator[](unsigned long int i) const 
   {
      Node<Data> *t = head;
      for(unsigned long j=0; j<i; j++)
         t->t-next;
      return t;
   }

   template <typename Data>
   inline Node<Data>* SetLst<Data>::binSearch(const Data& dat)
   {
      int i =0; j=size-1;
      do
      {
         int q = (i+j)/2;
         Node<Data>* t = l;
         for(int i =0; i<q; i++)	//Avanza fino a q
            t = t -> next;
         if( t -> val == val )
            return t;
         else if ( t -> val < val )
            i = q + 1;
         else
            j = q -1;
      }while( i <= j);
      return null;
   }

   template <typename Data>
   inline bool Exists(const Data&) const noexcept
   {
      return binSearch(dat) != nullptr;
   }
   
   template <typename Data>
   inline void Clear() const noexcept
   {
      this = SetLst<Data>();
   }
/* ************************************************************************** */

}

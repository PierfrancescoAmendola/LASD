
namespace lasd {

/* ************************************************************************** */
	//Constructors
	template<typename Data>
	SetVec<Data> :: SetVec()
	{
		size = head = tail = count =0;
		elements = nullptr;
	}
	
	template<typename Data>
	SetVec<Data> :: SetVec(const TraversableContainer<Data>& con)
	{
		size = con.Size();
		elements = new Data[size];
		unsigned long int i=0;
		con.Traverse
		(
			[this](const Data& dat)
			{
				this->Insert(dat);
			}
		);
	}
	
	template<typename Data>
	SetVec<Data> :: SetVec(MappableContainer<Data>&& con) noexcept
	{
		size = con.Size();
		elements = new Data[size];
		count = head = tail =0;
		con.Map
		(
			[this](const Data& dat)
			{
				this->Insert(dat);
			}
		);
	}
	
	// Copy
	template<typename Data>
	SetVec<Data> :: SetVec(const SetVec<Data>& vec)
	{
		size = vec.size;
		elements = new Data[size];
		unsigned long int i;
		for(i=0; i < size; i++)
		{
			elements[i] = vec[i];
		}	
		count = tail = i-1;
	}
	
	// Move
	template<typename Data>
	SetVec<Data> :: SetVec(SetVec<Data>&& vec) noexcept
	{
			size = count = 0;
			head = tail = 0;
			elements = nullptr;
			std :: swap(tail, vec.tail);
			std :: swap(count, vec.count);
			std :: swap(head, vec.head);
			std :: swap(size, vec.size);
			std :: swap(elements, vec.elements);
	}
	
	// Destructor
	template<typename Data>
	SetVec<Data> :: ~SetVec() 
	{
		delete[] elements;
	}
	
	// Copy assigment
	template<typename Data>
	inline SetVec<Data>& SetVec<Data> :: operator= (const SetVec<Data>& vec) 
	{
		delete[] elements;
		elements = new Data[size];
		head = tail = 0;
		for(; tail < size; tail++)
			elements[tail] = vec.elements[tail];
		count = tail;
	}
	
	template<typename Data>
	inline SetVec<Data>& SetVec<Data> :: operator= (SetVec<Data>&& vec) noexcept 
	{
		std :: swap(tail, vec.tail);
		std :: swap(count, vec.count);
		std :: swap(head, vec.head);
		std :: swap(size, vec.size);
		std :: swap(elements, vec.elements);
	}
	//Comparison operators
	template<typename Data>
	inline bool SetVec<Data> :: operator == (const SetVec<Data>& vec) const noexcept
	{
		if(size != vec.size)
			return false;
		for(unsigned long int i=0; i < size; i++)
			if( (*this)[i] < vec[i] )
				return false;
		return true;
	}
	
	template<typename Data>
	inline bool SetVec<Data> :: operator != (const SetVec<Data>& vec) const noexcept
	{
		return (*this) == vec;
	}
	
	// TestableContainer function
	template<typename Data>
	inline bool SetVec<Data> :: Exists(const Data& dat) const noexcept
	{
		bool found = false;
		unsigned long int i=0;
		while ( i < count && found == false)
		{	
			if( (*this)[i] == dat )
				found = true;
			i++;
		}
		return found;
	}
	
	// ClearableContainer function
	template<typename Data>
	inline void SetVec<Data> :: Clear() noexcept
	{
		size = 0;
		delete[] elements;
		elements = nullptr;	
	}
	
	// OrderedDictionaryContainer
	template<typename Data>
	inline const Data& SetVec<Data> :: Min() const
	{
		if( Empty() )
			throw std :: length_error("Container vuoto");
		return elements[head];
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: MinNRemove() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		const Data  *min= &Min();
		Data mincopy = *min;
		RemoveMin();
		return mincopy;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveMin() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		head = (head +1 ) % size;
		count--;
	}

	template<typename Data>
	inline const Data& SetVec<Data> :: Max() const
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		return elements[tail];
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: MaxNRemove()
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		const Data  *max = &Max();
		Data maxCopy = *max;
		RemoveMax();
		return maxCopy;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveMax() 
	{
		if(Empty())
			throw std :: length_error("Container vuoto");
		count--;
		tail = (size + tail -1) % size;
	}

	//Predecessor
	template<typename Data>
	inline const Data& SetVec<Data> :: Predecessor(const Data& dat) const
	{
		unsigned long int index = binSearch(dat);
		if(index == head || index == size )	//Se index e il minimo
			throw  std::length_error("Non eiste il predecessore\n");
		else
			return (*this)[index - 1];	//Posizioe nel vettore
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: PredecessorNRemove (const Data& dat) 
	{
		unsigned long int index = binSearch(dat);	//indice predecessore
		if(index == head || index == size)	//se dat e' il minimo
			throw  std::length_error("Non eiste il predecessore\n");
		Data val = operator[](index);
		Remove(operator[](index - 1));
		return val;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemovePredecessor (const Data& dat) 
	{
		unsigned long int i = binSearch ( dat );	//indice minimo
		if(i == tail)	//se dat e' il minimo
			throw  std::length_error("Non eiste il predecessore\n");
		Remove( (*this)[i+1] );
	}
	
	
	//Successor
	template<typename Data>
	inline const Data& SetVec<Data> :: Successor(const Data& dat) const
	{
		unsigned long int index = binSearch(dat);
		if(index == tail || index == size) //Se index e il massimo o non apprtiene al vettore
			throw  std::length_error("Non eiste il predecessore\n");
		else
			return (*this)[index + 1];	//Posizioe nel vettore
	}
	
	template<typename Data>
	inline Data SetVec<Data> :: SuccessorNRemove (const Data& dat) 
	{
		unsigned long int index = binSearch(dat);	//indice dat
		if(index == tail || index == size)	//se dat e' il massimo'
			throw  std::length_error("Non eiste il predecessore\n");
		Data val = operator[](index);
		Remove( (*this)[index + 1] );
		return val;
	}
	
	template<typename Data>
	inline void SetVec<Data> :: RemoveSuccessor (const Data& dat) 
	{
		unsigned long int i = binSearch ( dat );	//indice dat
		if(i == tail || i == size)	//se dat e' il massimo'
			throw  std::length_error("Non eiste il predecessore\n");
		Remove( (*this)[i+1] );
	}

	// DictionaryContainer functions
	template<typename Data>
	inline bool SetVec<Data> :: Insert(const Data& dat)
	{
		if(size == count)	//Buffer pieno
			Resize( 2*size +1 );
		if( dat < elements[head] )	// E minore del minimo
		{
			std :: cout << dat << " is Min\n";
			count++;
			head = (size - head ) % size;
			elements[head] = dat;
			
			std::cout << "Head: " << head << std::endl;
		}
		else if (dat > elements[tail])
		{
			std :: cout << dat << " is Max, old tail: " << tail;;
			
			tail = (tail + 1) % size;
			std::cout << " new tail: " << tail << std::endl;
			count++;
			elements[tail] = dat;
		}else
		{
			std::cout << "in the middle, count: " << count;
			unsigned long int i = 0;
			while( i<count && dat > (*this)[i] )
					i++;
			if( (*this)[i-1] == dat )
				return false;
			else
			{
				count++;
				for(unsigned long int j=count-1; j>i; j--)
					at(j) = (*this)[j-1];
				at(i) = dat;
				tail = (tail + 1) % size;
			}
		}
		//std :: cout << "head: " << head << ", tail: " << tail << ", size: "<< size <<", count=" << count << std::endl;
		std::cout << "Count =" << count <<  ", In insert: ";
		for(unsigned i=0; i<count; i++)
			std::cout << at(i) << ", ";
		std::cout << std::endl;
		return true;
	}

	template<typename Data>
	inline bool SetVec<Data> :: Insert(Data&& dat) noexcept
	{
		if(size == count)	//Buffer pieno
			Resize( 2*size +1 );
		if( dat < elements[head] )	// E minore del minimo
		{
			std :: cout << dat << " is Min\n";
			count++;
			head = (size - head ) % size;
			elements[head] = std :: move(dat);
		}
		else if (dat > elements[tail])
		{
			std :: cout << dat << " is Max\n";
			tail = (tail + 1) % size;
			count++;
			elements[tail] = std :: move(dat);
		}else
		{
			unsigned long int i = 0;
			while( i<count &&  dat > (*this)[i] )
				i++;
			if( (*this)[i-1] == dat )
				return false;
			else
			{
				count++;
				for(unsigned long int j=count-1; j>i; j--)
					at(j) = (*this)[j-1];
				at(i) = std :: move(dat);
				tail = (tail + 1) % size;
			}
		}
		//std :: cout << "head: " << head << ", tail: " << tail << ", size: "<< size <<", count=" << count << std::endl;
		std::cout << "Count =" << count <<  ", In insert: ";
		// for(unsigned i=0; i<count; i++)
		// 	std::cout << at(i) << ", ";
		// std::cout << std::endl;
		return true;
	}

	template<typename Data>
	inline bool SetVec<Data> :: Remove(const Data& dat)
	{
		unsigned long int i = binSearch(dat);
		if(i == size)
			return false;
		for(;i < count-1; i++)
			at(i) = (*this)[i+1];
		return true;
	}

	template<typename Data>
	inline const Data& SetVec<Data> :: operator[](unsigned long int i)  const
	{
		//std :: cout << "Index: " << i << " size= " << size <<std::endl;
		if( i<0 || i >= count)
		{
			std::cout << "Indice " << i << "errato\n";
			throw std :: out_of_range("Indice errato");
		}
		return elements[ (head + i ) % size ];
	}

	// ResizableContainer function
	template<typename Data>
	inline void SetVec<Data> :: Resize(unsigned long int N)
	{
		std :: cout << "Resize in " << N << std::endl;
		Data *vec = new Data[N];
		if(count > N)
			count = N;
		for(unsigned long int i=0; i<count; i++)
		{
			vec[i] = (*this)[i];// elements[ (head+i)%size ];
			std:: cout <<  (*this)[i] <<", ";		
		}	
		
		delete[] elements;
		elements = vec;
		head = 0;
		size = N;
		tail = (size + count -1) % size;
		
		std :: cout << "Resize head: " << head << ", tail: " << tail << ", count=" << count << std::endl;
		std::cout << "In Resize: ";
		for(unsigned i=0; i<count; i++)
			std::cout << at(i) << ", ";
		std::cout << std::endl;
	}
	
	//Auxiliary functions
	template<typename Data>	//binary search, return size if dat will not be found
	inline unsigned long int SetVec<Data> :: binSearch( const Data& dat) const
	{
		unsigned long int i=0, j=size-1;
		do{
			unsigned long int q = (i+j)/2;
			if( elements[head + q] == dat )
				return elements[head + q];
			else if ( elements[head + q] < dat )
				i = q + 1;
			else
				j = q -1;
		}
		while( i <= j);
		return size;	// se dat non e presente
	}

	template<typename Data>
	inline Data& SetVec<Data> :: at(unsigned long int i) 
	{
		//std :: cout << "Index: " << i << " size= " << size <<std::endl;
		if( i<0 || i >= count)
			throw std :: out_of_range("Indice-- errato");
		return elements[ (head + i) % size ];
	}
}
//set, no duplicati e ordinato, ric binaria
// Vettore circolare, per migliorare l'inserimento all'inizio, 2 indici head  e tail,  minimo e massimo
//head + size   prox cella libera, mod capcity
//size e capacity
//Ereditare Vector in modo protected e  le 3 funzioni in modalta pubblica;   metodo Exists
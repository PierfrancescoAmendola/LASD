
//
//  setvec.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//

namespace lasd
{

  // Funzione di BinarySearch

  template <typename Data>
  unsigned long SetVec<Data>::BinarySearch(const Data &data) const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      return size;
    }

    unsigned long start = 0;
    unsigned long end = size - 1;

    while (start <= end)
    {
      unsigned long center = start + (end - start) / 2;
      unsigned long physCenter = physicalIndex(center);

      if (Vector<Data>::elements[physCenter] == data)
      {
        return center; // Ritorna l'indice logico
      }

      if (Vector<Data>::elements[physCenter] < data)
      {
        start = center + 1;
      }
      else
      {
        if (center == 0)
        {
          break;
        }
        end = center - 1;
      }
    }

    return size;
  }

  template <typename Data>
  unsigned long SetVec<Data>::BinarySearchInsertion(const Data &data) const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      return 0;
    }

    unsigned long low = 0;
    unsigned long high = size - 1;

    while (low <= high)
    {
      unsigned long midPos = low + (high - low) / 2;

      if (Vector<Data>::elements[midPos] == data)
      {
        return midPos;
      }

      if (Vector<Data>::elements[midPos] < data)
      {
        low = midPos + 1;
      }
      else
      {
        if (midPos == 0)
        {
          break;
        }
        high = midPos - 1;
      }
    }

    return low;
  }

  /* ************************************************************************** */

  // Funzione per lo ShiftRight
  template <typename Data>
  void SetVec<Data>::ShiftRight(unsigned long logicalIndex)
  {
    if (size >= capacity || Vector<Data>::elements == nullptr)
    {
      unsigned long newCap = (capacity == 0) ? 1 : capacity * 2;
      Data *newArr = new Data[newCap]{};

      for (unsigned long idx = 0; idx < size; idx++)
      {
        unsigned long oldIdx = physicalIndex(idx);

        if (idx < logicalIndex)
        {
          newArr[idx] = Vector<Data>::elements[oldIdx];
        }
        else
        {
          newArr[idx + 1] = Vector<Data>::elements[oldIdx];
        }
      }

      delete[] Vector<Data>::elements;
      Vector<Data>::elements = newArr;
      capacity = newCap;
      head = 0;
      tail = size + 1;
    }
    else
    {
      tail = (tail + 1) % capacity;

      for (unsigned long i = size; i > logicalIndex; i--)
      {
        Vector<Data>::elements[physicalIndex(i)] = Vector<Data>::elements[physicalIndex(i - 1)];
      }
    }

    size++;
  }

  // Funzione per lo ShiftLeft
  template <typename Data>
  void SetVec<Data>::ShiftLeft(unsigned long logicalIndex)
  {
    if (size == 0)
      return;

    for (unsigned long idx = logicalIndex; idx < size - 1; idx++)
    {
      Vector<Data>::elements[physicalIndex(idx)] =
          Vector<Data>::elements[physicalIndex(idx + 1)];
    }

    tail = (tail == 0) ? capacity - 1 : tail - 1;
    size--;

    if (size > 0 && size <= capacity / 4 && capacity > 1)
    {
      unsigned long reducedCap = capacity / 2;
      Data *reducedArr = new Data[reducedCap]{};

      for (unsigned long j = 0; j < size; j++)
      {
        reducedArr[j] = Vector<Data>::elements[physicalIndex(j)];
      }

      delete[] Vector<Data>::elements;
      Vector<Data>::elements = reducedArr;
      capacity = reducedCap;
      head = 0;
      tail = size;
    }
  }

  /* ************************************************************************** */

  // Specific constructors
  // Costruttore da TraversableContainer
  template <typename Data>
  SetVec<Data>::SetVec(const TraversableContainer<Data> &container) : Vector<Data>(), capacity(0)
  {
    std::vector<Data> temp;

    container.Traverse([&temp](const Data &value)
                       { temp.push_back(value); });

    for (const auto &val : temp)
    {
      Insert(val);
    }
  }

  // Costruttore da MappableContainer
  template <typename Data>
  SetVec<Data>::SetVec(MappableContainer<Data> &&container) : Vector<Data>(), capacity(0)
  {
    std::vector<Data> temp;

    container.Map([&temp](Data &value){ temp.push_back(std::move(value)); });

    for (auto &val : temp)
    {
      Insert(std::move(val));
    }
  }

  /* ************************************************************************** */
  // Copy constructor

  template <typename Data>
  SetVec<Data>::SetVec(const SetVec<Data> &other)
  {
    *this = other; // Usa l'operatore di assegnazione per copiare
  }

  // Move constructor
  template <typename Data>
  SetVec<Data>::SetVec(SetVec<Data> &&other) noexcept
  {
    *this = std::move(other); // Usa l'operatore di assegnazione per spostare
  }

  /* ************************************************************************** */

  // Copy assignment
  template <typename Data>
  SetVec<Data> &SetVec<Data>::operator=(const SetVec<Data> &other)
  {
    if (this != &other)
    {
      Vector<Data>::operator=(other);
      capacity = other.capacity;
    }
    return *this;
  }

  // Move assignment
  template <typename Data>
  SetVec<Data> &SetVec<Data>::operator=(SetVec<Data> &&other) noexcept
  {
    if (this != &other)
    {
      Vector<Data>::operator=(std::move(other));
      capacity = other.capacity;
      other.capacity = 0;
    }
    return *this;
  }


  /* ************************************************************************** */

  // Comparison operators

  template <typename Data>
  bool SetVec<Data>::operator==(const SetVec<Data> &other) const noexcept
  {
    return Vector<Data>::operator==(other);
  }

  template <typename Data>
  inline bool SetVec<Data>::operator!=(const SetVec<Data> &other) const noexcept
  {
    return !(*this == other);
  }

  /* ************************************************************************** */

  // Specific member functions (inherited from OrderedDictionaryContainer)
  //Funzione di Min
  template <typename Data>
  const Data &SetVec<Data>::Min() const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    return Vector<Data>::elements[head];
  }

  

  //Funzione di MinNRemove
  template <typename Data>
  Data SetVec<Data>::MinNRemove()
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    Data minimum = Vector<Data>::elements[0];
    ShiftLeft(0);

    return minimum;
  }

  //Funzione di REmoveMin
  template <typename Data>
  void SetVec<Data>::RemoveMin()
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    ShiftLeft(0);
  }

  //Funzione di Max
  template <typename Data>
  const Data &SetVec<Data>::Max() const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    return Vector<Data>::elements[physicalIndex(size - 1)];
  }

  //Funzione di MaxNRemove
  template <typename Data>
  Data SetVec<Data>::MaxNRemove()
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    Data maximum = Vector<Data>::elements[size - 1];
    ShiftLeft(size - 1);

    return maximum;
  }

  //Funzione di RemoveMax
  template <typename Data>
  void SetVec<Data>::RemoveMax()
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    ShiftLeft(size - 1);
  }


  /* ************************************************************************** */


  template <typename Data>
  const Data &SetVec<Data>::Predecessor(const Data &data) const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos == 0)
    {
      throw std::length_error("Predecessor not found");
    }

    return Vector<Data>::elements[pos - 1];
  }

  template <typename Data>
  Data SetVec<Data>::PredecessorNRemove(const Data &data)
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos == 0)
    {
      throw std::length_error("Predecessor not found");
    }

    Data predValue = Vector<Data>::elements[pos - 1];
    ShiftLeft(pos - 1);

    return predValue;
  }

  template <typename Data>
  void SetVec<Data>::RemovePredecessor(const Data &data)
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos == 0)
    {
      throw std::length_error("Predecessor not found");
    }

    ShiftLeft(pos - 1);
  }


  /* ************************************************************************** */

  template <typename Data>
  const Data &SetVec<Data>::Successor(const Data &data) const
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos >= size || Vector<Data>::elements[pos] == data)
    {
      if (pos + 1 >= size)
      {
        throw std::length_error("Successor not found");
      }
      pos++;
    }

    return Vector<Data>::elements[pos];
  }

  template <typename Data>
  Data SetVec<Data>::SuccessorNRemove(const Data &data)
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos >= size || Vector<Data>::elements[pos] == data)
    {
      if (pos + 1 >= size)
      {
        throw std::length_error("Successor not found");
      }
      pos++;
    }

    Data succValue = Vector<Data>::elements[pos];
    ShiftLeft(pos);

    return succValue;
  }

  template <typename Data>
  void SetVec<Data>::RemoveSuccessor(const Data &data)
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      throw std::length_error("Empty set");
    }

    unsigned long pos = BinarySearchInsertion(data);

    if (pos >= size || Vector<Data>::elements[pos] == data)
    {
      if (pos + 1 >= size)
      {
        throw std::length_error("Successor not found");
      }
      pos++;
    }

    ShiftLeft(pos);
  }


  /* ************************************************************************** */

  // Specific member functions (inherited from DictionaryContainer)


  // Insert
  template <typename Data>
  bool SetVec<Data>::Insert(const Data &data)
  {
    if (size > 0 && Vector<Data>::elements != nullptr)
    {
      unsigned long insertPos = BinarySearchInsertion(data);

      if (insertPos < size && Vector<Data>::elements[insertPos] == data)
      {
        return false;
      }

      ShiftRight(insertPos);
      Vector<Data>::elements[insertPos] = data;
    }
    else
    {
      capacity = 1;
      Vector<Data>::elements = new Data[capacity]{};
      Vector<Data>::elements[0] = data;
      size = 1;
    }

    return true;
  }

  //insert move
  template <typename Data>
  bool SetVec<Data>::Insert(Data &&data)
  {
    if (size > 0 && Vector<Data>::elements != nullptr)
    {
      unsigned long insertPos = BinarySearchInsertion(data);

      if (insertPos < size && Vector<Data>::elements[insertPos] == data)
      {
        return false;
      }

      ShiftRight(insertPos);
      Vector<Data>::elements[insertPos] = std::move(data);
    }
    else
    {
      capacity = 1;
      Vector<Data>::elements = new Data[capacity]{};
      Vector<Data>::elements[0] = std::move(data);
      size = 1;
    }

    return true;
  }

  // Remove
  template <typename Data>
  bool SetVec<Data>::Remove(const Data &data)
  {
    if (size == 0 || Vector<Data>::elements == nullptr)
    {
      return false;
    }

    unsigned long pos = BinarySearch(data);

    if (pos == size)
    {
      return false;
    }

    ShiftLeft(pos);

    return true;
  }

  /* ************************************************************************** */
  // Specific member function (inherited from TestableContainer)

  template <typename Data>
  bool SetVec<Data>::Exists(const Data &data) const noexcept
  {
    return BinarySearch(data) != size;
  }

} // namespace lasd

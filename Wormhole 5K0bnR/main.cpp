#include <cstdint>
#include <iostream>
#include<ctime>
#include "list/list.hpp"
#include "zlasdtest/test.hpp"
//#include "zmytest/test.hpp"

/* ************************************************************************** */





/* ************************************************************************** */

// lasd::Vector<int> makeV(int); 
// lasd::Vector<int>&& makeRandV(); 

int main() 
{
  srand(time(NULL));
  std::cout << "LASD Libraries 2025" << std::endl;
  lasdtest();
  lasd::List<int> l{};
  l.InsertAtBack(3);
  l.InsertAtBack(rand()% 100);
  l.InsertAtBack(rand()% 100);
  for(unsigned i=0; i<l.Size(); i++)
    std::cout << l[i] << ", ";

  // lasd :: SetVec<int> vec( makeV(10) );
 
  // for(unsigned i=0; i<10; i++)
  //   vec.Insert(rand() %20);

  // // vec.Resize(20); 
  // // std::cout << "After rezize\n";
  // // for(unsigned i=0; i<10; i++)
  // //   vec.Insert(2*i +1);

  // for ( unsigned int  i=0; i<vec.Size(); i++ )
  //   std::cout << vec[i] << ", ";
  // return 0;
}

// lasd::Vector<int> makeV(int n)
// {
//   lasd::Vector<int> v (n);
//   for ( unsigned int  i=0; i<v.Size(); i++ )
//     v[i] = 2*i;
  
//   // std::cout << v.Front() << ", " << v.Back() << std::endl;
//   return v;
// }
   
// lasd::Vector<int>&& makeRandV()
// {
//   bool is_sorted(lasd::Vector<int>&);
//   srand(time(NULL));
  
//   int n =  rand() % 100;
//   lasd :: Vector<int> v(n);
//   std :: cout << "N ="<< n << std::endl; 
//   for(int i=0; i<n; i++)
//     v[i] = rand() % 100;
  
//   lasd :: SortableVector<int> v2 ( v );
//   std::cout <<"v2n";
  
//   if(! ( is_sorted(v2) ) )
//   {
//     std::cout << "Non E ordinato";
//     std::cout << std::endl;
//   }  
//   return std :: move(v);
// }

// bool is_sorted(lasd::Vector<int>& v)
// {
//   std::cout << "Is sorted\n";
//   for(unsigned i=1; i < v.Size(); i++)
//   {
//     std::cout << v[i] << " ";
//     if(v[i] < v[i-1])
//       return false;
//   }
//   std :: cout << std::endl;
//   return true;
// }
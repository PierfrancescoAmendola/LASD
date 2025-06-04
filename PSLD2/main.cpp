//
//  main.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 21/05/25.
//


#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"


// /* ************************************************************************** */

#include <iostream>

// /* ************************************************************************** */

int main()
{
  std::cout << "Lasd Libraries 2025" << std::endl;
  uint testnum = 0;
  uint testerr = 0;

  int scelta = -1;
  while (scelta != 0)
  {
    std::cout << "" << std::endl;
    std::cout << "-------------------Benevenuto alla fine dei giochi, pt.2-------------------" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Scegli il test con cui mettere alla prova il tuo codice: " << std::endl;
    std::cout << "" << std::endl;

    std::cout << "" << std::endl;
    std::cout << "Test prima parte:" << std::endl;
    std::cout << "" << std::endl;

    std::cout << "1)Test n°1 SimpleTest del Professore " << std::endl;
    std::cout << "2)Test n°2 List Test & Vector Test" << std::endl;
    std::cout << "3)Test n°3 TestMioEsercizio 1B" << std::endl;
    std::cout << "4)Test n°4 stressTestVectorAndList" << std::endl;
    std::cout << "5)Test n°5 mySetVecExtendedTests" << std::endl;
    std::cout << "6)Test n°6 SetVec" << std::endl;
    std::cout << "7)Test n°7 SetList" << std::endl;

    std::cout << "" << std::endl;
    std::cout << "Test seconda parte:" << std::endl;
    std::cout << "" << std::endl;


    std::cout << "8)Test n°8 HeapVec" << std::endl;
    std::cout << "9)Test n°9 HeapVec invasivo " << std::endl;
    std::cout << "10)Test n°10 PqHeap invasivo" << std::endl;

    std::cout << "0)Exit" << std::endl;

    
    std::cin >> scelta;
    if (scelta == 1)
      lasdtest();
    if (scelta == 2)
      personalLasdTest();
    if (scelta == 3)
      myTestSimpleExercise1B();
    if (scelta == 4)
      stressTestVectorAndList();
    if (scelta == 5)
      mySetVecExtendedTests(testnum, testerr);
    if (scelta == 6)
      testSetVec();
    if (scelta == 7)
      testSetLst();
    if (scelta == 8)
      testHeapVec();
    if (scelta == 9)
      TestHeapVec();
    if (scelta == 10)
      TestPqHeap();

      

  }

  std::cout<<""<<std::endl;

  std::cout<<"Se si è arrivati fino a questo punto, allora tutti i test sono stati superati."<<std::endl;
  std::cout<<"Congratulazioni, ha superato le sfide della prima libreria e della seconda, si merita il massimo"<<std::endl;

  std::cout<<""<<std::endl;
  return 0;

  

}
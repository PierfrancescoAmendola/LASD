//
//  main.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//


#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"


// /* ************************************************************************** */

#include <iostream>

// /* ************************************************************************** */

// int main() {
//   std::cout << "LASD Libraries 2025" << std::endl;
//   lasdtest();
//   //mytest();
//   return 0;
// }

// int main() {
//   unsigned short index = 3;

//   while(index != 0){
//     std::cout << std::endl << std::endl << "Inserire 0 per uscire, 1 per avviare il Simple Test, 2 per avviare il Personal Test"<< std::endl << std::endl <<
//       "0) Esci" << std::endl << "1) Simple Test" << std::endl << "2) Personal Test" << std::endl;
//     std::cout << "Numero da inserire: ";
//     std::cin >> index;
//     std::cout << std::endl << std::endl;

//     while(std::cin.fail()){
//       std::cin.clear();
//       std::cin.ignore();
//       std::cout << "Input non valido. Inserisci un numero: ";
//       std::cin >> index;
//       std::cout << std::endl << std::endl;
//     }

//     switch (index){
//       case 0:
//         return 0;
//       break;
//       case 1:
//         std::cout << "Lasd Libraries 2025" << std::endl;
//         lasdtest(); // Call in the menu of your library test!
//       break;
//       case 2:
//         std::cout << "Personal Lasd Libraries 2023" << std::endl;
//         personalLasdTest();
//       break;

//       default:
//         std::cout << "Inserire un numero valido";
//       break;
//     }
//   }
// }

int main()
{
  std::cout << "Lasd Libraries 2025" << std::endl;
  uint testnum = 0;
  uint testerr = 0;

  int scelta = -1;
  while (scelta != 0)
  {
    std::cout << "" << std::endl;
    std::cout << "-------------------Benevenuto alla fine dei giochi-------------------" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Scegli il test con cui mettere alla prova il tuo codice: " << std::endl;
    std::cout << "" << std::endl;
    std::cout << "1)Test n°1 SimpleTest del Professore " << std::endl;
    std::cout << "3)Test n°2 List Test & Vector Test" << std::endl;
    std::cout << "6)Test n°3 TestMioEsercizio 1B" << std::endl;
    std::cout << "8)Test n°4 testMarcoSetVec" << std::endl;
    std::cout << "9)Test n°5 stressTestVectorAndList" << std::endl;
    std::cout << "10)Test n°6 mySetVecExtendedTests" << std::endl;
    std::cout << "11)Test n°7 SetVec" << std::endl;
    std::cout << "12)Test n°8 SetList" << std::endl;

    std::cout << "0)Exit" << std::endl;
    std::cin >> scelta;
    if (scelta == 1)
      lasdtest();
    if (scelta == 2)
      personalLasdTest();
    if (scelta == 3)
      myTestSimpleExercise1B();
    if (scelta == 4)
      TestMarco();
    if (scelta == 5)
      stressTestVectorAndList();
    if (scelta == 6)
      mySetVecExtendedTests(testnum, testerr);
    if (scelta == 7)
      testSetVec();
    if (scelta == 8)
      testSetLst();
  }
  return 0;

}
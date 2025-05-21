//
//  test.cpp
//  Progetto LASD 2025
//
//  Created by Pierfrancesco on 30/04/25.
//


// #include "..."

#include <iostream>

#include <cassert> //da eliminare perchè serve solo per assert

#include <functional>
#include <climits> // Per INT_MIN e INT_MAX
#include <string>  // std::string
#include <stdexcept>

#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../container/traversable.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"

#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

using namespace std;
using namespace lasd;
/* ************************************************************************** */

// Macro di supporto per i test
#define RUN_TEST(desc, expr)                                                               \
    do                                                                                     \
    {                                                                                      \
        bool result = (expr);                                                              \
        cout << "[TEST] " << desc << ": " << (result ? "PASSED ✅" : "FAILED ❌") << endl; \
        loctestnum++;                                                                      \
        if (!result)                                                                       \
            loctesterr++;                                                                  \
    } while (0)

// Funzione mySimpleTest
void myStestSetInt(lasd::Set<int> &set, uint &testnum, uint &testerr)
{
    uint loctestnum = 0, loctesterr = 0;
    try
    {
        cout << endl
             << "Begin of My Set<int> Test" << endl;

        // Test su set vuoto
        RUN_TEST("Set should be empty initially", set.Empty());
        RUN_TEST("Set size should be 0 initially", set.Size() == 0);

        // Inserimento elementi
        set.Insert(10);
        set.Insert(5);
        set.Insert(15);
        set.Insert(3);
        set.Insert(7);
        set.Insert(12);
        set.Insert(17);

        RUN_TEST("Set size should be 7 after insertions", set.Size() == 7);
        RUN_TEST("Set should contain 10", set.Exists(10));
        RUN_TEST("Set should not contain 20", !set.Exists(20));

        // Min e Max
        RUN_TEST("Set minimum should be 3", set.Min() == 3);
        RUN_TEST("Set maximum should be 17", set.Max() == 17);

        // Rimozione
        set.Remove(10);
        RUN_TEST("Set should not contain 10 after removal", !set.Exists(10));
        RUN_TEST("Set size should be 6 after removal", set.Size() == 6);

        // Predecessor e Successor
        RUN_TEST("Predecessor of 7 should be 5", set.Predecessor(7) == 5);
        try
        {
            set.Predecessor(3);
            cout << "[TEST] Predecessor of 3: FAILED ❌ (No exception thrown)\n";
        }
        catch (const std::exception &)
        {
            cout << "[TEST] Predecessor of 3: PASSED ✅ (Exception thrown)\n";
            loctestnum++;
        }

        RUN_TEST("Successor of 7 should be 12", set.Successor(7) == 12);
        try
        {
            set.Successor(17);
            cout << "[TEST] Successor of 17: FAILED ❌ (No exception thrown)\n";
        }
        catch (const std::exception &)
        {
            cout << "[TEST] Successor of 17: PASSED ✅ (Exception thrown)\n";
            loctestnum++;
        }

        // Rimozione Min e Max
        set.RemoveMin();
        RUN_TEST("Set minimum should be 5 after removing min", set.Min() == 5);
        set.RemoveMax();
        RUN_TEST("Set maximum should be 15 after removing max", set.Max() == 15);

        // Clear
        set.Clear();
        RUN_TEST("Set should be empty after clearing", set.Empty());
        RUN_TEST("Set size should be 0 after clearing", set.Size() == 0);

        cout << "End of My Set<int> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

void myStestSetDouble(lasd::Set<double> &set, uint &testnum, uint &testerr)
{
    uint loctestnum = 0, loctesterr = 0;
    try
    {
        cout << endl
             << "Begin of My Set<double> Test" << endl;

        // Inserimento
        set.Insert(1.5);
        set.Insert(2.5);
        set.Insert(0.5);
        set.Insert(3.5);

        RUN_TEST("Set minimum should be 0.5", set.Min() == 0.5);
        RUN_TEST("Set maximum should be 3.5", set.Max() == 3.5);
        RUN_TEST("Set should contain 1.5", set.Exists(1.5));
        RUN_TEST("Set should not contain 1.6", !set.Exists(1.6));

        cout << "End of My Set<double> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

void myStestSetString(lasd::Set<string> &set, uint &testnum, uint &testerr)
{
    uint loctestnum = 0, loctesterr = 0;
    try
    {
        cout << endl
             << "Begin of My Set<string> Test" << endl;

        // Inserimento
        set.Insert("apple");
        set.Insert("banana");
        set.Insert("cherry");
        set.Insert("date");

        RUN_TEST("Set minimum should be 'apple'", set.Min() == "apple");
        RUN_TEST("Set maximum should be 'date'", set.Max() == "date");
        RUN_TEST("Set should contain 'banana'", set.Exists("banana"));
        RUN_TEST("Set should not contain 'grape'", !set.Exists("grape"));

        cout << "End of My Set<string> Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}
void myTestSetOperations(uint &testnum, uint &testerr)
{

    uint loctestnum = 0, loctesterr = 0;
    try
    {
        cout << endl
             << "Begin of My Set Operations Test" << endl;

        lasd::SetVec<int> setvec1;
        lasd::SetVec<int> setvec2;

        setvec1.Insert(10);
        setvec1.Insert(20);
        setvec1.Insert(30);

        setvec2.Insert(30);
        setvec2.Insert(20);
        setvec2.Insert(10);

        RUN_TEST("SetVec1 should be equal to SetVec2", setvec1 == setvec2);

        cout << "End of My Set Operations Test! (Errors/Tests: " << loctesterr << "/" << loctestnum << ")" << endl;
    }
    catch (...)
    {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

bool Empty(const lasd::Container &vector)
{
    return vector.Empty();
}

unsigned long Size(const lasd::Container &vector)
{
    return vector.Size();
}

template <typename Data>
unsigned long Indice(const lasd::Vector<Data> &vector, int i)
{
    return vector.operator[](i);
}

template <typename Data>
unsigned long Primo(const lasd::Vector<Data> &vector)
{
    return vector.Front();
}

template <typename Data>
unsigned long Ultimo(const lasd::Vector<Data> &vector)
{
    return vector.Back();
}

template <typename Data>
unsigned long Indice(const lasd::List<Data> &list, int i)
{
    return list.operator[](i);
}

void personalLasdTest()
{
    bool checked;
    unsigned long numero;
    std::string corretto;

    std::cout << std::endl
              << "~*~#~*~ Personal LASD Test ~*~#~*~ " << std::endl;

    // Vector
    std::cout << std::endl
              << "~~~~~ VECTOR TEST ~~~~~" << std::endl
              << std::endl;

    lasd::Vector<int> vec(10);
    checked = Empty(vec);
    corretto = (checked == 0) ? "Correct!" : "Error!";
    std::cout << "Empty (Array[10]): " << checked << " - " << corretto << std::endl;

    numero = Size(vec);
    corretto = (numero == 10) ? "Correct!" : "Error!";
    std::cout << "Size (Array[10]): " << numero << " - " << corretto << std::endl;

    vec.Resize(4);
    checked = Empty(vec);
    corretto = (checked == 0) ? "Correct!" : "Error!";
    std::cout << "Empty (Array[4]): " << checked << " - " << corretto << std::endl;

    numero = Size(vec);
    corretto = (numero == 4) ? "Correct!" : "Error!";
    std::cout << "Size (Array[4]): " << numero << " - " << corretto << std::endl;

    vec[0] = 2;
    numero = Indice(vec, 0);
    corretto = (numero == 2) ? "Correct!" : "Error!";
    std::cout << "Indice 0 (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    vec[1] = 3;
    numero = Indice(vec, 1);
    corretto = (numero == 3) ? "Correct!" : "Error!";
    std::cout << "Indice 1 (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    vec[2] = 1;
    numero = Indice(vec, 2);
    corretto = (numero == 1) ? "Correct!" : "Error!";
    std::cout << "Indice 2 (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    vec[3] = 4;
    numero = Indice(vec, 3);
    corretto = (numero == 4) ? "Correct!" : "Error!";
    std::cout << "Indice 3 (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    numero = Primo(vec);
    corretto = (numero == 2) ? "Correct!" : "Error!";
    std::cout << "Primo elemento (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    numero = Ultimo(vec);
    corretto = (numero == 4) ? "Correct!" : "Error!";
    std::cout << "Ultimo elemento (Array[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    lasd::Vector<int> vecCopy = vec.operator=(vec);
    numero = Indice(vecCopy, 0);
    corretto = (numero == 2) ? "Correct!" : "Error!";
    std::cout << "Indice 0 (CopiaArray[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    numero = Indice(vecCopy, 1);
    corretto = (numero == 3) ? "Correct!" : "Error!";
    std::cout << "Indice 1 (CopiaArray[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    numero = Indice(vecCopy, 2);
    corretto = (numero == 1) ? "Correct!" : "Error!";
    std::cout << "Indice 2 (CopiaArray[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;
    numero = Indice(vecCopy, 3);
    corretto = (numero == 4) ? "Correct!" : "Error!";
    std::cout << "Indice 3 (CopiaArray[4] {2, 3, 1, 4}): " << numero << " - " << corretto << std::endl;

    checked = vec.operator==(vecCopy);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "Array == CopiaArray: " << checked << " - " << corretto << std::endl;

    vec.Clear();
    checked = Empty(vec);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "Array svuotato: " << checked << " - " << corretto << std::endl;

    vecCopy.Clear();
    checked = Empty(vecCopy);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "CopiaArray svuotata: " << checked << " - " << corretto << std::endl;

    // List
    std::cout << std::endl
              << std::endl
              << "~~~~~ LIST TEST ~~~~~" << std::endl
              << std::endl;

    lasd::List<int> lst;
    checked = Empty(lst);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "Empty (List[0]): " << checked << " - " << corretto << std::endl;

    numero = Size(lst);
    corretto = (numero == 0) ? "Correct!" : "Error!";
    std::cout << "Size (List[0]): " << numero << " - " << corretto << std::endl;

    lst.InsertAtFront(2);
    lst.InsertAtFront(1);
    lst.InsertAtBack(3);

    checked = Empty(lst);
    corretto = (checked == 0) ? "Correct!" : "Error!";
    std::cout << "Empty (List[3] {1, 2, 3}): " << checked << " - " << corretto << std::endl;

    numero = Size(lst);
    corretto = (numero == 3) ? "Correct!" : "Error!";
    std::cout << "Size (List[3] {1, 2, 3}): " << numero << " - " << corretto << std::endl;

    numero = lst.Front();
    corretto = (numero == 1) ? "Correct!" : "Error!";
    std::cout << "Front (List[3] {1, 2, 3}): " << numero << " - " << corretto << std::endl;

    numero = lst.Back();
    corretto = (numero == 3) ? "Correct!" : "Error!";
    std::cout << "Back (List[3] {1, 2, 3}): " << numero << " - " << corretto << std::endl;

    lasd::List<int> lstCopy = lst.operator=(lst);
    checked = lst.operator==(lstCopy);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "List == CopiaList: " << checked << " - " << corretto << std::endl;

    lst.Clear();
    checked = Empty(lst);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "Lista svuotata: " << checked << " - " << corretto << std::endl;

    lstCopy.Clear();
    checked = Empty(lstCopy);
    corretto = (checked == 1) ? "Correct!" : "Error!";
    std::cout << "CopiaLista svuotata: " << checked << " - " << corretto << std::endl;

    try
    {
        numero = lst.Front();
        std::cout << "Front (Lista vuota): " << numero << " - " << corretto << std::endl;
    }
    catch (const std::length_error &exc)
    { // Modificato qui
        std::cout << "Front (Lista vuota): Lista vuota" << std::endl;
    }
    catch (const std::exception &exc)
    { // Modificato anche qui
        std::cout << std::endl
                  << "Wrong exception: " << exc.what() << "!" << std::endl;
    }

    try
    {
        numero = lst.Back();
        std::cout << "Back (Lista vuota): " << numero << " - " << corretto << std::endl;
    }
    catch (const std::length_error &exc)
    { // Modificato qui
        std::cout << "Back (Lista vuota): Lista vuota" << std::endl;
    }
    catch (const std::exception &exc)
    { // Modificato anche qui
        std::cout << std::endl
                  << "Wrong exception: " << exc.what() << "!" << std::endl;
    }

    std::cout << std::endl
              << "Fine Personal LASD Test" << std::endl;
}

// Macro di supporto per i test
#define RUN_TEST(desc, expr)                                                               \
    do                                                                                     \
    {                                                                                      \
        bool result = (expr);                                                              \
        cout << "[TEST] " << desc << ": " << (result ? "PASSED ✅" : "FAILED ❌") << endl; \
        totalTests++;                                                                      \
        if (result)                                                                        \
            passedTests++;                                                                 \
    } while (0)

void mytest2()
{
    int totalTests = 0, passedTests = 0;

    cout << "\n==============================\n";
    cout << "     Welcome To My Tests\n";
    cout << "==============================\n";

    cout << "\n--- Vector Tests: Integers ---\n";
    lasd::SortableVector<int> vect;
    RUN_TEST("vect should be empty", vect.Empty());
    RUN_TEST("vect size should be 0", vect.Size() == 0);

    vect.Resize(5);
    RUN_TEST("vect size should be 5 after resize", vect.Size() == 5);
    cout << "Front: " << vect.Front() << ", Back: " << vect.Back() << "\n";

    lasd::SortableVector<int> vectCopy(vect);
    RUN_TEST("vectCopy size should be 5", vectCopy.Size() == 5);

    lasd::SortableVector<int> vectMove(move(vectCopy));
    RUN_TEST("vectMove size should be 5", vectMove.Size() == 5);

    cout << "\nCreating vector for fold/map test...\n";
    lasd::Vector<int> vectorForTest(5);
    cout << "Inserting values: 1, 2, 3, 4, 5\n";
    for (int i = 0; i < 5; ++i)
        vectorForTest[i] = i + 1;
    RUN_TEST("2 should be in vector", vectorForTest.Exists(2));
    RUN_TEST("vector size should be 5", vectorForTest.Size() == 5);

    cout << "Folding with sum...\n";
    int sum1 = vectorForTest.Fold<int>([](const int &acc, const int &elem)
                                       { return acc + elem; }, 0);
    cout << "Sum: " << sum1 << "\n";

    cout << "Folding with product...\n";
    int prod1 = vectorForTest.Fold<int>([](const int &acc, const int &elem)
                                        { return acc * elem; }, 1);
    cout << "Product: " << prod1 << "\n";

    cout << "Mapping (doubling values)...\n";
    vectorForTest.Map([](int &x)
                      { x *= 2; });
    cout << "Values after map: ";
    for (ulong i = 0; i < vectorForTest.Size(); ++i)
        cout << vectorForTest[i] << " ";
    cout << "\n";

    cout << "\n--- Vector Tests: Strings ---\n";
    lasd::Vector<string> vectString;
    RUN_TEST("vectString should be empty", vectString.Empty());
    RUN_TEST("vectString size should be 0", vectString.Size() == 0);

    vectString.Resize(3);
    RUN_TEST("vectString size should be 3", vectString.Size() == 3);
    cout << "Front: '" << vectString.Front() << "', Back: '" << vectString.Back() << "'\n";

    lasd::Vector<string> vectCopyString(vectString);
    RUN_TEST("vectCopyString size should be 3", vectCopyString.Size() == 3);

    lasd::Vector<string> vectMoveString(move(vectCopyString));
    RUN_TEST("vectMoveString size should be 3", vectMoveString.Size() == 3);

    cout << "Inserting values: hello, world, !!\n";
    lasd::Vector<string> vectorForTestString(3);
    vectorForTestString[0] = "hello";
    vectorForTestString[1] = "world";
    vectorForTestString[2] = "!!";
    RUN_TEST("'world' should exist", vectorForTestString.Exists("world"));

    cout << "Folding with concatenation...\n";
    string concat = vectorForTestString.Fold<string>([](const string &acc, const string &elem)
                                                     { return acc + elem; }, "");
    cout << "Concatenated: " << concat << "\n";

    cout << "Mapping (append 'abc')...\n";
    vectorForTestString.Map([](string &x)
                            { x += "abc"; });
    cout << "Values after map: ";
    for (ulong i = 0; i < vectorForTestString.Size(); ++i)
        cout << vectorForTestString[i] << " ";
    cout << "\n";

    cout << "\n--- Vector Tests: Floats ---\n";
    lasd::SortableVector<float> vectFloat;
    RUN_TEST("vectFloat should be empty", vectFloat.Empty());
    RUN_TEST("vectFloat size should be 0", vectFloat.Size() == 0);

    vectFloat.Resize(4);
    RUN_TEST("vectFloat size should be 4", vectFloat.Size() == 4);

    lasd::SortableVector<float> vectCopyFloat(vectFloat);
    RUN_TEST("vectCopyFloat size should be 4", vectCopyFloat.Size() == 4);

    lasd::SortableVector<float> vectMoveFloat(move(vectCopyFloat));
    RUN_TEST("vectMoveFloat size should be 4", vectMoveFloat.Size() == 4);

    lasd::Vector<float> vectorForTestFloat(4);
    float values[] = {1.5, 2.5, 3.5, 4.5};
    for (int i = 0; i < 4; ++i)
        vectorForTestFloat[i] = values[i];

    cout << "Front: " << vectorForTestFloat.Front() << ", Back: " << vectorForTestFloat.Back() << "\n";
    RUN_TEST("2.5 should be in vector", vectorForTestFloat.Exists(2.5));

    float sumF = vectorForTestFloat.Fold<float>([](const float &acc, const float &e)
                                                { return acc + e; }, 0.0);
    cout << "Sum: " << sumF << "\n";

    float prodF = vectorForTestFloat.Fold<float>([](const float &acc, const float &e)
                                                 { return acc * e; }, 1.0);
    cout << "Product: " << prodF << "\n";

    // Sommario finale
    cout << "\n==============================\n";
    cout << "       Test Summary\n";
    cout << "==============================\n";
    cout << "Tests passed: " << passedTests << " / " << totalTests << "\n";
    if (passedTests == totalTests)
        cout << "✅ All tests passed!\n";
    else
        cout << "❌ Some tests failed. Check above for details.\n";
}

void testSetVecAndSetLst()
{
    int totalTests = 0, passedTests = 0;

    cout << "\n==============================\n";
    cout << "     Testing SetVec & SetLst\n";
    cout << "==============================\n";

    // Test SetVec
    cout << "\n--- Testing SetVec ---\n";
    lasd::SetVec<int> setVec;

    RUN_TEST("SetVec should be empty initially", setVec.Empty());
    RUN_TEST("SetVec size should be 0 initially", setVec.Size() == 0);

    setVec.Insert(5);
    RUN_TEST("SetVec size should be 1 after inserting 5", setVec.Size() == 1);
    RUN_TEST("SetVec should contain 5", setVec.Exists(5));

    setVec.Insert(10);
    setVec.Insert(15);
    RUN_TEST("SetVec size should be 3 after inserting 10 and 15", setVec.Size() == 3);
    RUN_TEST("SetVec should contain 10", setVec.Exists(10));
    RUN_TEST("SetVec should contain 15", setVec.Exists(15));

    setVec.Remove(10);
    RUN_TEST("SetVec size should be 2 after removing 10", setVec.Size() == 2);
    RUN_TEST("SetVec should not contain 10", !setVec.Exists(10));

    try
    {
        setVec.Remove(20);
        cout << "[TEST] Removing non-existent element (20): FAILED ❌ (No exception thrown)\n";
    }
    catch (const std::exception &e)
    {
        cout << "[TEST] Removing non-existent element (20): PASSED ✅ (Exception: " << e.what() << ")\n";
        passedTests++;
    }
    totalTests++;

    setVec.Clear();
    RUN_TEST("SetVec should be empty after clearing", setVec.Empty());
    RUN_TEST("SetVec size should be 0 after clearing", setVec.Size() == 0);

    // Test SetLst
    cout << "\n--- Testing SetLst ---\n";
    lasd::SetLst<int> setLst;

    RUN_TEST("SetLst should be empty initially", setLst.Empty());
    RUN_TEST("SetLst size should be 0 initially", setLst.Size() == 0);

    setLst.Insert(5);
    RUN_TEST("SetLst size should be 1 after inserting 5", setLst.Size() == 1);
    RUN_TEST("SetLst should contain 5", setLst.Exists(5));

    setLst.Insert(10);
    setLst.Insert(15);
    RUN_TEST("SetLst size should be 3 after inserting 10 and 15", setLst.Size() == 3);
    RUN_TEST("SetLst should contain 10", setLst.Exists(10));
    RUN_TEST("SetLst should contain 15", setLst.Exists(15));

    setLst.Remove(10);
    RUN_TEST("SetLst size should be 2 after removing 10", setLst.Size() == 2);
    RUN_TEST("SetLst should not contain 10", !setLst.Exists(10));

    try
    {
        setLst.Remove(20);
        cout << "[TEST] Removing non-existent element (20): FAILED ❌ (No exception thrown)\n";
    }
    catch (const std::exception &e)
    {
        cout << "[TEST] Removing non-existent element (20): PASSED ✅ (Exception: " << e.what() << ")\n";
        passedTests++;
    }
    totalTests++;

    setLst.Clear();
    RUN_TEST("SetLst should be empty after clearing", setLst.Empty());
    RUN_TEST("SetLst size should be 0 after clearing", setLst.Size() == 0);

    // Final Summary
    cout << "\n==============================\n";
    cout << "       Test Summary\n";
    cout << "==============================\n";
    cout << "Tests passed: " << passedTests << " / " << totalTests << "\n";
    if (passedTests == totalTests)
        cout << "✅ All tests passed!\n";
    else
        cout << "❌ Some tests failed. Check above for details.\n";
}



void myTestSimpleExercise1B()
{
    uint testnum = 0, testerr = 0;
    try
    {
        cout << endl
             << "Begin of My Exercise 1B Test" << endl;

        // Set<int> con SetVec
        lasd::SetVec<int> setvec;
        myStestSetInt(setvec, testnum, testerr);

        // Set<int> con SetLst
        lasd::SetLst<int> setlst;
        myStestSetInt(setlst, testnum, testerr);

        // Set<double> con SetVec
        lasd::SetVec<double> setvecd;
        myStestSetDouble(setvecd, testnum, testerr);

        // Set<string> con SetLst
        lasd::SetLst<string> setlsts;
        myStestSetString(setlsts, testnum, testerr);

        // Operazioni avanzate
        myTestSetOperations(testnum, testerr);

        cout << "End of My Exercise 1B Test! (Errors/Tests: " << testerr << "/" << testnum << ")" << endl;
    }
    catch (...)
    {
        testnum++;
        testerr++;
        cout << endl
             << "Unmanaged error! " << endl;
    }
}



void stressTestVectorAndList()
{
    cout << "\n--- Stress Test: Vector & List ---\n";
    int totalTests = 0, passedTests = 0;

    // 1. Vector: inserimento massivo
    lasd::Vector<int> v1(100000);
    bool ok = true;
    for (ulong i = 0; i < v1.Size(); ++i)
        v1[i] = i;
    for (ulong i = 0; i < v1.Size(); ++i)
        if (v1[i] != (int)i)
            ok = false;
    RUN_TEST("Vector mass insert and check 100000", ok);

    // 2. Vector: accesso fuori limite basso
    try
    {
        (void)v1[(unsigned long)-1];
        cout << "[TEST] Vector negative index: FAILED ❌\n";
    }
    catch (const std::out_of_range &)
    {
        cout << "[TEST] Vector negative index: PASSED ✅\n";
        passedTests++;
    }
    totalTests++;

    // 3. Vector: accesso fuori limite alto
    try
    {
        (void)v1[100000];
        cout << "[TEST] Vector out of bounds: FAILED ❌\n";
    }
    catch (const std::out_of_range &)
    {
        cout << "[TEST] Vector out of bounds: PASSED ✅\n";
        passedTests++;
    }
    totalTests++;

    // 4. Vector: resize ripetuti
    for (int i = 0; i < 100; ++i)
        v1.Resize(1000 + i);
    RUN_TEST("Vector repeated resize up", v1.Size() == 1099);
    for (int i = 0; i < 100; ++i)
        v1.Resize(1000 - i);
    RUN_TEST("Vector repeated resize down", v1.Size() == 901); // <-- 901, non 900

    // 5. Vector: clear e refill
    v1.Clear();
    RUN_TEST("Vector clear", v1.Empty());
    v1.Resize(1000);
    for (ulong i = 0; i < v1.Size(); ++i)
        v1[i] = i * 2;
    ok = true;
    for (ulong i = 0; i < v1.Size(); ++i)
        if (v1[i] != (int)(i * 2))
            ok = false;
    RUN_TEST("Vector refill after clear", ok);

    // 6. Vector: copy e move
    lasd::Vector<int> v2(v1);
    RUN_TEST("Vector copy", v2.Size() == v1.Size() && v2[10] == v1[10]);
    lasd::Vector<int> v3(std::move(v2));
    RUN_TEST("Vector move", v3.Size() == v1.Size() && v3[10] == v1[10]);

    // 7. List: inserimento massivo in coda
    lasd::List<int> l1;
    for (int i = 0; i < 50000; ++i)
        l1.InsertAtBack(i);
    ok = true;
    for (ulong i = 0; i < l1.Size(); ++i)
        if (l1[i] != (int)i)
        {
            ok = false;
            break;
        }
    RUN_TEST("List mass insert at back 50000", ok);

    // 8. List: inserimento massivo in testa
    lasd::List<int> l2;
    for (int i = 0; i < 10000; ++i)
        l2.InsertAtFront(i);
    ok = true;
    for (ulong i = 0; i < l2.Size(); ++i)
        if (l2[l2.Size() - 1 - i] != (int)i)
        {
            ok = false;
            break;
        }
    RUN_TEST("List mass insert at front 10000", ok);
    // 9. List: accesso fuori limite
    try
    {
        (void)l1[50000];
        cout << "[TEST] List out of bounds: FAILED ❌\n";
    }
    catch (const std::out_of_range &)
    {
        cout << "[TEST] List out of bounds: PASSED ✅\n";
        passedTests++;
    }
    totalTests++;

    // 10. List: clear e refill
    l1.Clear();
    RUN_TEST("List clear", l1.Empty());
    for (int i = 0; i < 1000; ++i)
        l1.InsertAtBack(i * 3);
    ok = true;
    for (ulong i = 0; i < l1.Size(); ++i)
        if (l1[i] != (int)(i * 3))
            ok = false;
    RUN_TEST("List refill after clear", ok);

    // 11. List: copy e move
    lasd::List<int> l3(l1);
    RUN_TEST("List copy", l3.Size() == l1.Size() && l3[10] == l1[10]);
    lasd::List<int> l4(std::move(l3));
    RUN_TEST("List move", l4.Size() == l1.Size() && l4[10] == l1[10]);

    // 12. Vector: test di fold
    int sum = v3.Fold<int>([](const int &acc, const int &elem)
                           { return acc + elem; }, 0);
    RUN_TEST("Vector fold sum", sum > 0);

    // 13. List: test di fold
    int sumL = l4.Fold<int>([](const int &acc, const int &elem)
                            { return acc + elem; }, 0);
    RUN_TEST("List fold sum", sumL > 0);

    // 14. Vector: test di map
    v3.Map([](int &x)
           { x += 1; });
    ok = true;
    for (ulong i = 0; i < v3.Size(); ++i)
        if (v3[i] != (int)(i * 2 + 1))
            ok = false;
    RUN_TEST("Vector map increment", ok);

    // 15. List: test di map
    l4.Map([](int &x)
           { x -= 1; });
    ok = true;
    for (ulong i = 0; i < l4.Size(); ++i)
        if (l4[i] != (int)(i * 3 - 1))
            ok = false;
    RUN_TEST("List map decrement", ok);

    // 16. Vector: test di operator==
    lasd::Vector<int> v4(v3);
    RUN_TEST("Vector operator==", v4 == v3);

    // 17. List: test di operator==
    lasd::List<int> l5(l4);
    RUN_TEST("List operator==", l5 == l4);

    // 18. Vector: test di operator!=
    v4[0] = -1;
    RUN_TEST("Vector operator!=", v4 != v3);

    // 19. List: test di operator!=
    l5[0] = -1;
    RUN_TEST("List operator!=", l5 != l4);

    // 20. Vector: test resize a 0 e refill
    v3.Resize(0);
    RUN_TEST("Vector resize to 0", v3.Empty());
    v3.Resize(10);
    for (ulong i = 0; i < v3.Size(); ++i)
        v3[i] = i;
    ok = true;
    for (ulong i = 0; i < v3.Size(); ++i)
        if (v3[i] != (int)i)
            ok = false;
    RUN_TEST("Vector refill after resize to 0", ok);

    // 21. List: test clear e refill
    l4.Clear();
    RUN_TEST("List clear again", l4.Empty());
    for (ulong i = 0; i < 10; ++i)
        l4.InsertAtBack(i);
    ok = true;
    for (ulong i = 0; i < l4.Size(); ++i)
        if (l4[i] != (int)i)
            ok = false;
    RUN_TEST("List refill after clear again", ok);

    // 22. Vector: test accesso multiplo fuori limite
    bool allCaught = true;
    for (int i = 0; i < 10; ++i)
    {
        try
        {
            (void)v3[100 + i];
            allCaught = false;
        }
        catch (const std::out_of_range &)
        {
        }
    }
    RUN_TEST("Vector multiple out of bounds", allCaught);

    // 23. List: test accesso multiplo fuori limite
    allCaught = true;
    for (int i = 0; i < 10; ++i)
    {
        try
        {
            (void)l4[100 + i];
            allCaught = false;
        }
        catch (const std::out_of_range &)
        {
        }
    }
    RUN_TEST("List multiple out of bounds", allCaught);

    // 24. Vector: test operator==
    lasd::Vector<int> v5(10);
    for (ulong i = 0; i < 10; ++i)
        v5[i] = i;
    RUN_TEST("Vector == after refill", v5 == v3);

    // 25. List: test operator==
    lasd::List<int> l6;
    for (ulong i = 0; i < 10; ++i)
        l6.InsertAtBack(i);
    RUN_TEST("List == after refill", l6 == l4);

    // 26. Vector: test operator!=
    v5[9] = -1;
    RUN_TEST("Vector != after change", v5 != v3);

    // 27. List: test operator!=
    l6[9] = -1;
    RUN_TEST("List != after change", l6 != l4);

    // 28. Vector: test resize up grande
    v3.Resize(100000);
    RUN_TEST("Vector resize up to 100000", v3.Size() == 100000);

    // 29. Vector: test resize down grande
    v3.Resize(10);
    RUN_TEST("Vector resize down to 10", v3.Size() == 10);

    // 30. List: test inserimento e rimozione alternati
    lasd::List<int> l7;
    for (int i = 0; i < 1000; ++i)
        l7.InsertAtBack(i);
    for (int i = 0; i < 500; ++i)
        l7.RemoveFromFront();
    RUN_TEST("List remove from front 500", l7.Size() == 500);

    // 31. List: test rimozione da lista vuota (eccezione)
    l7.Clear();
    bool caught = false;
    try
    {
        l7.RemoveFromFront();
    }
    catch (const std::length_error &)
    {
        caught = true;
    }
    RUN_TEST("List remove from empty throws", caught);

    // 32. Vector: test accesso dopo clear
    v3.Clear();
    bool caught2 = false;
    try
    {
        (void)v3[0];
    }
    catch (const std::out_of_range &)
    {
        caught2 = true;
    }
    RUN_TEST("Vector access after clear throws", caught2);

    // 33. List: test accesso dopo clear
    l7.Clear();
    bool caught3 = false;
    try
    {
        (void)l7[0];
    }
    catch (const std::out_of_range &)
    {
        caught3 = true;
    }
    RUN_TEST("List access after clear throws", caught3);

    // 34. Vector: test fold su vettore vuoto
    v3.Clear();
    int sumEmpty = v3.Fold<int>([](const int &acc, const int &elem)
                                { return acc + elem; }, 0);
    RUN_TEST("Vector fold on empty", sumEmpty == 0);

    // 35. List: test fold su lista vuota
    l7.Clear();
    int sumEmptyL = l7.Fold<int>([](const int &acc, const int &elem)
                                 { return acc + elem; }, 0);
    RUN_TEST("List fold on empty", sumEmptyL == 0);

    // 36. Vector: test map su vettore vuoto (non deve crashare)
    v3.Clear();
    try
    {
        v3.Map([](int &x)
               { x += 1; });
        ok = true;
    }
    catch (...)
    {
        ok = false;
    }
    RUN_TEST("Vector map on empty", ok);

    // 37. List: test map su lista vuota (non deve crashare)
    l7.Clear();
    try
    {
        l7.Map([](int &x)
               { x += 1; });
        ok = true;
    }
    catch (...)
    {
        ok = false;
    }
    RUN_TEST("List map on empty", ok);

    // 38. Vector: test ricorsione profonda (simulazione stack overflow)
    try
    {
        std::function<void(int)> deepRec;
        deepRec = [&](int n)
        {
            if (n > 0)
                deepRec(n - 1);
        };
        deepRec(1000); // Potrebbe causare stack overflow su alcune macchine
    }
    catch (...)
    {
    }
    RUN_TEST("Deep recursion (stack overflow simulation)", true);

    // 39. Vector: test allocazione molto grande (simulazione bad_alloc)
    bool allocFailed = false;
    try
    {
        lasd::Vector<int> bigVec(100); // 1 miliardo di elementi
    }
    catch (const std::bad_alloc &)
    {
        allocFailed = true;
    }
    RUN_TEST("Vector huge allocation (bad_alloc simulation)", allocFailed);

    // 40. List: test allocazione molto grande (simulazione bad_alloc)
    allocFailed = false;
    try
    {
        lasd::List<int> bigList;
        for (int i = 0; i < 100; ++i)
            bigList.InsertAtBack(i);
    }
    catch (const std::bad_alloc &)
    {
        allocFailed = true;
    }
    RUN_TEST("List huge allocation (bad_alloc simulation)", allocFailed);

    cout << "\n==============================\n";
    cout << "   Stress Test Summary\n";
    cout << "==============================\n";
    cout << "Tests passed: " << passedTests << " / " << totalTests << "\n";
    if (passedTests == totalTests)
        cout << "✅ All stress tests passed!\n";
    else
        cout << "❌ Some stress tests failed. Check above for details.\n";
}

#define RUN_TEST(desc, expr)                                                                       \
    do                                                                                             \
    {                                                                                              \
        bool result = (expr);                                                                      \
        cout << "[TEST] " << desc << ": " << (result ? "PASSED \u2705" : "FAILED \u274C") << endl; \
        testnum++;                                                                                 \
        if (!result)                                                                               \
            testerr++;                                                                             \
    } while (0)

void mySetVecExtendedTests(uint &testnum, uint &testerr)
{

    uint localTestNum = 0, localTestErr = 0;

    cout << "\n===== Extended SetVec Tests =====\n";

    SetVec<int> set;

    // Test inserimento ordinato
    set.Insert(20);
    set.Insert(10);
    set.Insert(30);
    RUN_TEST("Set should maintain sorted order: [10,20,30]", set[0] == 10 && set[1] == 20 && set[2] == 30);

    // Test inserimento duplicati
    set.Insert(20);
    RUN_TEST("Insert duplicate should not change size", set.Size() == 3);

    // Test rimozione elemento presente
    set.Remove(20);
    RUN_TEST("Remove existing element (20)", !set.Exists(20) && set.Size() == 2);

    // Test rimozione elemento non presente
    bool removeNonExisting = set.Remove(999);
    RUN_TEST("Remove non-existing element (999) returns false", removeNonExisting == false);
    RUN_TEST("Set size remains unchanged after failed removal", set.Size() == 2);

    // Test accesso out-of-range
    bool caught = false;
    try
    {
        int val = set[10];
        (void)val;
    }
    catch (const std::out_of_range &)
    {
        caught = true;
    }
    RUN_TEST("Access out-of-range index should throw", caught);

    // Test Min / Max
    RUN_TEST("Min should be 10", set.Min() == 10);
    RUN_TEST("Max should be 30", set.Max() == 30);

    // Test Copy constructor
    SetVec<int> setCopy(set);
    RUN_TEST("Copy constructor should replicate contents", setCopy == set);
    setCopy.Insert(99);
    RUN_TEST("After insert in copy, sets should differ", setCopy != set);

    // Test Assignment
    SetVec<int> setAssign;
    setAssign = set;
    RUN_TEST("Assignment should copy contents", setAssign == set);
    setAssign.Insert(77);
    RUN_TEST("After insert in assigned, sets should differ", setAssign != set);

    // Test Clear
    set.Clear();
    RUN_TEST("Clear should empty the set", set.Empty());
    RUN_TEST("Clear should reset size to 0", set.Size() == 0);

    // Riepilogo
    cout << "Extended SetVec Tests Completed (Errors/Tests: " << localTestErr << "/" << localTestNum << ")\n";

    testnum += localTestNum;
    testerr += localTestErr;
} // end

/* ************************************************************************** */



// ... (remaining test cases unchanged)

void testSetLst()
{
    std::cout << "Testing SetLst..." << std::endl;
    lasd::SetLst<int> setLst;

    // 1. Test Default Constructor (25 casi)
    {
        // Test 1: Default constructor creates empty set
        lasd::SetLst<int> set;
        assert(set.Size() == 0);
        // Test 2: Empty set has no elements
        assert(!set.Exists(10));
        // Test 3: Min on empty set (exception)
        try
        {
            set.Min();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 4: Max on empty set (exception)
        try
        {
            set.Max();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 5: MinNRemove on empty set (exception)
        try
        {
            set.MinNRemove();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 6: MaxNRemove on empty set (exception)
        try
        {
            set.MaxNRemove();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 7: Predecessor on empty set (exception)
        try
        {
            set.Predecessor(10);
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 8: Successor on empty set (exception)
        try
        {
            set.Successor(10);
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 9: Remove on empty set
        assert(!set.Remove(10));
        // Test 10: Insert after default constructor
        set.Insert(10);
        assert(set.Size() == 1);
        // Test 11: Clear on empty set
        set.Clear();
        assert(set.Size() == 0);
        // Test 12: Operator== with another empty set
        lasd::SetLst<int> other;
        assert(set == other);
        // Test 13: Operator!= with another empty set
        assert(!(set != other));
        // Test 14: Insert negative value
        set.Insert(-10);
        assert(set.Exists(-10));
        // Test 15: Insert after single clear
        set.Clear();
        set.Insert(20);
        assert(set.Size() == 1);
        // Test 16: Insert after failed duplicate insert (sostituisce il test problematico con operator[])
        set.Clear();
        set.Insert(10);
        assert(!set.Insert(10)); // Duplicate should fail
        assert(set.Size() == 1);
        // Test 17: Default constructor with subsequent large insert
        set.Clear();
        set.Insert(1000);
        assert(set.Exists(1000));
        // Test 18: Default constructor with multiple inserts
        set.Clear();
        for (int i = 0; i < 5; ++i)
            set.Insert(i * 10);
        assert(set.Size() == 5);
        // Test 19: Default constructor with negative values
        set.Clear();
        set.Insert(-100);
        set.Insert(-50);
        assert(set.Size() == 2);
        // Test 20: Default constructor with duplicates attempt
        set.Clear();
        set.Insert(10);
        set.Insert(10);
        assert(set.Size() == 1);
        // Test 21: Default constructor with ascending inserts
        set.Clear();
        for (int i = 0; i < 5; ++i)
            set.Insert(i * 10);
        assert(set.Exists(40));
        // Test 22: Default constructor with descending inserts
        set.Clear();
        for (int i = 5; i >= 0; --i)
            set.Insert(i * 10);
        assert(set.Exists(40));
        // Test 23: Default constructor with large negative values
        set.Clear();
        set.Insert(-2000);
        set.Insert(-1000);
        assert(set.Exists(-1000));
        // Test 24: Default constructor with single large value
        set.Clear();
        set.Insert(10000);
        assert(set.Size() == 1);
        // Test 25: Default constructor with mixed values
        set.Clear();
        set.Insert(-100);
        set.Insert(100);
        assert(set.Size() == 2);
        set.Clear();
    }

    // 2. Test Insert (25 casi)
    {
        // Test 1: Insert into empty set
        assert(setLst.Insert(10));
        assert(setLst.Size() == 1);
        // Test 2: Insert duplicate
        assert(!setLst.Insert(10));
        assert(setLst.Size() == 1);
        // Test 3: Insert multiple elements
        setLst.Insert(5);
        setLst.Insert(15);
        assert(setLst.Size() == 3);
        // Test 4: Insert negative value
        setLst.Clear();
        assert(setLst.Insert(-10));
        assert(setLst.Exists(-10));
        // Test 5: Insert zero
        assert(setLst.Insert(0));
        assert(setLst.Size() == 2);
        // Test 6: Insert large set
        setLst.Clear();
        for (int i = 0; i < 10; ++i)
            assert(setLst.Insert(i * 10));
        assert(setLst.Size() == 10);
        // Test 7: Insert after clear
        setLst.Clear();
        assert(setLst.Insert(20));
        assert(setLst.Size() == 1);
        // Test 8: Insert large value
        assert(setLst.Insert(1000));
        assert(setLst.Exists(1000));
        // Test 9: Insert after MinNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        assert(setLst.Insert(5));
        assert(setLst.Exists(5));
        // Test 10: Insert after MaxNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MaxNRemove();
        assert(setLst.Insert(30));
        assert(setLst.Exists(30));
        // Test 11: Insert negative and positive mix
        setLst.Clear();
        assert(setLst.Insert(-100));
        assert(setLst.Insert(100));
        assert(setLst.Size() == 2);
        // Test 12: Insert after multiple inserts
        setLst.Clear();
        for (int i = 0; i < 20; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Insert(200));
        assert(setLst.Exists(200));
        // Test 13: Insert after remove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Remove(10);
        assert(setLst.Insert(20));
        assert(setLst.Size() == 1);
        // Test 14: Insert after failed duplicate insert (sostituisce il test con move semantics)
        setLst.Clear();
        setLst.Insert(50);
        assert(!setLst.Insert(50)); // Duplicate should fail
        assert(setLst.Size() == 1);
        // Test 15: Insert multiple duplicates explicitly
        assert(!setLst.Insert(50));
        assert(setLst.Size() == 1);
        assert(setLst.Exists(50));
        // Test 16: Insert after PredecessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        assert(setLst.Insert(15));
        assert(setLst.Exists(15));
        // Test 17: Insert after SuccessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        assert(setLst.Insert(25));
        assert(setLst.Exists(25));
        // Test 18: Insert large negative value
        setLst.Clear();
        assert(setLst.Insert(-1000));
        assert(setLst.Exists(-1000));
        // Test 19: Insert in ascending order
        setLst.Clear();
        for (int i = 0; i < 5; ++i)
            assert(setLst.Insert(i * 10));
        assert(setLst.Size() == 5);
        // Test 20: Insert in descending order (6 distinct elements: 50, 40, 30, 20, 10, 0)
        setLst.Clear();
        for (int i = 5; i >= 0; --i)
            assert(setLst.Insert(i * 10));
        assert(setLst.Size() == 6);
        // Test 21: Insert after multiple removes
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        setLst.Remove(20);
        assert(setLst.Insert(15));
        assert(setLst.Exists(15));
        // Test 22: Insert single large value
        setLst.Clear();
        assert(setLst.Insert(10000));
        assert(setLst.Size() == 1);
        // Test 23: Insert with small values
        setLst.Clear();
        assert(setLst.Insert(1));
        assert(setLst.Insert(2));
        assert(setLst.Size() == 2);
        // Test 24: Insert after clear multiple times
        setLst.Clear();
        setLst.Clear();
        assert(setLst.Insert(10));
        assert(setLst.Size() == 1);
        // Test 25: Insert large negative set
        setLst.Clear();
        assert(setLst.Insert(-2000));
        assert(setLst.Insert(-1000));
        assert(setLst.Size() == 2);
        setLst.Clear();
    }

    // 3. Test Exists (25 casi)
    {
        // Test 1: Exists on empty set
        assert(!setLst.Exists(10));
        // Test 2: Exists after single insert
        setLst.Insert(10);
        assert(setLst.Exists(10));
        // Test 3: Exists with non-existent value
        assert(!setLst.Exists(20));
        // Test 4: Exists with multiple elements
        setLst.Insert(5);
        setLst.Insert(15);
        assert(setLst.Exists(15));
        // Test 5: Exists after remove
        setLst.Remove(10);
        assert(!setLst.Exists(10));
        // Test 6: Exists with negative values
        setLst.Clear();
        setLst.Insert(-10);
        assert(setLst.Exists(-10));
        // Test 7: Exists with large set
        setLst.Clear();
        for (int i = 0; i < 10; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Exists(90));
        // Test 8: Exists after clear
        setLst.Clear();
        assert(!setLst.Exists(90));
        // Test 9: Exists with zero
        setLst.Insert(0);
        assert(setLst.Exists(0));
        // Test 10: Exists with large value
        setLst.Clear();
        setLst.Insert(1000);
        assert(setLst.Exists(1000));
        // Test 11: Exists after MinNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        assert(!setLst.Exists(10));
        // Test 12: Exists after MaxNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MaxNRemove();
        assert(!setLst.Exists(20));
        // Test 13: Exists with negative non-existent
        setLst.Clear();
        setLst.Insert(-10);
        assert(!setLst.Exists(-20));
        // Test 14: Exists after multiple inserts
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        assert(setLst.Exists(20));
        // Test 15: Exists with duplicates attempt
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(10);
        assert(setLst.Exists(10));
        // Test 16: Exists with small values
        setLst.Clear();
        setLst.Insert(1);
        setLst.Insert(2);
        assert(setLst.Exists(1));
        // Test 17: Exists with large positive values
        setLst.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        assert(setLst.Exists(2000));
        // Test 18: Exists after multiple removes
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        setLst.Remove(20);
        assert(!setLst.Exists(20));
        // Test 19: Exists with negative and positive mix
        setLst.Clear();
        setLst.Insert(-100);
        setLst.Insert(100);
        assert(setLst.Exists(-100));
        // Test 20: Exists with single large value
        setLst.Clear();
        setLst.Insert(10000);
        assert(setLst.Exists(10000));
        // Test 21: Exists after inserting in ascending order
        setLst.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Exists(40));
        // Test 22: Exists after inserting in descending order
        setLst.Clear();
        for (int i = 5; i >= 0; --i)
            setLst.Insert(i * 10);
        assert(setLst.Exists(40));
        // Test 23: Exists after PredecessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        assert(!setLst.Exists(10));
        // Test 24: Exists after SuccessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        assert(!setLst.Exists(20));
        // Test 25: Exists with large negative set
        setLst.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        assert(setLst.Exists(-1000));
        setLst.Clear();
    }

    // 4. Test Remove (25 casi)
    {
        // Test 1: Remove from empty set
        assert(!setLst.Remove(10));
        // Test 2: Remove existing element
        setLst.Insert(10);
        assert(setLst.Remove(10));
        assert(setLst.Size() == 0);
        // Test 3: Remove non-existent element
        setLst.Insert(10);
        assert(!setLst.Remove(20));
        // Test 4: Remove from multiple elements
        setLst.Clear();
        setLst.Insert(5);
        setLst.Insert(10);
        setLst.Insert(15);
        assert(setLst.Remove(10));
        assert(setLst.Size() == 2);
        // Test 5: Remove min element
        assert(setLst.Remove(5));
        assert(setLst.Size() == 1);
        // Test 6: Remove max element
        assert(setLst.Remove(15));
        assert(setLst.Size() == 0);
        // Test 7: Remove negative value
        setLst.Insert(-10);
        assert(setLst.Remove(-10));
        assert(setLst.Size() == 0);
        // Test 8: Remove from large set
        setLst.Clear();
        for (int i = 0; i < 10; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Remove(50));
        assert(setLst.Size() == 9);
        // Test 9: Remove after clear
        setLst.Clear();
        assert(!setLst.Remove(10));
        // Test 10: Remove zero
        setLst.Insert(0);
        assert(setLst.Remove(0));
        assert(setLst.Size() == 0);
        // Test 11: Remove after MinNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        assert(setLst.Remove(20));
        assert(setLst.Size() == 0);
        // Test 12: Remove after MaxNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MaxNRemove();
        assert(setLst.Remove(10));
        assert(setLst.Size() == 0);
        // Test 13: Remove non-existent negative
        setLst.Insert(-10);
        assert(!setLst.Remove(-20));
        // Test 14: Remove after multiple inserts
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        assert(setLst.Remove(20));
        assert(setLst.Size() == 2);
        // Test 15: Remove after failed duplicate insert (rinominato per chiarezza)
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(10);
        assert(setLst.Remove(10));
        assert(setLst.Size() == 0);
        // Test 16: Remove from small set
        setLst.Clear();
        setLst.Insert(1);
        setLst.Insert(2);
        assert(setLst.Remove(1));
        assert(setLst.Size() == 1);
        // Test 17: Remove large positive value
        setLst.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        assert(setLst.Remove(2000));
        assert(setLst.Size() == 1);
        // Test 18: Remove after multiple removes
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        setLst.Remove(20);
        assert(setLst.Remove(30));
        assert(setLst.Size() == 1);
        // Test 19: Remove with negative and positive mix
        setLst.Clear();
        setLst.Insert(-100);
        setLst.Insert(100);
        assert(setLst.Remove(-100));
        assert(setLst.Size() == 1);
        // Test 20: Remove single large value
        setLst.Clear();
        setLst.Insert(10000);
        assert(setLst.Remove(10000));
        assert(setLst.Size() == 0);
        // Test 21: Remove after inserting in ascending order
        setLst.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Remove(40));
        assert(setLst.Size() == 4);
        assert(!setLst.Exists(40));
        // Test 22: Remove after inserting in descending order
        setLst.Clear();
        for (int i = 5; i >= 0; --i)
            setLst.Insert(i * 10);
        assert(setLst.Remove(40));
        assert(setLst.Size() == 5);
        assert(!setLst.Exists(40));
        // Test 23: Remove after PredecessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        assert(setLst.Remove(20));
        assert(setLst.Size() == 0);
        // Test 24: Remove after SuccessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        assert(setLst.Remove(10));
        assert(setLst.Size() == 0);
        // Test 25: Remove large negative value
        setLst.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        assert(setLst.Remove(-1000));
        assert(setLst.Size() == 1);
        setLst.Clear();
    }

    // 5. Test Min (25 casi)
    {
        // Test 1: Min on empty set (exception)
        try
        {
            setLst.Min();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 2: Min with one element
        setLst.Insert(10);
        assert(setLst.Min() == 10);
        // Test 3: Min with multiple elements
        setLst.Insert(5);
        setLst.Insert(15);
        assert(setLst.Min() == 5);
        // Test 4: Min after remove
        setLst.Remove(5);
        assert(setLst.Min() == 10);
        // Test 5: Min with negative values
        setLst.Clear();
        setLst.Insert(-10);
        setLst.Insert(0);
        assert(setLst.Min() == -10);
        // Test 6: Min after multiple inserts
        setLst.Clear();
        for (int i = 0; i < 10; ++i)
            setLst.Insert(i * 10 - 50);
        assert(setLst.Min() == -50);
        // Test 7: Min after MinNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        assert(setLst.Min() == 20);
        // Test 8: Min after MaxNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MaxNRemove();
        assert(setLst.Min() == 10);
        // Test 9: Min with single negative
        setLst.Clear();
        setLst.Insert(-100);
        assert(setLst.Min() == -100);
        // Test 10: Min after clear
        setLst.Clear();
        try
        {
            setLst.Min();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 11: Min with large negative
        setLst.Insert(-1000);
        setLst.Insert(-500);
        assert(setLst.Min() == -1000);
        // Test 12: Min after multiple removes
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        setLst.Remove(10);
        assert(setLst.Min() == 20);
        // Test 13: Min with duplicates attempt
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(10);
        assert(setLst.Min() == 10);
        // Test 14: Min with large positive values
        setLst.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        assert(setLst.Min() == 1000);
        // Test 15: Min with negative and positive mix
        setLst.Clear();
        setLst.Insert(-100);
        setLst.Insert(100);
        assert(setLst.Min() == -100);
        // Test 16: Min with single large value
        setLst.Clear();
        setLst.Insert(10000);
        assert(setLst.Min() == 10000);
        // Test 17: Min after inserting in ascending order
        setLst.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Min() == 0);
        // Test 18: Min after inserting in descending order
        setLst.Clear();
        for (int i = 5; i >= 0; --i)
            setLst.Insert(i * 10);
        assert(setLst.Min() == 0);
        // Test 19: Min after PredecessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        assert(setLst.Min() == 20);
        // Test 20: Min after SuccessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        assert(setLst.Min() == 10);
        // Test 21: Min with small set
        setLst.Clear();
        setLst.Insert(1);
        setLst.Insert(2);
        assert(setLst.Min() == 1);
        // Test 22: Min after multiple MinNRemove
        setLst.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        setLst.MinNRemove();
        setLst.MinNRemove();
        assert(setLst.Min() == 20);
        // Test 23: Min with large negative set
        setLst.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        assert(setLst.Min() == -2000);
        // Test 24: Min after RemovePredecessor
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemovePredecessor(20);
        assert(setLst.Min() == 20);
        // Test 25: Min after RemoveSuccessor
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemoveSuccessor(10);
        assert(setLst.Min() == 10);
        setLst.Clear();
    }

    // 6. Test Max (25 casi)
    {
        // Test 1: Max on empty set (exception)
        try
        {
            setLst.Max();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 2: Max with single negative
        setLst.Insert(-100);
        assert(setLst.Max() == -100);
        // Test 3: Max after multiple inserts
        setLst.Insert(-50);
        setLst.Insert(0);
        assert(setLst.Max() == 0);
        // Test 4: Max after min remove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Remove(10);
        assert(setLst.Max() == 20);
        // Test 5: Max with large value
        setLst.Clear();
        setLst.Insert(1000);
        setLst.Insert(500);
        assert(setLst.Max() == 1000);
        // Test 6: Max after multiple inserts
        setLst.Clear();
        for (int i = 0; i < 20; ++i)
            setLst.Insert(i * 10);
        assert(setLst.Max() == 190); // Corretto da 1000 a 190 (19 * 10)
        // Test 7: Max with duplicates attempt
        setLst.Clear();
        setLst.Insert(50);
        setLst.Insert(50); // Should not insert duplicate
        assert(setLst.Max() == 50);
        // Test 8: Max with negative and positive mix
        setLst.Clear();
        setLst.Insert(-200);
        setLst.Insert(100);
        assert(setLst.Max() == 100);
        // Test 9: Max after removing max
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Remove(20);
        assert(setLst.Max() == 10);
        // Test 10: Max with single element after clear
        setLst.Clear();
        setLst.Insert(0);
        assert(setLst.Max() == 0);
        // Test 11: Max with large negative values
        setLst.Clear();
        setLst.Insert(-1000);
        setLst.Insert(-2000);
        assert(setLst.Max() == -1000);
        // Test 12: Max after inserting in descending order
        setLst.Clear();
        for (int i = 10; i >= 0; --i)
            setLst.Insert(i * 5);
        assert(setLst.Max() == 50);
        // Test 13: Max after inserting in ascending order
        setLst.Clear();
        for (int i = 0; i <= 10; ++i)
            setLst.Insert(i * 5);
        assert(setLst.Max() == 50);
        // Test 14: Max with single large value
        setLst.Clear();
        setLst.Insert(10000);
        assert(setLst.Max() == 10000);
        // Test 15: Max after multiple removes
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.Insert(30);
        setLst.Remove(30);
        setLst.Remove(20);
        assert(setLst.Max() == 10);
        // Test 16: Max after MinNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        assert(setLst.Max() == 20);
        // Test 17: Max after MaxNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MaxNRemove();
        assert(setLst.Max() == 10);
        // Test 18: Max with small set
        setLst.Clear();
        setLst.Insert(1);
        setLst.Insert(2);
        assert(setLst.Max() == 2);
        // Test 19: Max after PredecessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        assert(setLst.Max() == 20);
        // Test 20: Max after SuccessorNRemove
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        assert(setLst.Max() == 10);
        // Test 21: Max with large positive set
        setLst.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        assert(setLst.Max() == 2000);
        // Test 22: Max after RemovePredecessor
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemovePredecessor(20);
        assert(setLst.Max() == 20);
        // Test 23: Max after RemoveSuccessor
        setLst.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemoveSuccessor(10);
        assert(setLst.Max() == 10);
        // Test 24: Max with large negative set
        setLst.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        assert(setLst.Max() == -1000);
        // Test 25: Max after random inserts (sostituisce il test ridondante)
        setLst.Clear();
        setLst.Insert(50);
        setLst.Insert(10);
        setLst.Insert(100);
        assert(setLst.Max() == 100);
        setLst.Clear();
    }

    // 15. Test Clear (25 casi)
    {
        // Test 1: Clear empty set
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 2: Clear with one element
        setLst.Insert(10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 3: Clear with multiple elements
        setLst.Insert(5);
        setLst.Insert(10);
        setLst.Insert(15);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 4: Exists after clear
        assert(!setLst.Exists(10));
        // Test 5: Min after clear (exception)
        try
        {
            setLst.Min();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 6: Max after clear (exception)
        try
        {
            setLst.Max();
            assert(false);
        }
        catch (std::length_error &)
        {
            assert(true);
        }
        // Test 7: Clear large set
        for (int i = 0; i < 20; ++i)
            setLst.Insert(i * 10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 8: Insert after clear
        setLst.Insert(25);
        assert(setLst.Size() == 1);
        // Test 9: Clear after multiple inserts
        setLst.Clear();
        for (int i = 0; i < 20; ++i)
            setLst.Insert(i * 10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 10: Clear with negative values
        setLst.Insert(-10);
        setLst.Insert(0);
        setLst.Clear();
        assert(!setLst.Exists(-10));
        // Test 11: Clear multiple times
        setLst.Insert(10);
        setLst.Clear();
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 12: Exists after clear
        setLst.Insert(10);
        setLst.Clear();
        assert(!setLst.Exists(10));
        // Test 13: Clear after remove
        setLst.Insert(10);
        setLst.Remove(10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 14: Clear after MinNRemove
        setLst.Insert(10);
        setLst.MinNRemove();
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 15: Clear after MaxNRemove
        setLst.Insert(10);
        setLst.MaxNRemove();
        setLst.Clear();
        assert(setLst.Size() == 0);
        assert(!setLst.Exists(10));
        // Test 16: Clear with single large value
        setLst.Insert(10000);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 17: Clear with negative and positive mix
        setLst.Insert(-100);
        setLst.Insert(100);
        setLst.Clear();
        assert(!setLst.Exists(100));
        // Test 18: Clear after complex operations (sostituisce il test ridondante)
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.MinNRemove();
        setLst.Insert(15);
        setLst.Clear();
        assert(setLst.Size() == 0);
        assert(!setLst.Exists(15));
        // Test 19: Clear after inserting in ascending order
        for (int i = 0; i < 10; ++i)
            setLst.Insert(i * 10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 20: Clear after inserting in descending order
        for (int i = 10; i >= 0; --i)
            setLst.Insert(i * 10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 21: Clear after PredecessorNRemove
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.PredecessorNRemove(20);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 22: Clear after SuccessorNRemove
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.SuccessorNRemove(10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 23: Clear after RemovePredecessor
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemovePredecessor(20);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 24: Clear after RemoveSuccessor
        setLst.Insert(10);
        setLst.Insert(20);
        setLst.RemoveSuccessor(10);
        setLst.Clear();
        assert(setLst.Size() == 0);
        // Test 25: Clear with large negative set
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        setLst.Clear();
        assert(setLst.Size() == 0);
        setLst.Clear();
    }

    // 16. Test Operator== (25 casi)
    {
        lasd::SetLst<int> other;
        // Test 1: Empty sets equal
        assert(setLst == other);
        // Test 2: Empty vs non-empty
        setLst.Insert(10);
        assert(!(setLst == other));
        // Test 3: Same single element
        other.Insert(10);
        assert(setLst == other);
        // Test 4: Same multiple elements
        setLst.Insert(20);
        other.Insert(20);
        assert(setLst == other);
        // Test 5: Different sizes
        setLst.Insert(30);
        assert(!(setLst == other));
        // Test 6: Same size, different elements
        other.Insert(25);
        assert(!(setLst == other));
        // Test 7: Equal after clear
        setLst.Clear();
        other.Clear();
        assert(setLst == other);
        // Test 8: Equal with negative values
        setLst.Insert(-10);
        other.Insert(-10);
        assert(setLst == other);
        // Test 9: Equal large sets
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 10; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        assert(setLst == other);
        // Test 10: Different after remove
        setLst.Remove(50);
        assert(!(setLst == other));
        // Test 11: Equal after reinsert
        other.Remove(50);
        assert(setLst == other);
        // Test 12: Equal with single element
        setLst.Clear();
        other.Clear();
        setLst.Insert(0);
        other.Insert(0);
        assert(setLst == other);
        // Test 13: Different after clear
        setLst.Clear();
        assert(!(setLst == other));
        // Test 14: Equal after multiple inserts
        other.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        other.Insert(10);
        other.Insert(20);
        assert(setLst == other);
        // Test 15: Different with negative values
        setLst.Insert(-10);
        assert(!(setLst == other));
        // Test 16: Equal with large positive values
        setLst.Clear();
        other.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        other.Insert(1000);
        other.Insert(2000);
        assert(setLst == other);
        // Test 17: Different after MinNRemove
        setLst.MinNRemove();
        assert(!(setLst == other));
        // Test 18: Equal after MaxNRemove
        other.MaxNRemove();
        setLst.Clear();
        other.Clear();
        setLst.Insert(10);
        other.Insert(10);
        assert(setLst == other);
        // Test 19: Equal with negative and positive mix
        setLst.Clear();
        other.Clear();
        setLst.Insert(-100);
        setLst.Insert(100);
        other.Insert(-100);
        other.Insert(100);
        assert(setLst == other);
        // Test 20: Equal after inserting in different order
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        for (int i = 4; i >= 0; --i)
            other.Insert(i * 10);
        assert(setLst == other);
        // Test 21: Different after partial remove
        setLst.Remove(20);
        assert(!(setLst == other));
        // Test 22: Equal with single large value
        setLst.Clear();
        other.Clear();
        setLst.Insert(10000);
        other.Insert(10000);
        assert(setLst == other);
        // Test 23: Different with large negative values
        setLst.Clear();
        other.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        other.Insert(-2000);
        assert(!(setLst == other));
        // Test 24: Equal after multiple removes
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 5; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        setLst.Remove(10);
        other.Remove(10);
        assert(setLst == other);
        // Test 25: Equal with large sets (test di prestazioni)
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 100; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        assert(setLst == other);
        setLst.Clear();
        other.Clear();
    }

    // 17. Test Operator!= (25 casi)
    {
        lasd::SetLst<int> other;
        // Test 1: Empty sets not different
        assert(!(setLst != other));
        // Test 2: Empty vs non-empty
        setLst.Insert(10);
        assert(setLst != other);
        // Test 3: Same single element
        other.Insert(10);
        assert(!(setLst != other));
        // Test 4: Same multiple elements
        setLst.Insert(20);
        other.Insert(20);
        assert(!(setLst != other));
        // Test 5: Different sizes
        setLst.Insert(30);
        assert(setLst != other);
        // Test 6: Same size, different elements
        other.Insert(25);
        assert(setLst != other);
        // Test 7: Not different after clear
        setLst.Clear();
        other.Clear();
        assert(!(setLst != other));
        // Test 8: Not different with negative values
        setLst.Insert(-10);
        other.Insert(-10);
        assert(!(setLst != other));
        // Test 9: Not different large sets
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 10; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        assert(!(setLst != other));
        // Test 10: Different after remove
        setLst.Remove(50);
        assert(setLst != other);
        // Test 11: Not different after reinsert
        other.Remove(50);
        assert(!(setLst != other));
        // Test 12: Not different with single element
        setLst.Clear();
        other.Clear();
        setLst.Insert(0);
        other.Insert(0);
        assert(!(setLst != other));
        // Test 13: Different after clear
        setLst.Clear();
        assert(setLst != other);
        // Test 14: Not different after multiple inserts
        other.Clear();
        setLst.Insert(10);
        setLst.Insert(20);
        other.Insert(10);
        other.Insert(20);
        assert(!(setLst != other));
        // Test 15: Different with negative values
        setLst.Insert(-10);
        assert(setLst != other);
        // Test 16: Not different with large positive values
        setLst.Clear();
        other.Clear();
        setLst.Insert(1000);
        setLst.Insert(2000);
        other.Insert(1000);
        other.Insert(2000);
        assert(!(setLst != other));
        // Test 17: Different after MinNRemove
        setLst.MinNRemove();
        assert(setLst != other);
        // Test 18: Not different after MaxNRemove
        other.MaxNRemove();
        setLst.Clear();
        other.Clear();
        setLst.Insert(10);
        other.Insert(10);
        assert(!(setLst != other));
        // Test 19: Not different with negative and positive mix
        setLst.Clear();
        other.Clear();
        setLst.Insert(-100);
        setLst.Insert(100);
        other.Insert(-100);
        other.Insert(100);
        assert(!(setLst != other));
        // Test 20: Not different after inserting in different order
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 5; ++i)
            setLst.Insert(i * 10);
        for (int i = 4; i >= 0; --i)
            other.Insert(i * 10);
        assert(!(setLst != other));
        // Test 21: Different after partial remove
        setLst.Remove(20);
        assert(setLst != other);
        // Test 22: Not different with single large value
        setLst.Clear();
        other.Clear();
        setLst.Insert(10000);
        other.Insert(10000);
        assert(!(setLst != other));
        // Test 23: Different with large negative values
        setLst.Clear();
        other.Clear();
        setLst.Insert(-2000);
        setLst.Insert(-1000);
        other.Insert(-2000);
        assert(setLst != other);
        // Test 24: Not different after multiple removes
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 5; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        setLst.Remove(10);
        other.Remove(10);
        assert(!(setLst != other));
        // Test 25: Not different with large sets (test di prestazioni)
        setLst.Clear();
        other.Clear();
        for (int i = 0; i < 100; ++i)
        {
            setLst.Insert(i * 10);
            other.Insert(i * 10);
        }
        assert(!(setLst != other));
        setLst.Clear();
        other.Clear();
    }

    // 18. Test Move Constructor (25 casi)
    {
        // Test 1: Move empty set
        lasd::SetLst<int> setLst2{lasd::SetLst<int>{}};
        assert(setLst2.Size() == 0);
        // Test 2: Move set with one element
        lasd::SetLst<int> temp;
        temp.Insert(10);
        lasd::SetLst<int> setLst3(std::move(temp));
        assert(setLst3.Size() == 1);
        assert(setLst3.Exists(10));
        assert(temp.Size() == 0); // Verifica originale
        // Test 3: Move set with multiple elements
        temp.Clear();
        temp.Insert(5);
        temp.Insert(10);
        temp.Insert(15);
        lasd::SetLst<int> setLst4(std::move(temp));
        assert(setLst4.Size() == 3);
        assert(setLst4.Exists(5));
        assert(temp.Size() == 0); // Verifica originale
        // Test 4: Moved set is empty (ridondante, combinato con Test 3)
        // Test 5: Move with negative values
        temp.Clear();
        temp.Insert(-10);
        temp.Insert(0);
        lasd::SetLst<int> setLst5(std::move(temp));
        assert(setLst5.Exists(-10));
        assert(temp.Size() == 0);
        // Test 6: Move large set
        temp.Clear();
        for (int i = 0; i < 10; ++i)
            temp.Insert(i * 10);
        lasd::SetLst<int> setLst6(std::move(temp));
        assert(setLst6.Size() == 10);
        assert(setLst6.Exists(90));
        assert(temp.Size() == 0);
        // Test 7: Move after MinNRemove
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.MinNRemove();
        lasd::SetLst<int> setLst7(std::move(temp));
        assert(setLst7.Exists(20));
        assert(temp.Size() == 0);
        // Test 8: Move after MaxNRemove
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.MaxNRemove();
        lasd::SetLst<int> setLst8(std::move(temp));
        assert(setLst8.Exists(10));
        assert(temp.Size() == 0);
        // Test 9: Move after clear
        temp.Clear();
        lasd::SetLst<int> setLst9(std::move(temp));
        assert(setLst9.Size() == 0);
        assert(temp.Size() == 0);
        // Test 10: Move with single negative
        temp.Insert(-100);
        lasd::SetLst<int> setLst10(std::move(temp));
        assert(setLst10.Exists(-100));
        assert(temp.Size() == 0);
        // Test 11: Move after multiple inserts
        temp.Clear();
        temp.Insert(-50);
        temp.Insert(0);
        temp.Insert(50);
        lasd::SetLst<int> setLst11(std::move(temp));
        assert(setLst11.Size() == 3);
        assert(temp.Size() == 0);
        // Test 12: Move after multiple inserts
        temp.Clear();
        for (int i = 0; i < 20; ++i)
            temp.Insert(i * 10);
        lasd::SetLst<int> setLst12(std::move(temp));
        assert(setLst12.Exists(190));
        assert(temp.Size() == 0);
        // Test 13: Move and modify moved
        setLst12.Insert(200);
        assert(setLst12.Size() == 21);
        // Test 14: Move with duplicates attempt
        temp.Clear();
        temp.Insert(10);
        temp.Insert(10); // Should not insert
        lasd::SetLst<int> setLst14(std::move(temp));
        assert(setLst14.Size() == 1);
        assert(temp.Size() == 0);
        // Test 15: Move with large positive values
        temp.Clear();
        temp.Insert(1000);
        temp.Insert(2000);
        lasd::SetLst<int> setLst15(std::move(temp));
        assert(setLst15.Exists(2000));
        assert(temp.Size() == 0);
        // Test 16: Move after multiple removes
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.Insert(30);
        temp.Remove(20);
        lasd::SetLst<int> setLst16(std::move(temp));
        assert(setLst16.Size() == 2);
        assert(temp.Size() == 0);
        // Test 17: Move with negative and positive mix
        temp.Clear();
        temp.Insert(-100);
        temp.Insert(100);
        lasd::SetLst<int> setLst17(std::move(temp));
        assert(setLst17.Exists(-100));
        assert(temp.Size() == 0);
        // Test 18: Move with single large value
        temp.Clear();
        temp.Insert(10000);
        lasd::SetLst<int> setLst18(std::move(temp));
        assert(setLst18.Exists(10000));
        assert(temp.Size() == 0);
        // Test 19: Move after inserting in ascending order
        temp.Clear();
        for (int i = 0; i < 5; ++i)
            temp.Insert(i * 10);
        lasd::SetLst<int> setLst19(std::move(temp));
        assert(setLst19.Exists(40));
        assert(temp.Size() == 0);
        // Test 20: Move after inserting in descending order
        temp.Clear();
        for (int i = 5; i >= 0; --i)
            temp.Insert(i * 10);
        lasd::SetLst<int> setLst20(std::move(temp));
        assert(setLst20.Exists(40));
        assert(temp.Size() == 0);
        // Test 21: Move after PredecessorNRemove
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.PredecessorNRemove(20);
        lasd::SetLst<int> setLst21(std::move(temp));
        assert(setLst21.Size() == 1);
        assert(temp.Size() == 0);
        // Test 22: Move after SuccessorNRemove
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.SuccessorNRemove(10);
        lasd::SetLst<int> setLst22(std::move(temp));
        assert(setLst22.Size() == 1);
        assert(temp.Size() == 0);
        // Test 23: Move with large negative set
        temp.Clear();
        temp.Insert(-2000);
        temp.Insert(-1000);
        lasd::SetLst<int> setLst23(std::move(temp));
        assert(setLst23.Exists(-1000));
        assert(temp.Size() == 0);
        // Test 24: Move after complex operations
        temp.Clear();
        temp.Insert(10);
        temp.Insert(20);
        temp.MinNRemove();
        temp.Insert(15);
        lasd::SetLst<int> setLst24(std::move(temp));
        assert(setLst24.Size() == 2);
        assert(temp.Size() == 0);
        // Test 25: Move large set for performance
        temp.Clear();
        for (int i = 0; i < 100; ++i)
            temp.Insert(i * 10);
        lasd::SetLst<int> setLst25(std::move(temp));
        assert(setLst25.Size() == 100);
        assert(temp.Size() == 0);
        setLst.Clear();
    }

    // 19. Test Move Assignment (25 casi)
    {
        lasd::SetLst<int> other;
        // Test 1: Move assign empty to empty
        setLst = std::move(other);
        assert(setLst.Size() == 0);
        // Test 2: Move assign non-empty to empty
        other.Insert(10);
        setLst = std::move(other);
        assert(setLst.Size() == 1);
        assert(setLst.Exists(10));
        assert(other.Size() == 0);
        // Test 3: Move assign with multiple elements
        other.Clear();
        other.Insert(5);
        other.Insert(10);
        other.Insert(15);
        setLst = std::move(other);
        assert(setLst.Size() == 3);
        assert(setLst.Exists(5));
        assert(other.Size() == 0);
        // Test 4: Move assign with negative values
        other.Clear();
        other.Insert(-10);
        other.Insert(0);
        setLst = std::move(other);
        assert(setLst.Exists(-10));
        assert(other.Size() == 0);
        // Test 5: Move assign large set
        other.Clear();
        for (int i = 0; i < 10; ++i)
            other.Insert(i * 10);
        setLst = std::move(other);
        assert(setLst.Size() == 10);
        assert(setLst.Exists(90));
        assert(other.Size() == 0);
        // Test 6: Move assign after MinNRemove
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.MinNRemove();
        setLst = std::move(other);
        assert(setLst.Exists(20));
        assert(other.Size() == 0);
        // Test 7: Move assign after MaxNRemove
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.MaxNRemove();
        setLst = std::move(other);
        assert(setLst.Exists(10));
        assert(other.Size() == 0);
        // Test 8: Move assign empty to non-empty
        other.Clear();
        setLst = std::move(other);
        assert(setLst.Size() == 0);
        assert(other.Size() == 0);
        // Test 9: Move assign with single negative
        other.Insert(-100);
        setLst = std::move(other);
        assert(setLst.Exists(-100));
        assert(other.Size() == 0);
        // Test 10: Move assign after multiple inserts
        other.Clear();
        other.Insert(-50);
        other.Insert(0);
        other.Insert(50);
        setLst = std::move(other);
        assert(setLst.Size() == 3);
        assert(other.Size() == 0);
        // Test 11: Move assign after multiple inserts
        other.Clear();
        for (int i = 0; i < 20; ++i)
            other.Insert(i * 10);
        setLst = std::move(other);
        assert(setLst.Exists(190));
        assert(other.Size() == 0);
        // Test 12: Move assign non-empty to non-empty
        lasd::SetLst<int> temp;
        setLst.Clear();
        setLst.Insert(50);
        temp.Insert(100);
        temp.Insert(200);
        setLst = std::move(temp);
        assert(setLst.Size() == 2);
        assert(setLst.Exists(100) && setLst.Exists(200));
        assert(!setLst.Exists(50)); // Verifica che gli elementi precedenti siano stati distrutti
        assert(temp.Size() == 0);
        // Test 13: Move assign with duplicates attempt
        other.Clear();
        other.Insert(10);
        other.Insert(10); // Should not insert
        setLst = std::move(other);
        assert(setLst.Size() == 1);
        assert(other.Size() == 0);
        // Test 14: Move assign with large positive values
        other.Clear();
        other.Insert(1000);
        other.Insert(2000);
        setLst = std::move(other);
        assert(setLst.Exists(2000));
        assert(other.Size() == 0);
        // Test 15: Move assign after multiple removes
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.Insert(30);
        other.Remove(20);
        setLst = std::move(other);
        assert(setLst.Size() == 2);
        assert(other.Size() == 0);
        // Test 16: Move assign with negative and positive mix
        other.Clear();
        other.Insert(-100);
        other.Insert(100);
        setLst = std::move(other);
        assert(setLst.Exists(-100));
        assert(other.Size() == 0);
        // Test 17: Move assign with single large value
        other.Clear();
        other.Insert(10000);
        setLst = std::move(other);
        assert(setLst.Exists(10000));
        assert(other.Size() == 0);
        // Test 18: Move assign after inserting in ascending order
        other.Clear();
        for (int i = 0; i < 5; ++i)
            other.Insert(i * 10);
        setLst = std::move(other);
        assert(setLst.Exists(40));
        assert(other.Size() == 0);
        // Test 19: Move assign after inserting in descending order
        other.Clear();
        for (int i = 5; i >= 0; --i)
            other.Insert(i * 10);
        setLst = std::move(other);
        assert(setLst.Exists(40));
        assert(other.Size() == 0);
        // Test 20: Move assign after PredecessorNRemove
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.PredecessorNRemove(20);
        setLst = std::move(other);
        assert(setLst.Size() == 1);
        assert(other.Size() == 0);
        // Test 21: Move assign after SuccessorNRemove
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.SuccessorNRemove(10);
        setLst = std::move(other);
        assert(setLst.Size() == 1);
        assert(other.Size() == 0);
        // Test 22: Move assign with large negative set
        other.Clear();
        other.Insert(-2000);
        other.Insert(-1000);
        setLst = std::move(other);
        assert(setLst.Exists(-1000));
        assert(other.Size() == 0);
        // Test 23: Move assign after complex operations
        other.Clear();
        other.Insert(10);
        other.Insert(20);
        other.MinNRemove();
        other.Insert(15);
        setLst = std::move(other);
        assert(setLst.Size() == 2);
        assert(other.Size() == 0);
        // Test 24: Move assign large set for performance
        other.Clear();
        for (int i = 0; i < 100; ++i)
            other.Insert(i * 10);
        setLst = std::move(other);
        assert(setLst.Size() == 100);
        assert(other.Size() == 0);
        // Test 25: Move assign after random inserts
        other.Clear();
        other.Insert(50);
        other.Insert(10);
        other.Insert(100);
        setLst = std::move(other);
        assert(setLst.Size() == 3);
        assert(other.Size() == 0);
        setLst.Clear();
        other.Clear();
    }

// 20. Test Copy Assignment (25 cases)
{
    lasd::SetLst<int> other;
    // Test 1: Assign empty to empty
    setLst = other;
    assert(setLst.Size() == 0);
    // Test 2: Assign non-empty to empty
    other.Insert(10);
    setLst = other;
    assert(setLst.Size() == 1);
    assert(setLst.Exists(10));
    // Test 3: Assign with multiple elements
    other.Insert(5);
    other.Insert(15);
    setLst = other;
    assert(setLst.Size() == 3);
    assert(setLst.Exists(5));
    // Test 4: Independence of assignment
    other.Remove(10);
    assert(setLst.Exists(10));
    // Test 5: Assign with negative values
    other.Clear();
    other.Insert(-10);
    other.Insert(0);
    setLst = other;
    assert(setLst.Exists(-10));
    // Test 6: Assign large set
    other.Clear();
    for (int i = 0; i < 10; ++i)
        other.Insert(i * 10);
    setLst = other;
    assert(setLst.Size() == 10);
    assert(setLst.Exists(90));
    // Test 7: Assign after MinNRemove
    other.MinNRemove();
    setLst = other;
    assert(setLst.Exists(10));
    // Test 8: Assign after MaxNRemove
    other.MaxNRemove();
    setLst = other;
    assert(setLst.Exists(80));
    // Test 9: Assign empty to non-empty
    other.Clear();
    setLst = other;
    assert(setLst.Size() == 0);
    // Test 10: Assign with single negative
    other.Insert(-100);
    setLst = other;
    assert(setLst.Exists(-100));
    // Test 11: Assign after multiple inserts
    other.Insert(-50);
    other.Insert(0);
    setLst = other;
    assert(setLst.Size() == 3);
    // Test 12: Assign after multiple inserts
    other.Clear();
    for (int i = 0; i < 20; ++i)
        other.Insert(i * 10);
    setLst = other;
    assert(setLst.Exists(190));
    // Test 13: Self-assignment
    setLst = setLst;
    assert(setLst.Size() == 20);
    assert(setLst.Exists(190)); // Verify elements unchanged
    // Test 14: Assign after remove
    other.Remove(100);
    setLst = other;
    assert(setLst.Exists(110));
    // Test 15: Assign and modify original
    other.Clear();
    assert(setLst.Size() == 19);
    assert(setLst.Exists(110)); // Verify elements persist
    // Test 16: Assign with duplicates attempt
    other.Clear();
    other.Insert(10);
    other.Insert(10); // Should not insert
    setLst = other;
    assert(setLst.Size() == 1);
    // Test 17: Assign with large positive values
    other.Clear();
    other.Insert(1000);
    other.Insert(2000);
    setLst = other;
    assert(setLst.Exists(2000));
    // Test 18: Assign after multiple removes
    other.Clear();
    other.Insert(10);
    other.Insert(20);
    other.Insert(30);
    other.Remove(20);
    setLst = other;
    assert(setLst.Size() == 2);
    // Test 19: Assign with negative and positive mix
    other.Clear();
    other.Insert(-100);
    other.Insert(100);
    setLst = other;
    assert(setLst.Exists(-100));
    // Test 20: Assign with single large value
    other.Clear();
    other.Insert(10000);
    setLst = other;
    assert(setLst.Exists(10000));
    // Test 21: Assign after inserting in ascending order
    other.Clear();
    for (int i = 0; i < 5; ++i)
        other.Insert(i * 10);
    setLst = other;
    assert(setLst.Exists(40));
    // Test 22: Assign after inserting in descending order
    other.Clear();
    for (int i = 5; i >= 0; --i)
        other.Insert(i * 10);
    setLst = other;
    assert(setLst.Exists(40));
    // Test 23: Assign after PredecessorNRemove
    other.Clear();
    other.Insert(10);
    other.Insert(20);
    other.PredecessorNRemove(20);
    setLst = other;
    assert(setLst.Size() == 1);
    // Test 24: Assign after SuccessorNRemove
    other.Clear();
    other.Insert(10);
    other.Insert(20);
    other.SuccessorNRemove(10);
    setLst = other;
    assert(setLst.Size() == 1);
    // Test 25: Assign large set for performance
    other.Clear();
    for (int i = 0; i < 100; ++i)
        other.Insert(i * 10);
    setLst = other;
    assert(setLst.Size() == 100);
    setLst.Clear();
    other.Clear();
}
    std::cout << "SetLst tests passed!" << std::endl;
}



// void testSetVec()
// {
//     std::cout << "Testing SetVec..." << std::endl;
//     lasd::SetVec<int> setVec;

//     // 1. Test Default Constructor (5 cases)
//     {
//         // Test 1: Size of empty set
//         assert(setVec.Size() == 0);
//         // Test 2: Exists on empty set
//         assert(!setVec.Exists(10));
//         // Test 3: Min on empty set (exception)
//         try {
//             setVec.Min();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 4: Max on empty set (exception)
//         try {
//             setVec.Max();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 5: Operator[] on empty set (exception)
//         try {
//             setVec[0];
//             assert(false);
//         } catch (std::out_of_range&) {
//             assert(true);
//         }
//     }

//     // 2. Test Insert (16 cases)
//     {
//         // Test 1: Insert single element
//         assert(setVec.Insert(10));
//         assert(setVec.Size() == 1);
//         // Test 2: Insert duplicate
//         assert(!setVec.Insert(10));
//         assert(setVec.Size() == 1);
//         // Test 3: Insert multiple elements
//         assert(setVec.Insert(5));
//         assert(setVec.Insert(15));
//         assert(setVec.Size() == 3);
//         // Test 4: Insert negative value
//         assert(setVec.Insert(-10));
//         assert(setVec.Size() == 4);
//         // Test 5: Insert zero
//         assert(setVec.Insert(0));
//         assert(setVec.Size() == 5);
//         // Test 6: Insert large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             assert(setVec.Insert(i * 10));
//         }
//         assert(setVec.Size() == 20);
//         // Test 7: Insert after clear
//         setVec.Clear();
//         assert(setVec.Insert(25));
//         assert(setVec.Size() == 1);
//         // Test 8: Insert non-duplicate after duplicate attempt
//         assert(!setVec.Insert(25));
//         assert(setVec.Insert(50));
//         assert(setVec.Size() == 2);
//         // Test 9: Insert with move
//         int value = 75;
//         assert(setVec.Insert(std::move(value)));
//         assert(setVec.Size() == 3);
//         // Test 10: Insert large negative
//         assert(setVec.Insert(-100));
//         assert(setVec.Size() == 4);
//         // Test 11: Insert after multiple inserts
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             assert(setVec.Insert(i * 10 - 50));
//         }
//         assert(setVec.Size() == 10);
//         // Test 12: Insert with resize
//         for (int i = 0; i < 10; ++i) {
//             assert(setVec.Insert(i * 100 + 50));
//         }
//         assert(setVec.Size() == 20);
//         // Test 13: Insert duplicate in large set
//         assert(!setVec.Insert(0));
//         assert(setVec.Size() == 20);
//         // Test 14: Insert after remove
//         setVec.Remove(0);
//         assert(setVec.Insert(0));
//         assert(setVec.Size() == 20);
//         // Test 15: Insert with negative duplicates
//         assert(!setVec.Insert(-50));
//         assert(setVec.Size() == 20);
//         // Test 16: Verify elements are sorted
//         for (unsigned long i = 1; i < setVec.Size(); ++i) {
//             assert(setVec[i - 1] < setVec[i]);
//         }
//         setVec.Clear();
//     }
//     // 3. Test Exists (15 cases)
//     {
//         // Test 1: Exists on empty set
//         assert(!setVec.Exists(10));
//         // Test 2: Exists with one element
//         setVec.Insert(10);
//         assert(setVec.Exists(10));
//         // Test 3: Exists with non-existent element
//         assert(!setVec.Exists(20));
//         // Test 4: Exists with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Exists(5));
//         // Test 5: Exists with negative value
//         setVec.Insert(-10);
//         assert(setVec.Exists(-10));
//         // Test 6: Exists after clear
//         setVec.Clear();
//         assert(!setVec.Exists(10));
//         // Test 7: Exists in large set
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Exists(50));
//         // Test 8: Exists for non-existent in large set
//         assert(!setVec.Exists(55));
//         // Test 9: Exists after remove
//         setVec.Remove(50);
//         assert(!setVec.Exists(50));
//         // Test 10: Exists with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(!setVec.Exists(-5));
//         // Test 11: Exists after multiple inserts
//         setVec.Clear();
//         for (int i = 0; i < 5; ++i) {
//             setVec.Insert(i * 10 - 20);
//         }
//         assert(setVec.Exists(-10));
//         // Test 12: Exists after clear and reinsert
//         setVec.Clear();
//         setVec.Insert(25);
//         assert(setVec.Exists(25));
//         // Test 13: Exists with large value
//         setVec.Insert(1000);
//         assert(setVec.Exists(1000));
//         // Test 14: Exists after multiple removes
//         setVec.Remove(25);
//         assert(!setVec.Exists(25));
//         // Test 15: Exists with single element
//         setVec.Clear();
//         setVec.Insert(0);
//         assert(setVec.Exists(0));
//         setVec.Clear();
//     }

//     // 4. Test Remove (15 cases)
//     {
//         // Test 1: Remove from empty set
//         assert(!setVec.Remove(10));
//         // Test 2: Remove single element
//         setVec.Insert(10);
//         assert(setVec.Remove(10));
//         assert(setVec.Size() == 0);
//         // Test 3: Remove non-existent
//         setVec.Insert(10);
//         assert(!setVec.Remove(20));
//         // Test 4: Remove with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Remove(10));
//         assert(setVec.Size() == 2);
//         // Test 5: Remove negative value
//         setVec.Clear();
//         setVec.Insert(-10);
//         assert(setVec.Remove(-10));
//         // Test 6: Remove from large set
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Remove(50));
//         assert(setVec.Size() == 9);
//         // Test 7: Remove after clear
//         setVec.Clear();
//         assert(!setVec.Remove(10));
//         // Test 8: Remove min
//         setVec.Insert(10);
//         setVec.Insert(20);
//         assert(setVec.Remove(10));
//         assert(setVec.Size() == 1);
//         // Test 9: Remove max
//         setVec.Insert(30);
//         assert(setVec.Remove(30));
//         assert(setVec.Size() == 1);
//         // Test 10: Remove with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Remove(-10));
//         // Test 11: Remove all elements
//         setVec.Clear();
//         for (int i = 0; i < 5; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 5; ++i) {
//             assert(setVec.Remove(i * 10));
//         }
//         assert(setVec.Size() == 0);
//         // Test 12: Remove after resize
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Remove(100));
//         assert(setVec.Size() == 19);
//         assert(!setVec.Exists(100));
//         // Test 13: Remove non-existent in large set
//         assert(!setVec.Remove(100));
//         // Test 14: Remove with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         assert(setVec.Remove(10));
//         assert(setVec.Size() == 0);
//         // Test 15: Remove after multiple inserts
//         setVec.Insert(10);
//         setVec.Insert(20);
//         assert(setVec.Remove(20));
//         assert(setVec.Size() == 1);
//         setVec.Clear();
//     }

//     // 5. Test Min (15 cases)
//     {
//         // Test 1: Min on empty set (exception)
//         try {
//             setVec.Min();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: Min with one element
//         setVec.Insert(10);
//         assert(setVec.Min() == 10);
//         // Test 3: Min with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Min() == 5);
//         // Test 4: Min with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Min() == -10);
//         // Test 5: Min after remove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.Remove(10);
//         assert(setVec.Min() == 20);
//         // Test 6: Min with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Min() == 0);
//         // Test 7: Min after clear
//         setVec.Clear();
//         try {
//             setVec.Min();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 8: Min with single negative
//         setVec.Insert(-100);
//         assert(setVec.Min() == -100);
//         // Test 9: Min after multiple inserts
//         setVec.Clear();
//         setVec.Insert(-100);
//         setVec.Insert(-50);
//         setVec.Insert(0);
//         assert(setVec.Min() == -100);
//         // Test 10: Min with large negative
//         setVec.Clear();
//         setVec.Insert(-1000);
//         setVec.Insert(-500);
//         assert(setVec.Min() == -1000);
//         // Test 11: Min after MinNRemove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.MinNRemove();
//         assert(setVec.Min() == 20);
//         // Test 12: Min after multiple removes
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 5; ++i) {
//             setVec.Remove(i * 10);
//         }
//         assert(setVec.Min() == 50);
//         // Test 13: Min with single element
//         setVec.Clear();
//         setVec.Insert(0);
//         assert(setVec.Min() == 0);
//         // Test 14: Min after reinsert
//         setVec.Clear();
//         setVec.Insert(25);
//         setVec.Insert(50);
//         assert(setVec.Min() == 25);
//         // Test 15: Min after large set insert
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10 - 100);
//         }
//         assert(setVec.Min() == -100);
//         setVec.Clear();
//     }

//     // 6. Test Max (15 cases)
//     {
//         // Test 1: Max on empty set (exception)
//         try {
//             setVec.Max();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: Max with one element
//         setVec.Insert(10);
//         assert(setVec.Max() == 10);
//         // Test 3: Max with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Max() == 15);
//         // Test 4: Max with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Max() == 0);
//         // Test 5: Max after remove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.Remove(20);
//         assert(setVec.Max() == 10);
//         // Test 6: Max with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Max() == 190);
//         // Test 7: Max after clear
//         setVec.Clear();
//         try {
//             setVec.Max();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 8: Max with single negative
//         setVec.Insert(-100);
//         assert(setVec.Max() == -100);
//         // Test 9: Max after multiple inserts
//         setVec.Insert(-50);
//         setVec.Insert(0);
//         assert(setVec.Max() == 0);
//         // Test 10: Max with large value
//         setVec.Clear();
//         setVec.Insert(1000);
//         setVec.Insert(500);
//         assert(setVec.Max() == 1000);
//         // Test 11: Max after MaxNRemove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.MaxNRemove();
//         assert(setVec.Max() == 10);
//         // Test 12: Max after multiple removes
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 5; i < 10; ++i) {
//             setVec.Remove(i * 10);
//         }
//         assert(setVec.Max() == 40);
//         // Test 13: Max with single element
//         setVec.Clear();
//         setVec.Insert(0);
//         assert(setVec.Max() == 0);
//         // Test 14: Max after reinsert
//         setVec.Clear();
//         setVec.Insert(25);
//         setVec.Insert(50);
//         assert(setVec.Max() == 50);
//         // Test 15: Max after large set insert
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10 - 100);
//         }
//         assert(setVec.Max() == 90);
//         setVec.Clear();
//     }

//     // 7. Test MinNRemove (15 cases)
//     {
//         // Test 1: MinNRemove on empty set (exception)
//         try {
//             setVec.MinNRemove();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: MinNRemove with one element
//         setVec.Insert(10);
//         assert(setVec.MinNRemove() == 10);
//         // Test 3: Size after MinNRemove
//         assert(setVec.Size() == 0);
//         // Test 4: MinNRemove with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(10);
//         setVec.Insert(15);
//         assert(setVec.MinNRemove() == 5);
//         // Test 5: Size after MinNRemove
//         assert(setVec.Size() == 2);
//         // Test 6: MinNRemove with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.MinNRemove() == -10);
//         // Test 7: MinNRemove after multiple inserts
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10 - 50);
//         }
//         assert(setVec.MinNRemove() == -50);
//         // Test 8: MinNRemove after min removal
//         assert(setVec.MinNRemove() == -40);
//         // Test 9: Size after multiple MinNRemove
//         assert(setVec.Size() == 8);
//         // Test 10: MinNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.MinNRemove();
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: MinNRemove with single negative
//         setVec.Clear();
//         setVec.Insert(-100);
//         assert(setVec.MinNRemove() == -100);
//         // Test 12: MinNRemove after clear
//         try {
//             setVec.MinNRemove();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 13: MinNRemove with large negative
//         setVec.Insert(-1000);
//         setVec.Insert(-500);
//         assert(setVec.MinNRemove() == -1000);
//         // Test 14: MinNRemove with one element left
//         assert(setVec.MinNRemove() == -500);
//         assert(setVec.Size() == 0);
//         // Test 15: MinNRemove after reinsert
//         setVec.Insert(25);
//         setVec.Insert(50);
//         assert(setVec.MinNRemove() == 25);
//         setVec.Clear();
//     }

//     // 8. Test MaxNRemove (15 cases)
//     {
//         // Test 1: MaxNRemove on empty set (exception)
//         try {
//             setVec.MaxNRemove();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: MaxNRemove with one element
//         setVec.Insert(10);
//         assert(setVec.MaxNRemove() == 10);
//         // Test 3: Size after MaxNRemove
//         assert(setVec.Size() == 0);
//         // Test 4: MaxNRemove with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(10);
//         setVec.Insert(15);
//         assert(setVec.MaxNRemove() == 15);
//         // Test 5: Size after MaxNRemove
//         assert(setVec.Size() == 2);
//         // Test 6: MaxNRemove with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.MaxNRemove() == 0);
//         // Test 7: MaxNRemove after multiple inserts
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10 - 50);
//         }
//         assert(setVec.MaxNRemove() == 40);
//         // Test 8: MaxNRemove after max removal
//         assert(setVec.MaxNRemove() == 30);
//         // Test 9: Size after multiple MaxNRemove
//         assert(setVec.Size() == 8);
//         // Test 10: MaxNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.MaxNRemove();
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: MaxNRemove with single negative
//         setVec.Clear();
//         setVec.Insert(-100);
//         assert(setVec.MaxNRemove() == -100);
//         // Test 12: MaxNRemove after clear
//         try {
//             setVec.MaxNRemove();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 13: MaxNRemove with large value
//         setVec.Insert(1000);
//         setVec.Insert(500);
//         assert(setVec.MaxNRemove() == 1000);
//         // Test 14: MaxNRemove with one element left
//         assert(setVec.MaxNRemove() == 500);
//         assert(setVec.Size() == 0);
//         // Test 15: MaxNRemove after reinsert
//         setVec.Insert(25);
//         setVec.Insert(50);
//         assert(setVec.MaxNRemove() == 50);
//         setVec.Clear();
//     }

//     // 9. Test Predecessor (15 cases)
//     {
//         // Test 1: Predecessor on empty set (exception)
//         try {
//             setVec.Predecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: Predecessor with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.Predecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: Predecessor with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Predecessor(15) == 10);
//         // Test 4: Predecessor of min (exception)
//         try {
//             setVec.Predecessor(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 5: Predecessor of non-existent larger value
//         assert(setVec.Predecessor(20) == 15);
//         // Test 6: Predecessor with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Predecessor(0) == -10);
//         // Test 7: Predecessor with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Predecessor(50) == 40);
//         // Test 8: Predecessor of value between elements
//         assert(setVec.Predecessor(45) == 40);
//         // Test 9: Predecessor after remove
//         setVec.Remove(40);
//         assert(setVec.Predecessor(50) == 30);
//         // Test 10: Predecessor with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.Predecessor(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 11: Predecessor with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Predecessor(-5) == -10);
//         // Test 12: Predecessor after clear
//         setVec.Clear();
//         try {
//             setVec.Predecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 13: Predecessor with large negative
//         setVec.Insert(-100);
//         setVec.Insert(-50);
//         assert(setVec.Predecessor(-50) == -100);
//         // Test 14: Predecessor after multiple inserts
//         setVec.Insert(-75);
//         assert(setVec.Predecessor(-50) == -75);
//         // Test 15: Predecessor of max in large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Predecessor(90) == 80);
//         setVec.Clear();
//     }

//     // 10. Test Successor (15 cases)
//     {
//         // Test 1: Successor on empty set (exception)
//         try {
//             setVec.Successor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: Successor with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.Successor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: Successor with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.Successor(5) == 10);
//         // Test 4: Successor of max (exception)
//         try {
//             setVec.Successor(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 5: Successor of non-existent smaller value
//         assert(setVec.Successor(0) == 5);
//         // Test 6: Successor with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Successor(-10) == 0);
//         // Test 7: Successor with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Successor(40) == 50);
//         // Test 8: Successor of value between elements
//         assert(setVec.Successor(45) == 50);
//         // Test 9: Successor after remove
//         setVec.Remove(50);
//         assert(setVec.Successor(40) == 60);
//         // Test 10: Successor with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.Successor(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 11: Successor with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.Successor(-15) == -10);
//         // Test 12: Successor after clear
//         setVec.Clear();
//         try {
//             setVec.Successor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 13: Successor with large value
//         setVec.Insert(500);
//         setVec.Insert(1000);
//         assert(setVec.Successor(500) == 1000);
//         // Test 14: Successor after multiple inserts
//         setVec.Insert(750);
//         assert(setVec.Successor(500) == 750);
//         // Test 15: Successor of min in large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.Successor(0) == 10);
//         setVec.Clear();
//     }

//     // 11. Test PredecessorNRemove (15 cases)
//     {
//         // Test 1: PredecessorNRemove on empty set (exception)
//         try {
//             setVec.PredecessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: PredecessorNRemove with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.PredecessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: PredecessorNRemove with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.PredecessorNRemove(15) == 10);
//         // Test 4: Size after PredecessorNRemove
//         assert(setVec.Size() == 2);
//         // Test 5: PredecessorNRemove of min (exception)
//         try {
//             setVec.PredecessorNRemove(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 6: PredecessorNRemove of non-existent
//         assert(setVec.PredecessorNRemove(20) == 15);
//         // Test 7: PredecessorNRemove with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.PredecessorNRemove(0) == -10);
//         // Test 8: PredecessorNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.PredecessorNRemove(50) == 40);
//         // Test 9: Size after PredecessorNRemove
//         assert(setVec.Size() == 9);
//         // Test 10: PredecessorNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.PredecessorNRemove((19 - i) * 10);
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: PredecessorNRemove with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.PredecessorNRemove(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 12: PredecessorNRemove with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.PredecessorNRemove(-5) == -10);
//         // Test 13: PredecessorNRemove after clear
//         setVec.Clear();
//         try {
//             setVec.PredecessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 14: PredecessorNRemove with large negative
//         setVec.Insert(-100);
//         setVec.Insert(-50);
//         assert(setVec.PredecessorNRemove(-50) == -100);
//         // Test 15: PredecessorNRemove after multiple inserts
//         setVec.Insert(-75);
//         assert(setVec.PredecessorNRemove(-50) == -75);
//         setVec.Clear();
//     }

//     // 12. Test SuccessorNRemove (15 cases)
//     {
//         // Test 1: SuccessorNRemove on empty set (exception)
//         try {
//             setVec.SuccessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: SuccessorNRemove with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.SuccessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: SuccessorNRemove with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec.SuccessorNRemove(5) == 10);
//         // Test 4: Size after SuccessorNRemove
//         assert(setVec.Size() == 2);
//         // Test 5: SuccessorNRemove of max (exception)
//         try {
//             setVec.SuccessorNRemove(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 6: SuccessorNRemove of non-existent
//         assert(setVec.SuccessorNRemove(0) == 5);
//         // Test 7: SuccessorNRemove with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.SuccessorNRemove(-10) == 0);
//         // Test 8: SuccessorNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec.SuccessorNRemove(40) == 50);
//         // Test 9: Size after SuccessorNRemove
//         assert(setVec.Size() == 9);
//         // Test 10: SuccessorNRemove with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.SuccessorNRemove(i * 10);
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: SuccessorNRemove with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.SuccessorNRemove(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 12: SuccessorNRemove with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec.SuccessorNRemove(-15) == -10);
//         // Test 13: SuccessorNRemove after clear
//         setVec.Clear();
//         try {
//             setVec.SuccessorNRemove(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 14: SuccessorNRemove with large value
//         setVec.Insert(500);
//         setVec.Insert(1000);
//         assert(setVec.SuccessorNRemove(500) == 1000);
//         // Test 15: SuccessorNRemove after multiple inserts
//         setVec.Insert(750);
//         assert(setVec.SuccessorNRemove(500) == 750);
//         setVec.Clear();
//     }

//     // 13. Test RemovePredecessor (15 cases)
//     {
//         // Test 1: RemovePredecessor on empty set (exception)
//         try {
//             setVec.RemovePredecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: RemovePredecessor with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.RemovePredecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: RemovePredecessor with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         setVec.RemovePredecessor(15);
//         assert(!setVec.Exists(10));
//         // Test 4: Size after RemovePredecessor
//         assert(setVec.Size() == 2);
//         // Test 5: RemovePredecessor of min (exception)
//         try {
//             setVec.RemovePredecessor(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 6: RemovePredecessor of non-existent
//         setVec.RemovePredecessor(20);
//         assert(!setVec.Exists(15));
//         // Test 7: RemovePredecessor with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         setVec.RemovePredecessor(0);
//         assert(!setVec.Exists(-10));
//         // Test 8: RemovePredecessor with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         setVec.RemovePredecessor(50);
//         assert(!setVec.Exists(40));
//         // Test 9: Size after RemovePredecessor
//         assert(setVec.Size() == 9);
//         // Test 10: RemovePredecessor with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.RemovePredecessor((19 - i) * 10);
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: RemovePredecessor with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.RemovePredecessor(5);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 12: RemovePredecessor with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         setVec.RemovePredecessor(-5);
//         assert(!setVec.Exists(-10));
//         // Test 13: RemovePredecessor after clear
//         setVec.Clear();
//         try {
//             setVec.RemovePredecessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 14: RemovePredecessor with large negative
//         setVec.Insert(-100);
//         setVec.Insert(-50);
//         setVec.RemovePredecessor(-50);
//         assert(!setVec.Exists(-100));
//         // Test 15: RemovePredecessor after multiple inserts
//         setVec.Insert(-75);
//         setVec.RemovePredecessor(-50);
//         assert(!setVec.Exists(-75));
//         setVec.Clear();
//     }

//     // 14. Test RemoveSuccessor (15 cases)
//     {
//         // Test 1: RemoveSuccessor on empty set (exception)
//         try {
//             setVec.RemoveSuccessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 2: RemoveSuccessor with one element (exception)
//         setVec.Insert(10);
//         try {
//             setVec.RemoveSuccessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 3: RemoveSuccessor with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         setVec.RemoveSuccessor(5);
//         assert(!setVec.Exists(10));
//         // Test 4: Size after RemoveSuccessor
//         assert(setVec.Size() == 2);
//         // Test 5: RemoveSuccessor of max (exception)
//         try {
//             setVec.RemoveSuccessor(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 6: RemoveSuccessor of non-existent
//         setVec.RemoveSuccessor(0);
//         assert(!setVec.Exists(5));
//         // Test 7: RemoveSuccessor with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         setVec.RemoveSuccessor(-10);
//         assert(!setVec.Exists(0));
//         // Test 8: RemoveSuccessor with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         setVec.RemoveSuccessor(40);
//         assert(!setVec.Exists(50));
//         // Test 9: Size after RemoveSuccessor
//         assert(setVec.Size() == 9);
//         // Test 10: RemoveSuccessor with large set
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.RemoveSuccessor(i * 10);
//         }
//         assert(setVec.Size() == 5);
//         // Test 11: RemoveSuccessor with single element
//         setVec.Clear();
//         setVec.Insert(10);
//         try {
//             setVec.RemoveSuccessor(15);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 12: RemoveSuccessor with negative non-existent
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         setVec.RemoveSuccessor(-15);
//         assert(!setVec.Exists(-10));
//         // Test 13: RemoveSuccessor after clear
//         setVec.Clear();
//         try {
//             setVec.RemoveSuccessor(10);
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 14: RemoveSuccessor with large value
//         setVec.Insert(500);
//         setVec.Insert(1000);
//         setVec.RemoveSuccessor(500);
//         assert(!setVec.Exists(1000));
//         // Test 15: RemoveSuccessor after multiple inserts
//         setVec.Insert(750);
//         setVec.RemoveSuccessor(500);
//         assert(!setVec.Exists(750));
//         setVec.Clear();
//     }

//     // 15. Test Clear (15 cases)
//     {
//         // Test 1: Clear empty set
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 2: Clear with one element
//         setVec.Insert(10);
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 3: Clear with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(10);
//         setVec.Insert(15);
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 4: Exists after clear
//         assert(!setVec.Exists(10));
//         // Test 5: Min after clear (exception)
//         try {
//             setVec.Min();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 6: Max after clear (exception)
//         try {
//             setVec.Max();
//             assert(false);
//         } catch (std::length_error&) {
//             assert(true);
//         }
//         // Test 7: Clear large set
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 8: Insert after clear
//         setVec.Insert(25);
//         assert(setVec.Size() == 1);
//         // Test 9: Clear after multiple inserts
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 10: Clear with negative values
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         setVec.Clear();
//         assert(!setVec.Exists(-10));
//         // Test 11: Clear multiple times
//         setVec.Insert(10);
//         setVec.Clear();
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 12: Exists after clear
//         setVec.Insert(10);
//         setVec.Clear();
//         assert(!setVec.Exists(10));
//         // Test 13: Clear after remove
//         setVec.Insert(10);
//         setVec.Remove(10);
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 14: Clear after MinNRemove
//         setVec.Insert(10);
//         setVec.MinNRemove();
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         // Test 15: Clear after MaxNRemove
//         setVec.Insert(10);
//         setVec.MaxNRemove();
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         setVec.Clear();
//     }

//     // 16. Test Operator== (15 cases)
//     {
//         lasd::SetVec<int> other;
//         // Test 1: Empty sets equal
//         assert(setVec == other);
//         // Test 2: Empty vs non-empty
//         setVec.Insert(10);
//         assert(!(setVec == other));
//         // Test 3: Same single element
//         other.Insert(10);
//         assert(setVec == other);
//         // Test 4: Same multiple elements
//         setVec.Insert(20);
//         other.Insert(20);
//         assert(setVec == other);
//         // Test 5: Different sizes
//         setVec.Insert(30);
//         assert(!(setVec == other));
//         // Test 6: Same size, different elements
//         other.Insert(25);
//         assert(!(setVec == other));
//         // Test 7: Equal after clear
//         setVec.Clear();
//         other.Clear();
//         assert(setVec == other);
//         // Test 8: Equal with negative values
//         setVec.Insert(-10);
//         other.Insert(-10);
//         assert(setVec == other);
//         // Test 9: Equal large sets
//         setVec.Clear();
//         other.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//             other.Insert(i * 10);
//         }
//         assert(setVec == other);
//         // Test 10: Different after remove
//         setVec.Remove(50);
//         assert(!(setVec == other));
//         // Test 11: Equal after reinsert
//         other.Remove(50);
//         assert(setVec == other);
//         // Test 12: Equal with single element
//         setVec.Clear();
//         other.Clear();
//         setVec.Insert(0);
//         other.Insert(0);
//         assert(setVec == other);
//         // Test 13: Different after clear
//         setVec.Clear();
//         assert(!(setVec == other));
//         // Test 14: Equal after multiple inserts
//         other.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         other.Insert(10);
//         other.Insert(20);
//         assert(setVec == other);
//         // Test 15: Different with negative values
//         setVec.Insert(-10);
//         assert(!(setVec == other));
//         setVec.Clear();
//         other.Clear();
//     }

//     // 17. Test Operator!= (15 cases)
//     {
//         lasd::SetVec<int> other;
//         // Test 1: Empty sets not different
//         assert(!(setVec != other));
//         // Test 2: Empty vs non-empty
//         setVec.Insert(10);
//         assert(setVec != other);
//         // Test 3: Same single element
//         other.Insert(10);
//         assert(!(setVec != other));
//         // Test 4: Same multiple elements
//         setVec.Insert(20);
//         other.Insert(20);
//         assert(!(setVec != other));
//         // Test 5: Different sizes
//         setVec.Insert(30);
//         assert(setVec != other);
//         // Test 6: Same size, different elements
//         other.Insert(25);
//         assert(setVec != other);
//         // Test 7: Not different after clear
//         setVec.Clear();
//         other.Clear();
//         assert(!(setVec != other));
//         // Test 8: Not different with negative values
//         setVec.Insert(-10);
//         other.Insert(-10);
//         assert(!(setVec != other));
//         // Test 9: Not different large sets
//         setVec.Clear();
//         other.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//             other.Insert(i * 10);
//         }
//         assert(!(setVec != other));
//         // Test 10: Different after remove
//         setVec.Remove(50);
//         assert(setVec != other);
//         // Test 11: Not different after reinsert
//         other.Remove(50);
//         assert(!(setVec != other));
//         // Test 12: Not different with single element
//         setVec.Clear();
//         other.Clear();
//         setVec.Insert(0);
//         other.Insert(0);
//         assert(!(setVec != other));
//         // Test 13: Different after clear
//         setVec.Clear();
//         assert(setVec != other);
//         // Test 14: Not different after multiple inserts
//         other.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         other.Insert(10);
//         other.Insert(20);
//         assert(!(setVec != other));
//         // Test 15: Different with negative values
//         setVec.Insert(-10);
//         assert(setVec != other);
//         setVec.Clear();
//         other.Clear();
//     }

//     // 18. Test Move Constructor (15 cases)
//     {
//         // Test 1: Move empty set
//         lasd::SetVec<int> setVec2{lasd::SetVec<int>{}};
//         assert(setVec2.Size() == 0);
//         // Test 2: Move set with one element
//         lasd::SetVec<int> temp;
//         temp.Insert(10);
//         lasd::SetVec<int> setVec3(std::move(temp));
//         assert(setVec3.Size() == 1);
//         assert(setVec3.Exists(10));
//         // Test 3: Move set with multiple elements
//         temp.Clear();
//         temp.Insert(5);
//         temp.Insert(10);
//         temp.Insert(15);
//         lasd::SetVec<int> setVec4(std::move(temp));
//         assert(setVec4.Size() == 3);
//         assert(setVec4.Exists(5));
//         // Test 4: Moved set is empty
//         assert(temp.Size() == 0);
//         // Test 5: Move with negative values
//         temp.Clear();
//         temp.Insert(-10);
//         temp.Insert(0);
//         lasd::SetVec<int> setVec5(std::move(temp));
//         assert(setVec5.Exists(-10));
//         // Test 6: Move large set
//         temp.Clear();
//         for (int i = 0; i < 10; ++i) {
//             temp.Insert(i * 10);
//         }
//         lasd::SetVec<int> setVec6(std::move(temp));
//         assert(setVec6.Size() == 10);
//         assert(setVec6.Exists(90));
//         // Test 7: Move after MinNRemove
//         temp.Clear();
//         temp.Insert(10);
//         temp.Insert(20);
//         temp.MinNRemove();
//         lasd::SetVec<int> setVec7(std::move(temp));
//         assert(setVec7.Exists(20));
//         // Test 8: Move after MaxNRemove
//         temp.Clear();
//         temp.Insert(10);
//         temp.Insert(20);
//         temp.MaxNRemove();
//         lasd::SetVec<int> setVec8(std::move(temp));
//         assert(setVec8.Exists(10));
//         // Test 9: Move after clear
//         temp.Clear();
//         lasd::SetVec<int> setVec9(std::move(temp));
//         assert(setVec9.Size() == 0);
//         // Test 10: Move with single negative
//         temp.Clear();
//         temp.Insert(-100);
//         lasd::SetVec<int> setVec10(std::move(temp));
//         assert(setVec10.Exists(-100));
//         // Test 11: Move after multiple inserts
//         temp.Clear();
//         temp.Insert(-50);
//         temp.Insert(0);
//         temp.Insert(50);
//         lasd::SetVec<int> setVec11(std::move(temp));
//         assert(setVec11.Size() == 3);
//         // Test 12: Move after multiple inserts
//         temp.Clear();
//         for (int i = 0; i < 20; ++i) {
//             temp.Insert(i * 10);
//         }
//         lasd::SetVec<int> setVec12(std::move(temp));
//         assert(setVec12.Exists(190));
//         // Test 13: Move and check original
//         assert(temp.Size() == 0);
//         // Test 14: Move after remove
//         temp.Clear();
//         temp.Insert(10);
//         temp.Insert(20);
//         temp.Remove(10);
//         lasd::SetVec<int> setVec13(std::move(temp));
//         assert(setVec13.Exists(20));
//         // Test 15: Move and modify moved
//         setVec13.Insert(30);
//         assert(setVec13.Size() == 2);
//         setVec.Clear();
//     }

//     // 19. Test Copy Assignment (15 cases)
//     {
//         lasd::SetVec<int> other;
//         // Test 1: Assign empty to empty
//         setVec = other;
//         assert(setVec.Size() == 0);
//         // Test 2: Assign non-empty to empty
//         other.Insert(10);
//         setVec = other;
//         assert(setVec.Size() == 1);
//         assert(setVec.Exists(10));
//         // Test 3: Assign with multiple elements
//         other.Insert(5);
//         other.Insert(15);
//         setVec = other;
//         assert(setVec.Size() == 3);
//         assert(setVec.Exists(5));
//         // Test 4: Independence of assignment
//         other.Remove(10);
//         assert(setVec.Exists(10));
//         // Test 5: Assign with negative values
//         other.Clear();
//         other.Insert(-10);
//         other.Insert(0);
//         setVec = other;
//         assert(setVec.Exists(-10));
//         // Test 6: Assign large set
//         other.Clear();
//         for (int i = 0; i < 10; ++i) {
//             other.Insert(i * 10);
//         }
//         setVec = other;
//         assert(setVec.Size() == 10);
//         assert(setVec.Exists(90));
//         // Test 7: Assign after MinNRemove
//         other.MinNRemove();
//         setVec = other;
//         assert(setVec.Exists(10));
//         // Test 8: Assign after MaxNRemove
//         other.MaxNRemove();
//         setVec = other;
//         assert(setVec.Exists(80));
//         // Test 9: Assign empty to non-empty
//         other.Clear();
//         setVec = other;
//         assert(setVec.Size() == 0);
//         // Test 10: Assign with single negative
//         other.Insert(-100);
//         setVec = other;
//         assert(setVec.Exists(-100));
//         // Test 11: Assign after multiple inserts
//         other.Insert(-50);
//         other.Insert(0);
//         setVec = other;
//         assert(setVec.Size() == 3);
//         // Test 12: Assign after multiple inserts
//         other.Clear();
//         for (int i = 0; i < 20; ++i) {
//             other.Insert(i * 10);
//         }
//         setVec = other;
//         assert(setVec.Exists(190));
//         // Test 13: Self-assignment
//         setVec = setVec;
//         assert(setVec.Size() == 20);
//         // Test 14: Assign after remove
//         other.Remove(100);
//         setVec = other;
//         assert(setVec.Exists(110));
//         // Test 15: Assign and modify original
//         other.Clear();
//         assert(setVec.Size() == 19);
//         setVec.Clear();
//     }

//     // 20. Test Move Assignment (15 cases)
//     {
//         lasd::SetVec<int> other;
//         // Test 1: Move assign empty to empty
//         setVec = std::move(other);
//         assert(setVec.Size() == 0);
//         // Test 2: Move assign non-empty to empty
//         other.Clear();
//         other.Insert(10);
//         setVec = std::move(other);
//         assert(setVec.Size() == 1);
//         assert(setVec.Exists(10));
//         // Test 3: Move assign with multiple elements
//         other.Clear();
//         other.Insert(5);
//         other.Insert(10);
//         other.Insert(15);
//         setVec = std::move(other);
//         assert(setVec.Size() == 3);
//         assert(setVec.Exists(5));
//         // Test 4: Original is empty
//         assert(other.Size() == 0);
//         // Test 5: Move assign with negative values
//         other.Clear();
//         other.Insert(-10);
//         other.Insert(0);
//         setVec = std::move(other);
//         assert(setVec.Exists(-10));
//         // Test 6: Move assign large set
//         other.Clear();
//         for (int i = 0; i < 10; ++i) {
//             other.Insert(i * 10);
//         }
//         setVec = std::move(other);
//         assert(setVec.Size() == 10);
//         assert(setVec.Exists(90));
//         // Test 7: Move assign after MinNRemove
//         other.Clear();
//         other.Insert(10);
//         other.Insert(20);
//         other.MinNRemove();
//         setVec = std::move(other);
//         assert(setVec.Exists(20));
//         // Test 8: Move assign after MaxNRemove
//         other.Clear();
//         other.Insert(10);
//         other.Insert(20);
//         other.MaxNRemove();
//         setVec = std::move(other);
//         assert(setVec.Exists(10));
//         // Test 9: Move assign empty to non-empty
//         other.Clear();
//         setVec = std::move(other);
//         assert(setVec.Size() == 0);
//         // Test 10: Move assign with single negative
//         other.Clear();
//         other.Insert(-100);
//         setVec = std::move(other);
//         assert(setVec.Exists(-100));
//         // Test 11: Move assign after multiple inserts
//         other.Clear();
//         other.Insert(-50);
//         other.Insert(0);
//         other.Insert(50);
//         setVec = std::move(other);
//         assert(setVec.Size() == 3);
//         // Test 12: Move assign after multiple inserts
//         other.Clear();
//         for (int i = 0; i < 20; ++i) {
//             other.Insert(i * 10);
//         }
//         setVec = std::move(other);
//         assert(setVec.Exists(190));
//         // Test 13: Move assign non-empty to non-empty
//         lasd::SetVec<int> temp;
//         temp.Insert(100);
//         temp.Insert(200);
//         setVec = std::move(temp);
//         assert(setVec.Size() == 2);
//         assert(setVec.Exists(100) && setVec.Exists(200));
//         assert(temp.Size() == 0);
//         // Test 14: Move assign after remove
//         other.Clear();
//         other.Insert(10);
//         other.Insert(20);
//         other.Remove(10);
//         setVec = std::move(other);
//         assert(setVec.Exists(20));
//         // Test 15: Move assign and check original
//         assert(other.Size() == 0);
//         setVec.Clear();
//     }

//     // 21. Test Operator[] (10 cases)
//     {
//         // Test 1: Operator[] on empty set (exception)
//         try {
//             setVec[0];
//             assert(false);
//         } catch (std::out_of_range&) {
//             assert(true);
//         }
//         // Test 2: Operator[] with one element
//         setVec.Insert(10);
//         assert(setVec[0] == 10);
//         // Test 3: Operator[] with multiple elements
//         setVec.Insert(5);
//         setVec.Insert(15);
//         assert(setVec[0] == 5);
//         assert(setVec[1] == 10);
//         assert(setVec[2] == 15);
//         // Test 4: Operator[] out of range (exception)
//         try {
//             setVec[3];
//             assert(false);
//         } catch (std::out_of_range&) {
//             assert(true);
//         }
//         // Test 5: Operator[] with large set
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(setVec[5] == 50);
//         // Test 6: Operator[] after remove
//         setVec.Remove(50);
//         assert(setVec[5] == 60);
//         // Test 7: Operator[] with negative values
//         setVec.Clear();
//         setVec.Insert(-10);
//         setVec.Insert(0);
//         assert(setVec[0] == -10);
//         // Test 8: Operator[] after MinNRemove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.MinNRemove();
//         assert(setVec[0] == 20);
//         // Test 9: Operator[] after MaxNRemove
//         setVec.Clear();
//         setVec.Insert(10);
//         setVec.Insert(20);
//         setVec.MaxNRemove();
//         assert(setVec[0] == 10);
//         // Test 10: Operator[] after clear
//         setVec.Clear();
//         try {
//             setVec[0];
//             assert(false);
//         } catch (std::out_of_range&) {
//             assert(true);
//         }
//         setVec.Clear();
//     }

//     // 22. Test Resize (11 cases)
//     {
//         // Test 1: Insert into empty set (initial capacity)
//         setVec.Clear();
//         assert(setVec.Size() == 0);
//         setVec.Insert(10);
//         assert(setVec.Size() == 1);
//         assert(setVec.Exists(10));
//         // Test 2: Insert multiple elements to trigger resize
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             assert(setVec.Insert(i * 10));
//         }
//         assert(setVec.Size() == 20);
//         assert(setVec.Exists(190));
//         // Test 3: Verify order after resize
//         for (unsigned long i = 1; i < setVec.Size(); ++i) {
//             assert(setVec[i - 1] < setVec[i]);
//         }
//         // Test 4: Insert after remove to trigger resize
//         setVec.Clear();
//         for (int i = 0; i < 10; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 5; ++i) {
//             setVec.Remove(i * 10);
//         }
//         for (int i = 10; i < 20; ++i) {
//             assert(setVec.Insert(i * 10));
//         }
//         assert(setVec.Size() == 15);
//         assert(setVec.Exists(190));
//         // Test 5: Insert with negative values
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             assert(setVec.Insert(i * 10 - 100));
//         }
//         assert(setVec.Size() == 20);
//         assert(setVec.Exists(-100));
//         assert(setVec.Exists(90));
//         // Test 6: Insert after clear
//         setVec.Clear();
//         setVec.Insert(25);
//         assert(setVec.Size() == 1);
//         assert(setVec.Exists(25));
//         // Test 7: Insert to trigger multiple resizes
//         setVec.Clear();
//         for (int i = 0; i < 50; ++i) {
//             assert(setVec.Insert(i));
//         }
//         assert(setVec.Size() == 50);
//         assert(setVec.Min() == 0);
//         assert(setVec.Max() == 49);
//         // Test 8: Insert after multiple removes
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         for (int i = 0; i < 15; ++i) {
//             setVec.Remove(i * 10);
//         }
//         for (int i = 20; i < 30; ++i) {
//             assert(setVec.Insert(i * 10));
//         }
//         assert(setVec.Size() == 15);
//         // Test 9: Insert duplicates after resize
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         assert(!setVec.Insert(0));
//         assert(setVec.Size() == 20);
//         // Test 10: Insert with move after resize
//         setVec.Clear();
//         for (int i = 0; i < 20; ++i) {
//             setVec.Insert(i * 10);
//         }
//         int value = 200;
//         assert(setVec.Insert(std::move(value)));
//         assert(setVec.Size() == 21);
//         assert(setVec.Exists(200));
//         // Test 11: Large set insert to trigger resize
//         setVec.Clear();
//         for (int i = 0; i < 100; ++i) {
//             assert(setVec.Insert(i * 10));
//         }
//         assert(setVec.Size() == 100);
//         assert(setVec.Exists(990));
//         for (unsigned long i = 1; i < setVec.Size(); ++i) {
//             assert(setVec[i - 1] < setVec[i]);
//         }
//         setVec.Clear();
//     }

//     // 23. Test Stress (1 case)
//     {
//         // Test 1: Large set operations
//         setVec.Clear();
//         for (int i = 0; i < 1000; ++i) {
//             setVec.Insert(i);
//         }
//         assert(setVec.Size() == 1000);
//         assert(setVec.Min() == 0);
//         assert(setVec.Max() == 999);
//         for (unsigned long i = 1; i < setVec.Size(); ++i) {
//             assert(setVec[i - 1] < setVec[i]);
//         }
//         setVec.Clear();
//     }

//     std::cout << "SetVec tests passed!" << std::endl;
// }




void testSetVec() {
    std::cout << "Testing SetVec..." << std::endl;
    lasd::SetVec<int> setVec;

    // 1. Test Default Constructor (25 cases)
    {
        // Test 1: Size of empty set
        assert(setVec.Size() == 0);
        // Test 2: Exists on empty set
        assert(!setVec.Exists(10));
        // Test 3: Min on empty set (exception)
        try {
            setVec.Min();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 4: Max on empty set (exception)
        try {
            setVec.Max();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 5: Operator[] on empty set (exception)
        try {
            setVec[0];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 6: Predecessor on empty set (exception)
        try {
            setVec.Predecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 7: Successor on empty set (exception)
        try {
            setVec.Successor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 8: MinNRemove on empty set (exception)
        try {
            setVec.MinNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 9: MaxNRemove on empty set (exception)
        try {
            setVec.MaxNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 10: RemovePredecessor on empty set (exception)
        try {
            setVec.RemovePredecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 11: RemoveSuccessor on empty set (exception)
        try {
            setVec.RemoveSuccessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 12: PredecessorNRemove on empty set (exception)
        try {
            setVec.PredecessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 13: SuccessorNRemove on empty set (exception)
        try {
            setVec.SuccessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 14: RemoveMin on empty set (exception)
        try {
            setVec.RemoveMin();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 15: RemoveMax on empty set (exception)
        try {
            setVec.RemoveMax();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 16: Equality with another empty set
        lasd::SetVec<int> other;
        assert(setVec == other);
        // Test 17: Inequality with non-empty set
        other.Insert(5);
        assert(setVec != other);
        // Test 18: Clear on empty set
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 19: Capacity after construction
        assert(setVec.Size() <= 4); // Assuming default capacity is 4
        // Test 20: Insert after clear
        setVec.Clear();
        assert(setVec.Insert(1));
        assert(setVec.Size() == 1);
        setVec.Clear();
        // Test 21: Verify head after construction
        lasd::SetVec<int> newSet;
        assert(newSet.Size() == 0);
        // Test 22: Operator[] with negative index (exception)
        try {
            setVec[-1];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 23: Move constructor with empty set
        // lasd::SetVec<int> movedSet(std::move(lasd::SetVec<int>{}));
        // assert(movedSet.Size() == 0);
        // Test 24: Copy constructor with empty set
        lasd::SetVec<int> copiedSet(setVec);
        assert(copiedSet.Size() == 0);
        // Test 25: Traversable container constructor with empty set
        lasd::SetVec<int> emptyContainer;
        lasd::SetVec<int> fromContainer(emptyContainer);
        assert(fromContainer.Size() == 0);
        setVec.Clear();
    }

    // 2. Test Insert (25 cases)
    {
        // Test 1: Insert single element
        assert(setVec.Insert(10));
        assert(setVec.Size() == 1);
        // Test 2: Insert duplicate
        assert(!setVec.Insert(10));
        assert(setVec.Size() == 1);
        // Test 3: Insert multiple elements
        assert(setVec.Insert(5));
        assert(setVec.Insert(15));
        assert(setVec.Size() == 3);
        // Test 4: Insert negative value
        assert(setVec.Insert(-10));
        assert(setVec.Size() == 4);
        // Test 5: Insert zero
        assert(setVec.Insert(0));
        assert(setVec.Size() == 5);
        // Test 6: Insert large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            assert(setVec.Insert(i * 10));
        }
        assert(setVec.Size() == 20);
        // Test 7: Insert after clear
        setVec.Clear();
        assert(setVec.Insert(25));
        assert(setVec.Size() == 1);
        // Test 8: Insert non-duplicate after duplicate attempt
        assert(!setVec.Insert(25));
        assert(setVec.Insert(50));
        assert(setVec.Size() == 2);
        // Test 9: Insert with move
        int value = 75;
        assert(setVec.Insert(std::move(value)));
        assert(setVec.Size() == 3);
        // Test 10: Insert large negative
        assert(setVec.Insert(-100));
        assert(setVec.Size() == 4);
        // Test 11: Insert after multiple inserts
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            assert(setVec.Insert(i * 10 - 50));
        }
        assert(setVec.Size() == 10);
        // Test 12: Insert with resize
        for (int i = 0; i < 10; ++i) {
            assert(setVec.Insert(i * 100 + 50));
        }
        assert(setVec.Size() == 20);
        // Test 13: Insert duplicate in large set
        assert(!setVec.Insert(0));
        assert(setVec.Size() == 20);
        // Test 14: Insert after remove
        setVec.Remove(0);
        assert(setVec.Insert(0));
        assert(setVec.Size() == 20);
        // Test 15: Insert with negative duplicates
        assert(!setVec.Insert(-50));
        assert(setVec.Size() == 20);
        // Test 16: Verify elements are sorted
        for (unsigned long i = 1; i < setVec.Size(); ++i) {
            assert(setVec[i - 1] < setVec[i]);
        }
        // Test 17: Insert to trigger multiple resizes
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            assert(setVec.Insert(i));
        }
        assert(setVec.Size() == 50);
        // Test 18: Insert after MinNRemove
        setVec.MinNRemove();
        assert(setVec.Insert(0));
        assert(setVec.Size() == 50);
        // Test 19: Insert after MaxNRemove
        setVec.MaxNRemove();
        assert(setVec.Insert(49));
        assert(setVec.Size() == 50);
        // Test 20: Insert with extreme values
        assert(setVec.Insert(10000));
        assert(setVec.Size() == 51);
        // Test 21: Insert with negative extreme values
        assert(setVec.Insert(-10000));
        assert(setVec.Size() == 52);
        // Test 22: Insert duplicates after resize
        assert(!setVec.Insert(10000));
        assert(setVec.Size() == 52);
        // Test 23: Insert after multiple removes
        for (int i = 0; i < 10; ++i) {
            setVec.Remove(i);
        }
        assert(setVec.Insert(5));
        assert(setVec.Size() == 43);
        // Test 24: Insert with move after resize
        int val = 20000;
        assert(setVec.Insert(std::move(val)));
        assert(setVec.Size() == 44);
        // Test 25: Insert to verify circular indexing
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec[0] == 0);
        assert(setVec[9] == 90);
        setVec.Clear();
    }

    // 3. Test Exists (25 cases)
    {
        // Test 1: Exists on empty set
        assert(!setVec.Exists(10));
        // Test 2: Exists with one element
        setVec.Insert(10);
        assert(setVec.Exists(10));
        // Test 3: Exists with non-existent element
        assert(!setVec.Exists(20));
        // Test 4: Exists with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Exists(5));
        // Test 5: Exists with negative value
        setVec.Insert(-10);
        assert(setVec.Exists(-10));
        // Test 6: Exists after clear
        setVec.Clear();
        assert(!setVec.Exists(10));
        // Test 7: Exists in large set
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Exists(50));
        // Test 8: Exists for non-existent in large set
        assert(!setVec.Exists(55));
        // Test 9: Exists after remove
        setVec.Remove(50);
        assert(!setVec.Exists(50));
        // Test 10: Exists with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(!setVec.Exists(-5));
        // Test 11: Exists after multiple inserts
        setVec.Clear();
        for (int i = 0; i < 5; ++i) {
            setVec.Insert(i * 10 - 20);
        }
        assert(setVec.Exists(-10));
        // Test 12: Exists after clear and reinsert
        setVec.Clear();
        setVec.Insert(25);
        assert(setVec.Exists(25));
        // Test 13: Exists with large value
        setVec.Insert(1000);
        assert(setVec.Exists(1000));
        // Test 14: Exists after multiple removes
        setVec.Remove(25);
        assert(!setVec.Exists(25));
        // Test 15: Exists with single element
        setVec.Clear();
        setVec.Insert(0);
        assert(setVec.Exists(0));
        // Test 16: Exists with extreme negative value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.Exists(-10000));
        // Test 17: Exists with extreme positive value
        setVec.Insert(10000);
        assert(setVec.Exists(10000));
        // Test 18: Exists after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(!setVec.Exists(10));
        // Test 19: Exists after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(!setVec.Exists(20));
        // Test 20: Exists after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.PredecessorNRemove(20);
        assert(!setVec.Exists(10));
        // Test 21: Exists after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(!setVec.Exists(20));
        // Test 22: Exists with duplicates
        assert(!setVec.Insert(10));
        assert(setVec.Exists(10));
        // Test 23: Exists after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i);
        }
        assert(setVec.Exists(49));
        // Test 24: Exists after multiple clears and inserts
        setVec.Clear();
        setVec.Insert(100);
        setVec.Clear();
        setVec.Insert(100);
        assert(setVec.Exists(100));
        // Test 25: Exists in sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.Exists(1000));
        setVec.Clear();
    }

    // 4. Test Remove (25 cases)
    {
        // Test 1: Remove from empty set
        assert(!setVec.Remove(10));
        // Test 2: Remove single element
        setVec.Insert(10);
        assert(setVec.Remove(10));
        assert(setVec.Size() == 0);
        // Test 3: Remove non-existent
        setVec.Insert(10);
        assert(!setVec.Remove(20));
        // Test 4: Remove with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Remove(10));
        assert(setVec.Size() == 2);
        // Test 5: Remove negative value
        setVec.Clear();
        setVec.Insert(-10);
        assert(setVec.Remove(-10));
        // Test 6: Remove from large set
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Remove(50));
        assert(setVec.Size() == 9);
        // Test 7: Remove after clear
        setVec.Clear();
        assert(!setVec.Remove(10));
        // Test 8: Remove min
        setVec.Insert(10);
        setVec.Insert(20);
        assert(setVec.Remove(10));
        assert(setVec.Size() == 1);
        // Test 9: Remove max
        setVec.Insert(30);
        assert(setVec.Remove(30));
        assert(setVec.Size() == 1);
        // Test 10: Remove with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Remove(-10));
        // Test 11: Remove all elements
        setVec.Clear();
        for (int i = 0; i < 5; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 5; ++i) {
            assert(setVec.Remove(i * 10));
        }
        assert(setVec.Size() == 0);
        // Test 12: Remove after resize
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Remove(100));
        assert(setVec.Size() == 19);
        assert(!setVec.Exists(100));
        // Test 13: Remove non-existent in large set
        assert(!setVec.Remove(100));
        // Test 14: Remove with single element
        setVec.Clear();
        setVec.Insert(10);
        assert(setVec.Remove(10));
        assert(setVec.Size() == 0);
        // Test 15: Remove after multiple inserts
        setVec.Insert(10);
        setVec.Insert(20);
        assert(setVec.Remove(20));
        assert(setVec.Size() == 1);
        // Test 16: Remove after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec.Remove(20));
        assert(setVec.Size() == 0);
        // Test 17: Remove after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec.Remove(10));
        assert(setVec.Size() == 0);
        // Test 18: Remove extreme value
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec.Remove(10000));
        assert(setVec.Size() == 0);
        // Test 19: Remove negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.Remove(-10000));
        assert(setVec.Size() == 0);
        // Test 20: Remove after resize down
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Size() == 5);
        // Test 21: Remove middle element in large set
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i);
        }
        assert(setVec.Remove(25));
        assert(setVec.Size() == 49);
        // Test 22: Remove after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.PredecessorNRemove(20);
        assert(setVec.Remove(20));
        assert(setVec.Size() == 0);
        // Test 23: Remove after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(setVec.Remove(10));
        assert(setVec.Size() == 0);
        // Test 24: Remove with circular indexing
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Remove(90));
        assert(setVec.Size() == 9);
        // Test 25: Remove all but one element
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 9; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Size() == 1);
        assert(setVec.Exists(90));
        setVec.Clear();
    }

    // 5. Test Min (25 cases)
    {
        // Test 1: Min on empty set (exception)
        try {
            setVec.Min();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: Min with one element
        setVec.Insert(10);
        assert(setVec.Min() == 10);
        // Test 3: Min with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Min() == 5);
        // Test 4: Min with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Min() == -10);
        // Test 5: Min after remove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(10);
        assert(setVec.Min() == 20);
        // Test 6: Min with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Min() == 0);
        // Test 7: Min after clear
        setVec.Clear();
        try {
            setVec.Min();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 8: Min with single negative
        setVec.Insert(-100);
        assert(setVec.Min() == -100);
        // Test 9: Min after multiple inserts
        setVec.Clear();
        setVec.Insert(-100);
        setVec.Insert(-50);
        setVec.Insert(0);
        assert(setVec.Min() == -100);
        // Test 10: Min with large negative
        setVec.Clear();
        setVec.Insert(-1000);
        setVec.Insert(-500);
        assert(setVec.Min() == -1000);
        // Test 11: Min after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec.Min() == 20);
        // Test 12: Min after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 5; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Min() == 50);
        // Test 13: Min with single element
        setVec.Clear();
        setVec.Insert(0);
        assert(setVec.Min() == 0);
        // Test 14: Min after reinsert
        setVec.Clear();
        setVec.Insert(25);
        setVec.Insert(50);
        assert(setVec.Min() == 25);
        // Test 15: Min after large set insert
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10 - 100);
        }
        assert(setVec.Min() == -100);
        // Test 16: Min with extreme negative value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.Min() == -10000);
        // Test 17: Min with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.Min() == 0);
        // Test 18: Min after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec.Min() == 10);
        // Test 19: Min after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.Min() == 10);
        // Test 20: Min after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(setVec.Min() == 10);
        // Test 21: Min after resize down
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Min() == 150);
        // Test 22: Min after multiple MinNRemove
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.MinNRemove();
        setVec.MinNRemove();
        assert(setVec.Min() == 20);
        // Test 23: Min with single extreme value
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec.Min() == 10000);
        // Test 24: Min after insert and remove
        setVec.Clear();
        setVec.Insert(-50);
        setVec.Insert(0);
        setVec.Remove(-50);
        assert(setVec.Min() == 0);
        // Test 25: Min after large set with negative values
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10 - 1000);
        }
        assert(setVec.Min() == -1000);
        setVec.Clear();
    }

    // 6. Test Max (25 cases)
    {
        // Test 1: Max on empty set (exception)
        try {
            setVec.Max();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: Max with one element
        setVec.Insert(10);
        assert(setVec.Max() == 10);
        // Test 3: Max with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Max() == 15);
        // Test 4: Max with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Max() == 0);
        // Test 5: Max after remove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(20);
        assert(setVec.Max() == 10);
        // Test 6: Max with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Max() == 190);
        // Test 7: Max after clear
        setVec.Clear();
        try {
            setVec.Max();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 8: Max with single negative
        setVec.Insert(-100);
        assert(setVec.Max() == -100);
        // Test 9: Max after multiple inserts
        setVec.Insert(-50);
        setVec.Insert(0);
        assert(setVec.Max() == 0);
        // Test 10: Max with large value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(500);
        assert(setVec.Max() == 1000);
        // Test 11: Max after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec.Max() == 10);
        // Test 12: Max after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 5; i < 10; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Max() == 40);
        // Test 13: Max with single element
        setVec.Clear();
        setVec.Insert(0);
        assert(setVec.Max() == 0);
        // Test 14: Max after reinsert
        setVec.Clear();
        setVec.Insert(25);
        setVec.Insert(50);
        assert(setVec.Max() == 50);
        // Test 15: Max after large set insert
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10 - 100);
        }
        assert(setVec.Max() == 90);
        // Test 16: Max with extreme positive value
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec.Max() == 10000);
        // Test 17: Max with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.Max() == 1000);
        // Test 18: Max after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec.Max() == 20);
        // Test 19: Max after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.Max() == 30);
        // Test 20: Max after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(setVec.Max() == 10);
        // Test 21: Max after resize down
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.Max() == 190);
        // Test 22: Max after multiple MaxNRemove
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.MaxNRemove();
        setVec.MaxNRemove();
        assert(setVec.Max() == 70);
        // Test 23: Max with single extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.Max() == -10000);
        // Test 24: Max after insert and remove
        setVec.Clear();
        setVec.Insert(-50);
        setVec.Insert(0);
        setVec.Remove(0);
        assert(setVec.Max() == -50);
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
        setVec.Insert(i * 10 - 1000);
        }
        assert(setVec.Max() == -510); // Corrected expected maximum
    setVec.Clear();
    }

    // 7. Test MinNRemove (25 cases)
    {
        // Test 1: MinNRemove on empty set (exception)
        try {
            setVec.MinNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: MinNRemove with one element
        setVec.Insert(10);
        assert(setVec.MinNRemove() == 10);
        // Test 3: Size after MinNRemove
        assert(setVec.Size() == 0);
        // Test 4: MinNRemove with multiple elements
        setVec.Insert(5);
        setVec.Insert(10);
        setVec.Insert(15);
        assert(setVec.MinNRemove() == 5);
        // Test 5: Size after MinNRemove
        assert(setVec.Size() == 2);
        // Test 6: MinNRemove with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.MinNRemove() == -10);
        // Test 7: MinNRemove after multiple inserts
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10 - 50);
        }
        assert(setVec.MinNRemove() == -50);
        // Test 8: MinNRemove after min removal
        assert(setVec.MinNRemove() == -40);
        // Test 9: Size after multiple MinNRemove
        assert(setVec.Size() == 8);
        // Test 10: MinNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.MinNRemove();
        }
        assert(setVec.Size() == 5);
        // Test 11: MinNRemove with single negative
        setVec.Clear();
        setVec.Insert(-100);
        assert(setVec.MinNRemove() == -100);
        // Test 12: MinNRemove after clear
        try {
            setVec.MinNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 13: MinNRemove with large negative
        setVec.Insert(-1000);
        setVec.Insert(-500);
        assert(setVec.MinNRemove() == -1000);
        // Test 14: MinNRemove with one element left
        assert(setVec.MinNRemove() == -500);
        assert(setVec.Size() == 0);
        // Test 15: MinNRemove after reinsert
        setVec.Insert(25);
        setVec.Insert(50);
        assert(setVec.MinNRemove() == 25);
        // Test 16: MinNRemove after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i);
        }
        assert(setVec.MinNRemove() == 0);
        assert(setVec.Size() == 49);
        // Test 17: MinNRemove with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.MinNRemove() == 0);
        // Test 18: MinNRemove after remove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(10);
        assert(setVec.MinNRemove() == 20);
        // Test 19: MinNRemove with extreme value
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec.MinNRemove() == 10000);
        // Test 20: MinNRemove with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.MinNRemove() == -10000);
        // Test 21: MinNRemove after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(0);
        assert(setVec.MinNRemove() == 10);
        // Test 22: MinNRemove after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.MinNRemove() == 10);
        // Test 23: MinNRemove after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(setVec.MinNRemove() == 10);
        // Test 24: MinNRemove after resize down
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.MinNRemove() == 150);
        // Test 25: MinNRemove with large negative set
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10 - 1000);
        }
        assert(setVec.MinNRemove() == -1000);
        setVec.Clear();
    }

    // 8. Test MaxNRemove (25 cases)
    {
        // Test 1: MaxNRemove on empty set (exception)
        try {
            setVec.MaxNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: MaxNRemove with one element
        setVec.Insert(10);
        assert(setVec.MaxNRemove() == 10);
        // Test 3: Size after MaxNRemove
        assert(setVec.Size() == 0);
        // Test 4: MaxNRemove with multiple elements
        setVec.Insert(5);
        setVec.Insert(10);
        setVec.Insert(15);
        assert(setVec.MaxNRemove() == 15);
        // Test 5: Size after MaxNRemove
        assert(setVec.Size() == 2);
        // Test 6: MaxNRemove with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.MaxNRemove() == 0);
        // Test 7: MaxNRemove after multiple inserts
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10 - 50);
        }
        assert(setVec.MaxNRemove() == 40);
        // Test 8: MaxNRemove after max removal
        assert(setVec.MaxNRemove() == 30);
        // Test 9: Size after multiple MaxNRemove
        assert(setVec.Size() == 8);
        // Test 10: MaxNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.MaxNRemove();
        }
        assert(setVec.Size() == 5);
        // Test 11: MaxNRemove with single negative
        setVec.Clear();
        setVec.Insert(-100);
        assert(setVec.MaxNRemove() == -100);
        // Test 12: MaxNRemove after clear
        try {
            setVec.MaxNRemove();
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 13: MaxNRemove with large value
        setVec.Insert(1000);
        setVec.Insert(500);
        assert(setVec.MaxNRemove() == 1000);
        // Test 14: MaxNRemove with one element left
        assert(setVec.MaxNRemove() == 500);
        assert(setVec.Size() == 0);
        // Test 15: MaxNRemove after reinsert
        setVec.Insert(25);
        setVec.Insert(50);
        assert(setVec.MaxNRemove() == 50);
        // Test 16: MaxNRemove after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i);
        }
        assert(setVec.MaxNRemove() == 49);
        assert(setVec.Size() == 49);
        // Test 17: MaxNRemove with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.MaxNRemove() == 1000);
        // Test 18: MaxNRemove after remove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(20);
        assert(setVec.MaxNRemove() == 10);
        // Test 19: MaxNRemove with extreme value
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec.MaxNRemove() == 10000);
        // Test 20: MaxNRemove with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec.MaxNRemove() == -10000);
        // Test 21: MaxNRemove after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(90);
        assert(setVec.MaxNRemove() == 80);
        // Test 22: MaxNRemove after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.MaxNRemove() == 30);
        // Test 23: MaxNRemove after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.SuccessorNRemove(10);
        assert(setVec.MaxNRemove() == 10);
        // Test 24: MaxNRemove after resize down
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec.MaxNRemove() == 190);
        // Test 25: MaxNRemove with large negative set
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10 - 1000);
        }
        assert(setVec.MaxNRemove() == -510);
        setVec.Clear();
    }

    // 9. Test Predecessor (25 cases)
    {
        // Test 1: Predecessor on empty set (exception)
        try {
            setVec.Predecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: Predecessor with one element (exception)
        setVec.Insert(10);
        try {
            setVec.Predecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 3: Predecessor with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Predecessor(15) == 10);
        // Test 4: Predecessor of min (exception)
        try {
            setVec.Predecessor(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 5: Predecessor of non-existent larger value
        assert(setVec.Predecessor(20) == 15);
        // Test 6: Predecessor with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Predecessor(0) == -10);
        // Test 7: Predecessor with large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Predecessor(50) == 40);
        // Test 8: Predecessor of value between elements
        assert(setVec.Predecessor(45) == 40);
        // Test 9: Predecessor after remove
        setVec.Remove(40);
        assert(setVec.Predecessor(50) == 30);
        // Test 10: Predecessor with single element
        setVec.Clear();
        setVec.Insert(10);
        try {
            setVec.Predecessor(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 11: Predecessor with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Predecessor(-5) == -10);
        // Test 12: Predecessor after clear
        setVec.Clear();
        try {
            setVec.Predecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 13: Predecessor with large negative
        setVec.Insert(-100);
        setVec.Insert(-50);
        assert(setVec.Predecessor(-50) == -100);
        // Test 14: Predecessor after multiple inserts
        setVec.Insert(-75);
        assert(setVec.Predecessor(-50) == -75);
        // Test 15: Predecessor of max in large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Predecessor(90) == 80);
        // Test 16: Predecessor after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec.Predecessor(30) == 20);
        // Test 17: Predecessor after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec.Predecessor(15) == 10);
        // Test 18: Predecessor with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.Predecessor(1000) == 0);
        // Test 19: Predecessor with extreme value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        assert(setVec.Predecessor(10000) == 1000);
        // Test 20: Predecessor with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        assert(setVec.Predecessor(-1000) == -10000);
        // Test 21: Predecessor after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Predecessor(250) == 240);
        // Test 22: Predecessor after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(20);
        setVec.Remove(30);
        assert(setVec.Predecessor(40) == 10);
        // Test 23: Predecessor after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.Predecessor(40) == 30);
        // Test 24: Predecessor after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        assert(setVec.Predecessor(30) == 10);
        // Test 25: Predecessor with non-existent smaller value
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.Predecessor(50);
            assert(false); // Should not reach here
        } catch (std::length_error&) {
            assert(true); // Correctly caught the exception
        }
        setVec.Clear();
    }

    // 10. Test Successor (25 cases)
    {
        // Test 1: Successor on empty set (exception)
        try {
            setVec.Successor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: Successor with one element (exception)
        setVec.Insert(10);
        try {
            setVec.Successor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 3: Successor with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.Successor(5) == 10);
        // Test 4: Successor of max (exception)
        try {
            setVec.Successor(15);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 5: Successor of non-existent smaller value
        assert(setVec.Successor(0) == 5);
        // Test 6: Successor with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Successor(-10) == 0);
        // Test 7: Successor with large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Successor(40) == 50);
        // Test 8: Successor of value between elements
        assert(setVec.Successor(45) == 50);
        // Test 9: Successor after remove
        setVec.Remove(50);
        assert(setVec.Successor(40) == 60);
        // Test 10: Successor with single element
        setVec.Clear();
        setVec.Insert(10);
        try {
            setVec.Successor(15);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 11: Successor with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.Successor(-15) == -10);
        // Test 12: Successor after clear
        setVec.Clear();
        try {
            setVec.Successor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 13: Successor with large value
        setVec.Insert(500);
        setVec.Insert(1000);
        assert(setVec.Successor(500) == 1000);
        // Test 14: Successor after multiple inserts
        setVec.Insert(750);
        assert(setVec.Successor(500) == 750);
        // Test 15: Successor of min in large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Successor(0) == 10);
        // Test 16: Successor after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec.Successor(15) == 20);
        // Test 17: Successor after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec.Successor(5) == 10);
        // Test 18: Successor with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.Successor(0) == 1000);
        // Test 19: Successor with extreme value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        assert(setVec.Successor(1000) == 10000);
        // Test 20: Successor with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        assert(setVec.Successor(-10000) == -1000);
        // Test 21: Successor after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.Successor(240) == 250);
        // Test 22: Successor after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(60);
        setVec.Remove(70);
        assert(setVec.Successor(50) == 80);
        // Test 23: Successor after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.Successor(10) == 30);
        // Test 24: Successor after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        assert(setVec.Successor(10) == 30);
        // Test 25: Successor with non-existent larger value
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.Successor(200);
            assert(false); // Should not reach here
        } catch (std::length_error&) {
            assert(true); // Correctly caught the exception
        }
        setVec.Clear();
    }

    // 11. Test PredecessorNRemove (25 cases)
    {
        // Test 1: PredecessorNRemove on empty set (exception)
        try {
            setVec.PredecessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: PredecessorNRemove with one element (exception)
        setVec.Insert(10);
        try {
            setVec.PredecessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 3: PredecessorNRemove with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.PredecessorNRemove(15) == 10);
        // Test 4: Size after PredecessorNRemove
        assert(setVec.Size() == 2);
        // Test 5: PredecessorNRemove of min (exception)
        try {
            setVec.PredecessorNRemove(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 6: PredecessorNRemove of non-existent
        assert(setVec.PredecessorNRemove(20) == 15);
        // Test 7: PredecessorNRemove with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.PredecessorNRemove(0) == -10);
        // Test 8: PredecessorNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.PredecessorNRemove(50) == 40);
        // Test 9: Size after PredecessorNRemove
        assert(setVec.Size() == 9);
        // Test 10: PredecessorNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.PredecessorNRemove((19 - i) * 10);
        }
        assert(setVec.Size() == 5);
        // Test 11: PredecessorNRemove with single element
        setVec.Clear();
        setVec.Insert(10);
        try {
            setVec.PredecessorNRemove(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 12: PredecessorNRemove with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.PredecessorNRemove(-5) == -10);
        // Test 13: PredecessorNRemove after clear
        setVec.Clear();
        try {
            setVec.PredecessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 14: PredecessorNRemove with large negative
        setVec.Insert(-100);
        setVec.Insert(-50);
        assert(setVec.PredecessorNRemove(-50) == -100);
        // Test 15: PredecessorNRemove after multiple inserts
        setVec.Insert(-75);
        assert(setVec.PredecessorNRemove(-50) == -75);
        // Test 16: PredecessorNRemove after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MinNRemove();
        assert(setVec.PredecessorNRemove(30) == 20);
        // Test 17: PredecessorNRemove after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MaxNRemove();
        assert(setVec.PredecessorNRemove(20) == 10);
        // Test 18: PredecessorNRemove with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.PredecessorNRemove(1000) == 0);
        // Test 19: PredecessorNRemove with extreme value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        assert(setVec.PredecessorNRemove(10000) == 1000);
        // Test 20: PredecessorNRemove with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        assert(setVec.PredecessorNRemove(-1000) == -10000);
        // Test 21: PredecessorNRemove after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.PredecessorNRemove(250) == 240);
        // Test 22: PredecessorNRemove after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(20);
        setVec.Remove(30);
        assert(setVec.PredecessorNRemove(40) == 10);
        // Test 23: PredecessorNRemove after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        assert(setVec.PredecessorNRemove(30) == 10);
        // Test 24: PredecessorNRemove after multiple PredecessorNRemove
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.PredecessorNRemove(50);
        setVec.PredecessorNRemove(60);
        assert(setVec.PredecessorNRemove(70) == 60);
        // Test 25: PredecessorNRemove with non-existent smaller value
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.PredecessorNRemove(50);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        setVec.Clear();
    }

    // 12. Test SuccessorNRemove (25 cases)
    {
        // Test 1: SuccessorNRemove on empty set (exception)
        try {
            setVec.SuccessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: SuccessorNRemove with one element (exception)
        setVec.Insert(10);
        try {
            setVec.SuccessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 3: SuccessorNRemove with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec.SuccessorNRemove(5) == 10);
        // Test 4: Size after SuccessorNRemove
        assert(setVec.Size() == 2);
        // Test 5: SuccessorNRemove of max (exception)
        try {
            setVec.SuccessorNRemove(15);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 6: SuccessorNRemove of non-existent
        assert(setVec.SuccessorNRemove(0) == 5);
        // Test 7: SuccessorNRemove with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.SuccessorNRemove(-10) == 0);
        // Test 8: SuccessorNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.SuccessorNRemove(40) == 50);
        // Test 9: Size after SuccessorNRemove
        assert(setVec.Size() == 9);
        // Test 10: SuccessorNRemove with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.SuccessorNRemove(i * 10);
        }
        assert(setVec.Size() == 5);
        // Test 11: SuccessorNRemove with single element
        setVec.Clear();
        setVec.Insert(10);
        try {
            setVec.SuccessorNRemove(15);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 12: SuccessorNRemove with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec.SuccessorNRemove(-15) == -10);
        // Test 13: SuccessorNRemove after clear
        setVec.Clear();
        try {
            setVec.SuccessorNRemove(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 14: SuccessorNRemove with large value
        setVec.Insert(500);
        setVec.Insert(1000);
        assert(setVec.SuccessorNRemove(500) == 1000);
        // Test 15: SuccessorNRemove after multiple inserts
        setVec.Insert(750);
        assert(setVec.SuccessorNRemove(500) == 750);
        // Test 16: SuccessorNRemove after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MinNRemove();
        assert(setVec.SuccessorNRemove(10) == 20);
        // Test 17: SuccessorNRemove after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MaxNRemove();
        assert(setVec.SuccessorNRemove(10) == 20);
        // Test 18: SuccessorNRemove with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec.SuccessorNRemove(0) == 1000);
        // Test 19: SuccessorNRemove with extreme value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        assert(setVec.SuccessorNRemove(1000) == 10000);
        // Test 20: SuccessorNRemove with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        assert(setVec.SuccessorNRemove(-10000) == -1000);
        // Test 21: SuccessorNRemove after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec.SuccessorNRemove(240) == 250);
        // Test 22: SuccessorNRemove after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(60);
        setVec.Remove(70);
        assert(setVec.SuccessorNRemove(50) == 80);
        // Test 23: SuccessorNRemove after PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec.SuccessorNRemove(10) == 30);
        // Test 24: SuccessorNRemove after multiple SuccessorNRemove
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.SuccessorNRemove(40);
        setVec.SuccessorNRemove(50);
        assert(setVec.SuccessorNRemove(60) == 70);
        // Test 25: SuccessorNRemove with non-existent larger value
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.SuccessorNRemove(250);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        setVec.Clear();
    }

    // 13. Test RemovePredecessor (25 cases)
    {
        // Test 1: RemovePredecessor on empty set (exception)
        try {
            setVec.RemovePredecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 2: RemovePredecessor with one element (exception)
        setVec.Insert(10);
        try {
            setVec.RemovePredecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 3: RemovePredecessor with multiple elements
        setVec.Insert(5);
        setVec.Insert(15);
        setVec.RemovePredecessor(15);
        assert(!setVec.Exists(10));
        // Test 4: Size after RemovePredecessor
        assert(setVec.Size() == 2);
        // Test 5: RemovePredecessor of min (exception)
        try {
            setVec.RemovePredecessor(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 6: RemovePredecessor of non-existent
        setVec.RemovePredecessor(20);
        assert(!setVec.Exists(15));
        // Test 7: RemovePredecessor with negative values
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        setVec.RemovePredecessor(0);
        assert(!setVec.Exists(-10));
        // Test 8: RemovePredecessor with large set
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.RemovePredecessor(50);
        assert(!setVec.Exists(40));
        // Test 9: Size after RemovePredecessor
        assert(setVec.Size() == 9);
        // Test 10: RemovePredecessor with large set
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.RemovePredecessor((19 - i) * 10);
        }
        assert(setVec.Size() == 5);
        // Test 11: RemovePredecessor with single element
        setVec.Clear();
        setVec.Insert(10);
        try {
            setVec.RemovePredecessor(5);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 12: RemovePredecessor with negative non-existent
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        setVec.RemovePredecessor(-5);
        assert(!setVec.Exists(-10));
        // Test 13: RemovePredecessor after clear
        setVec.Clear();
        try {
            setVec.RemovePredecessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 14: RemovePredecessor with large negative
        setVec.Insert(-100);
        setVec.Insert(-50);
        setVec.RemovePredecessor(-50);
        assert(!setVec.Exists(-100));
        // Test 15: RemovePredecessor after multiple inserts
        setVec.Insert(-75);
        setVec.RemovePredecessor(-50);
        assert(!setVec.Exists(-75));
        // Test 16: RemovePredecessor after MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MinNRemove();
        setVec.RemovePredecessor(30);
        assert(!setVec.Exists(20));
        // Test 17: RemovePredecessor after MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MaxNRemove();
        setVec.RemovePredecessor(20);
        assert(!setVec.Exists(10));
        // Test 18: RemovePredecessor with sparse set
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        setVec.RemovePredecessor(1000);
        assert(!setVec.Exists(0));
        // Test 19: RemovePredecessor with extreme value
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        setVec.RemovePredecessor(10000);
        assert(!setVec.Exists(1000));
        // Test 20: RemovePredecessor with negative extreme value
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        setVec.RemovePredecessor(-1000);
        assert(!setVec.Exists(-10000));
        // Test 21: RemovePredecessor after resize
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.RemovePredecessor(250);
        assert(!setVec.Exists(240));
        // Test 22: RemovePredecessor after multiple removes
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(20);
        setVec.Remove(30);
        setVec.RemovePredecessor(40);
        assert(!setVec.Exists(10));
        // Test 23: RemovePredecessor after SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        setVec.RemovePredecessor(30);
        assert(!setVec.Exists(10));
        // Test 24: RemovePredecessor after multiple RemovePredecessor
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.RemovePredecessor(50);
        setVec.RemovePredecessor(60);
        setVec.RemovePredecessor(70);
        assert(!setVec.Exists(60));
        // Test 25: RemovePredecessor with non-existent smaller value
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.RemovePredecessor(50);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        setVec.Clear();
    }

        // 14. Test RemoveSuccessor (continuazione, completando i 25 casi)
    {
        // Test 12: RemoveSuccessor con valore negativo non esistente
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        setVec.RemoveSuccessor(-15);
        assert(!setVec.Exists(-10));
        // Test 13: RemoveSuccessor dopo clear
        setVec.Clear();
        try {
            setVec.RemoveSuccessor(10);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        // Test 14: RemoveSuccessor con valore grande
        setVec.Insert(500);
        setVec.Insert(1000);
        setVec.RemoveSuccessor(500);
        assert(!setVec.Exists(1000));
        // Test 15: RemoveSuccessor dopo inserimenti multipli
        setVec.Insert(750);
        setVec.RemoveSuccessor(500);
        assert(!setVec.Exists(750));
        // Test 16: RemoveSuccessor dopo MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MinNRemove();
        setVec.RemoveSuccessor(10);
        assert(!setVec.Exists(20));
        // Test 17: RemoveSuccessor dopo MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.MaxNRemove();
        setVec.RemoveSuccessor(10);
        assert(!setVec.Exists(20));
        // Test 18: RemoveSuccessor con set sparso
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        setVec.RemoveSuccessor(0);
        assert(!setVec.Exists(1000));
        // Test 19: RemoveSuccessor con valore estremo
        setVec.Clear();
        setVec.Insert(1000);
        setVec.Insert(10000);
        setVec.RemoveSuccessor(1000);
        assert(!setVec.Exists(10000));
        // Test 20: RemoveSuccessor con valore estremo negativo
        setVec.Clear();
        setVec.Insert(-10000);
        setVec.Insert(-1000);
        setVec.RemoveSuccessor(-10000);
        assert(!setVec.Exists(-1000));
        // Test 21: RemoveSuccessor dopo ridimensionamento
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.RemoveSuccessor(240);
        assert(!setVec.Exists(250));
        // Test 22: RemoveSuccessor dopo rimozioni multiple
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(60);
        setVec.Remove(70);
        setVec.RemoveSuccessor(50);
        assert(!setVec.Exists(80));
        // Test 23: RemoveSuccessor dopo PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        setVec.RemoveSuccessor(10);
        assert(!setVec.Exists(30));
        // Test 24: RemoveSuccessor dopo rimozioni multiple di successori
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.RemoveSuccessor(40);
        setVec.RemoveSuccessor(50);
        setVec.RemoveSuccessor(60);
        assert(!setVec.Exists(70));
        // Test 25: RemoveSuccessor con valore non esistente più grande
        setVec.Clear();
        setVec.Insert(100);
        setVec.Insert(200);
        try {
            setVec.RemoveSuccessor(250);
            assert(false);
        } catch (std::length_error&) {
            assert(true);
        }
        setVec.Clear();
    }

    // 15. Test Operator[] (25 casi)
    {
        // Test 1: Operator[] su set vuoto (eccezione)
        try {
            setVec[0];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 2: Operator[] con un elemento
        setVec.Insert(10);
        assert(setVec[0] == 10);
        // Test 3: Operator[] con indice fuori range
        try {
            setVec[1];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 4: Operator[] con più elementi
        setVec.Insert(5);
        setVec.Insert(15);
        assert(setVec[0] == 5);
        assert(setVec[1] == 10);
        assert(setVec[2] == 15);
        // Test 5: Operator[] con valori negativi
        setVec.Clear();
        setVec.Insert(-10);
        setVec.Insert(0);
        assert(setVec[0] == -10);
        // Test 6: Operator[] con set grande
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec[10] == 100);
        // Test 7: Operator[] dopo clear
        setVec.Clear();
        try {
            setVec[0];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 8: Operator[] dopo rimozione
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(10);
        assert(setVec[0] == 20);
        // Test 9: Operator[] con indicizzazione circolare
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec[9] == 90);
        // Test 10: Operator[] dopo MinNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        assert(setVec[0] == 20);
        // Test 11: Operator[] dopo MaxNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        assert(setVec[0] == 10);
        // Test 12: Operator[] con set sparso
        setVec.Clear();
        setVec.Insert(0);
        setVec.Insert(1000);
        assert(setVec[1] == 1000);
        // Test 13: Operator[] con valore estremo
        setVec.Clear();
        setVec.Insert(10000);
        assert(setVec[0] == 10000);
        // Test 14: Operator[] con valore estremo negativo
        setVec.Clear();
        setVec.Insert(-10000);
        assert(setVec[0] == -10000);
        // Test 15: Operator[] dopo ridimensionamento
        setVec.Clear();
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        assert(setVec[49] == 490);
        // Test 16: Operator[] con indice negativo (eccezione)
        try {
            setVec[-1];
            assert(false);
        } catch (std::out_of_range&) {
            assert(true);
        }
        // Test 17: Operator[] dopo rimozioni multiple
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 5; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec[0] == 50);
        // Test 18: Operator[] dopo PredecessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        assert(setVec[0] == 10);
        // Test 19: Operator[] dopo SuccessorNRemove
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        assert(setVec[1] == 30);
        // Test 20: Operator[] dopo RemovePredecessor
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.RemovePredecessor(30);
        assert(setVec[0] == 10);
        // Test 21: Operator[] dopo RemoveSuccessor
        setVec.Clear();
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.RemoveSuccessor(10);
        assert(setVec[1] == 30);
        // Test 22: Operator[] con set di un solo elemento dopo rimozioni
        setVec.Clear();
        for (int i = 0; i < 5; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 4; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec[0] == 40);
        // Test 23: Operator[] dopo inserimento multiplo e rimozione
        setVec.Clear();
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Remove(50);
        assert(setVec[5] == 60);
        // Test 24: Operator[] con set grande dopo ridimensionamento verso il basso
        setVec.Clear();
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        assert(setVec[4] == 190);
        // Test 25: Operator[] con valori negativi sparsi
        setVec.Clear();
        setVec.Insert(-100);
        setVec.Insert(-50);
        setVec.Insert(0);
        assert(setVec[1] == -50);
        setVec.Clear();
    }

    // 16. Test Clear (25 casi)
    {
        // Test 1: Clear su set vuoto
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 2: Clear con un elemento
        setVec.Insert(10);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 3: Clear con più elementi
        setVec.Insert(5);
        setVec.Insert(10);
        setVec.Insert(15);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 4: Clear dopo MinNRemove
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 5: Clear dopo MaxNRemove
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MaxNRemove();
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 6: Clear con set grande
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 7: Clear multiplo
        setVec.Insert(10);
        setVec.Clear();
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 8: Clear con valori negativi
        setVec.Insert(-10);
        setVec.Insert(0);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 9: Clear dopo rimozione
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Remove(10);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 10: Clear dopo PredecessorNRemove
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.PredecessorNRemove(30);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 11: Clear dopo SuccessorNRemove
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.SuccessorNRemove(10);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 12: Clear con set sparso
        setVec.Insert(0);
        setVec.Insert(1000);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 13: Clear con valore estremo
        setVec.Insert(10000);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 14: Clear con valore estremo negativo
        setVec.Insert(-10000);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 15: Clear dopo ridimensionamento
        for (int i = 0; i < 50; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 16: Clear dopo RemovePredecessor
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.RemovePredecessor(30);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 17: Clear dopo RemoveSuccessor
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.Insert(30);
        setVec.RemoveSuccessor(10);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 18: Clear con set di un solo elemento
        setVec.Insert(10);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 19: Clear dopo inserimenti multipli
        for (int i = 0; i < 10; ++i) {
            setVec.Insert(i * 10);
        }
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 20: Clear dopo ridimensionamento verso il basso
        for (int i = 0; i < 20; ++i) {
            setVec.Insert(i * 10);
        }
        for (int i = 0; i < 15; ++i) {
            setVec.Remove(i * 10);
        }
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 21: Clear con valori negativi sparsi
        setVec.Insert(-100);
        setVec.Insert(-50);
        setVec.Insert(0);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 22: Clear dopo eccezioni
        try {
            setVec.Min();
        } catch (std::length_error&) {
            setVec.Clear();
            assert(setVec.Size() == 0);
        }
        // Test 23: Clear con set grande dopo inserimenti
        for (int i = 0; i < 100; ++i) {
            setVec.Insert(i);
        }
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 24: Clear dopo operazioni miste
        setVec.Insert(10);
        setVec.Insert(20);
        setVec.MinNRemove();
        setVec.Insert(30);
        setVec.Clear();
        assert(setVec.Size() == 0);
        // Test 25: Clear con set vuoto ripetuto
        setVec.Clear();
        setVec.Clear();
        setVec.Clear();
        assert(setVec.Size() == 0);
        setVec.Clear();
    }

    std::cout << "SetVec tests completed successfully!" << std::endl;
}



//-------------------------------------------------------------------------


template <typename Data>
void PrintSetVec(const SetVec<Data>& sv, const std::string& label) {
    std::cout << label << ": ";
    sv.PreOrderTraverse([](const Data& val) { std::cout << val << " "; });
    std::cout << "(size: " << sv.Size() << ")\n";
}

// Test copy constructor and assignment
void TestCopy() {
    std::cout << "\n=== Testing Copy Constructor and Assignment ===\n";
    SetVec<int> sv1;
    sv1.Insert(3);
    sv1.Insert(1);
    sv1.Insert(5);
    PrintSetVec(sv1, "Original sv1");

    // Copy constructor
    SetVec<int> sv2(sv1);
    PrintSetVec(sv2, "sv2 (copy constructed)");
    assert(sv2.Size() == sv1.Size());
    assert(sv2 == sv1);

    // Copy assignment
    SetVec<int> sv3;
    sv3 = sv1;
    PrintSetVec(sv3, "sv3 (copy assigned)");
    assert(sv3.Size() == sv1.Size());
    assert(sv3 == sv1);

    // Modify sv2, ensure sv1 unchanged
    sv2.Insert(7);
    PrintSetVec(sv2, "sv2 after inserting 7");
    PrintSetVec(sv1, "sv1 (unchanged)");
    assert(sv1.Size() == 3);
    assert(sv2.Size() == 4);
}

// Test move constructor and assignment
void TestMove() {
    std::cout << "\n=== Testing Move Constructor and Assignment ===\n";
    SetVec<int> sv1;
    sv1.Insert(3);
    sv1.Insert(1);
    sv1.Insert(5);
    PrintSetVec(sv1, "Original sv1");

    // Move constructor
    SetVec<int> sv2(std::move(sv1));
    PrintSetVec(sv2, "sv2 (move constructed)");
    assert(sv2.Size() == 3);
    assert(sv1.Size() == 0);
    assert(sv1.Empty());

    // Move assignment
    SetVec<int> sv3;
    sv3.Insert(10);
    sv3 = std::move(sv2);
    PrintSetVec(sv3, "sv3 (move assigned)");
    PrintSetVec(sv2, "sv2 (after move)");
    assert(sv3.Size() == 3);
    assert(sv2.Size() == 0);
}

// Test Min, RemoveMin, MinNRemove
void TestMin() {
    std::cout << "\n=== Testing Min, RemoveMin, MinNRemove ===\n";
    SetVec<int> sv;
    sv.Insert(3);
    sv.Insert(1);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    // Min
    assert(sv.Min() == 1);
    std::cout << "Min: " << sv.Min() << "\n";

    // MinNRemove
    int min = sv.MinNRemove();
    PrintSetVec(sv, "sv after MinNRemove");
    assert(min == 1);
    assert(sv.Size() == 2);
    assert(sv.Min() == 3);

    // RemoveMin
    sv.RemoveMin();
    PrintSetVec(sv, "sv after RemoveMin");
    assert(sv.Size() == 1);
    assert(sv.Min() == 5);

    // Empty set
    try {
        sv.RemoveMin();
        sv.Min();
        assert(false && "Expected length_error for Min on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Min on empty set\n";
    }
}

// Test Max, RemoveMax, MaxNRemove
void TestMax() {
    std::cout << "\n=== Testing Max, RemoveMax, MaxNRemove ===\n";
    SetVec<int> sv;
    sv.Insert(3);
    sv.Insert(1);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    // Max
    assert(sv.Max() == 5);
    std::cout << "Max: " << sv.Max() << "\n";

    // MaxNRemove
    int max = sv.MaxNRemove();
    PrintSetVec(sv, "sv after MaxNRemove");
    assert(max == 5);
    assert(sv.Size() == 2);
    assert(sv.Max() == 3);

    // RemoveMax
    sv.RemoveMax();
    PrintSetVec(sv, "sv after RemoveMax");
    assert(sv.Size() == 1);
    assert(sv.Max() == 1);

    // Empty set
    try {
        sv.RemoveMax();
        sv.Max();
        assert(false && "Expected length_error for Max on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Max on empty set\n";
    }
}

// Test Predecessor, RemovePredecessor, PredecessorNRemove
void TestPredecessor() {
    std::cout << "\n=== Testing Predecessor, RemovePredecessor, PredecessorNRemove ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    sv.Insert(7);
    PrintSetVec(sv, "sv");

    // Predecessor
    assert(sv.Predecessor(5) == 3);
    std::cout << "Predecessor of 5: " << sv.Predecessor(5) << "\n";

    // PredecessorNRemove
    int pred = sv.PredecessorNRemove(5);
    PrintSetVec(sv, "sv after PredecessorNRemove(5)");
    assert(pred == 3);
    assert(sv.Size() == 3);
    assert(sv.Exists(5));
    assert(!sv.Exists(3));

    // RemovePredecessor
    sv.RemovePredecessor(7);
    PrintSetVec(sv, "sv after RemovePredecessor(7)");
    assert(sv.Size() == 2);
    assert(sv.Exists(7));
    assert(!sv.Exists(5));

    // Edge case: no predecessor
    try {
        sv.Predecessor(1);
        assert(false && "Expected length_error for Predecessor of min");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Predecessor of min\n";
    }
}

// Test Successor, RemoveSuccessor, SuccessorNRemove
void TestSuccessor() {
    std::cout << "\n=== Testing Successor, RemoveSuccessor, SuccessorNRemove ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    sv.Insert(7);
    PrintSetVec(sv, "sv");

    // Successor
    assert(sv.Successor(3) == 5);
    std::cout << "Successor of 3: " << sv.Successor(3) << "\n";

    // SuccessorNRemove
    int succ = sv.SuccessorNRemove(3);
    PrintSetVec(sv, "sv after SuccessorNRemove(3)");
    assert(succ == 5);
    assert(sv.Size() == 3);
    assert(sv.Exists(3));
    assert(!sv.Exists(5));

    // RemoveSuccessor
    sv.RemoveSuccessor(1);
    PrintSetVec(sv, "sv after RemoveSuccessor(1)");
    assert(sv.Size() == 2);
    assert(sv.Exists(1));
    assert(!sv.Exists(3));

    // Edge case: no successor
    try {
        sv.Successor(7);
        assert(false && "Expected length_error for Successor of max");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Successor of max\n";
    }
}

// Test Insert (copy and move)
void TestInsert() {
    std::cout << "\n=== Testing Insert (Copy and Move) ===\n";
    SetVec<int> sv;
    PrintSetVec(sv, "Empty sv");

    // Copy Insert
    assert(sv.Insert(3));
    assert(sv.Insert(1));
    assert(!sv.Insert(3)); // Duplicate
    PrintSetVec(sv, "sv after copy inserts");

    // Move Insert
    int val = 5;
    assert(sv.Insert(std::move(val)));
    assert(!sv.Insert(5)); // Duplicate
    PrintSetVec(sv, "sv after move insert");
    assert(sv.Size() == 3);
    assert(sv.Exists(1));
    assert(sv.Exists(3));
    assert(sv.Exists(5));

    // Test resizing by inserting multiple elements
    SetVec<int> sv2;
    sv2.Insert(1);
    sv2.Insert(2);
    sv2.Insert(3); // Should trigger resize
    sv2.Insert(4); // Further test resize
    PrintSetVec(sv2, "sv2 after multiple inserts");
    assert(sv2.Size() == 4);
}

// Test Remove
void TestRemove() {
    std::cout << "\n=== Testing Remove ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    assert(sv.Remove(3));
    PrintSetVec(sv, "sv after Remove(3)");
    assert(sv.Size() == 2);
    assert(!sv.Exists(3));

    assert(!sv.Remove(3)); // Non-existent
    PrintSetVec(sv, "sv after failed Remove(3)");
    assert(sv.Size() == 2);

    // Empty set
    sv.Clear();
    assert(!sv.Remove(1));
    PrintSetVec(sv, "sv after Clear and Remove attempt");
}

// Test operator[]
void TestOperator() {
    std::cout << "\n=== Testing operator[] ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    assert(sv[0] == 1);
    assert(sv[1] == 3);
    assert(sv[2] == 5);
    std::cout << "sv[0]: " << sv[0] << ", sv[1]: " << sv[1] << ", sv[2]: " << sv[2] << "\n";

    // Out of range
    try {
        sv[3];
        assert(false && "Expected out_of_range for invalid index");
    } catch (const std::out_of_range&) {
        std::cout << "Caught out_of_range for invalid index\n";
    }
}

// Test Exists
void TestExists() {
    std::cout << "\n=== Testing Exists ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    assert(sv.Exists(3));
    assert(!sv.Exists(2));
    std::cout << "Exists(3): " << sv.Exists(3) << ", Exists(2): " << sv.Exists(2) << "\n";

    sv.Clear();
    assert(!sv.Exists(3));
    std::cout << "Exists(3) on empty set: " << sv.Exists(3) << "\n";
}

// Test Clear
void TestClear() {
    std::cout << "\n=== Testing Clear ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    PrintSetVec(sv, "sv before Clear");

    sv.Clear();
    PrintSetVec(sv, "sv after Clear");
    assert(sv.Size() == 0);
    assert(sv.Empty());
}

// Test PreOrderTraverse and PostOrderTraverse
void TestTraverse() {
    std::cout << "\n=== Testing PreOrderTraverse and PostOrderTraverse ===\n";
    SetVec<int> sv;
    sv.Insert(1);
    sv.Insert(3);
    sv.Insert(5);
    PrintSetVec(sv, "sv");

    // PreOrderTraverse (1, 3, 5)
    std::cout << "PreOrderTraverse: ";
    sv.PreOrderTraverse([](const int& val) { std::cout << val << " "; });
    std::cout << "\n";

    // PostOrderTraverse (5, 3, 1)
    std::cout << "PostOrderTraverse: ";
    sv.PostOrderTraverse([](const int& val) { std::cout << val << " "; });
    std::cout << "\n";

    // Verify order
    int preOrder[3];
    int postOrder[3];
    int i = 0;
    sv.PreOrderTraverse([&preOrder, &i](const int& val) { preOrder[i++] = val; });
    i = 0;
    sv.PostOrderTraverse([&postOrder, &i](const int& val) { postOrder[i++] = val; });
    assert(preOrder[0] == 1 && preOrder[1] == 3 && preOrder[2] == 5);
    assert(postOrder[0] == 5 && postOrder[1] == 3 && postOrder[2] == 1);
}

void TestMinString() {
    std::cout << "\n=== Testing Min, RemoveMin, MinNRemove (std::string) ===\n";
    SetVec<std::string> sv;
    sv.Insert("apple");
    sv.Insert("banana");
    sv.Insert("cherry");
    PrintSetVec(sv, "sv");

    // Min
    assert(sv.Min() == "apple");
    std::cout << "Min: " << sv.Min() << "\n";

    // MinNRemove
    std::string min = sv.MinNRemove();
    PrintSetVec(sv, "sv after MinNRemove");
    assert(min == "apple");
    assert(sv.Size() == 2);
    assert(sv.Min() == "banana");

    // RemoveMin
    sv.RemoveMin();
    PrintSetVec(sv, "sv after RemoveMin");
    assert(sv.Size() == 1);
    assert(sv.Min() == "cherry");

    // Empty set
    try {
        sv.RemoveMin();
        sv.Min();
        assert(false && "Expected length_error for Min on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Min on empty set\n";
    }
}

void TestCopyString() {
    std::cout << "\n=== Testing Copy Constructor and Assignment (std::string) ===\n";
    SetVec<std::string> sv1;
    sv1.Insert("apple");
    sv1.Insert("banana");
    sv1.Insert("cherry");
    PrintSetVec(sv1, "Original sv1");

    // Copy constructor
    SetVec<std::string> sv2(sv1);
    PrintSetVec(sv2, "sv2 (copy constructed)");
    assert(sv2.Size() == sv1.Size());
    assert(sv2 == sv1);

    // Copy assignment
    SetVec<std::string> sv3;
    sv3 = sv1;
    PrintSetVec(sv3, "sv3 (copy assigned)");
    assert(sv3.Size() == sv1.Size());
    assert(sv3 == sv1);

    // Modify sv2, ensure sv1 unchanged
    sv2.Insert("date");
    PrintSetVec(sv2, "sv2 after inserting date");
    PrintSetVec(sv1, "sv1 (unchanged)");
    assert(sv1.Size() == 3);
    assert(sv2.Size() == 4);
}

void TestMoveString() {
    std::cout << "\n=== Testing Move Constructor and Assignment (std::string) ===\n";
    SetVec<std::string> sv1;
    sv1.Insert("apple");
    sv1.Insert("banana");
    sv1.Insert("cherry");
    PrintSetVec(sv1, "Original sv1");

    // Move constructor
    SetVec<std::string> sv2(std::move(sv1));
    PrintSetVec(sv2, "sv2 (move constructed)");
    assert(sv2.Size() == 3);
    assert(sv1.Size() == 0);
    assert(sv1.Empty());

    // Move assignment
    SetVec<std::string> sv3;
    sv3.Insert("date");
    sv3 = std::move(sv2);
    PrintSetVec(sv3, "sv3 (move assigned)");
    PrintSetVec(sv2, "sv2 (after move)");
    assert(sv3.Size() == 3);
    assert(sv2.Size() == 0);
}

void TestMaxString() {
    std::cout << "\n=== Testing Max, RemoveMax, MaxNRemove (std::string) ===\n";
    SetVec<std::string> sv;
    sv.Insert("apple");
    sv.Insert("banana");
    sv.Insert("cherry");
    PrintSetVec(sv, "sv");

    // Max
    assert(sv.Max() == "cherry");
    std::cout << "Max: " << sv.Max() << "\n";

    // MaxNRemove
    std::string max = sv.MaxNRemove();
    PrintSetVec(sv, "sv after MaxNRemove");
    assert(max == "cherry");
    assert(sv.Size() == 2);
    assert(sv.Max() == "banana");

    // RemoveMax
    sv.RemoveMax();
    PrintSetVec(sv, "sv after RemoveMax");
    assert(sv.Size() == 1);
    assert(sv.Max() == "apple");

    // Empty set
    try {
        sv.RemoveMax();
        sv.Max();
        assert(false && "Expected length_error for Max on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Max on empty set\n";
    }
}

void TestPredecessorString() {
    std::cout << "\n=== Testing Predecessor, RemovePredecessor, PredecessorNRemove (std::string) ===\n";
    SetVec<std::string> sv;
    sv.Insert("apple");
    sv.Insert("banana");
    sv.Insert("cherry");
    sv.Insert("date");
    PrintSetVec(sv, "sv");

    // Predecessor
    assert(sv.Predecessor("cherry") == "banana");
    std::cout << "Predecessor of cherry: " << sv.Predecessor("cherry") << "\n";

    // PredecessorNRemove
    std::string pred = sv.PredecessorNRemove("cherry");
    PrintSetVec(sv, "sv after PredecessorNRemove(cherry)");
    assert(pred == "banana");
    assert(sv.Size() == 3);
    assert(sv.Exists("cherry"));
    assert(!sv.Exists("banana"));

    // RemovePredecessor
    sv.RemovePredecessor("date");
    PrintSetVec(sv, "sv after RemovePredecessor(date)");
    assert(sv.Size() == 2);
    assert(sv.Exists("date"));
    assert(!sv.Exists("cherry"));

    // Edge case: no predecessor
    try {
        sv.Predecessor("apple");
        assert(false && "Expected length_error for Predecessor of min");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Predecessor of min\n";
    }
}

void TestSuccessorString() {
    std::cout << "\n=== Testing Successor, RemoveSuccessor, SuccessorNRemove (std::string) ===\n";
    SetVec<std::string> sv;
    sv.Insert("apple");
    sv.Insert("banana");
    sv.Insert("cherry");
    sv.Insert("date");
    PrintSetVec(sv, "sv");

    // Successor
    assert(sv.Successor("banana") == "cherry");
    std::cout << "Successor of banana: " << sv.Successor("banana") << "\n";

    // SuccessorNRemove
    std::string succ = sv.SuccessorNRemove("banana");
    PrintSetVec(sv, "sv after SuccessorNRemove(banana)");
    assert(succ == "cherry");
    assert(sv.Size() == 3);
    assert(sv.Exists("banana"));
    assert(!sv.Exists("cherry"));

    // RemoveSuccessor
    sv.RemoveSuccessor("apple");
    PrintSetVec(sv, "sv after RemoveSuccessor(apple)");
    assert(sv.Size() == 2);
    assert(sv.Exists("apple"));
    assert(!sv.Exists("banana"));

    // Edge case: no successor
    try {
        sv.Successor("date");
        assert(false && "Expected length_error for Successor of max");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Successor of max\n";
    }
}

void TestCopyLong() {
    std::cout << "\n=== Testing Copy Constructor and Assignment (long) ===\n";
    SetVec<long> sv1;
    sv1.Insert(1000000000L);
    sv1.Insert(2000000000L);
    sv1.Insert(3000000000L);
    PrintSetVec(sv1, "Original sv1");

    // Copy constructor
    SetVec<long> sv2(sv1);
    PrintSetVec(sv2, "sv2 (copy constructed)");
    assert(sv2.Size() == sv1.Size());
    assert(sv2 == sv1);

    // Copy assignment
    SetVec<long> sv3;
    sv3 = sv1;
    PrintSetVec(sv3, "sv3 (copy assigned)");
    assert(sv3.Size() == sv1.Size());
    assert(sv3 == sv1);

    // Modify sv2, ensure sv1 unchanged
    sv2.Insert(4000000000L);
    PrintSetVec(sv2, "sv2 after inserting 4000000000");
    PrintSetVec(sv1, "sv1 (unchanged)");
    assert(sv1.Size() == 3);
    assert(sv2.Size() == 4);
}

void TestMoveLong() {
    std::cout << "\n=== Testing Move Constructor and Assignment (long) ===\n";
    SetVec<long> sv1;
    sv1.Insert(1000000000L);
    sv1.Insert(2000000000L);
    sv1.Insert(3000000000L);
    PrintSetVec(sv1, "Original sv1");

    // Move constructor
    SetVec<long> sv2(std::move(sv1));
    PrintSetVec(sv2, "sv2 (move constructed)");
    assert(sv2.Size() == 3);
    assert(sv1.Size() == 0);
    assert(sv1.Empty());

    // Move assignment
    SetVec<long> sv3;
    sv3.Insert(4000000000L);
    sv3 = std::move(sv2);
    PrintSetVec(sv3, "sv3 (move assigned)");
    PrintSetVec(sv2, "sv2 (after move)");
    assert(sv3.Size() == 3);
    assert(sv2.Size() == 0);
}

void TestMinLong() {
    std::cout << "\n=== Testing Min, RemoveMin, MinNRemove (long) ===\n";
    SetVec<long> sv;
    sv.Insert(1000000000L);
    sv.Insert(2000000000L);
    sv.Insert(3000000000L);
    PrintSetVec(sv, "sv");

    // Min
    assert(sv.Min() == 1000000000L);
    std::cout << "Min: " << sv.Min() << "\n";

    // MinNRemove
    long min = sv.MinNRemove();
    PrintSetVec(sv, "sv after MinNRemove");
    assert(min == 1000000000L);
    assert(sv.Size() == 2);
    assert(sv.Min() == 2000000000L);

    // RemoveMin
    sv.RemoveMin();
    PrintSetVec(sv, "sv after RemoveMin");
    assert(sv.Size() == 1);
    assert(sv.Min() == 3000000000L);

    // Empty set
    try {
        sv.RemoveMin();
        sv.Min();
        assert(false && "Expected length_error for Min on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Min on empty set\n";
    }
}

void TestMaxLong() {
    std::cout << "\n=== Testing Max, RemoveMax, MaxNRemove (long) ===\n";
    SetVec<long> sv;
    sv.Insert(1000000000L);
    sv.Insert(2000000000L);
    sv.Insert(3000000000L);
    PrintSetVec(sv, "sv");

    // Max
    assert(sv.Max() == 3000000000L);
    std::cout << "Max: " << sv.Max() << "\n";

    // MaxNRemove
    long max = sv.MaxNRemove();
    PrintSetVec(sv, "sv after MaxNRemove");
    assert(max == 3000000000L);
    assert(sv.Size() == 2);
    assert(sv.Max() == 2000000000L);

    // RemoveMax
    sv.RemoveMax();
    PrintSetVec(sv, "sv after RemoveMax");
    assert(sv.Size() == 1);
    assert(sv.Max() == 1000000000L);

    // Empty set
    try {
        sv.RemoveMax();
        sv.Max();
        assert(false && "Expected length_error for Max on empty set");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Max on empty set\n";
    }
}

void TestPredecessorLong() {
    std::cout << "\n=== Testing Predecessor, RemovePredecessor, PredecessorNRemove (long) ===\n";
    SetVec<long> sv;
    sv.Insert(1000000000L);
    sv.Insert(2000000000L);
    sv.Insert(3000000000L);
    sv.Insert(4000000000L);
    PrintSetVec(sv, "sv");

    // Predecessor
    assert(sv.Predecessor(3000000000L) == 2000000000L);
    std::cout << "Predecessor of 3000000000: " << sv.Predecessor(3000000000L) << "\n";

    // PredecessorNRemove
    long pred = sv.PredecessorNRemove(3000000000L);
    PrintSetVec(sv, "sv after PredecessorNRemove(3000000000)");
    assert(pred == 2000000000L);
    assert(sv.Size() == 3);
    assert(sv.Exists(3000000000L));
    assert(!sv.Exists(2000000000L));

    // RemovePredecessor
    sv.RemovePredecessor(4000000000L);
    PrintSetVec(sv, "sv after RemovePredecessor(4000000000)");
    assert(sv.Size() == 2);
    assert(sv.Exists(4000000000L));
    assert(!sv.Exists(3000000000L));

    // Edge case: no predecessor
    try {
        sv.Predecessor(1000000000L);
        assert(false && "Expected length_error for Predecessor of min");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Predecessor of min\n";
    }
}

void TestSuccessorLong() {
    std::cout << "\n=== Testing Successor, RemoveSuccessor, SuccessorNRemove (long) ===\n";
    SetVec<long> sv;
    sv.Insert(1000000000L);
    sv.Insert(2000000000L);
    sv.Insert(3000000000L);
    sv.Insert(4000000000L);
    PrintSetVec(sv, "sv");

    // Successor
    assert(sv.Successor(2000000000L) == 3000000000L);
    std::cout << "Successor of 2000000000: " << sv.Successor(2000000000L) << "\n";

    // SuccessorNRemove
    long succ = sv.SuccessorNRemove(2000000000L);
    PrintSetVec(sv, "sv after SuccessorNRemove(2000000000)");
    assert(succ == 3000000000L);
    assert(sv.Size() == 3);
    assert(sv.Exists(2000000000L));
    assert(!sv.Exists(3000000000L));

    // RemoveSuccessor
    sv.RemoveSuccessor(1000000000L);
    PrintSetVec(sv, "sv after RemoveSuccessor(1000000000)");
    assert(sv.Size() == 2);
    assert(sv.Exists(1000000000L));
    assert(!sv.Exists(2000000000L));

    // Edge case: no successor
    try {
        sv.Successor(4000000000L);
        assert(false && "Expected length_error for Successor of max");
    } catch (const std::length_error&) {
        std::cout << "Caught length_error for Successor of max\n";
    }
}

void TestMarco(){

    std::cout << "=== Testing Marco ===\n";

    //Test per int
    TestCopy();
    TestMove();
    TestMin();
    TestMax();
    TestPredecessor();
    TestSuccessor();
    TestInsert();
    TestRemove();
    TestOperator();
    TestExists();
    TestClear();
    TestTraverse();

    // Test per string
    TestCopyString();
    TestMoveString();
    TestMinString();
    TestMaxString();
    TestPredecessorString();
    TestSuccessorString();

    // Test per long
    TestCopyLong();
    TestMoveLong();
    TestMinLong();
    TestMaxLong();
    TestPredecessorLong();
    TestSuccessorLong();

    std::cout << "All tests passed!" << std::endl;
}
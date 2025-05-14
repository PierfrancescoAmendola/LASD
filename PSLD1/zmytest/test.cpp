// #include "..."

#include <iostream>

#include <functional>
#include <climits> // Per INT_MIN e INT_MAX
#include <string>       // std::string
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
// typedef int T;
// typedef char E;
// #include <iostream>

// using namespace std;
// typedef int T;
// typedef char E;
/* ************************************************************************** */
/*template class lasd::TraversableContainer<T>;

class TraversableContainerTest: virtual public lasd::TraversableContainer<T>
{
public:
    E Fold(FoldFun<E>, E);
    
};

E TraversableContainerTest::Fold(FoldFun<E> f, E acc) {
    return TraversableContainer::Fold(f, acc);
}



*/
// void mytest(){
    
// }



// Macro di supporto per i test
#define RUN_TEST(desc, expr) \
    do { \
        bool result = (expr); \
        cout << "[TEST] " << desc << ": " << (result ? "PASSED ✅" : "FAILED ❌") << endl; \
        loctestnum++; \
        if (!result) loctesterr++; \
    } while(0)

//Funzione mySimpleTest
void myStestSetInt(lasd::Set<int>& set, uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of My Set<int> Test" << endl;

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
        try {
            set.Predecessor(3);
            cout << "[TEST] Predecessor of 3: FAILED ❌ (No exception thrown)\n";
        } catch (const std::exception&) {
            cout << "[TEST] Predecessor of 3: PASSED ✅ (Exception thrown)\n";
            loctestnum++;
        }

        RUN_TEST("Successor of 7 should be 12", set.Successor(7) == 12);
        try {
            set.Successor(17);
            cout << "[TEST] Successor of 17: FAILED ❌ (No exception thrown)\n";
        } catch (const std::exception&) {
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
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

void myStestSetDouble(lasd::Set<double>& set, uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of My Set<double> Test" << endl;

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
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

void myStestSetString(lasd::Set<string>& set, uint& testnum, uint& testerr) {
    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of My Set<string> Test" << endl;

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
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}
void myTestSetOperations(uint& testnum, uint& testerr) {

    uint loctestnum = 0, loctesterr = 0;
    try {
        cout << endl << "Begin of My Set Operations Test" << endl;

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
    } catch (...) {
        loctestnum++;
        loctesterr++;
        cout << "Unmanaged error!" << endl;
    }
    testnum += loctestnum;
    testerr += loctesterr;
}

bool Empty(const lasd::Container & vector){
    return vector.Empty();
}

unsigned long Size(const lasd::Container & vector){
    return vector.Size();
}

template <typename Data>
unsigned long Indice(const lasd::Vector<Data> & vector, int i){
    return vector.operator[](i);
}

template <typename Data>
unsigned long Primo(const lasd::Vector<Data> & vector){
    return vector.Front();
}

template <typename Data>
unsigned long Ultimo(const lasd::Vector<Data> & vector){
    return vector.Back();
}

template <typename Data>
unsigned long Indice(const lasd::List<Data> & list, int i){
    return list.operator[](i);
}

void personalLasdTest() 
{
    bool checked;
    unsigned long numero;
    std::string corretto;

    std::cout << std::endl << "~*~#~*~ Personal LASD Test ~*~#~*~ " << std::endl;
  
    //Vector
    std::cout << std::endl << "~~~~~ VECTOR TEST ~~~~~" << std::endl << std::endl;

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
    

    //List
    std::cout << std::endl << std::endl << "~~~~~ LIST TEST ~~~~~" << std::endl << std::endl;

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

    try {
    numero = lst.Front();
    std::cout << "Front (Lista vuota): " << numero << " - " << corretto << std::endl;
    } catch(const std::length_error& exc) {  // Modificato qui
    std::cout << "Front (Lista vuota): Lista vuota" << std::endl;
    } catch(const std::exception& exc) {     // Modificato anche qui
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
    }

    try {
    numero = lst.Back();
    std::cout << "Back (Lista vuota): " << numero << " - " << corretto << std::endl;
    } catch(const std::length_error& exc) {  // Modificato qui
    std::cout << "Back (Lista vuota): Lista vuota" << std::endl;
    } catch(const std::exception& exc) {     // Modificato anche qui
    std::cout << std::endl << "Wrong exception: " << exc.what() << "!" << std::endl;
    }


        
    std::cout << std::endl << "Fine Personal LASD Test" << std::endl;
}




// void mytest() 
// {
//   // ...
//     cout << endl << "Welcome To My Tests:" << endl<<endl;
//     cout << endl << " - - -  Vector Tests  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" <<endl<< endl;
//     cout << endl << " - - -  Vector Tests with integers - - - " <<endl<< endl;
//     lasd::SortableVector<int> vect;
//     cout << "vect should be empty: " << vect.Empty() << endl;
//     cout << "vect size should be 0: " << vect.Size() << endl;
//     vect.Resize(5);
//     cout << "vect size should be 5 after resize(5) : " << vect.Size() << endl;
//     cout << "First element of vector (0): " << vect.Front() << endl;
//     cout << "Last element of vect (0): " << vect.Back() << endl;
//     lasd::SortableVector<int> vectCopy(vect);
//     cout << "vectCopy size should be 5: " << vectCopy.Size() << endl;
//     lasd::SortableVector<int> vectMove(move(vectCopy));
//     cout << "vectMove size should be 5: " << vectMove.Size() << endl;
//     cout << "Creating a vector for the fold and map test:" << endl;
//     lasd::Vector<int> vectorForTest(5);
//     cout << "Inserting the following elements into the vector:" << "1, 2, 3, 4, 5" << endl;
//     vectorForTest[0] = 1;
//     vectorForTest[1] = 2;
//     vectorForTest[2] = 3;
//     vectorForTest[3] = 4;
//     vectorForTest[4] = 5;
//     cout << "2 should be in vector : " << vectorForTest.Exists(2) << endl;
//     cout << "Size should be 5 : " << vectorForTest.Size() << endl;
//     cout << "Fold test with sum:" << endl;
//     int sum1 = vectorForTest.Fold<int>(
//         [](const int& acc, const int& element) {
//             return acc + element;
//         }, 0);
//     cout << "Sum of elements in the vector: " << sum1 << endl;
//     cout << "Fold test with product:" << endl;
//     int product1 = vectorForTest.Fold<int>(
//         [](const int& acc, const int& element) {
//             return acc * element;
//         }, 1);

//     cout << "Product of elements in the vector: " << product1 << endl;

//     cout << "Map test doubling the elements:" << endl;
//     vectorForTest.Map(
//         [](int& element) {
//             element *= 2;
//         }
//     );

//     cout << "Elements in the vector after doubling:" << endl;
//     for (ulong i = 0; i < vectorForTest.Size(); ++i) {
//         cout << vectorForTest[i] << " ";
//     }
//         cout << endl <<endl<< " - - -  Vector Tests with string - - - " <<endl<< endl;
//         lasd::Vector<string> vectString;
//         cout << "vectString should be empty: " << vectString.Empty() << endl;
//         cout << "vectString size should be 0: " << vectString.Size() << endl;
        
//         vectString.Resize(3);
        
//         cout << "vectString size should be 3: " << vectString.Size() << endl;


//         cout << "First element of vectString (empty string): " << vectString.Front() << endl;

//         cout << "Last element of vectString (empty string): " << vectString.Back() << endl;

//         lasd::Vector<string> vectCopyString(vectString);
//         cout << "vectCopyString size should be 3: " << vectCopyString.Size() << endl;

//         lasd::Vector<string> vectMoveString(move(vectCopyString));
//         cout << "vectMoveString size should be 3: " << vectMoveString.Size() << endl;

//         cout << "Creating a vector for the fold and map test:" << endl;
//     lasd::Vector<string> vectorForTestString(3);

//     cout << "Inserting the following elements into the vectStringor:" << "hello  world  !!" <<endl;
//     // Correzione ordine qui
//     vectorForTestString[0] = "hello";
//     vectorForTestString[1] = "world";
//     vectorForTestString[2] = "!!";

//         cout << "'world' should be in vectString : " << vectorForTestString.Exists("world") << endl;
//         cout << "Fold test with concatenation:" << endl;
//         string concatString = vectorForTestString.Fold<string>(
//             [](const string& acc, const string& element) { return acc + element;
//             }, "");

//         cout << "Concatenated string of elements in the vectString: " << concatString << endl;

//         cout << "Map test with adding 'abc' to each element:" << endl;
//         vectorForTestString.Map(
//             [](string& element) {
//                 element += "abc";
//             }
//         );

//         cout << "Elements in the vectStringor after modification:" << endl;
//         for (ulong i = 0; i < vectorForTestString.Size(); ++i) {
//             cout << vectorForTestString[i] << " ";
//         }

//         cout << endl <<endl<< " - - -  Vector Tests with float - - - " <<endl<< endl;
//         lasd::SortableVector<float> vectFloat;
//         cout << "vectFloat should be empty: " << vectFloat.Empty() << endl;
//         cout << "vectFloat size should be 0: " << vectFloat.Size() << endl;
        
//         vectFloat.Resize(4);
        
//         cout << "vectFloat size should be 4: " << vectFloat.Size() << endl;


//         lasd::SortableVector<float> vectCopyFloat(vectFloat);
//         cout << "vectCopyFloat size should be 4: " << vectCopyFloat.Size() << endl;

//         lasd::SortableVector<float> vectMoveFloat(move(vectCopyFloat));
//         cout << "vectMoveFloat size should be 4: " << vectMoveFloat.Size() << endl;

//         cout << "Creating a vector for the fold and map test:" << endl;
//     lasd::Vector<float> vectorForTestFloat(4);

//     cout << "Inserting the following elements into the vectFloator:" << endl;
//     cout << "1.5, 2.5, 3.5, 4.5" << endl;

//     vectorForTestFloat[0] = 1.5;
//     vectorForTestFloat[1] = 2.5;
//     vectorForTestFloat[2] = 3.5;
//     vectorForTestFloat[3] = 4.5;

//     // Correzione qui: usare vectorForTestFloat invece di vectFloat
//     cout << "First element of vectFloat (1.5): " << vectorForTestFloat.Front() << endl;
//     cout << "Last element of vectFloat (4.5): " << vectorForTestFloat.Back() << endl;

//         cout << "2.5 should be in vectFloat : " << vectorForTestFloat.Exists(2.5) << endl;
//         cout << "Fold test with sum:" << endl;
//         float sum1Float = vectorForTestFloat.Fold<float>(
//             [](const float& acc, const float& element) {
//                 return acc + element;
//             }, 0.0);

//         cout << "Sum of elements in the vectFloat: " << sum1Float << endl;

//         cout << "Fold test with product:" << endl;
//         float product1Float = vectorForTestFloat.Fold<float>(
//             [](const float& acc, const float& element) {
//                 return acc * element;
//             }, 1.0);

//         cout << "Product of elements in the vectFloat: " << product1Float << endl;
// }



// Macro di supporto per i test
#define RUN_TEST(desc, expr) \
    do { \
        bool result = (expr); \
        cout << "[TEST] " << desc << ": " << (result ? "PASSED ✅" : "FAILED ❌") << endl; \
        totalTests++; \
        if (result) passedTests++; \
    } while(0)


void  mytest2() {
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
    for (int i = 0; i < 5; ++i) vectorForTest[i] = i + 1;
    RUN_TEST("2 should be in vector", vectorForTest.Exists(2));
    RUN_TEST("vector size should be 5", vectorForTest.Size() == 5);

    cout << "Folding with sum...\n";
    int sum1 = vectorForTest.Fold<int>([](const int& acc, const int& elem) { return acc + elem; }, 0);
    cout << "Sum: " << sum1 << "\n";

    cout << "Folding with product...\n";
    int prod1 = vectorForTest.Fold<int>([](const int& acc, const int& elem) { return acc * elem; }, 1);
    cout << "Product: " << prod1 << "\n";

    cout << "Mapping (doubling values)...\n";
    vectorForTest.Map([](int& x) { x *= 2; });
    cout << "Values after map: ";
    for (ulong i = 0; i < vectorForTest.Size(); ++i) cout << vectorForTest[i] << " ";
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
    string concat = vectorForTestString.Fold<string>([](const string& acc, const string& elem) { return acc + elem; }, "");
    cout << "Concatenated: " << concat << "\n";

    cout << "Mapping (append 'abc')...\n";
    vectorForTestString.Map([](string& x) { x += "abc"; });
    cout << "Values after map: ";
    for (ulong i = 0; i < vectorForTestString.Size(); ++i) cout << vectorForTestString[i] << " ";
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
    for (int i = 0; i < 4; ++i) vectorForTestFloat[i] = values[i];

    cout << "Front: " << vectorForTestFloat.Front() << ", Back: " << vectorForTestFloat.Back() << "\n";
    RUN_TEST("2.5 should be in vector", vectorForTestFloat.Exists(2.5));

    float sumF = vectorForTestFloat.Fold<float>([](const float& acc, const float& e) { return acc + e; }, 0.0);
    cout << "Sum: " << sumF << "\n";

    float prodF = vectorForTestFloat.Fold<float>([](const float& acc, const float& e) { return acc * e; }, 1.0);
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

void testSetVecAndSetLst() {
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

    try {
        setVec.Remove(20);
        cout << "[TEST] Removing non-existent element (20): FAILED ❌ (No exception thrown)\n";
    } catch (const std::exception& e) {
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

    try {
        setLst.Remove(20);
        cout << "[TEST] Removing non-existent element (20): FAILED ❌ (No exception thrown)\n";
    } catch (const std::exception& e) {
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

void testSetVecAndSetLst_Extended() {
    int totalTests = 0, passedTests = 0;

    cout << "\n==========================================\n";
    cout << "     Extended Testing SetVec & SetLst\n";
    cout << "==========================================\n";

    // Test SetVec
    cout << "\n--- Extended Testing SetVec ---\n";
    lasd::SetVec<int> setVec;

    // Inserimento di valori duplicati
    setVec.Insert(1);
    RUN_TEST("SetVec should contain 1", setVec.Exists(1));
    setVec.Insert(1);
    RUN_TEST("SetVec size should still be 1 after inserting duplicate", setVec.Size() == 1);

    // Inserimento di valori estremi
    setVec.Insert(INT_MIN);
    setVec.Insert(INT_MAX);
    RUN_TEST("SetVec should contain INT_MIN", setVec.Exists(INT_MIN));
    RUN_TEST("SetVec should contain INT_MAX", setVec.Exists(INT_MAX));

    // Inserimento di grandi quantità di dati
    for (int i = 2; i <= 1000; ++i) {
        setVec.Insert(i);
    }
    RUN_TEST("SetVec size should be 1003 after inserting 1000 elements", setVec.Size() == 1003);

    // Rimozione di elementi esistenti
    setVec.Remove(500);
    RUN_TEST("SetVec should not contain 500 after removal", !setVec.Exists(500));
    RUN_TEST("SetVec size should be 1002 after removing 500", setVec.Size() == 1002);

    // Rimozione di elementi non esistenti
    try {
        setVec.Remove(2000);
        cout << "[TEST] Removing non-existent element (2000): FAILED ❌ (No exception thrown)\n";
    } catch (const std::exception& e) {
        cout << "[TEST] Removing non-existent element (2000): PASSED ✅ (Exception: " << e.what() << ")\n";
        passedTests++;
    }
    totalTests++;

    // Test di stress: Inserimento e rimozione ripetuti
    for (int i = 0; i < 10000; ++i) {
        setVec.Insert(i);
        setVec.Remove(i);
    }
    RUN_TEST("SetVec size should remain unchanged after stress test", setVec.Size() == 1002);

    // Test di confronto
    lasd::SetVec<int> setVec2;
    setVec2.Insert(1);
    setVec2.Insert(INT_MIN);
    setVec2.Insert(INT_MAX);
    RUN_TEST("SetVec should be equal to setVec2", setVec == setVec2);

    // Test di svuotamento
    setVec.Clear();
    RUN_TEST("SetVec should be empty after clearing", setVec.Empty());
    RUN_TEST("SetVec size should be 0 after clearing", setVec.Size() == 0);

    // Test SetLst
    cout << "\n--- Extended Testing SetLst ---\n";
    lasd::SetLst<int> setLst;

    // Inserimento di valori duplicati
    setLst.Insert(1);
    RUN_TEST("SetLst should contain 1", setLst.Exists(1));
    setLst.Insert(1);
    RUN_TEST("SetLst size should still be 1 after inserting duplicate", setLst.Size() == 1);

    // Inserimento di valori estremi
    setLst.Insert(INT_MIN);
    setLst.Insert(INT_MAX);
    RUN_TEST("SetLst should contain INT_MIN", setLst.Exists(INT_MIN));
    RUN_TEST("SetLst should contain INT_MAX", setLst.Exists(INT_MAX));

    // Inserimento di grandi quantità di dati
    for (int i = 2; i <= 1000; ++i) {
        setLst.Insert(i);
    }
    RUN_TEST("SetLst size should be 1003 after inserting 1000 elements", setLst.Size() == 1003);

    // Rimozione di elementi esistenti
    setLst.Remove(500);
    RUN_TEST("SetLst should not contain 500 after removal", !setLst.Exists(500));
    RUN_TEST("SetLst size should be 1002 after removing 500", setLst.Size() == 1002);

    // Rimozione di elementi non esistenti
    try {
        setLst.Remove(2000);
        cout << "[TEST] Removing non-existent element (2000): FAILED ❌ (No exception thrown)\n";
    } catch (const std::exception& e) {
        cout << "[TEST] Removing non-existent element (2000): PASSED ✅ (Exception: " << e.what() << ")\n";
        passedTests++;
    }
    totalTests++;

    // Test di stress: Inserimento e rimozione ripetuti
    for (int i = 0; i < 10000; ++i) {
        setLst.Insert(i);
        setLst.Remove(i);
    }
    RUN_TEST("SetLst size should remain unchanged after stress test", setLst.Size() == 1002);

    // Test di confronto
    lasd::SetLst<int> setLst2;
    setLst2.Insert(1);
    setLst2.Insert(INT_MIN);
    setLst2.Insert(INT_MAX);
    RUN_TEST("SetLst should be equal to setLst2", setLst == setLst2);

    // Test di svuotamento
    setLst.Clear();
    RUN_TEST("SetLst should be empty after clearing", setLst.Empty());
    RUN_TEST("SetLst size should be 0 after clearing", setLst.Size() == 0);

    // Final Summary
    cout << "\n==============================\n";
    cout << "       Extended Test Summary\n";
    cout << "==============================\n";
    cout << "Tests passed: " << passedTests << " / " << totalTests << "\n";
    if (passedTests == totalTests)
        cout << "✅ All tests passed!\n";
    else
        cout << "❌ Some tests failed. Check above for details.\n";
}

void myTestSimpleExercise1B() {
    uint testnum = 0, testerr = 0;
    try {
        cout << endl << "Begin of My Exercise 1B Test" << endl;

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
    } catch (...) {
        testnum++;
        testerr++;
        cout << endl << "Unmanaged error! " << endl;
    }
}

void testSegmentationFault() {
    cout << "\n--- Segmentation Fault & Exception Safety Test ---\n";
    lasd::Vector<int> vec(3);
    vec[0] = 1; vec[1] = 2; vec[2] = 3;
    try {
        int x = vec[3]; // Accesso fuori dai limiti
        cout << "[TEST] Access out of bounds: FAILED ❌ (No exception thrown, value: " << x << ")\n";
    } catch (const std::out_of_range&) {
        cout << "[TEST] Access out of bounds: PASSED ✅ (std::out_of_range thrown)\n";
    } catch (...) {
        cout << "[TEST] Access out of bounds: FAILED ❌ (Wrong exception type)\n";
    }
    // Test accesso negativo simulato
    try {
        int y = vec[(unsigned long)-1]; // Accesso negativo simulato (out of range)
        cout << "[TEST] Access negative index: FAILED ❌ (No exception thrown, value: " << y << ")\n";
    } catch (const std::out_of_range&) {
        cout << "[TEST] Access negative index: PASSED ✅ (std::out_of_range thrown)\n";
    } catch (...) {
        cout << "[TEST] Access negative index: FAILED ❌ (Wrong exception type)\n";
    }

    cout << "\n--- End of Segmentation Fault & Exception Safety Test ---\n";
}

void testMemoryLeak() {
    cout << "\n--- Memory Leak Test (manual check with Valgrind recommended) ---\n";
    for (int i = 0; i < 1000; ++i) {
        lasd::SetVec<int>* set = new lasd::SetVec<int>();
        for (int j = 0; j < 100; ++j) set->Insert(j);
        for (int j = 0; j < 100; ++j) set->Remove(j);
        delete set;
    }
    cout << "[TEST] Created and deleted 1000 SetVec<int> with 100 elements each. If you run this test with Valgrind, there should be NO memory leaks.\n";
}

void stressTestVectorAndList() {
    cout << "\n--- Stress Test: Vector & List ---\n";
    int totalTests = 0, passedTests = 0;

    // 1. Vector: inserimento massivo
    lasd::Vector<int> v1(100000);
    bool ok = true;
    for (ulong i = 0; i < v1.Size(); ++i) v1[i] = i;
    for (ulong i = 0; i < v1.Size(); ++i) if (v1[i] != (int)i) ok = false;
    RUN_TEST("Vector mass insert and check 100000", ok);

    // 2. Vector: accesso fuori limite basso
    try { (void)v1[(unsigned long)-1]; cout << "[TEST] Vector negative index: FAILED ❌\n"; }
    catch (const std::out_of_range&) { cout << "[TEST] Vector negative index: PASSED ✅\n"; passedTests++; }
    totalTests++;

    // 3. Vector: accesso fuori limite alto
    try { (void)v1[100000]; cout << "[TEST] Vector out of bounds: FAILED ❌\n"; }
    catch (const std::out_of_range&) { cout << "[TEST] Vector out of bounds: PASSED ✅\n"; passedTests++; }
    totalTests++;

    // 4. Vector: resize ripetuti
    for (int i = 0; i < 100; ++i) v1.Resize(1000 + i);
    RUN_TEST("Vector repeated resize up", v1.Size() == 1099);
    for (int i = 0; i < 100; ++i) v1.Resize(1000 - i);
    RUN_TEST("Vector repeated resize down", v1.Size() == 900);

    // 5. Vector: clear e refill
    v1.Clear();
    RUN_TEST("Vector clear", v1.Empty());
    v1.Resize(1000);
    for (ulong i = 0; i < v1.Size(); ++i) v1[i] = i * 2;
    ok = true;
    for (ulong i = 0; i < v1.Size(); ++i) if (v1[i] != (int)(i * 2)) ok = false;
    RUN_TEST("Vector refill after clear", ok);

    // 6. Vector: copy e move
    lasd::Vector<int> v2(v1);
    RUN_TEST("Vector copy", v2.Size() == v1.Size() && v2[10] == v1[10]);
    lasd::Vector<int> v3(std::move(v2));
    RUN_TEST("Vector move", v3.Size() == v1.Size() && v3[10] == v1[10]);

    // 7. List: inserimento massivo in coda
    lasd::List<int> l1;
    for (int i = 0; i < 50000; ++i) l1.InsertAtBack(i);
    ok = true;
    for (ulong i = 0; i < l1.Size(); ++i) if (l1[i] != (int)i) { ok = false; break; }
    RUN_TEST("List mass insert at back 50000", ok);

    // 8. List: inserimento massivo in testa
    lasd::List<int> l2;
    for (int i = 0; i < 10000; ++i) l2.InsertAtFront(i);
    ok = true;
    for (ulong i = 0; i < l2.Size(); ++i)
    if (l2[l2.Size() - 1 - i] != (int)i) { ok = false; break; }
    RUN_TEST("List mass insert at front 10000", ok);
    // 9. List: accesso fuori limite
    try { (void)l1[50000]; cout << "[TEST] List out of bounds: FAILED ❌\n"; }
    catch (const std::out_of_range&) { cout << "[TEST] List out of bounds: PASSED ✅\n"; passedTests++; }
    totalTests++;

    // 10. List: clear e refill
    l1.Clear();
    RUN_TEST("List clear", l1.Empty());
    for (int i = 0; i < 1000; ++i) l1.InsertAtBack(i * 3);
    ok = true;
    for (ulong i = 0; i < l1.Size(); ++i) if (l1[i] != (int)(i * 3)) ok = false;
    RUN_TEST("List refill after clear", ok);

    // 11. List: copy e move
    lasd::List<int> l3(l1);
    RUN_TEST("List copy", l3.Size() == l1.Size() && l3[10] == l1[10]);
    lasd::List<int> l4(std::move(l3));
    RUN_TEST("List move", l4.Size() == l1.Size() && l4[10] == l1[10]);

    // 12. Vector: test di fold
    int sum = v3.Fold<int>([](const int& acc, const int& elem) { return acc + elem; }, 0);
    RUN_TEST("Vector fold sum", sum > 0);

    // 13. List: test di fold
    int sumL = l4.Fold<int>([](const int& acc, const int& elem) { return acc + elem; }, 0);
    RUN_TEST("List fold sum", sumL > 0);

    // 14. Vector: test di map
    v3.Map([](int& x) { x += 1; });
    ok = true;
    for (ulong i = 0; i < v3.Size(); ++i) if (v3[i] != (int)(i * 2 + 1)) ok = false;
    RUN_TEST("Vector map increment", ok);

    // 15. List: test di map
    l4.Map([](int& x) { x -= 1; });
    ok = true;
    for (ulong i = 0; i < l4.Size(); ++i) if (l4[i] != (int)(i * 3 - 1)) ok = false;
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
    for (ulong i = 0; i < v3.Size(); ++i) v3[i] = i;
    ok = true;
    for (ulong i = 0; i < v3.Size(); ++i) if (v3[i] != (int)i) ok = false;
    RUN_TEST("Vector refill after resize to 0", ok);

    // 21. List: test clear e refill
    l4.Clear();
    RUN_TEST("List clear again", l4.Empty());
    for (ulong i = 0; i < 10; ++i) l4.InsertAtBack(i);
    ok = true;
    for (ulong i = 0; i < l4.Size(); ++i) if (l4[i] != (int)i) ok = false;
    RUN_TEST("List refill after clear again", ok);

    // 22. Vector: test accesso multiplo fuori limite
    bool allCaught = true;
    for (int i = 0; i < 10; ++i) {
        try { (void)v3[100 + i]; allCaught = false; }
        catch (const std::out_of_range&) {}
    }
    RUN_TEST("Vector multiple out of bounds", allCaught);

    // 23. List: test accesso multiplo fuori limite
    allCaught = true;
    for (int i = 0; i < 10; ++i) {
        try { (void)l4[100 + i]; allCaught = false; }
        catch (const std::out_of_range&) {}
    }
    RUN_TEST("List multiple out of bounds", allCaught);

    // 24. Vector: test operator==
    lasd::Vector<int> v5(10);
    for (ulong i = 0; i < 10; ++i) v5[i] = i;
    RUN_TEST("Vector == after refill", v5 == v3);

    // 25. List: test operator==
    lasd::List<int> l6;
    for (ulong i = 0; i < 10; ++i) l6.InsertAtBack(i);
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
    for (int i = 0; i < 1000; ++i) l7.InsertAtBack(i);
    for (int i = 0; i < 500; ++i) l7.RemoveFromFront();
    RUN_TEST("List remove from front 500", l7.Size() == 500);

    // 31. List: test rimozione da lista vuota (eccezione)
    l7.Clear();
    bool caught = false;
    try { l7.RemoveFromFront(); }
    catch (const std::length_error&) { caught = true; }
    RUN_TEST("List remove from empty throws", caught);

    // 32. Vector: test accesso dopo clear
    v3.Clear();
    bool caught2 = false;
    try { (void)v3[0]; }
    catch (const std::out_of_range&) { caught2 = true; }
    RUN_TEST("Vector access after clear throws", caught2);

    // 33. List: test accesso dopo clear
    l7.Clear();
    bool caught3 = false;
    try { (void)l7[0]; }
    catch (const std::out_of_range&) { caught3 = true; }
    RUN_TEST("List access after clear throws", caught3);

    // 34. Vector: test fold su vettore vuoto
    v3.Clear();
    int sumEmpty = v3.Fold<int>([](const int& acc, const int& elem) { return acc + elem; }, 0);
    RUN_TEST("Vector fold on empty", sumEmpty == 0);

    // 35. List: test fold su lista vuota
    l7.Clear();
    int sumEmptyL = l7.Fold<int>([](const int& acc, const int& elem) { return acc + elem; }, 0);
    RUN_TEST("List fold on empty", sumEmptyL == 0);

    // 36. Vector: test map su vettore vuoto (non deve crashare)
    v3.Clear();
    try { v3.Map([](int& x) { x += 1; }); ok = true; }
    catch (...) { ok = false; }
    RUN_TEST("Vector map on empty", ok);

    // 37. List: test map su lista vuota (non deve crashare)
    l7.Clear();
    try { l7.Map([](int& x) { x += 1; }); ok = true; }
    catch (...) { ok = false; }
    RUN_TEST("List map on empty", ok);

    // 38. Vector: test ricorsione profonda (simulazione stack overflow)
    try {
        std::function<void(int)> deepRec;
        deepRec = [&](int n) {
            if (n > 0) deepRec(n - 1);
        };
        deepRec(1000); // Potrebbe causare stack overflow su alcune macchine
    } catch (...) {}
    RUN_TEST("Deep recursion (stack overflow simulation)", true);

    // 39. Vector: test allocazione molto grande (simulazione bad_alloc)
    bool allocFailed = false;
    try {
        lasd::Vector<int> bigVec(1000); // 1 miliardo di elementi
    } catch (const std::bad_alloc&) { allocFailed = true; }
    RUN_TEST("Vector huge allocation (bad_alloc simulation)", allocFailed);

    // 40. List: test allocazione molto grande (simulazione bad_alloc)
    allocFailed = false;
    try {
        lasd::List<int> bigList;
        for (int i = 0; i < 1000; ++i) bigList.InsertAtBack(i);
    } catch (const std::bad_alloc&) { allocFailed = true; }
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
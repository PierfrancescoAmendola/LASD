
// #include "..."

#include <iostream>

#include <functional>


#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../container/traversable.hpp"


#include "../vector/vector.hpp"

#include "../list/list.hpp"


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




void mytest() 
{
  // ...
    cout << endl << "Welcome To My Tests:" << endl<<endl;
    cout << endl << " - - -  Vector Tests  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" <<endl<< endl;
    cout << endl << " - - -  Vector Tests with integers - - - " <<endl<< endl;
    lasd::SortableVector<int> vect;
    cout << "vect should be empty: " << vect.Empty() << endl;
    cout << "vect size should be 0: " << vect.Size() << endl;
    vect.Resize(5);
    cout << "vect size should be 5 after resize(5) : " << vect.Size() << endl;
    cout << "First element of vector (0): " << vect.Front() << endl;
    cout << "Last element of vect (0): " << vect.Back() << endl;
    lasd::SortableVector<int> vectCopy(vect);
    cout << "vectCopy size should be 5: " << vectCopy.Size() << endl;
    lasd::SortableVector<int> vectMove(move(vectCopy));
    cout << "vectMove size should be 5: " << vectMove.Size() << endl;
    cout << "Creating a vector for the fold and map test:" << endl;
    lasd::Vector<int> vectorForTest(5);
    cout << "Inserting the following elements into the vector:" << "1, 2, 3, 4, 5" << endl;
    vectorForTest[0] = 1;
    vectorForTest[1] = 2;
    vectorForTest[2] = 3;
    vectorForTest[3] = 4;
    vectorForTest[4] = 5;
    cout << "2 should be in vector : " << vectorForTest.Exists(2) << endl;
    cout << "Size should be 5 : " << vectorForTest.Size() << endl;
    cout << "Fold test with sum:" << endl;
    int sum1 = vectorForTest.Fold<int>(
        [](const int& acc, const int& element) {
            return acc + element;
        }, 0);
    cout << "Sum of elements in the vector: " << sum1 << endl;
    cout << "Fold test with product:" << endl;
    int product1 = vectorForTest.Fold<int>(
        [](const int& acc, const int& element) {
            return acc * element;
        }, 1);

    cout << "Product of elements in the vector: " << product1 << endl;

    cout << "Map test doubling the elements:" << endl;
    vectorForTest.Map(
        [](int& element) {
            element *= 2;
        }
    );

    cout << "Elements in the vector after doubling:" << endl;
    for (ulong i = 0; i < vectorForTest.Size(); ++i) {
        cout << vectorForTest[i] << " ";
    }
        cout << endl <<endl<< " - - -  Vector Tests with string - - - " <<endl<< endl;
        lasd::Vector<string> vectString;
        cout << "vectString should be empty: " << vectString.Empty() << endl;
        cout << "vectString size should be 0: " << vectString.Size() << endl;
        
        vectString.Resize(3);
        
        cout << "vectString size should be 3: " << vectString.Size() << endl;


        cout << "First element of vectString (empty string): " << vectString.Front() << endl;

        cout << "Last element of vectString (empty string): " << vectString.Back() << endl;

        lasd::Vector<string> vectCopyString(vectString);
        cout << "vectCopyString size should be 3: " << vectCopyString.Size() << endl;

        lasd::Vector<string> vectMoveString(move(vectCopyString));
        cout << "vectMoveString size should be 3: " << vectMoveString.Size() << endl;

        cout << "Creating a vector for the fold and map test:" << endl;
    lasd::Vector<string> vectorForTestString(3);

    cout << "Inserting the following elements into the vectStringor:" << "hello  world  !!" <<endl;
    // Correzione ordine qui
    vectorForTestString[0] = "hello";
    vectorForTestString[1] = "world";
    vectorForTestString[2] = "!!";

        cout << "'world' should be in vectString : " << vectorForTestString.Exists("world") << endl;
        cout << "Fold test with concatenation:" << endl;
        string concatString = vectorForTestString.Fold<string>(
            [](const string& acc, const string& element) { return acc + element;
            }, "");

        cout << "Concatenated string of elements in the vectString: " << concatString << endl;

        cout << "Map test with adding 'abc' to each element:" << endl;
        vectorForTestString.Map(
            [](string& element) {
                element += "abc";
            }
        );

        cout << "Elements in the vectStringor after modification:" << endl;
        for (ulong i = 0; i < vectorForTestString.Size(); ++i) {
            cout << vectorForTestString[i] << " ";
        }

        cout << endl <<endl<< " - - -  Vector Tests with float - - - " <<endl<< endl;
        lasd::SortableVector<float> vectFloat;
        cout << "vectFloat should be empty: " << vectFloat.Empty() << endl;
        cout << "vectFloat size should be 0: " << vectFloat.Size() << endl;
        
        vectFloat.Resize(4);
        
        cout << "vectFloat size should be 4: " << vectFloat.Size() << endl;


        lasd::SortableVector<float> vectCopyFloat(vectFloat);
        cout << "vectCopyFloat size should be 4: " << vectCopyFloat.Size() << endl;

        lasd::SortableVector<float> vectMoveFloat(move(vectCopyFloat));
        cout << "vectMoveFloat size should be 4: " << vectMoveFloat.Size() << endl;

        cout << "Creating a vector for the fold and map test:" << endl;
    lasd::Vector<float> vectorForTestFloat(4);

    cout << "Inserting the following elements into the vectFloator:" << endl;
    cout << "1.5, 2.5, 3.5, 4.5" << endl;

    vectorForTestFloat[0] = 1.5;
    vectorForTestFloat[1] = 2.5;
    vectorForTestFloat[2] = 3.5;
    vectorForTestFloat[3] = 4.5;

    // Correzione qui: usare vectorForTestFloat invece di vectFloat
    cout << "First element of vectFloat (1.5): " << vectorForTestFloat.Front() << endl;
    cout << "Last element of vectFloat (4.5): " << vectorForTestFloat.Back() << endl;

        cout << "2.5 should be in vectFloat : " << vectorForTestFloat.Exists(2.5) << endl;
        cout << "Fold test with sum:" << endl;
        float sum1Float = vectorForTestFloat.Fold<float>(
            [](const float& acc, const float& element) {
                return acc + element;
            }, 0.0);

        cout << "Sum of elements in the vectFloat: " << sum1Float << endl;

        cout << "Fold test with product:" << endl;
        float product1Float = vectorForTestFloat.Fold<float>(
            [](const float& acc, const float& element) {
                return acc * element;
            }, 1.0);

        cout << "Product of elements in the vectFloat: " << product1Float << endl;
}



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

        
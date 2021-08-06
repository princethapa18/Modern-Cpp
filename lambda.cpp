/* Week 32 06 august 2021 
   Lambda Expression
   lambdas are const function by default
   [capture-list](parameters) -> return-type { Method body };
 
   int x;
   double y;


   auto lambda = [x, y](int a, int b) -> bool{ return (a*b) < (x*y); } ;
   int a = 3, b = 7;
   lambda(a, b);

   this lambda function return type is bool which is automatically deduced (even if don't specify -> bool)

   ------------------------------------------------------------
   class Functor {
       int x;
       double y;
    public:
       Functor(int x, int y) : x{x}, y{y} {}
       bool operator(int a , int b) const {
           return (a*b) < (x*y);
       }
   };

   Functor functorObj{x, y}; // ctor call
   int a = 3, b = 7;
   functorObj(a, b); // function call
   
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef enum FUNTYPE
{   
    FUNCTIONS = 1,
    VECTORS,
    TENSORS
} FUNTYPE;

typedef struct FunctionInfo
{
    int funtype;
    std::string funname;
    FunctionInfo(int ftype, std::string fname) : funtype(ftype) , funname(fname) {}
    FunctionInfo() : funtype(0) , funname("") {}
} FunctionInfo;

void addToFunctionList(FUNTYPE funtype, std::string fname, std::vector<FunctionInfo>& funInfoList )
{
    FunctionInfo funInfo{funtype, fname};
    funInfoList.push_back(funInfo);
}

void printFunctionList(std::vector<FunctionInfo>& funInfoList)
{
    for(auto itr : funInfoList)
    {
        switch (itr.funtype)
        {
        case FUNTYPE::FUNCTIONS:
            cout << "S: " << itr.funname << endl;
            break;
        case FUNTYPE::VECTORS:
            cout << "V: " << itr.funname << endl;
            break;
        case FUNTYPE::TENSORS:
            cout << "T: " << itr.funname << endl;
            break;      
        default:
            cout << "Invalid function " << endl;
            break;
        }        
    }
}

void test()
{
    int i = 20;
    double d = 4.6;
    float f = 3.5f;

    //[=] captures all (which are used in the lambda expression)  by value 
    auto l = [=]() { std::cout << "i : " << i << " d: " << d << std::endl ; };
    l(); // O/P   i : 20 d: 4.6

    // auto l1 = [=](int a) 
    // { 
    //     i *= f;
    //     d *= f; 
    //     std::cout << "i : " << i << " d: " << d;
    // };
    //l1(f); 
    /* this gives error as lambda functions are const by default 
       Its like    []() const { ... ; };

        error: assignment of read-only variable ‘i’
         i *= f;
        error: assignment of read-only variable ‘d’
         d *= f; 
        Inorder to modify use mutable keyword (only if captured by value. If captured by reference (may not be needed there))
    */
    auto l1_mutable = [=](float f1) mutable 
    { 
        i *= f1;
        d *= f1; 
        std::cout << "i : " << i << " d: " << d << std::endl ;
    };
    l1_mutable(f); // O/P i : 70 d: 16.1

    // Capture all by reference
    auto l_ref = [&](float f1) 
    { 
        i *= f1;
        d *= f1;
        std::cout << "i : " << i << " d: " << d << std::endl ; 
    };
    l_ref(4.5); // O/P   i : 90 d: 20.7

    // Mixed   i and d are captured by value and f is captured by reference
    auto l_mixed = [=, &f]()
    {
        ++f;
        std::cout << "i : " << i << " d: " << d << " f: " << f << std::endl ; 
    };
    l_mixed(); // O/P  i : 90 d: 20.7 f: 4.5     f is incremented by 1
}

int main()
{
    int var = 42;
    // Capture by reference
    auto lambda = [var](){ std::cout << var << std::endl; };

    for(int i= 0; i < 3; i++)
    {
        var++; 
        lambda();  // prints 42, 42, 42 because var is captured by copy so therefore it only prints 42
    }

    std::cout << "var's value before capturing by refernce: " << var << std::endl;
    // Capture by reference
    auto lambda_ref = [&var]() {std::cout << var << std::endl; }; // var is captured by reference. Its value is 45

    for(int i= 0; i < 3; i++)
    {
        var++; 
        lambda_ref();     // prints 46, 47, 48
    }
    test();

    // Using a lambda as a compare function for sorting
    std::vector<FunctionInfo> funInfoList; // added in random order
    addToFunctionList(FUNTYPE::FUNCTIONS, "Moment in local X", funInfoList);
    addToFunctionList(FUNTYPE::VECTORS, "Displacement", funInfoList);
    addToFunctionList(FUNTYPE::VECTORS, "Acceleration", funInfoList);
    addToFunctionList(FUNTYPE::FUNCTIONS, "Moment in local X", funInfoList);
    addToFunctionList(FUNTYPE::TENSORS, "Stress Tensor", funInfoList);
    addToFunctionList(FUNTYPE::FUNCTIONS, "Displacement in X", funInfoList);
    addToFunctionList(FUNTYPE::FUNCTIONS, "Displacement in Y", funInfoList);
    addToFunctionList(FUNTYPE::TENSORS, "Strain Tensor", funInfoList);
    addToFunctionList(FUNTYPE::FUNCTIONS, "Principal major stress", funInfoList);

    std::cout << "********* funInfoList before sort ************\n";
    printFunctionList(funInfoList);

    std::sort(funInfoList.begin(), funInfoList.end(), 
              [](const FunctionInfo& a, const FunctionInfo& b)
              {
                  if(a.funtype == b.funtype)
                    return a.funname < b.funname;
                  return a.funtype < b.funtype;
              } );

    std::cout << "********* funInfoList after sort ************\n";
    printFunctionList(funInfoList);              
}

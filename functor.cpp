
/* 25 aug 2020  
 * ************* Functor (Function Object) ********************************
 * A function object allows an instance object of a class to be called or invoked as if it were an ordinary function. 
 * In C++ this is carried out by overloading operator().
*/

/* Benefits of a functor:
 * 1. Smart function: capabalities beyond operator()
 *    It can remember state
 * 2. It can have its own type
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class X
{
public:
  void operator()(std::string str)
  {
      cout << "calling functor X with parameter " << str << endl;
  }
  
};

/* Parameterized functor */
class Y
{
public:
  Y(int i) {}
  void operator()(std::string str) {
      cout << "calling functor X with parameter " << str << endl;
  }  
};

void add2(int i) {
  cout << i + 2 << endl;   // 2 is hardcoded // not extensible
}

template<int val>
void addVal(int i)
{
  cout << val + i << endl;  // more flexible but resolved at compile time.
}

class AddValue {
  int val;
public:
  AddValue(int j) : val(j) { }
  void operator() (int i) {
      cout << i + val << endl;
  }
};

/* Parameter Binding */

int main()
{
  X foo;
  foo("Hello"); 
  Y(8)("Hi");
  
  std::vector<int> vec = {2,3,4,5};
  //for_each(vec.begin(), vec.end(), add2);
  //for_each(vec.begin(), vec.end(), addVal<2>); //resolved at compile time . ok
  
  int x = 2;
  // for_each(vec.begin(), vec.end(), addVal<x>); // resolved at run time. gives error 
  // error: the value of ‘x’ is not usable in a constant expression
  // for_each(vec.begin(), vec.end(), addVal<x>);
  
  // template argument deduction/substitution failed:
  // functor.cpp:58:45: note:   couldn't deduce template parameter ‘_Funct’
  // for_each(vec.begin(), vec.end(), addVal<x>);
  
  for_each(vec.begin(), vec.end(), AddValue(x));// the best solution
  
  for( int i : vec)
    cout << " " << i << " ";
  
  return 0;
}

// compiling with c++11
// g++ -std=c++11 functor.cpp -o functor

/* Built in functors */
// less greater   greater_equal less_equal 

// int x = multiplies<int>()(3,4); // x = 3 * 4

// if(not_equal_to<int>()(x,10))   // if(x != 10)
//    cout << x << endl;













/*  13 June 2020 
    ******* "Explicitly defaulted and deleted function" ****************
    =default
    =delete

    Special member functions
    They are defined by the compiler even if not defined by the user.
    They are: 
    1 Default ctor 
    2 Copy ctor 
    3 Move ctor
    4 Copy Assignment optor
    5 Move Assignment optor
    6 Destructor

    --> If any constructor is explicitly declared, then no default constructor is automatically generated.
    --> If a virtual destructor is explicitly declared, then no default destructor is automatically generated.
    --> If a move constructor or move-assignment operator is explicitly declared, then:
            No copy constructor is automatically generated.
            No copy-assignment operator is automatically generated.
    --> If a copy constructor, copy-assignment operator, move constructor, move-assignment operator, or destructor is explicitly declared, then:
            No move constructor is automatically generated.
            No move-assignment operator is automatically generated

*/

#include <iostream>
using namespace std;

class A
{
    int a;
public:
    A(int x) : a(x) { }    
    A()=default; // instructs compiler to generate the default ctor. 
    /* A defaulted function needs to be a special member function (default constructor, copy constructor, destructor etc), 
        or has no default arguments
    */
    //A(int x = 0)=default; // error: ‘A::A(int)’ cannot be defaulted
    //void setA(int x)=default; // error: ‘void A::setA(int)’ cannot be defaulted
    int getA() const {return a;}
};

// C++
class NonCopyable
{
public:
    NonCopyable() {};
private:
    // copy ctor and copy assign. optor is declared in pvt. so as to not allow copy and copy assignment 
    NonCopyable(const NonCopyable&);           
    NonCopyable& operator=(const NonCopyable&);
};

// C++11
class NonCopyable1
{
    public:
    NonCopyable1()=default;
    NonCopyable1(const NonCopyable1&)=delete; // copy constructor is deleted 
    NonCopyable1& operator=(const NonCopyable1&)=delete; // copy assignment optor is deleted
};
/*
    You can delete special member functions as well as normal member functions and 
    non-member functions to prevent them from being defined or called. 
    Deleting of special member functions provides a cleaner way of preventing 
    the compiler from generating special member functions that you don't want.
*/

template <typename T>
T addFun(T t1, T t2)
{
    return t1 + t2;
}

double addFun(double d1, double d2)=delete; // double version of this function won't be generated

int main()
{
    A obj; // bc we have defined a custom (paramterized ctor) the compiler doesn't generate a default ctor. Therefore this gives error
           // error: no matching function for call to ‘A::A()’
    //cout << obj.getA() << endl;
    //A obj1(10);
    //cout << obj1.getA() << endl;

    cout << addFun(5, 6) << endl;        // int   version of the addFun()
    cout << addFun(1.3f, 3.4f) << endl;  // float version
    std::string s1 = "hello";
    std::string s2 = " there";
    cout << addFun(s1, s2) << endl;      // string version
    //cout << addFun(1.3, 3.4) << endl;  // double version ---> error: use of deleted function ‘double addFun(double, double)’

    NonCopyable1 nonCopy;
    //NonCopyable1 nonCopy1(nonCopy); // Copy not allowed   ---> error: use of deleted function ‘NonCopyable1::NonCopyable1(const NonCopyable1&)’
    //NonCopyable1 nonCopy2;
    //nonCopy2 = nonCopy1;   // Copy Assingment not allowed ---> error: use of deleted function ‘NonCopyable1& NonCopyable1::operator=(const NonCopyable1&)’

    return 0;
}
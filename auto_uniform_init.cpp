// 7  May  2020
// 13 June 2020

/* auto type deduction
   uniform initialization
*/

#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

//static const std::vector<int> fib = {0, 1, 1, 2, 3, 5, 8, 13, 21};

class Test
{
    int _x;
    public:
    Test():_x(0) { cout << "Test()" << endl;}
    Test(int x) : _x(x) {cout << "Test(int x)" << endl;}
    Test(const Test &obj) {
        _x = obj._x;
        cout << "Test(const Test &obj)" << endl;
    }
    Test& operator=(const Test &obj){
        if(this != &obj)
        {
            _x = obj._x;
        }
        cout << "operator=(const Test &obj)" << endl;
        return *this;
    }

    void setX(int x) 
    {
        _x = x;
        cout << "setX(int x)" << endl;
    }
    int getX() const {return _x;}
};

int Sum(int x, int y) 
{
	return x + y;
}

int main()
{
    //for (auto i : fib)
    //    cout << i <<  endl;

    //std::for_each(begin(fib), end(fib), [](int i){cout << i << endl;});

    /* Uniform initialization
    /* Why use it?
    /* 1 .Prevents narrowing . double to float or double to int or float to int or char to int not allowed.
     */
    int i = 10;
    double d = 5.67;
    int i1 = d;    // i1 becomes 5  [truncation]
    //int i2 {d};  // error . narrowing not allowed   warning: narrowing conversion of ‘d’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
    char c1 = i1;  // int to char. ok
    //char c2{i1}; // error . warning: narrowing conversion of ‘i1’ from ‘int’ to ‘char’ inside { } [-Wnarrowing]

    //Test t1(6);
    //cout << "x : " << t1.getX() << endl;
    // 2. C++ Most Vexing Parse
    //Test t2();     // doesn't call the default constructor Test() . Because compile thinks its a function. 
    //t2.setX(11);   // error: request for member ‘setX’ in ‘t2’, which is of non-class type ‘Test()’
    //cout << "x : " << t2.getX() << endl; 

    //Test t2{};     // calls the default constructor Test()
    //t2.setX(11);   // ok
    //cout << "x : " << t2.getX() << endl;

    Test t3(16);  // direct initialization
    Test t4 = 18;
    initializer_list<int> mylist {10,20,30};

    // auto
    auto i2 = 10;
	auto j2 = 5;
	auto sum = i2 + 4.3f;

	auto result = Sum(i2, j2);
	static auto y = 2;
	const int const_x = 10;

	auto value = const_x; // value is deduced to int
    value++; // ok
    cout << "value: " << value << endl; 

	//Works with qualifiers
	const auto var = const_x; // var is deduced to const int
    //var++; // error: increment of read-only variable ‘var’

	auto &var1 = const_x; 	// var1 is deduced to const reference	
    cout << "var1: " << var1 << endl; 

    //var1++; // error: increment of read-only reference ‘var1’
    //cout << "var1: " << var1 << endl;  

    //Deduced to a pointer. * is not necessary
    //auto ptr = &x;
    //int *ptr = &x; //error: invalid conversion from ‘const int*’ to ‘int*’

    // x is of type const int so therefore a pointer pointing to the const int type should be used

    ///---------- A pointer pointing to a const int type --------------------
    //    const int* my_ptr;   my_ptr is a pointer pointing to a const int

    const int* ptr_pointing_to_const_int = &const_x;  // ptr is pointing to a const int type 
    //*ptr = *ptr + 5;  // error: assignment of read-only location ‘* ptr’

	cout << "*ptr_pointing_to_const_int: " << *ptr_pointing_to_const_int << endl;
    cout << "&ptr_pointing_to_const_int: " << &ptr_pointing_to_const_int << endl;

    const int const_g = 10;
    ptr_pointing_to_const_int = &const_g; // Now it is pointing to another const int type
    cout << "*ptr_pointing_to_const_int: " << *ptr_pointing_to_const_int << endl;
    cout << "&ptr_pointing_to_const_int: " << &ptr_pointing_to_const_int << endl;

    ///---------- A const pointer pointing to an int type --------------------
    //          int* const my_ptr;   my_ptr  is a const pointer pointing to an int
    //    const int* const my_ptr2;  my_ptr2 is a const pointer pointing to a  const int
    
    int abc = 60, def = 90;   
    int* const const_ptr_pointing_to_int = &abc; 

    cout << "*ptr_pointing_to_const_int: " << *ptr_pointing_to_const_int << endl;
    cout << "&ptr_pointing_to_const_int: " << &ptr_pointing_to_const_int << endl;

    //const_ptr_pointing_to_int = &def; // error: assignment of read-only variable ‘const_ptr_pointing_to_int’  can't point to another variable

    auto ptr_to_const = &const_x;  // ptr_to_const is deduced to a pointer to const int 
    //*ptr_to_const = 5; // error: assignment of read-only location ‘* ptr_to_const’

    ptr_to_const = &const_g; // ok . can point to another const int type

    const auto const_ptr_to_const = &const_x; // deduced to the const pointer pointing to a const int

    //const_ptr_to_const = &const_g; //error: assignment of read-only variable ‘const_ptr_to_const’  // can't point to another const int type

    int z = 15;
	auto ptr1 = &z;
    *ptr1 = *ptr1 + 5;
	cout << "*ptr1: " << *ptr1 << endl;
    cout << "&ptr1: " << &ptr1 << endl;

	//auto list {10}; //int list {10} single element
	auto list = {10,20,30}; // std::initializer_list <int> list
	//auto list {10,20,30}; //compiler-error

    for(auto item: list)
        cout << item << " ";

    return 0;
}

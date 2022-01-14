/*  Week 02   14 Jan 2022
    Perfect forwarding
    universal reference (coined by Scott Meyers)  [also called as forwarding reference]

    template<class... Args>
    void emplace_back(Args&&... args)        // deduced parameter types .  
    Forwarding or Universal reference

    int&&    ---> rvalue reference
    auto&&   ---> universal reference 

    rvalue
    temporary object
    no name
    no address

    int x = 9;   x is lvalue 9 is rvalue

    std::forward   ---> defined in <utility>
    (1)
    template< class T >
    T&& forward( typename std::remove_reference<T>::type& t ) noexcept;(since C++11)(until C++14)
    template< class T >
    constexpr T&& forward( std::remove_reference_t<T>& t ) noexcept;(since C++14)	
    template< class T >

    (2)
    T&& forward( typename std::remove_reference<T>::type&& t ) noexcept;(since C++11)(until C++14)
    template< class T >
    constexpr T&& forward( std::remove_reference_t<T>&& t ) noexcept;

    1) Forwards lvalues as either lvalues or as rvalues, depending on T
    2) Forwards rvalues as rvalues and prohibits forwarding of rvalues as lvalues
*/

#include <iostream>
#include <vector>

void foo(int&& i) 
{
    std::cout << "foo" << i << std::endl;
}

template <typename T>
void bar(T&& i)
{
    std::cout << "bar " << i << std::endl;
}

/*
    Here T&& is not a rvalue reference but it is a universal reference or forwarding refererence.
    Because T&&  is  type deduction  therefore the parameter of bar() binds to both lvalue as well as rvalue
*/

class Pt
{
    float _x, _y, _z;
    // some more members
public:
    Pt(float x = 0.f, float y = 0.f, float z = 0.f) : _x(x), _y(y), _z(z) { std::cout << "ctor1\n"; }
    float getX() const {return _x;}
    float getY() const {return _y;}
    float getZ() const {return _z;}
};

template <typename T, typename Arg>
T create(Arg& a)
{
    return T(a);
}

template <typename T, typename Arg>
T create(const Arg& a)
{
    return T(a);
}

/* using std::forward */
template<typename T, typename Arg>
T create1(Arg&& a)
{
    return T(std::forward<Arg>(a));
}

int main()
{
    foo(1); // passed an rvalue
    int k =0;
    //foo(k); // this will give error  kyuki usko rvalue mangta hai aur lvalue diyela hai
    // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’

    bar(1); // Okay 
    bar(k); // this is also okay

    /* int&& is rvalue referernce */
    //int&& x = k; // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    int&& y = 5; //ok

    /* auto&&   can be lvalue or a rvalue reference . Therefore it is also called as universal reference */
    auto&& z = 4; // rvalue assigned
    auto&& d = k; // lvalue assigned

    const int cnstk = 5;
    auto&& e = cnstk;
    bar(cnstk);

    /*--------------------------------*/
    std::vector<Pt> vec;
    {
        //Pt pt{1.f, 2.f, 3.f};
        //vec.push_back(std::move(pt));
        vec.emplace_back(1.f, 2.f, 3.f);
    }

    std::cout << "vec[0].getX() " << vec[0].getX() << std::endl;

    /*-------------------*/
    int five = 5;
    int myFive = create<int>(five);
    // When there is no overloaded function taking const reference. Following gives error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    int myFive2 = create<int>(5); 

    int myFive3 = create1<int>(five);
    int myFive4 = create1<int>(5);


    return 0;
}
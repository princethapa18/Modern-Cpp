/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>

/* 22 june 2024

  generice template class for understanding move semantics
  std::move() - converts a lvalue reference into a r value reference

*/

template <typename T>
class MyVec 
{
private:
    size_t m_size;
    T*     m_data;
public:
    MyVec(size_t size): m_size(size) {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        if(m_size > 0) {
            m_data = new T[m_size];
            for(size_t i = 0; i < m_size; ++i) {
                m_data[i] = T{};    
            }
        } else {
            m_data = nullptr;
        }
    }
    
    MyVec(const MyVec& other) {
        std::cout <<__PRETTY_FUNCTION__ << "\n";
        m_size = other.m_size;
        m_data = other.m_data;
    }
    
    MyVec& operator=(MyVec& other) {
       std::cout <<__PRETTY_FUNCTION__ << "\n";
        if(this != &other) {
            m_size = other.m_size;
            m_data = other.m_data;
        }
        
        return *this; 
    }
    
    // move ctor
    MyVec(MyVec&& other) {
      std::cout <<__PRETTY_FUNCTION__ << "\n";
        delete[] m_data;
        m_size = other.m_size;
        m_data = other.m_data;
    }
    
    MyVec& operator=(MyVec&& other) noexcept {
        std::cout <<__PRETTY_FUNCTION__ << "\n";
        if(this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_data = other.m_data;
        }
        
        return *this;
    }
    
    size_t Size() const { return m_size; }
    T*     Data() const { return m_data; }
};

template <typename T>
void PrintVec(const MyVec<T>& vec) 
{
    for(size_t i = 0; i< vec.Size(); ++i) {
        std::cout << vec.Data()[i];
        if(i+1 != vec.Size()) std::cout << ", ";
    }
    std::cout << "\n";
}


int main()
{
    MyVec<int> ids(5);
    std::cout << " printing ids\n";
    PrintVec(ids);
    
    MyVec<std::string> strs(6);
    strs.Data()[1] = " some string ";
    strs.Data()[2] = "test data";
    std::cout << " printing strs\n";
    PrintVec(strs);
    
    MyVec<std::string> strs1 = strs; // copy ctor will be called
    MyVec<std::string> strs2 = std::move(strs1); // move ctor 
    
    // constructs a vector of float of size 5, 
    // then converts this vector into r value reference 
    // then calls the move ctor of vec 
    MyVec<float> vec{ std::move(MyVec<float>(4)) }; 
    
    MyVec<int> ids2(6);
    ids2.Data()[3] = 5;
    ids2.Data()[4] = 7;
    std::cout << " printing ids2\n";
    PrintVec(ids2);
    
    MyVec<int> ids3(5);
    
    ids3 = ids2; // copy assignment 
    ids = std::move(ids2); // move assignment
    std::cout << " printing ids\n";
    PrintVec(ids);
    
    return 0;
}

/* output
MyVec<T>::MyVec(size_t) [with T = int; size_t = long unsigned int]
 printing ids
0, 0, 0, 0, 0
MyVec<T>::MyVec(size_t) [with T = std::__cxx11::basic_string<char>; size_t = long unsigned int]
 printing strs
,  some string , test data, , , 
MyVec<T>::MyVec(const MyVec<T>&) [with T = std::__cxx11::basic_string<char>]
MyVec<T>::MyVec(MyVec<T>&&) [with T = std::__cxx11::basic_string<char>]
MyVec<T>::MyVec(size_t) [with T = float; size_t = long unsigned int]
MyVec<T>::MyVec(MyVec<T>&&) [with T = float]
MyVec<T>::MyVec(size_t) [with T = int; size_t = long unsigned int]
 printing ids2
0, 0, 0, 5, 7, 0
MyVec<T>::MyVec(size_t) [with T = int; size_t = long unsigned int]
MyVec<T>& MyVec<T>::operator=(MyVec<T>&) [with T = int]
MyVec<T>& MyVec<T>::operator=(MyVec<T>&&) [with T = int]
 printing ids
0, 0, 0, 5, 7, 0
*/

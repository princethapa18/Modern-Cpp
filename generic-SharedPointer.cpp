/* 8 Mar 2022
   Generic shared pointer implementation
    -> (arrow) vs . (dot) operator
   overloading -> and .
   shared_ptr implementation
*/

#include <iostream>
using namespace std;

class Counter
{
    unsigned int m_counter{};
public:
    Counter() : m_counter(0) { cout << "default Counter ctor\n"; };

    // delete copy ctor
    Counter(const Counter&) = delete;
    // delete copy assignment operator
    Counter& operator=(const Counter&) = delete;

    // Destructor
    ~Counter(){}
    void reset() 
    {
        m_counter = 0;
    }

    unsigned int get()
    {
        return m_counter;
    }
    // post increment
    void operator++()
    {
        m_counter++;
    }
    // pre increment
    void operator++(int) {m_counter++;}
    void operator--() {m_counter--;}
    void operator--(int){m_counter--;}

    // overload << operator
    // not needed
    friend ostream& operator<< (ostream& os,  const Counter& counter)
    {
        os << "counter value : " << counter.m_counter << endl;
        return os; 
    }
};

template <typename T>
class Shared_ptr
{
    T *m_ptr;
    Counter *m_counter;
public:
    explicit Shared_ptr(T* ptr = nullptr)
    {
        cout << "\nexplicit ctor";
        m_ptr = ptr;
        m_counter = new Counter();
        if(ptr)
        {
            (*m_counter)++;
        }
    }
    // Copy ctor
    Shared_ptr(Shared_ptr<T>& sp)
    {
        cout << "\nCopy ctor";
        m_ptr = sp.m_ptr;
        m_counter = sp.m_counter;
        (*m_counter)++;
    }

    Shared_ptr& operator=(Shared_ptr<T>& sp)
    {
        cout << "\nCopy assignment operator";
        if(this != &sp)
        {
            m_ptr = sp.m_ptr;
            m_counter = sp.m_counter;
            (*m_counter)++; //  first dereference the pointer and then increment the value it points to
            // *m_counter++ is not the same. It means  *(m_counter++) // increment pointer, and dereference unincremented address
        }
        else
        {
            cout << "\nTrying to assign self";
        }
        cout << "\n---- this " << this  << " *this " << *this << endl;
        return *this;
    }

    // Reference count
    unsigned int use_count() {return m_counter->get();}
    // Get the pointer
    T* get() {return m_ptr;}

    // Overload * operator
    T& operator*()
    {
        return *m_ptr;
    }
    // Overload -> operator
    T* operator->()
    {
        return m_ptr;
    }
    // Destructor
    ~Shared_ptr()
    {
        cout << "\nDestructor";
        (*m_counter)--;
        if(m_counter->get()==0)
        {
            delete m_counter;
            delete m_ptr;
        }
    }

    friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp)
    {
        os << " Address pointed : " << sp.get() << endl;
        os << *(sp.m_counter) << endl;
        return os;
    }
};

int main()
{
    Shared_ptr<int> ptr1(new int(151));
    cout << "---- Shared pointers ptr1 ----\n";
    *ptr1 = 100;
    cout << " ptr1's value now: " << *ptr1 << endl;
    cout << ptr1;

    ptr1 = ptr1; // self assignment

    {
        // ptr2 pointing to same integer
        // which ptr1 is pointing to 
        // Shared pointer ref count should have increased to 2 now.
        Shared_ptr<int> ptr2 = ptr1; 
        cout << "--- Shared pointers ptr1, ptr2 ----\n";
        cout << ptr1;
        cout << ptr2;

        {
            Shared_ptr<int> ptr3;
            cout << "initial ptr3 " << ptr3 << " \n";
            ptr3 = ptr2;
            // Shared pointer ref count should have increased to 3 now
            cout << "--- Shared pointers ptr1, ptr2, ptr3 ----\n";
            cout << ptr1;
            cout << ptr2;        
            cout << ptr3;
        }

        // ptr3 is out of scope
        // It would have been destructed
        // So shared pointer reference counter
        // should have decreased to 2 now
        cout << "--- Shared pointers ptr1, ptr2 ---\n";
        cout << ptr1;
        cout << ptr2;
    }

    // ptr2 is out of scope
    // should have decreased now to 1.
    cout << "--- Shared pointers ptr1 ----\n";
    cout << ptr1;

    return 0;
}


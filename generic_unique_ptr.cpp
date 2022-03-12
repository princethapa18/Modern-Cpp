/* 12 Mar 2022
   Implementing a generic unique ptr
   
   https://en.cppreference.com/w/cpp/memory/unique_ptr   
   Defined in header <memory>

template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;                             (1)	(since C++11)
template <
    class T,
    class Deleter
> class unique_ptr<T[], Deleter>;               (2)   (since C++11)


// note: this implementation does not disable this overload for array types
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

*/

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/* Generic unique_ptr implementation todo 
template <class T, class Deleter = std::default_delete<T> >
class myUniquePtr
{
   T * m_ptr;
public:
   explicit myUniquePtr( T *p = nullptr) : m_ptr{p} {}
   myUniquePtr(const myUniquePtr&) = delete; // delete copy ctor
   myUniquePtr<T*>& operator=(const myUniquPtr&) = delete; // delete assignment operator
   myUniquePtr(myUniquePtr&& temp)
   {
      m_ptr = temp.m_ptr;
      temp.m_ptr = nullptr;
   }
   myUniquePtr<T*>&& operator=(myUniquePtr&& temp)
   {

   }
};
*/

//static int heapAllocatedSize = 0;

struct Element
{
   int eleId;
   int pid;
   string str;
   int * nodeIds;
   int nodeSize;
   explicit Element(int eid = 0 , int pd = 0 , string s = "") : eleId{eid}, pid{pd}, str{s} 
   { 
      cout << " Element's ctor" << endl; 
      nodeSize = 0;
   }
   void insertNodeIds(vector<int>& nids)
   {  
      if(nodeSize != nids.size())
      {
         if(nodeIds)
            delete[] nodeIds;
         nodeIds = new int[nids.size()];
      }
      nodeSize = nids.size();
      std::copy(nids.begin(), nids.end(), nodeIds);
   }

   ~Element() 
   { 
      cout << " Element's dtor\n";
   }

   friend ostream& operator<<(ostream& os, const Element *e);

   // void* operator new(size_t size)
   // {
   //    cout << "overloaded new operator\n";
   //    // warning: ‘operator new’ must not return NULL unless it is declared ‘throw()’ (or -fcheck-new is in effect)
   //    // return nullptr; 
   //    void *p = nullptr;
   //    try {
   //       p = ::operator new(size);    // here this works fine
   //       //p = malloc(size);
   //       cout << "memory successfully allocated\n";
   //    }
   //    catch (const bad_alloc& e) {
   //       cout << "memory allocation failed: " << e.what() << endl;
   //    }
   //    return p;
   // }

   // void operator delete(void *p)
   // {
   //    cout << " overloaded delete operator\n";
   //    if(p)
   //    {
   //       //size_t size = sizeof(p);
   //       // we don't know the type of the p 
   //       //cout << "deallocating size : " << size << endl;
   //       //heapAllocatedSize -= size;
   //       free(p);
   //    }
   // }

   //void* operator new[](size_t size);
   //void delete [](void *p);
};

// don't use friend here
ostream& operator<<(ostream& os, const Element *e)
{
   if(e)
   {
      cout << "eleId: " << e->eleId << " pid: " << e->pid << " element name: " << e->str <<endl;
      cout << "----- node ids ------\n";
      for(int i = 0; i < e->nodeSize; ++i)
      {
         //cout << e->nodeIds[i] << " ";
         cout << (*e).nodeIds[i] << " ";
      }
   }
   else
   {
      cout << " Element is null\n";
   }
}

// You should not overload the global new and delete operator

// void* operator new(size_t size)
// {
//    cout << "overloaded new operator\n";
//    // warning: ‘operator new’ must not return NULL unless it is declared ‘throw()’ (or -fcheck-new is in effect)
//    // return nullptr; 
//    void *p = nullptr;
//    try {
//       //p = ::operator new(size);   
//       p = malloc(size);
//       cout << "memory successfully allocated\n";
//    }
//    catch (const bad_alloc& e) {
//       cout << "memory allocation failed: " << e.what() << endl;
//    }
//    return p;
// }

// void operator delete(void *p)
// {
//    cout << " overloaded delete operator\n";
//    if(p)
//    {
//       //size_t size = sizeof(p);
//       // we don't know the type of the p 
//       //cout << "deallocating size : " << size << endl;
//       //heapAllocatedSize -= size;
//       free(p);
//    }
// }

struct ElementDeleter
{
   void operator()(Element *e)
   {
      cout << "Element Deleter\n";
      if(!e) return;
      cout << e;
      delete [] e->nodeIds;
      delete e;
   }
};

class CustomDeleter
{
   public:
   void operator()(Element *e)
   {
      cout << "Custom Deleter\n";
      if(!e) return;
      cout << e;
      delete [] e->nodeIds;
      delete e;
   }
};

int main()
{
   //unique_ptr<int> ptr = new int(5); // this gives error
   // Element * p  = new Element{2, 5 , "quad"};
   // vector<int> vec = { 2, 3, 4, 5, 6};
   // p->insertNodeIds(vec);
   // delete p;  // this leaks

   /* Custom deleter*/
   unique_ptr<Element, ElementDeleter> ptr_elem{ new Element{3, 4, "tria"}};
   vector<int> vec1 = {4, 5, 6};
   ptr_elem.get()->insertNodeIds(vec1);

   /*
   unique_ptr<Element, [](Element *p) { 
                         if(!p) return; 
                         cout << p;
                         delete[] p->nodeIds; 
                         delete p; } > ptr_elem1 = make_unique<Element>(4, 6, "tetra");

   Passing a lambda gives error
   error: lambda-expression in template-argument
    unique_ptr<Element, [](Element *p) {
                        ^
generic_unique_ptr.cpp:192:38: error: template argument 2 is invalid
                          delete p; } > ptr_elem1 = make_unique<Element>(4, 6, "tetra");
                                      ^
generic_unique_ptr.cpp:192:86: error: cannot convert ‘std::_MakeUniq<Element>::__single_object {aka std::unique_ptr<Element, std::default_delete<Element> >}’ to ‘int’ in initialization
                          delete p; } > ptr_elem1 = make_unique<Element>(4, 6, "tetra");                      
   */

   /*
   template<typename T, typename... Args>
   std::unique_ptr<T> make_unique(Args&&... args)
   {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
   }
   */

   //unique_ptr<Element, ElementDeleter> ptr_elem1 = make_unique<Element>(4, 6, "tetra");
   /* Can't use a custom deleter with make_unique
       error: conversion from ‘std::_MakeUniq<Element>::__single_object {aka std::unique_ptr<Element, std::default_delete<Element> >}’ to non-scalar type ‘std::unique_ptr<Element, ElementDeleter>’ requested
   */
   unique_ptr<Element, CustomDeleter> ptr_elem1{ new Element{4, 6, "tetra"} };
   unique_ptr<Element, CustomDeleter> ptr_elem2 = std::move(ptr_elem1);
   Element *elm = ptr_elem1.get(); // elm is null because  ptr_elem1 doesn't own it anymore
   cout << elm; // 

   /* gdb output
   (gdb) next
234        cout << elm;
   (gdb) info locals
   ptr_elem = std::unique_ptr<Element> containing 0x605040
   vec1 = std::vector of length 3, capacity 3 = {4, 5, 6}
   ptr_elem1 = std::unique_ptr<Element> containing 0x0
   ptr_elem2 = std::unique_ptr<Element> containing 0x6050e0
   elm = 0x0
   (gdb) print ptr_elem2.get()
   $2 = (Element *) 0x6050e0

   */

   //int * pr = new int{6};
   // unique_ptr<int> ptr{pr};
   // unique_ptr<int> ptr1{new int(3)};
   // unique_ptr<int> ptr_int = make_unique<int>(1); // initialize to 0
   // unique_ptr<int> ptr_int1 = make_unique<int>(6);
   // unique_ptr<float[]> ptr_floatArr{new float[5]};

   // for(int i = 0; i < 5; i++)
   //    cout << ptr_floatArr.get()[i] << endl;

   //if(heapAllocatedSize != 0)
   //   cout << " Memory leaks !!! size : " << heapAllocatedSize << " not freed." << endl;

   return 0;
}

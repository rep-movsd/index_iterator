# index_iterator
An iterator that wraps array/vector indices

std::vector is probably the most useful container, but it has one limitation - namely that iterators to a vector get invalidated when the vector reallocates memory in response to push_back() or resize() 
This is because vector<T>::iterator is simply a T* and is tied to an actual address

This iterator uses integer indices instead - so as long as your iterator points to within the array bounds, it is not invalidated.

To use this iterator class, simply include the requisite header and use the vibegin() and viend() global functions instead of begin() and end()

    #include "index_iterator/index_iterator.hpp"

    void fn(std::vector<int> v)
    {
      for(auto i = vibegin(v); i != viend(v); ++i)
      {
        // Do whatever you like with *i ... modifying the vector v in this loop won't cause invalidation and undefined behavior
      }
    }
  
The downside of this however is that there is extra an indirection when dereferencing it.
Measuring the performance of std::sort() on a vector with 100 million random int elements using this iterator produces the following result:

    Name                    Count                   Time(ms)                Average(ms)
    -----------------------------------------------------------------------------------
    Sort index_iter                 1                       8830                    8830
    Sort iterator                   1                       8487                    8487
    
This is about 4%, which is not too bad.
The timing code is provided by an RAII class Timer in timer/Timer.cpp - I use it for almost all my C++ programs.
You can find the documentation for that class in the README in that folder. 

The main program just performs a basic test and the test on std::sort() and is compiled with:

    g++ -O3 main.cpp timer/Timer.cpp
    
Note: 
In no way does this iterator avoid the basic problem of dangling references - an iterator points to a buffer, and if that buffer has been deallocated, dereferencing the iterator will cause UB.




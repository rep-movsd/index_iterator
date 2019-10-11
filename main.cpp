#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <random>

// function timer
#include "timer/Timer.h"

#include "viter/viter.hpp"


typedef std::uniform_int_distribution<mt19937::result_type> Dist;

void test1()
{
  std::cout << "Inserting 10 elements" << std::endl;
  
  vector<int> x;
  const int N = 10;
  for(int i = 0; i < N; ++i)
  {
    x.push_back(i);
  }
  
  std::copy(vibegin(x), viend(x), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;
  auto vii = vibegin(x) + 5;
  std::cout << "element at index 5: " << *vii << std::endl;
  
  std::cout << "Inserting 10 more" << std::endl;
  for(int i = N; i < N*2; ++i)
  {
    x.push_back(i);
  }
  
  std::copy(vibegin(x), viend(x), std::ostream_iterator<int>(std::cout, ","));
  std::cout << std::endl;
  std::cout << "element at index 5: " << *vii << std::endl;
  
  
  std::cout << "Inserting 10 elements" << std::endl;
}


void test_sort()
{
  // Generate zillion random ints 
  const size_t N = 100'000'000;
  std::random_device dev;
  std::mt19937 rng(dev());
  Dist dist(0, 10000);
  
  vector<int> x1, x2;
  x1.reserve(N);
  x2.reserve(N);

  for(int i = 0; i < N; ++i)
  {
    int k = dist(rng);
    x1.push_back(k);
    x2.push_back(k);
  }
  
  {
    Timer t("Sort with normal iterator");
    std::sort(begin(x1), end(x1));
    std::cout << x1[N/2] << std::endl;
  }  
  
  {
    Timer t("Sort with viter iterator");
    std::sort(vibegin(x2), viend(x2));
    std::cout << x2[N/2] << std::endl;
  }
}


int main()
{
  test();
  test_sort();
}
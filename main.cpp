#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <random>

// function timer
#include "timer/Timer.h"

#include "index_iterator/index_iterator.hpp"


typedef std::uniform_int_distribution<std::mt19937::result_type> Dist;

void dump_vec(std::vector<int> &x)
{
  std::copy(begin(x), end(x), std::ostream_iterator<int>(std::cout, ","));
  std::cout << '\n';
}

template<class V> void dump_index_iterator(V &v)
{
  std::cout << v.vec << '\n';
  std::cout << v.pos << "\n\n";
}

void test_basic()
{
  std::cout << "Inserting 10 elements" << '\n';
  
  std::vector<int> x;
  const int N = 10;
  for(int i = 0; i < N; ++i)
  {
    x.push_back(i);
  }
  
  std::copy(vibegin(x), viend(x), std::ostream_iterator<int>(std::cout, ","));
  std::cout << '\n';
  auto vii = vibegin(x) + 5;
  std::cout << "element at index 5: " << *vii << '\n';
  
  std::cout << "Inserting 10 more" << '\n';
  for(int i = N; i < N*2; ++i)
  {
    x.push_back(i);
  }
  
  dump_vec(x);
  std::cout << "element at index 5: " << *vii << "\n\n";
}


void test_sort()
{
  // Generate zillion random ints 
  const size_t N = 100'000'000;
  
  std::cout << "Generating " << N << " random elements\n";
  std::random_device dev;
  std::mt19937 rng(dev());
  Dist dist(0, N);
  
  std::vector<int> x1, x2;
  x1.reserve(N);
  x2.reserve(N);

  for(int i = 0; i < N; ++i)
  {
    int k = dist(rng);
    x1.push_back(k);
    x2.push_back(k);
  }
  
  {
    Timer t("Sort iterator");
    std::cout << "Sort with normal iterator\n";
    std::sort(std::begin(x1), std::end(x1));
  }  
  
  {
    Timer t("Sort index_iter");
    std::cout << "Sort with index_iterator\n";
    std::sort(vibegin(x2), viend(x2));
    std::cout << (std::is_sorted(std::begin(x2), std::end(x2)) ? "Success" : "Fail") << "\n\n";
  }
}


int main()
{
  test_basic();
  test_sort();
  
  Timer::dump();
}
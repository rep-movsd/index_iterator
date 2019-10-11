#include <vector>
#include <iterator>

template<class VEC> class viter
{
public:
  using size_type = typename VEC::size_type;
  using difference_type = typename VEC::difference_type;
  using value_type = typename VEC::value_type;
  using pointer	= typename VEC::pointer;
  using reference = typename VEC::reference;
  using iterator_category	= std::random_access_iterator_tag;
  
private:
  size_type pos;
  VEC* vec;
    
public:
  viter(VEC *vec = nullptr, size_type pos = 0): vec(vec), pos(pos) {}
  
  // Use array indexing for deref
  reference operator*() 
  {
    return (*vec)[pos];
  }
  
  // Standard boilerplate implementations for ++, --, + and -
  viter& operator++()   { ++pos; return *this; }
  viter operator++(int) { viter tmp(*this); operator++(); return tmp;}
  
  viter& operator--()   { --pos; return *this;}
  viter operator--(int) { viter tmp(*this); operator--();  return tmp;}
  
  viter& operator+(difference_type i) { pos += i; return *this;}
  viter& operator-(difference_type i) { pos -= i; return *this;}
  
  difference_type operator-(const viter& rhs) {return pos - rhs.pos;}
};

// begin and end viter makers
template<class VEC> viter<VEC> vibegin(VEC &vec)
{ 
  return viter<VEC>{&vec};
} 

template<class VEC> viter<VEC> viend(VEC &vec) 
{ 
  return viter<VEC>{&vec, vec.size()};
} 

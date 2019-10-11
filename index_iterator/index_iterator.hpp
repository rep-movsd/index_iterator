#include <vector>
#include <iterator>

template<class VEC> class index_iterator
{
public:
  using size_type = typename VEC::size_type;
  using difference_type = typename VEC::difference_type;
  using value_type = typename VEC::value_type;
  using pointer	= typename VEC::pointer;
  using reference = typename VEC::reference;
  using iterator_category	= std::random_access_iterator_tag;
  
  size_type pos;
  VEC* vec;
    
public:
  index_iterator(VEC *vec_ = nullptr, size_type pos_ = 0): vec(vec_), pos(pos_) {}
  
  // Use array indexing for deref
  reference operator*() {return (*vec)[pos];}
  
  // Standard boilerplate implementations for ++, --, + and -
  
  #define PREFIX(CODE) {CODE; return *this;}
  index_iterator& operator++()                         PREFIX((++pos))
  index_iterator& operator--()                         PREFIX((--pos))
  index_iterator& operator+=(difference_type i)        PREFIX((pos += i))
  index_iterator& operator-=(difference_type i)        PREFIX((pos -= i))
  #undef PREFIX
    
  index_iterator operator++(int)                       {index_iterator tmp(*this); ++pos; return tmp;}
  index_iterator operator--(int)                       {index_iterator tmp(*this); --pos; return tmp;}
  
  index_iterator operator+(difference_type i)          {return index_iterator(vec, pos+i);}
  index_iterator operator-(difference_type i)          {return index_iterator(vec, pos-i);}
 
  #define BIN_OP(OP) operator OP (const index_iterator& rhs) {return pos OP rhs.pos;}
  difference_type BIN_OP(-)
  bool            BIN_OP(<)
  bool            BIN_OP(!=)
  bool            BIN_OP(==)
  #undef BIN_OP

};

// begin and end index_iterator makers
template<class VEC> index_iterator<VEC> vibegin(VEC &vec)
{ 
  return index_iterator<VEC>{&vec};
} 

template<class VEC> index_iterator<VEC> viend(VEC &vec) 
{ 
  return index_iterator<VEC>{&vec, vec.size()};
} 

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
  index_iterator& operator++()                         {++pos; return *this;}
  index_iterator& operator--()                         {--pos; return *this;}

  index_iterator& operator+=(difference_type i)        {pos += i; return *this;}
  index_iterator& operator-=(difference_type i)        {pos -= i; return *this;}

  index_iterator operator++(int)                       {index_iterator tmp(*this); ++pos; return tmp;}
  index_iterator operator--(int)                       {index_iterator tmp(*this); --pos; return tmp;}
  
  index_iterator operator+(difference_type i)          {return index_iterator(vec, pos+i);}
  index_iterator operator-(difference_type i)          {return index_iterator(vec, pos-i);}
  
  difference_type operator-(const index_iterator& rhs) {return pos - rhs.pos;}
  bool operator<(const index_iterator& rhs)            {return pos < rhs.pos;}
  bool operator==(const index_iterator& rhs)           {return pos == rhs.pos;}
  bool operator!=(const index_iterator& rhs)           {return pos != rhs.pos;}

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

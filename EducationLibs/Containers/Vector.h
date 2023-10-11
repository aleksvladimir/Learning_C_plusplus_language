#pragma once
#include <stdexcept>

template<typename T>
class Vector
{
  T * buf_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
public:

  void push_back( const T& elem )
  {
    
  }
  void push_back( T && elem )
  {

  }
  void pop_back()
  {
    
  }
  size_t capacity() const noexcept
  {
    return capacity_;
  }
  size_t size() const noexcept
  {
    return size_;
  }
  T& at( size_t i ) 
  {
    if ( i < size() )
      return buf_[ i ];
    throw std::out_of_range("");
  }
  const T & at( size_t i ) const
  {
    if ( i < size() )
      return buf_[ i ];
    throw std::out_of_range();
  }
  bool empty() const noexcept
  {
    return size() == 0;
  }
  void reserve( size_t newCapacity ) noexcept
  {
    capacity_ = newCapacity;
  }
  void clear()
  {
    
  }
  void shrink_to_fit()
  {
    
  }
  void resize( size_t newSize ) noexcept
  {
    size_ = newSize;
  }
  void resize( size_t newSize, const T & val ) noexcept
  {
    size_ = newSize;
  }
};

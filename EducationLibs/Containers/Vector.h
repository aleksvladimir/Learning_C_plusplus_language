#pragma once
#include <memory>
#include <stdexcept>
#include <algorithm>

template<typename T>
class Vector
{
  T* data_ = nullptr;   // elements buffer
  size_t size_ = 0;     // current elements count
  size_t capacity_ = 0; // how many elements can fit
public:
  
  // 1,2,3 <- 4
  void push_back( const T& elem )
  {
    const auto hasAvailableQuantity = capacity_ > size_;
    if ( !hasAvailableQuantity )
    {
      capacity_ = std::max( 1u, capacity_ * 2 );
      auto p = new T[ capacity_ ];
      std::copy( data_, data_ + size_, p );
      delete[] data_;
      data_ = p;
    }
    size_++;
    data_[ size_ - 1 ] = elem;
  }
  void push_back( T && elem )
  {
    push_back( elem );
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
      return data_[ i ];
    throw std::out_of_range("");
  }
  const T & at( size_t i ) const
  {
    if ( i < size() )
      return data_[ i ];
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

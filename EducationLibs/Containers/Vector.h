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

  T* alloc( size_t newSize )
  {
    return newSize ? new T[ newSize ] : nullptr;
  }
  void realloc()
  {
    auto p = alloc( capacity_ );
    for ( int i = 0; i < size_; ++i )
      p[ i ] = std::forward<T>( data_[ i ] );
    delete[] data_;
    data_ = p;
  }

public:

  Vector() = default;
  Vector( size_t newSize )
  {
    data_ = alloc( capacity_ = size_ = newSize );
    std::fill( data_, data_ + size_, 0 );     // or memcpy
  }
  Vector( size_t newSize, T value )
  {
    data_ = alloc( capacity_ = size_ = newSize );
    std::fill( data_, data_ + size_, value ); // or memcpy
  }

  template<class U>
  void push_back( U && elem )
  {
    const auto hasAvailableQuantity = capacity_ > size_;
    if ( !hasAvailableQuantity )
    {
      capacity_ = std::max( 1u, capacity_ * 2 );
      realloc();
    }
    data_[ size_++ ] = std::forward<U>( elem );
  }
  void pop_back()
  {
    if ( size_ != 0 )
    {
      data_[ size_ - 1 ].~T();
      size_--;      
    }
  }
  size_t capacity() const noexcept
  {
    return capacity_;
  }
  size_t size() const noexcept
  {
    return size_;
  }
  T& operator [] ( size_t i ) noexcept
  {
    return data_[ i ];
  }
  const T & operator [] ( size_t i ) const noexcept
  {
    return data_[ i ];
  }
  T& back() noexcept
  {
    return data_[ size_ - 1 ];
  }
  const T& back() const noexcept
  {
    return data_[ size_ - 1 ];
  }
  T& at( size_t i ) 
  {
    if ( i < size_ )
      return data_[ i ];
    throw std::out_of_range("");
  }
  const T & at( size_t i ) const
  {
    if ( i < size_ )
      return data_[ i ];
    throw std::out_of_range();
  }
  bool empty() const noexcept
  {
    return size_ == 0;
  }
  void reserve( size_t newCapacity ) noexcept
  {
    if ( newCapacity > capacity_ )
    {
      capacity_ = newCapacity;
      realloc();
    }
  }
  void clear()
  {
    while ( size_ > 0 )
      pop_back();
  }
  void shrink_to_fit()
  {
    capacity_ = size_;
    realloc();
  }
  void resize( size_t newSize, const T & val = T() ) noexcept
  {
    while ( newSize < size_ )
      pop_back();
    if ( newSize > size_ )
    {
      if ( newSize > capacity_ )
        reserve( newSize );
      while ( newSize > size_ )
        push_back( val );
    }
  }
};

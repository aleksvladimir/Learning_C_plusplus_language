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

  Vector() = default;
  Vector( size_t newSize )
  {
    data_ = alloc( capacity_ = size_ = newSize );
    std::fill( data_, data_ + size_, 0 );
  }
  Vector( size_t newSize, T value )
  {
    data_ = alloc( capacity_ = size_ = newSize );
    std::fill( data_, data_ + size_, value );
  }
  Vector( std::initializer_list<T> i_list )
  {
    data_ = alloc( capacity_ = size_ = i_list.size() );
    std::copy( i_list.begin(), i_list.end(), data_ );
  }
  Vector( const Vector & other )
  {
    data_ = alloc( capacity_ = size_ = other.size_ );
    std::copy( other.data_, other.data_ + other.size_, data_ );
  }
  Vector( Vector && other )
  {
    other.swap( *this );
  }
  ~Vector()
  {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  bool operator == ( const Vector & other ) const
  {
    return std::equal( data_, data_ + size_, other.data_, other.data_ + other.size_ );
  }

  Vector& operator = ( const Vector& other )
  {
    resize( other.size_ );
    std::copy( other.data_, other.data_ + other.size_, data_ );
    return *this;
  }
  
  Vector& operator = ( Vector&& other )
  {
    Vector tmp_other( std::move( other ) );
    tmp_other.swap( this );
    return *this;
  }

  T* data()
  {
    return data_;
  }

  void swap( Vector & other ) noexcept
  {
    data_ = std::exchange( other.data_, data_ );
    size_ = std::exchange( other.size_, size_ );
    capacity_ = std::exchange( other.capacity_, capacity_ );
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
      data_[ --size_ ].~T();
  } 
  [[nodiscard]] size_t capacity() const noexcept
  {
    return capacity_;
  }
  [[nodiscard]] size_t size() const noexcept
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
  [[nodiscard]] const T& back() const noexcept
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
private:
  static T * alloc( size_t newSize )
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
};

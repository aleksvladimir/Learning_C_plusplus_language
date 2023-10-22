#pragma once
#include "Vector.h"

/**
 * \brief Deque
 * \tparam T - type_value
 */
template<typename T>
class Deque
{
  Vector<T> ** array_of_vectors = nullptr;
  Vector<T> * topVec = nullptr;
  Vector<T> * bottomVec = nullptr;
  size_t element_count_ = 0;
  size_t array_capacity_ = 0;
  const size_t DEFAULT_SIZE = 5;
  const size_t DEFAULT_VEC_SIZE = 3;

public:

  Deque() = default;
  Deque( size_t size, T& value = T() )
  {
    //todo
  }
  Deque( const Deque & other )
  {
    //todo
  }
  ~Deque()
  {
    //todo: implement copy and move constructor and operator to avoid double deletion
    delete[] array_of_vectors;
  }

  void push_back( const T & value )
  {
    if ( element_count_ == 0 )
    {
      array_capacity_ = DEFAULT_SIZE;
      array_of_vectors = new Vector<T>*[ array_capacity_ ];
      topVec = bottomVec = array_of_vectors[ array_capacity_ / 2 ] = new Vector<T>( DEFAULT_VEC_SIZE );
      topVec->operator[]( DEFAULT_VEC_SIZE / 2 ) = value;
      element_count_++;
    }
    //else
    //{ 
    //  tail_->next = p;
    //  p->prev = tail_;
    //  tail_ = p;
    //}
  }
//  void push_front( const T & value )
//  {
//    if ( size_++ == 0 )
//      head_ = tail_ = new Node<T>( value );
//    else
//    {
//      auto p = new Node<T>( value );
//      head_->prev = p;
//      p->next = head_;
//      head_ = p;
//    }
//  }
//  void pop_back()
//  {
//    auto prev = tail_->prev;
//    delete tail_;
//    tail_ = prev;
//    --size_;
//  }
//  void pop_front()
//  {
//    auto next = head_->next;
//    delete head_;
//    head_ = next;
//    --size_;
//  }
//  T & back()
//  {
//    return tail_->value;
//  }
//  const T & back() const
//  {
//    return tail_->value;
//  }
//  T & front()
//  {
//    return head_->value;
//  }
//  const T & front() const
//  {
//    return head_->value;
//  }
  [[nodiscard]] size_t size() const noexcept
  {
    return element_count_;
  }
//  void clear()
//  {
//    while ( tail_->prev )
//      pop_back();
//    delete head_;
//    --size_;
//  }
//  void reverse()
//  {
//    auto oldTail = tail_;
//    while ( head_ != tail_ )
//    {
//      tail_->prev = std::exchange( tail_->next, tail_->prev );
//      tail_ = tail_->next;
//    }
//    head_ = oldTail;
//  }
//
//private:
//  Node<T> * partition( Node<T> * first, Node<T> * last )
//  {
//    auto pivot = first;
//    auto front = first;
//    while ( front != nullptr && front != last )
//    {
//      if ( front->value < last->value )
//      {
//        pivot = first;
//        front->value = std::exchange( first->value, front->value );
//        first = first->next;
//      }
//      front = front->next;
//    }
//    last->value = std::exchange( first->value, last->value );
//    return pivot;
//  }
//  void sort( Node<T> * first, Node<T> * last )
//  {
//    if ( first == last )
//      return;
//
//    auto pivot = partition( first, last );
//    if ( pivot != nullptr && pivot->next != nullptr )
//      sort( pivot->next, last );
//
//    if ( pivot != nullptr && first != pivot )
//      sort( first, pivot );
//  }
//public:
//  void sort()
//  {
//    sort( head_, tail_ );
//  }
    
  size_t capacity() const noexcept
  {
    return array_capacity_ * DEFAULT_VEC_SIZE;
  }
  //T& operator [] ( size_t i ) noexcept
  //{
  //  return data_[ i ];
  //}
  //const T & operator [] ( size_t i ) const noexcept
  //{
  //  return data_[ i ];
  //}
  //T& back() noexcept
  //{
  //  return data_[ size_ - 1 ];
  //}
  //const T& back() const noexcept
  //{
  //  return data_[ size_ - 1 ];
  //}
  //T& at( size_t i ) 
  //{
  //  if ( i < element_count_ )
  //    return data_[ i ];
  //  throw std::out_of_range("");
  //}
  //const T & at( size_t i ) const
  //{
  //  if ( i < size_ )
  //    return data_[ i ];
  //  throw std::out_of_range();
  //}
  //bool empty() const noexcept
  //{
  //  return size_ == 0;
  //}
  
  //void shrink_to_fit()
  //{
  //  capacity_ = size_;
  //  realloc();
  //}
  //void resize( size_t newSize, const T & val = T() ) noexcept
  //{
  //  while ( newSize < size_ )
  //    pop_back();
  //  if ( newSize > size_ )
  //  {
  //    if ( newSize > capacity_ )
  //      reserve( newSize );
  //    while ( newSize > size_ )
  //      push_back( val );
  //  }
  //}
};

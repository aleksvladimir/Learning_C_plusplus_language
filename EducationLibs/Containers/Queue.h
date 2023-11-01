#pragma once
#include <deque>

/**
 * \brief FIFO
 * push(), pop(), size(), empty(), back(), front(), emplace()
 */
template<typename T, class Container = std::deque<T>> // list or deque
class Queue
{
  Container container_;

public:
  template<typename U>
  void push( U && value )
  {
    container_.push_back( std::forward<U>( value ) );
  }
  void pop()
  {
    container_.pop_front();
  }
  [[nodiscard]] size_t size() const noexcept
  {
    return container_.size();
  }
  [[nodiscard]] bool empty() const noexcept
  {
    return container_.empty();
  }
  T & back()
  {
    return container_.back();
  }
  T & front()
  {
    return container_.front();
  }
  template<class... Args>
  void emplace( Args&&... args )
  {
    container_.emplace_back( std::forward<Args>( args )... );
  }
};
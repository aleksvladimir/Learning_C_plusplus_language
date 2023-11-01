#pragma once
#include <deque>


/**
 * \brief
 * pop(), push(), size(), empty(), top(), emplace()
 */
template<typename T, class Container = std::deque<T>>
class Stack
{
  Container container_;

public:
  template<typename U>
  void push( U&& value )
  {
    container_.push_back( std::forward<U>( value ) );
  }
  void pop()
  {
    container_.pop_back();
  }
  [[nodiscard]] size_t size() const noexcept
  {
    return container_.size();
  }
  [[nodiscard]] bool empty() const noexcept
  {
    return container_.empty();
  }
  T& top()
  {
    return container_.back();
  }
  template<class... Args>
  void emplace( Args&&... args )
  {
    container_.emplace_back( std::forward<Args>( args )... );
  }
};
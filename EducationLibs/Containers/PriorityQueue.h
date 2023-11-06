#pragma once
#include <deque>


/**
 * \brief Head always MAX element
 * pop(), push(), size(), empty(), top(), emplace()
 */
template<
  class T,
  class Container = std::deque<T>,                             // vector or deque (Random Access Iterator)
  class Compare = std::less<typename Container::value_type>>
class PriorityQueue
{
  Container container_;

public:
  // O(log(N)) + complexity of Container::push_back
  template<typename U>
  void push( U && value )
  {
    container_.push_back( std::forward<U>( value ) );
    upSifting();
  }
  template<class... Args>
  void emplace( Args&&... args )
  {
    container_.emplace_back( std::forward<Args>( args )... );
    upSifting();
  }
  void pop()
  {
    if ( container_.empty() )
      return;
    if ( container_.size() > 1 )
      std::iter_swap( container_.begin(), container_.end() - 1 );
    container_.pop_back();
    downSifting();

  }
  [[nodiscard]] size_t size() const noexcept
  {
    return container_.size();
  }
  [[nodiscard]] bool empty() const noexcept
  {
    return container_.empty();
  }
  T & top()
  {
    return container_.front();
  }
private:
  static size_t getLeftIdx( size_t index )
  {
    return index * 2 + 1;
  }
  static size_t getRightIdx( size_t index )
  {
    return index * 2 + 2;
  }
  static size_t getParentIdx( size_t index )
  {
    return index == 0 ? 0 : ( index - 1 ) / 2;
  }
  void upSifting()
  {
    auto lastInsertIdx = container_.size() - 1;
    while ( lastInsertIdx != 0 )
    {
      auto lastInsertParentIndex = getParentIdx( lastInsertIdx );
      if ( container_[ lastInsertIdx ] > container_[ lastInsertParentIndex ] )
      {
        std::iter_swap( container_.begin() + lastInsertIdx, container_.begin() + lastInsertParentIndex );
        lastInsertIdx = lastInsertParentIndex;  // move to parent
      }
      else
        break;
    }
  }
  void downSifting()
  {
    auto parentIndex = 0;
    while ( parentIndex < container_.size() )
    {
      auto leftIndex = getLeftIdx( parentIndex );
      auto rightIndex = getRightIdx( parentIndex );
      const bool needSwapLeft = isRightNodeGreater( leftIndex, rightIndex ) ? false :
                                needSwapParentWith( parentIndex, leftIndex );
      const bool needSwapRight = needSwapParentWith( parentIndex, rightIndex );
      if ( needSwapLeft )
      {
        std::iter_swap( container_.begin() + parentIndex, container_.begin() + leftIndex );
        parentIndex = leftIndex;
      }
      else if ( needSwapRight )
      {
        std::iter_swap( container_.begin() + parentIndex, container_.begin() + rightIndex );
        parentIndex = rightIndex;
      }
      else
        break;
    }
  }
  [[nodiscard]] bool isRightNodeGreater( size_t leftIndex, size_t rightIndex ) const
  {
    return leftIndex < container_.size() && rightIndex < container_.size() &&
           container_[ leftIndex ] < container_[ rightIndex ];
  }
  [[nodiscard]] bool needSwapParentWith( size_t parentIndex, size_t nodeIndex ) const
  {
    return nodeIndex < container_.size() && container_[ parentIndex ] < container_[ nodeIndex ];
  }
};
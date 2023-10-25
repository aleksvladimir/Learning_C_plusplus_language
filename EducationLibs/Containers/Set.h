#pragma once

/**
 * \brief 
 * \tparam T
 *
 * // todo:
 * - insert(), erase(), find()
 * - clear(), size(), empty()
 */
template<typename T>
class Set
{
  struct Node
  {
    template<typename U>
    explicit Node( U&& value ) : data( std::forward<U>( value ) ){}
    T data = T{};
    Node * left = nullptr;
    Node * right = nullptr;
  };

  Node* root_ = nullptr;
  size_t size_ = 0;

public:
  Set() = default;
  Set( std::initializer_list<T> init )
  {
    //todo
  }
  ~Set()
  {
    clear();
  }
  
  /**
   * \brief Erases all elements from the container. After this call, size() returns zero.
   * Invalidates any references, pointers, or iterators referring to contained elements.
   * Any past-the-end iterator remains valid.
   * \Complexity
   * Linear in the size of the container, i.e., the number of elements.
   */
  void clear()
  {
    //todo
  }
  size_t size()
  {
    return 0;
  }
  template<typename U>
  void insert( U&& data )
  {
    if ( empty() )
      root_ = new Node( std::forward<U>( data ) );
    else if ( insert( root_, data ) )
      size_++;
  }
  [[nodiscard]] bool insert( Node* node, const T & data )
  {
    return false; // todo
  }
  [[nodiscard]] bool empty() const noexcept
  {
    return size_ == 0;
  }
};

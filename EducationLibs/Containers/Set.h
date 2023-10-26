#pragma once

/**
 * \brief 
 * \tparam T
 *
 * size(), insert(), empty(), find()
 *
 * // todo:
 * - erase()
 * - clear() 
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
  template<typename U>
  size_t erase( U && data )
  {
    //todo
    return 0u;
  }
  Node* find( const T & data )
  {
    return empty() ? nullptr : find( root_, data );
  }
  Node* find( Node* & node, const T & data )
  {
    if ( data < node->data )
      return node->left ? find( node->left, data ) : nullptr;
    if ( data > node->data )
      return node->right ? find( node->right, data ) : nullptr;
    return node;
  }
  [[nodiscard]] size_t size() const noexcept
  {
    return size_;
  }
  template<typename U>
  void insert( U&& data )
  {
    if ( empty() )
      root_ = new Node( std::forward<U>( data ) );
    else if ( !insert( root_, std::forward<U>( data ) ) )
      return;
    size_++;
  }
  template<typename U>
  [[nodiscard]] bool insert( Node* node, U && data )
  {
    if ( data < node->data )
      return node->left ? insert( node->left, data ) : node->left = new Node( std::forward<U>( data ) );
    return node->right ? insert( node->right, data ) : node->right = new Node( std::forward<U>( data ) );
  }
  [[nodiscard]] bool empty() const noexcept
  {
    return size_ == 0;
  }
};

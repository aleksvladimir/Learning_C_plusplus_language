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
    if ( !empty() )
    {
      removeNode( root_ );
      size_ = 0;
    }
  }
private:
  void removeNode( Node*& node )
  {
    if ( node )
    {
      removeNode( node->left );
      removeNode( node->right );
      delete node;
      node = nullptr;
    }
  }
public:
  template<typename U>
  [[nodiscard]] size_t erase( U && data )
  {
    size_t res = 0u;
    if ( !empty() )
    {
      Node*& delNode = find( root_, data );
      if ( !delNode )
        return res;

      if ( !delNode->right )
      {
        if ( delNode->left )
        {
          std::swap( delNode->data, delNode->left->data );
          delete delNode->left;
          delNode->left = nullptr;
        }
        else
        {
          delete delNode;
          delNode = nullptr;
        }
      }
      else
      {
        // 1 step to right and find node with minimal value,
        // if all children is null then
        //   change current value with minimal value
        //   and destroy found node
        Node* leftMost = delNode->right;
        while( leftMost->left )
          leftMost = leftMost->left;
        std::swap( delNode->data, leftMost->data );
        if ( leftMost->right )
        {
          std::swap( leftMost->data, leftMost->right->data );
          delete leftMost->right;
          leftMost->right = nullptr;
        }
        else
        {
          delete leftMost;
          leftMost = nullptr;
        }
      }
      size_--;
      res = 1u;
    }
    return res;
  }
  Node*& find( const T & data )
  {
    if ( !empty() )
      return find( root_, data );
    return root_;
  }
private:
  Node*& find( Node* & node, const T & data )
  {
    if ( node == nullptr )
      return node;
    if ( data < node->data )
      return find( node->left, data );
    if ( data > node->data )
      return find( node->right, data );
    return node;
  }
public:
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

#pragma once
#include <stdexcept>

// taken from https://github.com/thaliaarchi/deque/tree/master#circular-array-algorithm
namespace circular_array_algorithm
{
  /**
   * \brief Deque with circular array algorithm (not full implementation)
   * \tparam T - type_value
   *
   * example:
   * deque.push_back(1);    // [ 1 . . . . ]
   * deque.push_front(0);   // [ 1 . . . 0 ] - Wrap elements
   * deque.push_front(1);   // [ 1 . . 1 0 ]
   * deque.push_front(2);   // [ 1 . 2 1 0 ]
                            //       ^- front
   */
  template<typename T>
  class Deque
  {
    T * container_;
    size_t capacity_;
    size_t size_;
    size_t front_;

    static const size_t DEFAULT_CAPACITY = 64;

  public:

    Deque() : Deque( DEFAULT_CAPACITY ) {}
    Deque( size_t capacity )
      : container_( new T[ capacity ] ), capacity_( capacity ), size_( 0 ), front_( 0 ) {}
    ~Deque()
    {
      delete[] container_;
    }
    void push_front( T value )
    {
      front_ = ( front_ - 1 ) % capacity_;
      container_[ front_ ] = value;
      size_++;
      reallocate();
    }
    void push_back( T value )
    {
      container_[ ( front_ + size_ ) % capacity_ ] = value;
      size_++;
      reallocate();
    }
    void reallocate() {
      if ( size_ < capacity_ )
        return;
      reserve( capacity_ * 2 );
    }
    void reserve( size_t capacity )
    {
      if ( capacity <= capacity_ ) 
        return;

      T * new_container = new T[ capacity ];
      for ( size_t i = 0; i < size_; i++ ) 
        new_container[ i ] = container_[ ( i + front_ ) % capacity_ ];

      delete[] container_;
      container_ = new_container;
      capacity_ = capacity;
      front_ = 0;
    }
    [[nodiscard]] size_t size() const noexcept
    {
      return size_;
    }
    T & at( size_t index )
    {
      if ( index >= size_ )
        out_of_range( "index", index, ">=", "this->size()", size_ );

      return operator[]( index );
    }
    T & operator[]( size_t index )
    {
      return container_[ ( front_ + index ) % capacity_ ];
    }
    [[nodiscard]] size_t capacity() const noexcept
    {
      return capacity_;
    }
    static void out_of_range( const char * id_1, size_t value_1,
                              const char * op, const char * id_2, size_t value_2 )
    {
      std::ostringstream out;
      out << "Deque: " << id_1 << " (which is " << value_1 << ") "
        << op << " " << id_2 << " (which is " << value_2 << ")";
      throw std::out_of_range( out.str() );
    }
  };  
}

namespace like_linked_list
{
  /*
   *  push_back(), pop_back(), push_front(), clear(), size(), resize(), empty(), pop_front()
   *  at(), []
   *  
   */

   /**
    * \brief Deque by Doubly Linked List
    * \tparam T - type_value
    */
  template<typename T>
  class Deque
  {
    template<typename T>
    struct Node
    {
      Node() = default;
      Node( T val ) noexcept : value( val ) {}
      T value = T();
      Node<T> * next = nullptr;
      Node<T> * prev = nullptr;
    };

    Node<T> * head_ = nullptr;
    Node<T> * tail_ = nullptr;
    size_t size_ = 0;

  public:

    Deque() = default;
    Deque( size_t newSize, T && value = T() )
    {
      resize( newSize, value );
    }
    Deque( const Deque & other )
    {
      head_ = other.head_;
      tail_ = other.tail_;
      size_ = other.size_;
    }
    ~Deque()
    {
      if ( size() )
        clear();
    }
    void push_back( const T & value )
    {
      if ( size_++ == 0 )
        head_ = tail_ = new Node<T>( value );
      else
      {
        auto p = new Node<T>( value );
        tail_->next = p;
        p->prev = tail_;
        tail_ = p;
      }
    }
    void push_front( const T & value )
    {
      if ( size_++ == 0 )
        head_ = tail_ = new Node<T>( value );
      else
      {
        auto p = new Node<T>( value );
        head_->prev = p;
        p->next = head_;
        head_ = p;
      }
    }
    void pop_back()
    {
      auto prev = tail_->prev;
      delete tail_;
      tail_ = prev;
      --size_;
    }
    void pop_front()
    {
      auto next = head_->next;
      delete head_;
      head_ = next;
      --size_;
    }
    T & back()
    {
      return tail_->value;
    }
    const T & back() const
    {
      return tail_->value;
    }
    T & front()
    {
      return head_->value;
    }
    const T & front() const
    {
      return head_->value;
    }
    [[nodiscard]] size_t size() const noexcept
    {
      return size_;
    }
    bool empty() const noexcept
    {
      return size_ == 0;
    }
    void clear()
    {
      while ( tail_->prev )
        pop_back();
      delete head_;
      --size_;
    }
    void resize( size_t newSize, const T & val = T() )
    {
      while ( newSize < size_ )
        pop_back();
      while ( newSize > size_ )
        push_back( val );
    }
    // O(N)!!!
    T & at( size_t i )
    {
      return findNode( i )->value;
    }
    // O(N)!!!
    const T & at( size_t i ) const
    {
      return findNode( i )->value;
    }
    // O(N)!!!
    T & operator [] ( size_t i )
    {
      return findNode( i )->value;
    }
    // O(N)!!!
    const T & operator [] ( size_t i ) const
    {
      return findNode( i )->value;
    }

  private:
    Node<T>* findNode( size_t i )
    {
      if ( i >= size_ )
        throw std::out_of_range( "" );

      auto cnt = 0u;
      Node<T> * node = head_;
      while ( node->next && cnt < i )
      {
        node = node->next;
        cnt++;
      }
      return node;
    }
    Node<T> const * findNode( size_t i ) const
    {
      if ( i >= size_ )
        throw std::out_of_range( "" );

      auto cnt = 0u;
      Node<T> * node = head_;
      while ( node->next && cnt < i )
      {
        node = node->next;
        cnt++;
      }
      return node;
    }
  };
}

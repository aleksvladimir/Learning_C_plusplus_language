#pragma once

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

namespace dec_as_doubly_linked_list
{
  /*
   * todo:
   *  push_back(), pop_back(), push_front(), pop_front()
   *  clear(), resize(), shrink_to_fit()
   *  size(), empty(), capacity(), at()
   */
}

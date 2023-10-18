#pragma once

/**
 * \brief Linked list
 * \tparam T - type_value
 * todo:
 *  sort()
 */
template<typename T>
class List
{
  template<typename T>
  struct Node
  {
    Node() = default;
    Node( T val ) noexcept : value( val ) {}
    T value = T();
    Node * next = nullptr;
    Node * prev = nullptr;
  };

  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  size_t size_ = 0;

public:

  List() = default;
  List( size_t size, T& value = T() )
  {
    //todo
  }
  List( const List& other )
  {
    //todo
  }
  ~List()
  {
    //todo
  }
  void push_back( const T& value )
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
  T& back()
  {
    return tail_->value;
  }
  const T& back() const
  {
    return tail_->value;
  }
  T& front()
  {
    return head_->value;
  }
  const T& front() const
  {
    return head_->value;
  }
  [[nodiscard]] size_t size() const noexcept
  {
    return size_;
  }
  bool empty() const noexcept
  {
    return head_ == tail_;
  }
  void clear()
  {
    while ( tail_->prev )
      pop_back();
    delete head_;
    --size_;
  }
  void reverse()
  {
    auto oldTail = tail_;
    while ( head_ != tail_ )
    {
      tail_->prev = std::exchange( tail_->next, tail_->prev );
      tail_ = tail_->next;
    }
    head_ = oldTail;
  }
};

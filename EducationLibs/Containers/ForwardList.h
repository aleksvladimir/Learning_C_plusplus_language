#pragma once

/**
 * \brief Singly Linked List
 * \tparam T - type_value
 */
template<typename T>
class ForwardList
{
  template<typename T>
  struct Node
  {
    Node() = default;
    Node( T val ) noexcept : value( val ) {}
    T value = T();
    Node<T> * next = nullptr;
  };

  Node<T>* head_ = nullptr;
  size_t size_ = 0;

public:

  ForwardList() = default;
  ForwardList( size_t size, T& value = T() )
  {
    //todo
  }
  ForwardList( const ForwardList & other )
  {
    //todo
  }
  ~ForwardList()
  {
    //todo
  }
  void push_front( const T & value )
  {
    if ( size_++ == 0 )
      head_ = new Node<T>( value );
    else
    {
      auto p = new Node<T>( value );
      p->next = head_;
      head_ = p;
    }    
  }
  void pop_front()
  {
    auto next = head_->next;
    delete head_;
    head_ = next;
    --size_;
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
    return size_ == 0;
  }
  void clear()
  {
    while ( head_->next )
      pop_front();
    delete head_;
    --size_;
  }
  void reverse()
  {
    Node<T> * p = nullptr;
    while ( head_->next )
      p = std::exchange( head_, std::exchange( head_->next, p ) );
    head_->next = p;
  }
};

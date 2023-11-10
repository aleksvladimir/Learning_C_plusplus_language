#pragma once
#include "BaseStrongPtr.h"

template<typename T, typename D = DefDeleter<T> >
class AutoPtr : public BaseStrongPtr<T, D>
{
public:

  explicit AutoPtr( typename BaseStrongPtr<T>::value_type_t * ptr = nullptr ) noexcept : BaseStrongPtr( ptr ) {}
  AutoPtr( AutoPtr& other ) noexcept : BaseStrongPtr( other.release() ) {}
  AutoPtr& operator = ( AutoPtr& other ) noexcept
  {
    reset( other.release() );
    return *this;
  }
  ~AutoPtr()
  {
    this->m_deleter( this->myPtr_ );
  }
  typename BaseStrongPtr<T>::value_type_t * release() noexcept
  {
    auto tmp = this->myPtr_;
    this->myPtr_ = nullptr;
    return tmp;
  }
  void reset( typename BaseStrongPtr<T>::value_type_t * ptr = nullptr ) noexcept
  {
    if ( ptr != this->myPtr_ )
      this->m_deleter( this->myPtr_ );
    this->myPtr_ = ptr;
  }
};

// protect from UB
template<>
class AutoPtr<void>
{
  AutoPtr() = delete;
};
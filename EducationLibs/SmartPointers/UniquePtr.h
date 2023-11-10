#pragma once
#include "BaseStrongPtr.h"
#include "HelperClass\Uncopyable.h"

template<typename T, typename D = DefDeleter<T> >
class UniquePtr : public BaseStrongPtr<T,D>, Uncopyable
{
public:

  explicit UniquePtr( typename BaseStrongPtr<T>::value_type_t * ptr = nullptr ) noexcept : BaseStrongPtr( ptr ) {}
  UniquePtr( UniquePtr && ptr ) noexcept
  {
    this->myPtr_ = ptr.release();
  }
  UniquePtr & operator = ( UniquePtr && ptr )
  {
    reset( ptr.release() );
    return *this;
  }
  ~UniquePtr()
  {
    this->m_deleter( this->myPtr_ );
  }

  typename BaseStrongPtr<T>::value_type_t * release() noexcept
  {
    auto tmp = this->myPtr_;
    this->myPtr_ = nullptr;
    return tmp;
  }
  void reset( typename BaseStrongPtr<T>::value_type_t * ptr = nullptr )
  {
    if ( ptr != this->myPtr_ )
      this->m_deleter( this->myPtr_ );
    this->myPtr_ = ptr;
  }
};

// protect from UB
template<>
class UniquePtr<void>
{
  UniquePtr() = delete;
};

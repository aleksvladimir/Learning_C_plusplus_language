#pragma once
#include "BaseStrongPtr.h"

template<class T>
class AutoPtr : public BaseStrongPtr<T>
{
public:

  explicit AutoPtr( T* ptr = nullptr ) noexcept : BaseStrongPtr( ptr ) {}
  AutoPtr( AutoPtr& other ) noexcept : BaseStrongPtr( other.release() ) {}
  AutoPtr& operator = ( AutoPtr& other ) noexcept
  {
    reset( other.release() );
    return *this;
  }
  ~AutoPtr()
  {
    delete myPtr_;
  }
  T* release() noexcept
  {
    auto tmp = myPtr_;
    myPtr_ = nullptr;
    return tmp;
  }
  void reset( T* ptr = nullptr ) noexcept
  {
    if ( ptr != myPtr_ )
      delete myPtr_;
    myPtr_ = ptr;
  }
};

// protect from UB
template<>
class AutoPtr<void>
{
  AutoPtr() = delete;
};
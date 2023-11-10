#pragma once
#include "BaseStrongPtr.h"
#include "HelperClass\Uncopyable.h"

template<class T>
class UniquePtr : public BaseStrongPtr<T>, Uncopyable
{
public:

  explicit UniquePtr( T * ptr = nullptr ) : BaseStrongPtr( ptr ) {}
  UniquePtr( UniquePtr && ptr )
  {
    myPtr_ = ptr.release();
  }
  UniquePtr & operator = ( UniquePtr && ptr )
  {
    reset( ptr.release() );
    return *this;
  }
  ~UniquePtr()
  {
    delete myPtr_;
  }

  T * release()
  {
    auto tmp = myPtr_;
    myPtr_ = nullptr;
    return tmp;
  }
  void reset( T * ptr = nullptr )
  {
    if ( ptr != myPtr_ )
      delete myPtr_;
    myPtr_ = ptr;
  }
};

// protect from UB
template<>
class UniquePtr<void>
{
  UniquePtr() = delete;
};

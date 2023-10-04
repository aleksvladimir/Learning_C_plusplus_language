#pragma once
#include "BaseStrongPtr.h"

template<class T>
class UniquePtr : public BaseStrongPtr<T>
{
public:

  // default_ctr
  UniquePtr( T * ptr = nullptr ) : BaseStrongPtr( ptr ) {}

  // copy_ctr
  UniquePtr( const UniquePtr & ptr ) = delete;

  // copy_operator
  UniquePtr & operator = ( UniquePtr & ptr ) = delete;

  // move_ctr
  UniquePtr( UniquePtr && ptr )
  {
    myPtr_ = ptr.release();
  }

  // move_operator
  UniquePtr & operator = ( UniquePtr && ptr )
  {
    myPtr_ = ptr.release();
    return *this;
  }

  // dtr
  ~UniquePtr()
  {
    delete myPtr_;
  }

  // release
  T * release()
  {
    auto tmp = myPtr_;
    myPtr_ = nullptr;
    return tmp;
  }

  // reset
  void reset( T * ptr = nullptr )
  {
    if ( ptr != myPtr_ )
      delete myPtr_;
    myPtr_ = ptr;
  }
};

#pragma once
#include "BaseStrongPtr.h"

template<class T>
class AutoPtr : public BaseStrongPtr<T>
{
public:

  // default_ctr
  AutoPtr( T * ptr = nullptr ) : BaseStrongPtr( ptr ) {}

  // copy_ctr
  AutoPtr( AutoPtr<T> & autoPtr )
  {
    myPtr_ = autoPtr.release();
  }

  // copy_operator
  AutoPtr<T> & operator = ( AutoPtr<T> & right )
  {
    myPtr_ = right.release();
    return *this;
  }

  // dtr
  ~AutoPtr()
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

#pragma once

#include "SharedPtr.h"

template<class T>
class WeakPtr
{
  T * myPtr_ = nullptr;
  int * rep_use_ = nullptr;

public:

  // default_ctr nullptr
  WeakPtr() = default;
  ~WeakPtr() = default;

  // copy_ctr weak-weak
  WeakPtr( const WeakPtr<T> & weakPtr )
  {
    // TODO:
  }

  // copy_ctr weak-make_shared
  WeakPtr( const SharedPtr<T> & sharedPtr )
  {
    // TODO:
  }

  // move_ctr
  WeakPtr( WeakPtr<T> && weakPtr )
  {
    // TODO:
  }

  // copy_operator weak-weak
  WeakPtr<T> & operator = ( WeakPtr<T> & right )
  {
    return *this; // TODO:
  }

  // copy_operator weak-shared
  WeakPtr<T> & operator = ( SharedPtr<T> & right )
  {
    return *this; // TODO:
  }

  // move_operator
  WeakPtr<T> & operator = ( WeakPtr<T> && weakPtr )
  {
    return *this; // TODO:
  }

  // use_count
  long use_count()
  {
    return 0; // TODO:
  }

  // expired
  bool expired()
  {
    return use_count() == 0;
  }

  // reset
  void reset()
  {
    // TODO:
  }

  // lock 
  SharedPtr<T> lock()
  {
    SharedPtr<T> shr_ptr;
    const bool isIncrSuccess = rep_use_ && *rep_use_ != 0;
    if ( isIncrSuccess ) {
      ++( *rep_use_ );
      // TODO:
      //shr_ptr.myPtr_ = myPtr_;
      //shr_ptr.rep_use_ = rep_use_;
    }

    return shr_ptr;
  }
};

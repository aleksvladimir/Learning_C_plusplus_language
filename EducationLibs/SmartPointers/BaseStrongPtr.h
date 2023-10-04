#pragma once

template<class T>
class BaseStrongPtr
{
protected:
  T * myPtr_ = nullptr;

public:

  // default_ctr
  BaseStrongPtr( T * ptr = nullptr ) : myPtr_( ptr ) {}

  // get
  T * get()
  {
    return myPtr_;
  }

  // *
  T & operator * ()
  {
    return *get();
  }

};

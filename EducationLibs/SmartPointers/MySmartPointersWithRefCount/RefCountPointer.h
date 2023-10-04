#pragma once

/**
 * \brief Simple auto keeper of the number of reference to one memory
 */
template<class T>
class RefCountPointer
{
private:
  T * pointer;

public:

  RefCountPointer( T * p ) : pointer( p )
  {
    pointer->Grab();
  }


  RefCountPointer( const RefCountPointer<T> & cp ) : pointer( cp.pointer )
  {
    pointer->Grab();
  }

  RefCountPointer<T> & operator = ( const RefCountPointer<T> & cp )
  {
    if ( this == &cp ) return *this;
    pointer->Release();
    pointer = cp.pointer;
    pointer->Grab();
    return *this;
  }

  ~RefCountPointer()
  {
    pointer->Release();
  }

  T * operator -> ()
  {
    return pointer;
  }
};

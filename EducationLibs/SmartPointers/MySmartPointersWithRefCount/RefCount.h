#pragma once

/**
 * \brief Simple keeper of the number of reference to one memory
 */
class RefCount
{
protected:
  unsigned long count;  // ref count
public:
  RefCount() : count( 0 ) {}
  RefCount( RefCount & ) : count( 0 ) {}
  RefCount & operator = ( const RefCount & )
  {
    return *this; // doesn't change 
  }
  virtual ~RefCount(){} // workpiece
  void Grab() { count++; }
  void Release()
  {
    if ( count > 0 ) 
      count--;
    if ( count == 0 ) 
      delete this;
  }
};

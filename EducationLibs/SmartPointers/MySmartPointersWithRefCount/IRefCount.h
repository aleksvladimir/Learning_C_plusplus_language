#pragma once

#include "RefCountPointer.h"
#include "RefCount.h"

/**
 * \brief Interface for simple keeper of the number of reference to one memory with
 *        protect from artful user - he can't create IRefCount without RefCountPointer
 */
class IRefCount : public RefCount
{
protected:
  IRefCount() = default;

public:

  // user can't create IRefCount without RefCountPointer
  static RefCountPointer<IRefCount> make()
  {
    return RefCountPointer<IRefCount>( new IRefCount() );
  }
};

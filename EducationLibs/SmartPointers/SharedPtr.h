#pragma once
#include "BaseStrongPtr.h"

// Simple implementation of SharedPtr
template<class T>
class SharedPtr : public BaseStrongPtr<T>
{
  int* rep_use_ = nullptr;

public:

  // default_ctr
  SharedPtr( T* ptr = nullptr ) : BaseStrongPtr( ptr )
  {
    rep_use_ = new int( 0 );
    if ( ptr )
      *rep_use_ = 1;
  }

  // copy_ctr
  SharedPtr( SharedPtr & right )
  {
    myPtr_ = right.myPtr_;
    ++( *right.rep_use_ );
    rep_use_ = right.rep_use_;
  }

  // copy_operator
  SharedPtr & operator = ( SharedPtr & right )
  {
    bool isOwner = myPtr_ == right.myPtr_;
    if ( !isOwner )
      ( *this ).~SharedPtr(); // clear self memory with check rep_use

    myPtr_ = right.myPtr_;
    ++( *right.rep_use_ );
    rep_use_ = right.rep_use_;
    return *this;
  }

  // move_ctr
  SharedPtr( SharedPtr && right )
  {
    myPtr_ = right.myPtr_;
    rep_use_ = right.rep_use_;
    right.myPtr_ = nullptr;
    right.rep_use_ = nullptr;
  }

  // move_operator
  SharedPtr & operator = ( SharedPtr && right )
  {
    // TODO: SharedPtr( std::move( right ) ).swap( *this );
    // TODO: void swap( SharedPtr &  )

    bool isOwner = myPtr_ == right.myPtr_;
    if ( !isOwner )
      ( *this ).~SharedPtr(); // clear self memory with check rep_use
    
    myPtr_ = right.myPtr_;
    rep_use_ = right.rep_use_;
    right.myPtr_ = nullptr;
    right.rep_use_ = nullptr;
    if ( isOwner )
      --( *rep_use_ );  // decrement rep_use when does absorption occur
    return *this;
  }

  // dtr
  ~SharedPtr()
  {
    if ( rep_use_ && 
         ( *rep_use_ == 0 ||
         --( *rep_use_ ) == 0 ) )
    {
      delete rep_use_;
      rep_use_ = nullptr;
      delete myPtr_;
      myPtr_ = nullptr;
    }
  }

  // reset
  void reset()
  {
    ( *this ).~SharedPtr();
    rep_use_ = nullptr;
    myPtr_ = nullptr;
  }

  // strong ref count (use)
  long use_count() const
  {
    return rep_use_ ? *rep_use_ : 0;
  }
};
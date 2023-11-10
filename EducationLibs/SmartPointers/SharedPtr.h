#pragma once
#include "BaseStrongPtr.h"

// Simple implementation of SharedPtr
template<typename T, typename D = DefDeleter<T> >
class SharedPtr : public BaseStrongPtr<T,D>
{
  int* rep_use_ = nullptr;

public:

  // default_ctr
  SharedPtr( typename BaseStrongPtr<T>::value_type_t* ptr = nullptr ) : BaseStrongPtr( ptr )
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
    const bool isOwner = this->myPtr_ == right.myPtr_;
    if ( !isOwner )
      ( *this ).~SharedPtr(); // clear self memory with check rep_use

    this->myPtr_ = right.myPtr_;
    ++( *right.rep_use_ );
    rep_use_ = right.rep_use_;
    return *this;
  }

  // move_ctr
  SharedPtr( SharedPtr && right ) noexcept
  {
    this->myPtr_ = right.myPtr_;
    rep_use_ = right.rep_use_;
    right.myPtr_ = nullptr;
    right.rep_use_ = nullptr;
  }

  // move_operator
  SharedPtr & operator = ( SharedPtr && right )
  {
    // TODO: SharedPtr( std::move( right ) ).swap( *this );
    // TODO: void swap( SharedPtr &  )

    bool isOwner = this->myPtr_ == right.myPtr_;
    if ( !isOwner )
      ( *this ).~SharedPtr(); // clear self memory with check rep_use
    
    this->myPtr_ = right.myPtr_;
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
      this->m_deleter( rep_use_ );
      rep_use_ = nullptr;
      this->m_deleter( this->myPtr_ );
      this->myPtr_ = nullptr;
    }
  }

  // reset
  void reset()
  {
    ( *this ).~SharedPtr();
    rep_use_ = nullptr;
    this->myPtr_ = nullptr;
  }

  // strong ref count (use)
  [[nodiscard]] long use_count() const
  {
    return rep_use_ ? *rep_use_ : 0;
  }
};

// protect from UB
template<>
class SharedPtr<void>
{
  SharedPtr() = delete;
};

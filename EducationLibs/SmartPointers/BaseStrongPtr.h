#pragma once

template<class T>
class BaseStrongPtr
{
public:
  BaseStrongPtr( T* ptr = nullptr ) : myPtr_( ptr ) {}
  T* get() const noexcept
  {
    return myPtr_;
  }
  T& operator*() const noexcept
  {
    return *get();
  }

protected:
  T* myPtr_ = nullptr;
};

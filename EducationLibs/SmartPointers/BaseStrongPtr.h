#pragma once

template<typename T>
struct DefDeleter
{
  void operator ()( T * ptr )
  {
    delete ptr;
  }
};

template<typename T>
struct DefDeleter<T[]>
{
  void operator ()( T * ptr )
  {
    delete[] ptr;
  }
};

template<class T, typename D = DefDeleter<T> >
class BaseStrongPtr
{
public:
  using value_type_t = std::remove_extent_t<T>;
  using deleter_type_t = D;

  BaseStrongPtr( value_type_t * ptr = nullptr ) noexcept : myPtr_( ptr ) {}
  value_type_t * get() const noexcept
  {
    return myPtr_;
  }
  value_type_t & operator*() const noexcept
  {
    return *get();
  }

protected:
  value_type_t * myPtr_ = nullptr;
  deleter_type_t m_deleter;
};

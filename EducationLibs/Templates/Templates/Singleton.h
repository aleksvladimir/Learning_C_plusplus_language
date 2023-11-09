struct NonCopyable
{
  NonCopyable( const NonCopyable & ) = delete;
  NonCopyable & operator=( const NonCopyable & ) = delete;
protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

struct NonMoveable
{
  NonMoveable( NonMoveable && ) = delete;
  NonMoveable & operator=( const NonMoveable & ) = delete;
protected:
  NonMoveable() = default;
  ~NonMoveable() = default;
};

template<typename T>
struct Singleton : private NonCopyable, private NonMoveable
{
  static T & getInstance()
  {
    static T instance;
    return instance;
  }
protected:
  Singleton() = default;
};

struct FileManager : Singleton<FileManager>
{
  int val;  // для проверки, что память всегда одна и та же
};

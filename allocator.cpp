//
// Created by Aaron Berry on 4/21/21.
//

#include "iostream"
#include <new>

template <class T>
struct RemoveConst
{
  typedef T type;
};

template <class T>
struct RemoveConst<const T>
{
  typedef T type;
};

template<typename T>
class Allocator {
 public :
  //    typedefs
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

 public :
  //    convert an allocator<T> to allocator<U>
  template<typename U>
  struct rebind {
    typedef Allocator<U> other;
  };

 public :
  explicit Allocator() {}
  ~Allocator() {}
  explicit Allocator(Allocator const&) {}
  template<typename U>
  explicit Allocator(Allocator<U> const&) {}

  //    address
  pointer address(reference r) { return &r; }
//const_pointer address(const_reference r) { return &r; }

  //    memory allocation
  pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = nullptr) {
    return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T)));
  }
  void deallocate(pointer p, size_type) {
    ::operator delete(p);
  }

  //    size
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  //    construction/destruction
  void construct(pointer p, const T& t) { new(const_cast<typename RemoveConst<T>::type*>(p)) T(t); }
  void destroy(pointer p) { p->~T(); }

  bool operator==(Allocator const&) { return true; }
  bool operator!=(Allocator const& a) { return !operator==(a); }
};    //    end of class Allocator


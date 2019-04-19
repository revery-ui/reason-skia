// Simple template to wrap C++ object as OCaml custom value
// Author: ygrek <ygrek@autistici.org>
// Version: 2016-11-18

// This is free and unencumbered software released into the public domain.
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any means.
// For more information, please refer to <http://unlicense.org/>

// value wrapped<Ptr>::alloc(Ptr)
//    creates custom value with pointer to C++ object inside
//    finalizer will release pointer (whether destructor will be called
//    depends on the semantics of the pointer)
// void wrapped<Ptr>::release(value)
//    releases wrapped pointer
// Ptr const& wrapped<Ptr>::get(value)
//    returns pointer to wrapped object
//    raises OCaml Invalid_argument exception if pointer was already released
// size_t wrapped<Ptr>::count()
//    returns the number of currently allocated Ptr wrappers
//
// wrapped<> manages smart pointers to C++ objects
// wrapped_ptr<> manages raw pointers (owns pointed object, release() destroys object)
//
// generational_global_root is a RAII wrapper to register GC roots
// caml_blocking_section is a RAII wrapper to release runtime lock in the given scope
// without_runtime_lock executes function with runtime lock released

extern "C" {
#define CAML_NAME_SPACE
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/signals.h>
}

#include <memory>

// name used as identifier for custom_operations
// should be instantiated for each wrapped pointer class
template<class T>
char const* ml_name();

// Ptr is a smart pointer class,
// e.g.: std::auto_ptr, boost::shared_ptr, boost::intrusive_ptr
template<class Ptr>
class wrapped
{
private:
  struct ml_wrapped
  {
    ml_wrapped(Ptr x, size_t t) : tag(t), p(x) {} // copy is ok
    ml_wrapped(typename Ptr::element_type* x, size_t t) : tag(t), p(x) {}
    size_t tag;
    Ptr p;
  };

  static size_t count_;

#define Wrapped_val(v) (*(ml_wrapped**)Data_custom_val(v))

  static void finalize(value v)
  {
    release(v);
    delete Wrapped_val(v);
  }

public:
  typedef Ptr type;

  static size_t count() { return count_; }
  static char const* name() { return ml_name<Ptr>(); }
  static size_t tag(value v) { return Wrapped_val(v)->tag; }

  static Ptr const& get(value v) // do not copy
  {
    Ptr const& p = Wrapped_val(v)->p;
    //printf("get %lx : %s\n",(size_t)p.get(),name());
    if (NULL == p.get()) caml_invalid_argument(name());
    return p;
  }

  static void release(value v)
  {
    Ptr& p = Wrapped_val(v)->p;
    //printf("release %lx : %s\n",(size_t)p.get(),name());
    if (NULL == p.get()) return;
    count_--;
    p.reset();
  }

  template<class TPtr>
  static value alloc(TPtr p, size_t tag = 0)
  {
    //printf("alloc %lx : %s\n",(size_t)p.get(),name());
    CAMLparam0();
    CAMLlocal1(v);

    static struct custom_operations wrapped_ops = {
      const_cast<char*>(name()),
      finalize,
      custom_compare_default,
      custom_hash_default,
      custom_serialize_default,
      custom_deserialize_default,
#if defined(custom_compare_ext_default)
      custom_compare_ext_default,
#endif
    };

    v = caml_alloc_custom(&wrapped_ops, sizeof(ml_wrapped*), 0, 1);

    Wrapped_val(v) = new ml_wrapped(p, tag);

    count_++;

    CAMLreturn(v);
  }

#undef Wrapped_val

}; //wrapped

template<class T>
size_t wrapped<T>::count_ = 0;

template <typename T>
struct raw_ptr
{
#if __cplusplus >= 201103L
  typedef std::unique_ptr<T> ptr;
#else
  typedef std::auto_ptr<T> ptr;
#endif
};

template<class T>
struct wrapped_ptr : public wrapped<typename raw_ptr<T>::ptr>
{
  typedef wrapped<typename raw_ptr<T>::ptr> base;
  static T* get(value v)
  {
    return base::get(v).get();
  }
  static value alloc(T* p, size_t tag = 0)
  {
    return base::alloc(p,tag);
  }
}; // wrapped_ptr

#if defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

static size_t UNUSED wrapped_tag(value x) { return wrapped_ptr<void>::tag(x); }

class caml_blocking_section // : boost::noncopyable
{
public:
  caml_blocking_section() { caml_enter_blocking_section(); }
  ~caml_blocking_section() { caml_leave_blocking_section(); }
private:
  caml_blocking_section( const caml_blocking_section& );
  const caml_blocking_section& operator=( const caml_blocking_section& );
};

class generational_global_root // : boost::noncopyable
{
public:
  generational_global_root(value v)
  {
    v_ = v;
    caml_register_generational_global_root(&v_);
  }
  ~generational_global_root()
  {
    caml_remove_generational_global_root(&v_);
    v_ = Val_unit;
  }
  void set(value v)
  {
    caml_modify_generational_global_root(&v_, v);
  }
  value get()
  {
    return v_;
  }
private:
  generational_global_root(generational_global_root const&);
  const generational_global_root& operator=(generational_global_root const&);
private:
  value v_;
};

#if __cplusplus >= 201103L
template<typename Func, typename ... Args>
auto without_runtime_lock(Func f, Args && ... args) -> decltype(f(std::forward<Args>(args)...))
{
  caml_blocking_section lock;
  return f(std::forward<Args>(args)...);
}
#endif

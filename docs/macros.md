# Macros used in Qt

## Q_DECLARE_PRIVATE

declare a private class

```cpp
#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr));) } \
    inline const Class##Private* d_func() const \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr));) } \
    friend class Class##Private;
```

Q_DECLARE_PRIVATE(Foo) will be:

```cpp
inline FooPrivate* d_func() {
  Q_CAST_IGNORE_ALIGN(return reinterpret_cast<FooPrivate *>(qGetPtrHelper(d_ptr));) 
}

inline const FooPricate* d_func() const {
  Q_CAST_IGNORE_ALIGN(return reinterpret_cast<FooPrivate *>(qGetPtrHelper(d_ptr));) 
}

friend class FooPrivate;
```

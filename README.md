[![Build Status](https://travis-ci.org/niXman/impl-container.svg?branch=master)](https://travis-ci.org/niXman/impl-container)

impl-container
==============

Container of implementations with getter by key and verifying the uniqueness of stored implementations

#### "Simple example"
```cpp
struct type1 { int method() const {...} };
struct type2 { int method() const {...} };
struct type3 { int method() const {...} };

impl_container<type1, type1> cont( // static assertion: 'only unique types allowed'
   2 // arguments to types constructors
);
impl_container<type1, type2, type3> cont(
   2 // arguments to types constructors
);

std::cout << cont.get<type1>().method() << std::endl;
std::cout << cont.get<type2>().method() << std::endl;
std::cout << cont.get<type3>().method() << std::endl;
std::cout << cont.get<type4>().method() << std::endl; // static assertion:
   // 'impl_container doesn't contains implementation with this type'

```

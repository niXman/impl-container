[![Build Status](https://travis-ci.org/niXman/impl-container.svg?branch=master)](https://travis-ci.org/niXman/impl-container)

impl-container
==============

Container of implementations with getter by key and verifying the uniqueness of stored implementations

#### "Simple example"
```cpp
struct type1 {
    int v;
    type1(int v):v(v){}
    int m() const { return v+v; }
};
struct type2 {
    int v;
    type2(int v):v(v){}
    int m() const { return v+v+v; }
};
struct type3 {
    int v;
    type3(int v):v(v){}
    int m() const { return v+v+v+v; }
};

struct type4 {
    int v;
    type4(int v):v(v) {}
    int m() const { return v+v+v+v+v; }
};

int main() {
    //impl_container<type1, type1> cont(2); // static assertion: only unique types allowed
    impl_container<type1, type2, type3> cont(2);

    std::cout << cont.get<type1>().m() << std::endl; // 4
    std::cout << cont.get<type2>().m() << std::endl; // 6
    std::cout << cont.get<type3>().m() << std::endl; // 8
    //std::cout << cont.get<type4>().m() << std::endl; // static assertion: 
    // impl_container doesn't contains this type
}
```

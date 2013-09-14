impl-container
==============

Контейнер реализаций с геттером по ключу и проверкой уникальности хранимых реализаций

```cpp
//impl_container<type1, type1> cont( // static assertion: 'only unique types allowed'
   2 // arguments to types constructors
);
impl_container<type1, type2, type3> cont(
   2 // arguments to types constructors
);

std::cout << cont.get<type1>().m() << std::endl; // 4
std::cout << cont.get<type2>().m() << std::endl; // 6
std::cout << cont.get<type3>().m() << std::endl; // 8
//std::cout << cont.get<type4>().m() << std::endl; // static assertion:
   // 'impl_container doesn't contains implementation with this type'

```

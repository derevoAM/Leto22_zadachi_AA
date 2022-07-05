#include <iostream>

template<unsigned int N>
constexpr unsigned int factorial()
{
    static_assert(N >= 0);
    return N * factorial<N - 1>();
}

template<>
constexpr unsigned int factorial<1>()
{
    return 1;
}

template<>
constexpr unsigned int factorial<0>()
{
    return 1;
}

int main()
{
    std::cout << factorial<8>();
}
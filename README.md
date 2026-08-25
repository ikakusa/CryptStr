# About this
This is a header-only library to xor-encryption for strings at compile time works above c++20

# Usage
See [CryptStr.cpp](./CryptStr/CryptStr.cpp)

# Download
Also see [CryptStr.h](./CryptStr/CryptStr.h)

# How it works

At compile time, a seed is determined based on `__COUNTER__` and `__TIME__`, and the string is obfuscated using XOR.
Even for the same string, each instance will have a different seed, making it less readable from an analyst’s perspective.

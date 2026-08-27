# About this
This is a header-only library to xor-encryption for strings at compile time works above c++20

# Usage
See [CryptStr.cpp](./CryptStr/CryptStr.cpp)

# Download
Also see [CryptStr.h](./CryptStr/CryptStr.h)

# How it works

At compile time, a seed is determined based on `__COUNTER__` and `__TIME__`, and the string is obfuscated using XOR.
Even for the same string, each instance will have a different seed, making it less readable from an analyst’s perspective.

# Analysis results
Encrypted string and plain string

<img width="429" height="63" alt="image" src="https://github.com/user-attachments/assets/18d535a5-dda8-4432-9d2e-a8d7754d4266" />

This is a function that decrypts the strings using seed functions different each character

<img width="369" height="727" alt="image" src="https://github.com/user-attachments/assets/aae6d772-9172-4527-959e-c9ba9c40d41c" />

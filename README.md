# About this
This is a header-only library to xor-encryption for strings at compile time works above c++20

# Usage
```cpp
#include <iostream>
#include  "CryptStr.h"

int main()
{
	// easy to use, just like a normal string literal
	std::string protected_hello = protect("Hello, World");
	
	// Also works with wide strings and UTF-8 strings or any other character type
	std::wstring protected_wide_hello = protect(L"Hello, World");
	std::u8string protected_u8_hello = protect(u8"Hello, World");
	//

	// Also there is a lite weighted version of the protection, which is faster and smaller, but less secure
	std::string lite_protected_hello = lprotect("Hello, World");
	//

	//Output: Hello, World
	std::cout << protected_hello << std::endl;

	std::cout << lite_protected_hello << std::endl;

	std::wcout << protected_wide_hello << std::endl;
	std::cout << reinterpret_cast<const char*>(protected_u8_hello.c_str()) << std::endl;
}
```
(Also you can check [CryptStr.cpp](./CryptStr/CryptStr.cpp))

# Download
See [CryptStr.h](./CryptStr/CryptStr.h)

# How it works

At compile time, a seed is determined based on `__COUNTER__` and `__TIME__`, and the string is obfuscated using XOR.
Even for the same string, each instance will have a different seed, making it less readable from an analyst’s perspective.

# Analysis results
Encrypted string and plain string

<img width="429" height="63" alt="image" src="https://github.com/user-attachments/assets/18d535a5-dda8-4432-9d2e-a8d7754d4266" />

String after encrypted

<img width="318" height="91" alt="image" src="https://github.com/user-attachments/assets/97db46c3-8a2d-45e8-97a8-1d970d557076" />

This is a function that decrypts the strings using seed functions different each character

<img width="369" height="727" alt="image" src="https://github.com/user-attachments/assets/aae6d772-9172-4527-959e-c9ba9c40d41c" />

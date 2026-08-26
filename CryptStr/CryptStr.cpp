#include <iostream>
#include  "CryptStr.h"

int main()
{
	// easy to use, just like a normal string literal
	auto protected_hello = protect("Hello, World");
	
	auto protected_hello2 = protect2("Hello, World"); //Decrypt on RAII
	const char* buffer2 = protected_hello2.buffer();
	//const char* buffer = protected_string; //operator const CharType*() is also available

	// Also works with wide strings and UTF-8 strings or any other character type
	std::wstring protected_wide_hello = protect(L"Hello, World");
	std::u8string protected_u8_hello = protect(u8"Hello, World");
	//

	//Output: Hello, World!
	std::cout << protected_hello << std::endl;
	std::cout << buffer2 << std::endl;

	std::wcout << protected_wide_hello << std::endl;
	std::cout << reinterpret_cast<const char*>(protected_u8_hello.c_str()) << std::endl;
}
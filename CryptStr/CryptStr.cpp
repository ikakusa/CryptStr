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

	// Also there is a lite weighted version of the protection, which is smaller
	std::string lite_protected_hello = lprotect("Hello, World");
	//

	//Output: Hello, World!
	std::cout << protected_hello << std::endl;

	std::cout << lite_protected_hello << std::endl;

	std::wcout << protected_wide_hello << std::endl;
	std::cout << reinterpret_cast<const char*>(protected_u8_hello.c_str()) << std::endl;
}
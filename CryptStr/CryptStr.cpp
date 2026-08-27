#include <iostream>
#include  "CryptStr.h"

int main()
{
	// easy to use, just like a normal string literal
	std::string protected_hello = protect("Hello, World");
	
	// Also works with wide strings and UTF-8 strings or any other character type
	std::wstring protected_wide_hello = protect(L"Hello, World");
	std::u8string protected_u8_hello = ikakusa::protected_string<decltype(u8"Hello, World")&, sizeof(u8"Hello, World"), 14>(u8"Hello, World", std::make_index_sequence<(sizeof(u8"Hello, World") / sizeof(std::remove_cv_t<std::remove_extent_t<std::remove_cvref_t<decltype(u8"Hello, World")>>>) - 1)>{}).reveal(std::make_index_sequence<(sizeof(u8"Hello, World") / sizeof(std::remove_cv_t<std::remove_extent_t<std::remove_cvref_t<decltype(u8"Hello, World")>>>) - 1)>{});
	//

	// Also there is a lite weighted version of the protection, which is faster and smaller, but less secure
	std::string lite_protected_hello = lprotect("Hello, World");
	//

	//Output: Hello, World!
	std::cout << protected_hello << std::endl;

	std::cout << lite_protected_hello << std::endl;

	std::wcout << protected_wide_hello << std::endl;
	std::cout << reinterpret_cast<const char*>(protected_u8_hello.c_str()) << std::endl;
}
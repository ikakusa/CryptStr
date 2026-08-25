#include <iostream>
#include  "CryptStr.h"

int main()
{
	auto protected_string = protect("Hello, World!");
	const char* buffer = protected_string.buffer();
	//const char* buffer = protected_string; //operator const CharType*() is also available
	
	//Output: Hello, World!
	std::cout << buffer << std::endl;
}
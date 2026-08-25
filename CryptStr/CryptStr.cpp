#include <iostream>
#include  "CryptStr.h"

int main()
{
	std::string crypted = protect("Hello, World!");
	
	//Output: Hello, World!
	std::cout << crypted << std::endl;
}
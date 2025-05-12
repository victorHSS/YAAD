#include <iostream>
#include <fstream>
#include <string>
#include <format>

#include <algorithm>
#include <cctype>

#include "interpreter/Scanner.hpp"

int main()
{
	std::ifstream file("main.asm");
	std::string line{};
	
	size_t count{0};
	while ( getline(file, line) )
	{
		std::transform(line.cbegin(),line.cend(),line.begin(),tolower);
		
		std::cout << std::format("{:03d} '{}'\n", count++, line);
		std::deque<Token> tokens = Scanner::analyse(line);
		
		for (auto &token : tokens)
			std::cout << token << std::endl;
		
		getline(std::cin, line);
		//Parser::parse();
		//Interpreter::execute(tokens,count);
	}
	
	return 0;
}

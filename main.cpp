#include <iostream>
#include <fstream>
#include <string>
#include <format>

int main()
{
	//ler arquivo
	//ler linha
	//processar linha - para minusculas
	
	//chamar scanner para linha
	//chamar interpretador
	std::ifstream file("rsc/keywords.lst");
	std::string line;
	
	int count{0};
	while ( getline(file, line))
	{
		std::cout << std::format("{:03d} '{}'\n",count++,line);
	}
	
	return 0;
}

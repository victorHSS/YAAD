#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string_view>
using std::string_view;

#include <vector>
using std::vector;

#include "Token.hpp"

class Scanner
{
public:
	Scanner() = delete;
	~Scanner() = delete;
	
	static vector<Token> analyse( string_view );

private:
	static size_t pos{};
	static vector<Token> tokenList{};
	
	//auxiliares
	static void ignoreBlank( string_view );
	
	static char lookAhead( string_view );
	
	static void isPunct( string_view );
	
	static void isIndirectAddress( string_view );
	static void isLiteral( string_view );
};

#endif // SCANNER_HPP

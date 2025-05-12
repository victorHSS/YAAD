#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string_view>
using std::string_view;

#include <deque>
using std::deque;

#include "Token.hpp"

class Scanner
{
public:
	Scanner() = delete;
	~Scanner() = delete;
	
	static deque<Token> analyse( string_view );

private:
	static size_t pos;
	static deque<Token> tokenList;
	
	//auxiliares
	static void ignoreBlank( string_view );
	
	static char lookAhead( string_view );
	
	static TOKEN_SUBTYPE trickLiteralType( string_view );
	
	static void isPunct( string_view );
	static void isLiteral( string_view );
	static void isWordIdentifier( string_view );
	static void isString( string_view );
};

#endif // SCANNER_HPP

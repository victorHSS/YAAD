#include "Scanner.hpp"

#include <cctype>

#include <stdexcept>

static vector<Token> Scanner::analyse(string_view line)
{
	pos = 0;				//apontador para o char corrente
	tokenList.clear();
	
	while(true)
	{
		ignoreBlank(line);
		
		if (pos >= line.size())
			return tokenList;
		
		if (ispunct(line[pos]))
			isPunct(line);
		else if (isdigit(line[pos]))
			isLiteral(line);
	}

}

static void Scanner::ignoreBlank(string_view line)
{
	return line.find_first_not_of(" \t");
}

static char Scanner::lookAhead( string_view line)
{
	if (pos < line.size() - 1)
		return line[pos + 1];
	
	return '\0';
}

static void Scanner::isPunct( string_view line )
{
	if (line[pos] == ',') {
		tokenList.push_back( Token{TOKEN_TYPE::DELIMITER , ','} );
		++pos;
	}
	else if (line[pos] == ';')
		pos = line.size();
	else if (line[pos] == '[')
		isIndirectAddress(line);
	//( - EXPRESSION
	//- -> numeros negativos... ver se o último token é um delimitador e chama isLiteral
}

static void Scanner::isIndirectAddress( string_view line )
{
	size_t endP = line.find_first_of(']');
	
	if (endP == string_view::npos)
		throw std::runtime_error("']' não encontrado.");
	
	//aqui eu vou ter que detalhar mais... mas está bom para começo de conversa
	tokenList.push_back( Token{TOKEN_TYPE::IDENTIFIER, line.substr(pos, endP - pos + 1)} );
}

static void Scanner::isLiteral( string_view line )
{
	
}
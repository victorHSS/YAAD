#include "Scanner.hpp"

#include <cctype>
#include <string>
#include <stdexcept>

#include <set>
using std::set;

using namespace std::literals;

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
		else if (isalpha(line[pos])
			isWordIdentifier(line);
	}

}

static void Scanner::ignoreBlank(string_view line)
{
	return line.find_first_not_of(" \t\n"sv);
}

static char Scanner::lookAhead( string_view line)
{
	if (pos < line.size() - 1)
		return line[pos + 1];
	
	return '\0';
}

static void Scanner::isPunct( string_view line )
{
	if (line[pos] == ';')
		pos = line.size();
	else if (set{'(',')','[',']',','}.contains(line[pos]) ) {
		tokenList.push_back( Token{TOKEN_TYPE::DELIMITER , line[pos]} );
		++pos;
	}
	else if (line[pos] == '-')
	{
		if (tokenList.back().isDelimiter())
			isLiteral(line);
		else 
			tokenList.push_back( Token{TOKEN_TYPE::OPERATOR , '-'} );
	}
}

static void Scanner::isLiteral( string_view line )
{
	//char lh = lookAhead(line);
	size_t endP{};
	
	if (line[pos] == '-')
	{
		endP = line.substr(pos+1).find_last_of("0123456789"sv) + 1;
		tokenList.push_back( 
			Token{TOKEN_TYPE::LITERAL, line.substr(pos, endP - pos), TOKEN_SUBTYPE::DECIMAL_BASE} 
		);
	} 
	else
	{ 
		endP = line.find_last_of("0123456789abcdefxoqbh"sv) + 1;
		tokenList.push_back( 
			Token{TOKEN_TYPE::LITERAL, line.substr(pos, endP - pos)} 
		);
	}
	
	// VALIDAR?
	
	pos = endP;
}

static void Scanner::isWordIdentifier( string_view line )
{
	string word{};
	while (isalphanum(line[pos]) 
	{
		word += line[pos];
		pos++;
	}
	//registrador
	//palavra-chave
	//label
}
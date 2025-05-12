#include "Scanner.hpp"

#include <iostream>//

#include <cctype>
#include <string>
#include <stdexcept>

#include <string>
using std::string;

#include <set>
using std::set;

#include <fstream>

using namespace std::literals;

size_t Scanner::pos{};
deque<Token> Scanner::tokenList{};

deque<Token> Scanner::analyse(string_view line)
{
	pos = 0;				//apontador para o char corrente
	tokenList.clear();
	
	//std::cout << "analyse: \"" << line.substr(pos) << "\"" << std::endl;//
	
	while(true)
	{
		ignoreBlank(line);
				
		if (pos >= line.size())
			return tokenList;
		
		if (ispunct(line[pos]))
			isPunct(line);
		else if (isdigit(line[pos]))
			isLiteral(line);
		else if (isalpha(line[pos]))
			isWordIdentifier(line);
	}

}

void Scanner::ignoreBlank(string_view line)
{
	while (line[pos] == ' ' || line[pos] == '\t') pos++;
}

char Scanner::lookAhead( string_view line)
{
	if (pos < line.size() - 1)
		return line[pos + 1];
	
	return '\0';
}

void Scanner::isPunct( string_view line )
{
	if (line[pos] == ';')
	{
		pos = line.size();
	}
	else if (set{'(',')','[',']',',',':'}.contains(line[pos]) )
	{
		tokenList.push_back( Token{TOKEN_TYPE::DELIMITER , std::string{1,line[pos]}, pos} );
		++pos;
	}
	else if (set{'.','_'}.contains(line[pos]))
	{
		isWordIdentifier(line);
	}
	else if (line[pos] == '\'')
	{
		isString(line);
	}
	else if (line[pos] == '-')
	{
		if (tokenList.back().isDelimiter())
			isLiteral(line);
		else 
		{
			tokenList.push_back( Token{TOKEN_TYPE::OPERATOR , std::string{1,'-'}, pos} );
			++pos;
		}
	}
	
}

void Scanner::isString( string_view line )
{
	size_t endP{line.substr(pos + 1).find_first_of('\'')};
	std::string str{line.substr(pos + 1).substr(0,endP)};
	
	tokenList.push_back( Token{TOKEN_TYPE::LITERAL , str, pos, TOKEN_SUBTYPE::STRING} );
	
	pos += str.size() + 2;
}

void Scanner::isLiteral( string_view line )
{
	size_t endP{};
	std::string num{};
	
	if (line[pos] == '-')
	{
		num += '-';
		endP++;
		while (endP < line.size() && isdigit(line[endP]))
			num += line[endP++];

		tokenList.push_back( 
			Token{TOKEN_TYPE::LITERAL, num , pos, TOKEN_SUBTYPE::DECIMAL_BASE} 
		);
	} 
	else
	{
		endP = pos;
		while (endP < line.size() && (isxdigit(line[endP]) || set{'b','o','q','x'}.contains(line[endP])) )
			num += line[endP++];

		tokenList.push_back( 
			Token{TOKEN_TYPE::LITERAL, num, pos, trickLiteralType(num)} 
		);
	}
	
	pos = endP;
}

TOKEN_SUBTYPE Scanner::trickLiteralType( string_view num)
{
	if ( num.starts_with("0x"sv) || num.ends_with("h"sv) )
		return TOKEN_SUBTYPE::HEXA_BASE;
	else if ( num.starts_with("0b"sv) || num.ends_with("b"sv) )
		return TOKEN_SUBTYPE::BINARY_BASE;
	else if ( num.starts_with("0o"sv) || num.starts_with("0q"sv) || num.ends_with("o"sv) )
		return TOKEN_SUBTYPE::OCTAL_BASE;
	
	return TOKEN_SUBTYPE::DECIMAL_BASE;
}

void Scanner::isWordIdentifier( string_view line )
{
	string word{}, item{};
	static set<string> regs{};
	static set<string> keywords{};
	
	size_t tPos{pos};
	while ( isalnum(line[tPos]) || line[tPos] == '_' || line[tPos] == '.' ) 
		word += line[tPos++];
	
	if (regs.empty())
	{
		std::ifstream file("rsc/regs.lst");
		while (getline(file,item)) regs.insert(item);
	}
	
	if (keywords.empty())
	{
		std::ifstream file("rsc/keywords.lst");
		while (getline(file,item)) keywords.insert(item);
	}
	
	if (regs.contains(word))
		tokenList.push_back( Token{ TOKEN_TYPE::REGISTER , word , pos } );
	else if (keywords.contains(word))
		tokenList.push_back( Token{ TOKEN_TYPE::KEYWORD , word , pos } );
	else
		tokenList.push_back( Token{ TOKEN_TYPE::LABEL , word , pos } );
	
	pos+= word.size();
}
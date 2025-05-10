#include "Scanner.hpp"

#include <cctype>
#include <string>
#include <stdexcept>

#include <string>
using std::string;

#include <set>
using std::set;

#include <fstream>

using namespace std::literals;

static size_t Scanner::pos{};
static vector<Token> Scanner tokenList{};

static vector<Token> Scanner::analyse(string_view line)
{
	pos = 0;				//apontador para o char corrente
	tokenList.clear();
	
	while(true)
	{
		ignoreBlank(line);
		
		if (pos >= line.size() || pos == string_view::npos)
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
	return line.find_first_not_of(" \t"sv);
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
	{
		pos = line.size();
	}
	else if (set{'(',')','[',']',',',':'}.contains(line[pos]) )
	{
		tokenList.push_back( Token{TOKEN_TYPE::DELIMITER , line[pos], pos} );
		++pos;
	}
	else if (line[pos] == '.')
	{
		isWordIdentifier(line);
	}
	else if (line[pos] == '-')
	{
		if (tokenList.back().isDelimiter())
			isLiteral(line);
		else 
		{
			tokenList.push_back( Token{TOKEN_TYPE::OPERATOR , '-', pos} );
			++pos;
		}
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
			Token{TOKEN_TYPE::LITERAL, line.substr(pos, endP - pos), pos, TOKEN_SUBTYPE::DECIMAL_BASE} 
		);
	} 
	else
	{ 
		endP = line.find_last_of("0123456789abcdefxoqbh"sv) + 1;
		tokenList.push_back( 
			Token{TOKEN_TYPE::LITERAL, line.substr(pos, endP - pos), pos} 
		);
	}
	
	// VALIDAR?
	
	pos = endP;
}

static void Scanner::isWordIdentifier( string_view line )
{
	string word{}, item{};
	static set<string> regs{};
	static set<string> keywords{};
	
	while (isalphanum(line[pos])) 
		word += line[pos];
	
	if (regs.empty())
	{
		std::ifstream file("../rsc/regs.lst");
		while (getline(file,item)) regs.insert(item);
	}
	
	if (keywords.empty())
	{
		std::ifstream file("../rsc/keywords.lst");
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
#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <string_view>

using std::string, std::string_view;

enum class TOKEN_TYPE {
	KEYWORD,
	IDENTIFIER,
	LITERAL,
	OPERATOR,
	DELIMITER
};

enum class TOKEN_SUBTYPE {
	NONE,
	HEXA_BASE,
	OCTAL_BASE,
	DECIMAL_BASE,
	BINARY_BASE
};

class Token
{
public:
	Token(TOKEN_TYPE type, string_view value, TOKEN_SUBTYPE subType = TOKEN_SUBTYPE::NONE):
		type{type},
		value{value},
		subType{subType} {}
		
	TOKEN_TYPE getType() const { return type; }
	string getValue() const { return value; }
	
	bool isDelimiter() { return type == TOKEN_TYPE::DELIMITER; }
	
	~Token() = default;
private:
	TOKEN_TYPE type;
	string value;
	TOKEN_SUBTYPE subType;
};

#endif // TOKEN_HPP

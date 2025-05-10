#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>
#include <string_view>
using std::string, std::string_view;

#include <format>

enum class TOKEN_TYPE {
	KEYWORD		= 0,
	REGISTER,
	LABEL,
	
	LITERAL,
	
	OPERATOR,
	
	DELIMITER
};

const char *const token_type_str[] =
{
	"KEYWORD",
	"REGISTER",
	"LABEL",
	
	"LITERAL",
	
	"OPERATOR",
	
	"DELIMITER"
};


enum class TOKEN_SUBTYPE {
	NONE		= 0,
	HEXA_BASE,
	OCTAL_BASE,
	DECIMAL_BASE,
	BINARY_BASE,
	
	STRING
};

const char *const token_subtype_str[] =
{
	"NONE",
	"HEXA_BASE",
	"OCTAL_BASE",
	"DECIMAL_BASE",
	"BINARY_BASE",
	
	"STRING"
};

class Token
{
	friend std::ostream &operator<<(std::ostream &out, const Token &token)
	{
		out << std::format("Token(tp[{}] val['{}'] pos[{}] stp[{}])",
			token_type_str[ static_cast<int>(token.type) ],
			token.value,
			token.sPos,
			token_subtype_str[ static_cast<int>(token.subType) ]
		);
		
		return out;
	}
public:
	Token(TOKEN_TYPE type, string_view value, size_t sPos, TOKEN_SUBTYPE subType = TOKEN_SUBTYPE::NONE):
		type{type},
		value{value},
		sPos{sPos},
		subType{subType} {}
		
	TOKEN_TYPE getType() const { return type; }
	string getValue() const { return value; }
	int getPos() const { return sPos; }
	
	bool isDelimiter() { return type == TOKEN_TYPE::DELIMITER; }
	
	~Token() = default;
private:
	TOKEN_TYPE type;
	string value;
	size_t sPos;
	TOKEN_SUBTYPE subType;
};

#endif // TOKEN_HPP

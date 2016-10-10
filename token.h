#ifndef token_h
#define token_h

#include <string>

struct Token {
	enum{
		PLUS, MINUS, NUMBER, VARIABLE, SIN, COS, POW, PRODUCT, DIVIDE, PI, UD
	} type;
	
	union{
	
		char variable;
		double number;
	
	};
	
	Token();
	bool isBinaryOperator() const;
	bool isUnaryOperator() const;
	bool isNullary() const;
	bool isOperator() const;
    bool isConstant() const;
    bool isAlbean() const;
    void parse(std::string word);
    Token &operator=(const Token &other);
    bool operator==(const Token &rhs) const;
    bool operator!=(const Token &rhs) const;

    const double PRECISION = 0.0000001;
};

std::ostream &operator<<(std::ostream &s, const Token &form);

#endif

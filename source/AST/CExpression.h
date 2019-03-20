#pragma once

#include <string>
using std::string;

class CExpression {
public:
    virtual ~CExpression();
    virtual string to_asm() const = 0;
};

class CExpressionInt: public CExpression {
public:
    CExpressionInt(int value);
    ~CExpressionInt();
    string to_asm() const;

    int value;
};

class CExpressionVar: public CExpression {
public:
    CExpressionVar(const string variable);
    ~CExpressionVar();
    string to_asm() const;

    string variable;
};

class CExpressionComposed: public CExpression {
public:
    CExpressionComposed(CExpression * lhs, char op, CExpression * rhs);
    ~CExpressionComposed();
    string to_asm() const;

    CExpression * lhs;
    char op;
    CExpression * rhs;
};


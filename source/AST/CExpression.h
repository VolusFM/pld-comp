#pragma once

#include <iostream>
using std::ostream;
#include <string>
using std::string;
#include <utility>
using std::pair;

class CFunction;
class CFG;

class CExpressionPart {
public:
    virtual ~CExpressionPart() = default;
    virtual CExpressionPart* optimize();
    virtual string to_IR(CFG* cfg) const = 0;
};

class CExpression {
public:
    CExpression(CExpressionPart* expr);
    ~CExpression();
    
    void to_IR_full(CFG* cfg) const;
    string to_IR_part(CFG* cfg) const;
    void to_IR_bool(CFG* cfg) const;
    
    void optimize();
    
private:
    CExpressionPart* expr;
};

class CExpressionInt: public CExpressionPart {
public:
    CExpressionInt(int value);
    ~CExpressionInt() = default;
    string to_IR(CFG* cfg) const;
    
    int value;
};

class CExpressionVar: public CExpressionPart {
public:
    CExpressionVar(string variable);
    ~CExpressionVar() = default;
    string to_IR(CFG* cfg) const;
    
    string variable;
};

class CExpressionVarArray: public CExpressionPart {
public:
    CExpressionVarArray(string variable, CExpressionPart* index);
    ~CExpressionVarArray();
    string to_IR(CFG* cfg) const;
    string to_IR_address(CFG* cfg) const;
    
    string variable;
    CExpressionPart* index;
};

class CExpressionComposed: public CExpressionPart {
public:
    CExpressionComposed(CExpressionPart* lhs, string op, CExpressionPart* rhs);
    ~CExpressionComposed();
    CExpressionPart* optimize();
    string to_IR(CFG* cfg) const;
    
    CExpressionPart* lhs;
    string op;
    CExpressionPart* rhs;
    
private:
    // no copy wanted
    CExpressionComposed(const CExpressionComposed&); // no implementation
    CExpressionComposed& operator=(const CExpressionComposed&); // no implementation
};


#pragma once

#include <string>
using std::string;

#include "CInstruction.h"

class CExpression : public CInstruction {
public:
  virtual string to_asm() const = 0;
};

class CExpressionInt : public CExpression {
public:
  string to_asm() const;
  
  int valeur;
};

class CExpressionVar : public CExpression {
public:
  string to_asm() const;
  
  string variable;
};

class CExpressionCompose : public CExpression {
public:
  string to_asm() const;
  
  CExpression* lhs;
  char op;
  CExpression* rhs;
};


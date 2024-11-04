#ifndef EXPR_HPP
#define EXPR_HPP

#include <sstream>
#include <string>

// Abstract class Expression
class Expression {
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

// Class for numeric expressions
class NumExpression : public Expression {
 private:
  long value;

 public:
  NumExpression(long v) : value(v) {}
  virtual std::string toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }
};

// Class for plus expressions
class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    std::ostringstream oss;
    oss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return oss.str();
  }
};

#endif

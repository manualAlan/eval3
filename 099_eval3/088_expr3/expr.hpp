#ifndef EXPR_HPP
#define EXPR_HPP

#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
};

class BinaryExpression : public Expression {
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  BinaryExpression(Expression * left, Expression * right) : lhs(left), rhs(right) {}
  virtual ~BinaryExpression() {
    delete lhs;
    delete rhs;
  }
};

class NumExpression : public Expression {
 private:
  long value;

 public:
  NumExpression(long v) : value(v) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }
  long evaluate() const { return value; }
};

class PlusExpression : public BinaryExpression {
 public:
  PlusExpression(Expression * left, Expression * right) : BinaryExpression(left, right) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return oss.str();
  }
  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
};

class MinusExpression : public BinaryExpression {
 public:
  MinusExpression(Expression * left, Expression * right) :
      BinaryExpression(left, right) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return oss.str();
  }
  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public BinaryExpression {
 public:
  TimesExpression(Expression * left, Expression * right) :
      BinaryExpression(left, right) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return oss.str();
  }
  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public BinaryExpression {
 public:
  DivExpression(Expression * left, Expression * right) : BinaryExpression(left, right) {}
  std::string toString() const {
    std::ostringstream oss;
    oss << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return oss.str();
  }
  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};

#endif

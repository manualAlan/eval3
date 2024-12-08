#ifndef POLY_HPP
#define POLY_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

// Exception class for convergence failure
template<typename NumT>
class convergence_failure : public std::exception {
 public:
  const NumT value;
  explicit convergence_failure(const NumT & val) : value(val) {}
  virtual const char * what() const throw() { return "Convergence failure"; }
};

template<typename NumT>
class Polynomial {
 private:
  std::map<unsigned, NumT> terms;

  void simplify() {
    typename std::map<unsigned, NumT>::iterator it = terms.begin();
    while (it != terms.end()) {
      if (it->second == NumT()) {
        typename std::map<unsigned, NumT>::iterator toErase = it;
        ++it;
        terms.erase(toErase);
      }
      else {
        ++it;
      }
    }
    if (terms.empty()) {
      terms[0] = NumT();
    }
  }

 public:
  Polynomial() { terms[0] = NumT(); }

  void addTerm(const NumT & c, unsigned p) {
    if (terms.count(p)) {
      terms[p] += c;
      if (terms[p] == NumT()) {
        terms.erase(p);
      }
    }
    else if (c != NumT()) {
      terms[p] = c;
    }
    simplify();
  }

  Polynomial operator-() const {
    Polynomial result;
    typename std::map<unsigned, NumT>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); ++it) {
      result.terms[it->first] = -it->second;
    }
    return result;
  }

  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial result(*this);
    typename std::map<unsigned, NumT>::const_iterator it;
    for (it = rhs.terms.begin(); it != rhs.terms.end(); ++it) {
      result.addTerm(it->second, it->first);
    }
    result.simplify();
    return result;
  }

  Polynomial operator-(const Polynomial & rhs) const { return *this + (-rhs); }

  Polynomial operator*(const NumT & n) const {
    Polynomial result;
    typename std::map<unsigned, NumT>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); ++it) {
      result.terms[it->first] = it->second * n;
    }
    result.simplify();
    return result;
  }

  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial result;
    typename std::map<unsigned, NumT>::const_iterator it1, it2;
    for (it1 = terms.begin(); it1 != terms.end(); ++it1) {
      for (it2 = rhs.terms.begin(); it2 != rhs.terms.end(); ++it2) {
        unsigned new_exp = it1->first + it2->first;
        NumT new_coeff = it1->second * it2->second;
        result.addTerm(new_coeff, new_exp);
      }
    }
    result.simplify();
    return result;
  }

  bool operator==(const Polynomial & rhs) const { return terms == rhs.terms; }

  bool operator!=(const Polynomial & rhs) const { return !(*this == rhs); }

  Polynomial & operator+=(const Polynomial & rhs) {
    *this = *this + rhs;
    return *this;
  }

  Polynomial & operator-=(const Polynomial & rhs) {
    *this = *this - rhs;
    return *this;
  }

  Polynomial & operator*=(const Polynomial & rhs) {
    *this = *this * rhs;
    return *this;
  }

  Polynomial & operator*=(const NumT & n) {
    *this = *this * n;
    return *this;
  }

  NumT eval(const NumT & x) const {
    NumT result = 0;
    typename std::map<unsigned, NumT>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); ++it) {
      result += it->second * std::pow(x, it->first);
    }
    return result;
  }

  NumT operator()(const NumT & x) const { return eval(x); }

  Polynomial derivative() const {
    Polynomial result;
    typename std::map<unsigned, NumT>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); ++it) {
      if (it->first > 0) {
        result.addTerm(NumT(it->first) * it->second, it->first - 1);
      }
    }
    result.simplify();
    return result;
  }

  // Convert function
  template<typename OtherNumT>
  Polynomial<OtherNumT> convert() const {
    Polynomial<OtherNumT> result;
    for (typename std::map<unsigned, NumT>::const_iterator it = terms.begin();
         it != terms.end();
         ++it) {
      result.addTerm(OtherNumT(it->second), it->first);
    }
    return result;
  }

  // Find zero function using Newton-Raphson method
  template<typename ToleranceT>
  NumT findZero(NumT x,
                unsigned maxSteps,
                const ToleranceT & tolerance,
                const ToleranceT & deriv_tolerance) {
    Polynomial deriv = derivative();
    unsigned stepsLeft = maxSteps;
    while (stepsLeft > 0) {
      NumT y = eval(x);
      if (std::abs(y) <= tolerance) {
        return x;
      }
      NumT dy = deriv.eval(x);
      if (std::abs(dy) < deriv_tolerance) {
        throw convergence_failure<NumT>(x);
      }
      x = x - y / dy;
      --stepsLeft;
    }
    throw convergence_failure<NumT>(x);
  }

  template<typename N>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

template<typename NumT>
std::ostream & operator<<(std::ostream & os, const Polynomial<NumT> & p) {
  if (p.terms.empty() || (p.terms.size() == 1 && p.terms.begin()->second == NumT())) {
    return os << NumT();
  }

  bool first = true;
  typename std::map<unsigned, NumT>::const_reverse_iterator it;
  for (it = p.terms.rbegin(); it != p.terms.rend(); ++it) {
    if (it->second == NumT()) {
      continue;
    }
    if (!first) {
      os << " + ";
    }
    os << it->second << "*x^" << it->first;
    first = false;
  }
  return os;
}

#endif

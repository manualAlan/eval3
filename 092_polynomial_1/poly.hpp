#ifndef POLY_HPP
#define POLY_HPP

#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

template<typename NumT>
class Polynomial {
 private:
  std::map<unsigned, NumT> terms;  // Key: exponent, Value: coefficient

  // Helper function to remove zero terms and simplify
  void simplify() {
    for (typename std::map<unsigned, NumT>::iterator it = terms.begin();
         it != terms.end();) {
      if (it->second == NumT()) {
        it = terms.erase(it);  // Erase returns the next iterator, so reassign it directly
      }
      else {
        ++it;
      }
    }
    if (terms.empty()) {
      terms[0] = NumT();  // Ensure the polynomial is "0" if all terms are removed
    }
  }

 public:
  // Default constructor
  Polynomial() {
    terms[0] = NumT();  // Initialize to "0"
  }

  // Add a term to the polynomial
  void addTerm(const NumT & c, unsigned p) {
    if (terms.count(p)) {
      terms[p] += c;
      if (terms[p] == NumT()) {  // Remove term if coefficient becomes 0
        terms.erase(p);
      }
    }
    else if (c != NumT()) {
      terms[p] = c;
    }
    simplify();
  }

  // Negation operator
  Polynomial operator-() const {
    Polynomial result;
    for (typename std::map<unsigned, NumT>::const_iterator it = terms.begin();
         it != terms.end();
         ++it) {
      result.terms[it->first] = -it->second;
    }
    return result;
  }

  // Addition operator
  Polynomial operator+(const Polynomial & rhs) const {
    Polynomial result(*this);
    for (typename std::map<unsigned, NumT>::const_iterator it = rhs.terms.begin();
         it != rhs.terms.end();
         ++it) {
      result.addTerm(it->second, it->first);
    }
    result.simplify();
    return result;
  }

  // Subtraction operator
  Polynomial operator-(const Polynomial & rhs) const { return *this + (-rhs); }

  // Scalar multiplication
  Polynomial operator*(const NumT & n) const {
    Polynomial result;
    for (typename std::map<unsigned, NumT>::const_iterator it = terms.begin();
         it != terms.end();
         ++it) {
      result.terms[it->first] = it->second * n;
    }
    result.simplify();
    return result;
  }

  // Polynomial multiplication
  Polynomial operator*(const Polynomial & rhs) const {
    Polynomial result;
    for (typename std::map<unsigned, NumT>::const_iterator it1 = terms.begin();
         it1 != terms.end();
         ++it1) {
      for (typename std::map<unsigned, NumT>::const_iterator it2 = rhs.terms.begin();
           it2 != rhs.terms.end();
           ++it2) {
        unsigned new_exp = it1->first + it2->first;
        NumT new_coeff = it1->second * it2->second;
        result.addTerm(new_coeff, new_exp);
      }
    }
    result.simplify();
    return result;
  }

  // Equality operators
  bool operator==(const Polynomial & rhs) const { return terms == rhs.terms; }

  bool operator!=(const Polynomial & rhs) const { return !(*this == rhs); }

  // Compound assignment operators
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

  // Friend function for output
  template<typename N>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

// Output operator
template<typename NumT>
std::ostream & operator<<(std::ostream & os, const Polynomial<NumT> & p) {
  if (p.terms.empty() || (p.terms.size() == 1 && p.terms.begin()->second == NumT())) {
    return os << NumT();  // Output "0" when the polynomial is just zero
  }

  bool first = true;
  for (typename std::map<unsigned, NumT>::const_reverse_iterator it = p.terms.rbegin();
       it != p.terms.rend();
       ++it) {
    if (it->second == NumT()) {
      continue;  // Skip terms with zero coefficients
    }
    if (!first) {
      os << " + ";
    }
    os << it->second << "*x^" << it->first;
    first = false;
  }
  return os;
}

#endif  // POLY_HPP

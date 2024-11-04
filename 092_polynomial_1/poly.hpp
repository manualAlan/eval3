#include <complex>
#include <iostream>
#include <vector>

template<typename NumT>
class Polynomial {
 private:
  std::vector<std::pair<NumT, unsigned> > terms;

 public:
  Polynomial() : terms{{NumT(), 0}} {}
  Polynomial operator+(const Polynomial & rhs) const;
  Polynomial operator-() const;
  Polynomial operator-(const Polynomial & rhs) const;
  Polynomial operator*(const NumT & n) const;
  Polynomial operator*(const Polynomial & rhs) const;
  bool operator!=(const Polynomial & rhs) const;
  bool operator==(const Polynomial & rhs) const;
  void addTerm(const NumT & c, unsigned p);
  Polynomial & operator+=(const Polynomial & rhs);
  Polynomial & operator-=(const Polynomial & rhs);
  Polynomial & operator*=(const Polynomial & rhs);
  Polynomial & operator*=(const NumT & rhs);

  template<typename N>
  friend std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p);
};

template<typename NumT>
Polynomial<NumT> Polynomial<NumT>::operator+(const Polynomial & rhs) const {
  Polynomial result = *this;
  result += rhs;
  return result;
}

template<typename NumT>
Polynomial<NumT> Polynomial<NumT>::operator-() const {
  Polynomial result;
  for (const auto & term : terms) {
    result.addTerm(-term.first, term.second);
  }
  return result;
}

template<typename NumT>
Polynomial<NumT> Polynomial<NumT>::operator-(const Polynomial & rhs) const {
  Polynomial result = *this;
  result -= rhs;
  return result;
}

template<typename NumT>
Polynomial<NumT> Polynomial<NumT>::operator*(const NumT & n) const {
  Polynomial result;
  for (const auto & term : terms) {
    result.addTerm(term.first * n, term.second);
  }
  return result;
}

template<typename NumT>
Polynomial<NumT> Polynomial<NumT>::operator*(const Polynomial & rhs) const {
  Polynomial result;
  for (const auto & lhsTerm : terms) {
    for (const auto & rhsTerm : rhs.terms) {
      result.addTerm(lhsTerm.first * rhsTerm.first, lhsTerm.second + rhsTerm.second);
    }
  }
  return result;
}

template<typename NumT>
bool Polynomial<NumT>::operator!=(const Polynomial & rhs) const {
  return !(*this == rhs);
}

template<typename NumT>
bool Polynomial<NumT>::operator==(const Polynomial & rhs) const {
  return terms == rhs.terms;
}

template<typename NumT>
void Polynomial<NumT>::addTerm(const NumT & c, unsigned p) {
  for (auto & term : terms) {
    if (term.second == p) {
      term.first += c;
      return;
    }
  }
  terms.emplace_back(c, p);
}

template<typename NumT>
Polynomial<NumT> & Polynomial<NumT>::operator+=(const Polynomial & rhs) {
  for (const auto & term : rhs.terms) {
    addTerm(term.first, term.second);
  }
  return *this;
}

template<typename NumT>
Polynomial<NumT> & Polynomial<NumT>::operator-=(const Polynomial & rhs) {
  for (const auto & term : rhs.terms) {
    addTerm(-term.first, term.second);
  }
  return *this;
}

template<typename NumT>
Polynomial<NumT> & Polynomial<NumT>::operator*=(const Polynomial & rhs) {
  *this = *this * rhs;
  return *this;
}

template<typename NumT>
Polynomial<NumT> & Polynomial<NumT>::operator*=(const NumT & rhs) {
  for (auto & term : terms) {
    term.first *= rhs;
  }
  return *this;
}

template<typename N>
std::ostream & operator<<(std::ostream & os, const Polynomial<N> & p) {
  for (size_t i = 0; i < p.terms.size(); ++i) {
    os << p.terms[i].first << "*x^" << p.terms[i].second;
    if (i + 1 < p.terms.size())
      os << " + ";
  }
  return os;
}

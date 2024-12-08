#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class LinearFunction : public Function<int, int> {
 private:
  float m_slope;
  float m_intercept;

 public:
  LinearFunction() : m_slope(1), m_intercept(0) {}
  LinearFunction(float intercept, float slope) : m_slope(slope), m_intercept(intercept) {}
  virtual int invoke(int x) { return static_cast<int>(m_slope * x + m_intercept); }
};

class LimitedFunction : public Function<int, int> {
 private:
  unsigned m_limit;
  Function<int, int> * m_func;
  const char * m_message;

 public:
  LimitedFunction(unsigned limit, Function<int, int> * func, const char * message) :
      m_limit(limit), m_func(func), m_message(message) {}
  virtual int invoke(int x) {
    if (m_limit == 0) {
      fprintf(stderr, "Exceeded allowed calls in %s\n", m_message);
      exit(EXIT_FAILURE);
    }
    --m_limit;
    return m_func->invoke(x);
  }
};

void verify(Function<int, int> * f,
            int low,
            int high,
            int expected,
            const char * description) {
  int maxCalls = (high > low) ? log2(high - low) + 1 : 1;
  LimitedFunction limitedFunc(maxCalls, f, description);
  int result = binarySearchForZero(&limitedFunc, low, high);
  if (result != expected) {
    fprintf(stderr, "Unexpected result: %d in %s\n", result, description);
    exit(EXIT_FAILURE);
  }
}

int main() {
  LinearFunction linearFunc1;
  verify(&linearFunc1, 3, 10, 3, "test1");
  verify(&linearFunc1, -10, 10, 0, "test2");
  verify(&linearFunc1, -10, -1, -2, "test3");
  verify(&linearFunc1, 0, 5, 0, "test4");
  verify(&linearFunc1, -5, 0, -1, "test5");
  verify(&linearFunc1, 5, -5, 5, "test6");
  verify(&linearFunc1, 0, 0, 0, "test7");
  verify(&linearFunc1, -1, -1, -1, "test8");

  LinearFunction linearFunc2(-100, 100);
  verify(&linearFunc2, -100, 100, 1, "test9");

  LinearFunction linearFunc3(-99, 100);
  verify(&linearFunc3, -100, 100, 0, "test10");

  return 0;
}

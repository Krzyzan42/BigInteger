# BigInteger_uni

This is a small c++ project for university. Please do not use in real projects, there exists better, faster and more reliable versions of this.

This project is an implementation of BigInteger from Java. With this implementation, you can add, subtract, multiply, divide and compare arbitrarily big integers. Usage is presented in main.cpp as test cases. 
As a way of storing these integers, BigInteger uses array of decimal digits represented as int. Arithmetic operations are implemented similarly to how you would do these operation on paper. One thing to note is that as you do operations on these numbers, their array size will grow, as all operations allocate enough memory to handle worst case scenarios (multiplication of two 20digit numbers will always allocate array of 40digits) and currently there's no way to shrink these arrays.

Also dividing by 0 returns 0 remainder 0, because we were forbidden to throw exceptions

Usage:
```c++
#include <iostream>
#include "BigInteger.h"

int main() {
  BigInteger a(133245), b(2101275), c(-927159);
  BigInteger d = a*b+c;
  
  std::cout << d.toString() << std::endl; //279983460216
  return 0;
}
```


Plans for the future (unlikely to be implemented):
  * Add exception to division by 0
  * Make arrays automatically smaller for numbers like '00000000000245'
  * Migrate to std::array or std::vector (again, uni constraints)
  * Add power operation
  * Add ability to cast back to int smaller numbers
  * Make operators work with built-in c++ types
  * Optimize algorithms
  * Add modulo operator

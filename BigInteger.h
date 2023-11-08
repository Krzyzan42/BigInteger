#pragma once

#include <iostream>
#include "Array.h"

class BigInteger
{
    // both of these are basically constants
    // only place they change is in constructor
    Array *m_digits;
    bool m_negative;

    // UTILITY FUNCTIONS---------------------------------------------------------------------

    // Recursive function for converting x to a digitArray
    // "digits_left" is needed for recurency
    void intToDigitArray(int x, int digits_left, Array &target) const;

    // Utility function for division and multiplication by hand
    // Multiplies a*digit, stores result in "result"
    // result is required to have length at least a.length + 1
    // result is completely overriden
    void mulByDigit(const Array &a, int digit, Array &result) const;

    // Utility function for divison by hand
    // Returns divident/divisor, but result is in range 0-9
    int howManyFit(const Array &divident, const Array &divisor) const;

    // shifts all digits in an array to the right and sets a[0] = 0
    void shiftRight(Array &a) const;

    // compares two numbers. Returns:
    // a > b -> -1
    // a = b -> 0
    // a < b -> 1 
    int compareUnsigned(const Array &a, const Array &b) const;
    
    // Utility function for substraction by hand
    // Borrows a number, so number[digit_index] will be >= 10
    void borrow(Array &number, int digit_index) const;

    // END OF UTILITY FUNCTIONS-------------------------------------------------------------


    // UNSIGNED OPERATIONS------------------------------------------------------------------

    // Adds two unsigned numbers, stores result in the "result" array
    // b = b * 10^b_offset, this is useful for multiplication
    void addUnsigned(const Array &a, const Array &b, Array &result, int b_offset = 0) const;

    // Subtracts two unsigned numbers, puts resulting number into "result"
    // a is required to be bigger than b, since the result must unsigned
    // Having a smaller than b will result in an undefined behaviour
    void subUnsigned(const Array &a, const Array &b, Array &result) const;

    // Multiplies two unsigned numbers
    Array* mulUnsigned(const Array &a, const Array &b) const;

    // Divides two unsigned numbers
    Array* divUnsigned(const Array &a, const Array &b) const;

    // END OF UNSIGNED OPERATIONS----------------------------------------------------------



    // Adds two signed nubers, returns another signed number
    // This function works out if and how digit should be 
    // added or subtracted and if result is negative
    // then uses "addUnsigned" and "subUnsigned" appropieatly
    std::pair<Array*, bool> addSigned(const Array &a, bool a_neg, const Array &b, bool b_neg) const;

    // Compares two BigIntegers, returns -1 if a>b, 0 if a==b, 1 if a>b
    int compare(const BigInteger &a, const BigInteger &b) const;

    // This constructor claims ownership of the "digits"
    BigInteger(Array *digits, bool negative);
public:
    // Defaults to BigInteger(0)
    BigInteger();

    BigInteger(int number);

    // Creates deep copy of the "other"
    BigInteger(const BigInteger &other);

    BigInteger operator-() const;
    BigInteger operator+(const BigInteger &other) const;
    BigInteger operator-(const BigInteger &other) const;
    BigInteger operator*(const BigInteger &other) const;
    BigInteger operator/(const BigInteger &other) const;
    BigInteger operator++() const;
    BigInteger operator--() const;
    bool operator<(const BigInteger &other) const;
    bool operator<=(const BigInteger &other) const;
    bool operator==(const BigInteger &other) const;
    bool operator!=(const BigInteger &other) const;
    bool operator>=(const BigInteger &other) const;
    bool operator>(const BigInteger &other) const;

    std::string toString() const;
};
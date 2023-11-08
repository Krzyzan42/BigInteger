#include "BigInteger.h"
#include <math.h>
#include <string.h>

void BigInteger::intToDigitArray(int x, int digits_left, Array &target) const
{
    if (digits_left == 0)
        return;

    int digit = x % 10;
    target[target.length() - digits_left] = digit;

    int reduced = floor(1.0 * x / 10);
    intToDigitArray(reduced, digits_left - 1, target);
}

void BigInteger::borrow(Array &number, int digit_index) const
{
    int next_index = digit_index + 1;
    if (number[next_index] == 0)
        borrow(number, next_index);

    number[next_index] -= 1;
    number[digit_index] += 10;
}

void BigInteger::mulByDigit(const Array &a, int digit, Array &result) const
{
    const int a_len = a.length();
    int carry = 0;

    for (int i = 0; i < result.length(); i++)
    {
        int a_val = a.length() > i ? a[i] : 0;

        int mul_result = digit * a_val + carry;
        carry = floor(1.f * mul_result / 10.f);
        result[i] = mul_result % 10;
    }
}

// returns divident/divisor capped by 9
// Just keeps multiplying divisor until its bigger than divident
int BigInteger::howManyFit(const Array &divident, const Array &divisor) const
{
    Array result(divisor.length() + 1);
    for (int i = 1; i < 10; i++)
    {
        mulByDigit(divisor, i, result);
        int c_res = compareUnsigned(divident, result);
        if (c_res == 1)
            return i - 1;
        else if (c_res == 0)
            return i;
    }
    return 9;
}

void BigInteger::shiftRight(Array &a) const
{
    for (int i = a.length() - 1; i >= 1; i--)
        a[i] = a[i - 1];
    a[0] = 0;
}

int BigInteger::compareUnsigned(const Array &a, const Array &b) const
{
    for (int i = std::max(a.length(), b.length()) - 1; i >= 0; i--)
    {
        int a_val = a.length() > i ? a[i] : 0;
        int b_val = b.length() > i ? b[i] : 0;

        if (a_val > b_val)
            return -1;
        else if (a_val < b_val)
            return 1;
    }
    return 0;
}

// Algorthm for addition by hand
void BigInteger::addUnsigned(const Array &a, const Array &b, Array &c, int b_offset) const
{
    int carry = 0;
    for (int i = 0; i < c.length(); i++)
    {
        int a_val = a.length() > i ? a[i] : 0; 
        int b_val = 0;
        if (0 <= i - b_offset && i - b_offset < b.length())
            b_val = b[i - b_offset];

        int sum = a_val + b_val + carry;
        if (sum >= 10)
        {
            sum -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        c[i] = sum;
    }
}

// Algorithm for subtraction by hand
// Puts result in c
void BigInteger::subUnsigned(const Array &a, const Array &b, Array &c) const
{
    int c_len = std::max(a.length(), b.length());
    c.fill(0);

    for (int i = 0; i < a.length(); i++)
        c[i] = a[i];

    for (int i = 0; i < c_len; i++)
    {
        int b_val = b.length() > i ? b[i] : 0;
        int c_val = c[i];

        if (c_val < b_val)
        {
            borrow(c, i);
            c_val = c[i];
        }

        c[i] = c_val - b_val;
    }
}

// Algorithm for multiplication by hand
Array* BigInteger::mulUnsigned(const Array &a, const Array &b) const
{
    // Prepare algorithm
    Array *components = new Array[b.length()];
    for (int i = 0; i < b.length(); i++)
        components[i] = Array(a.length() + 1);

    // Calculate all components
    for (int i = 0; i < b.length(); i++)
        mulByDigit(a, b[i], components[i]);

    // Add all of the components
    Array *read_buffer = new Array(a.length() + b.length());
    Array *write_buffer = new Array(a.length() + b.length());
    read_buffer->fill(0);
    write_buffer->fill(0);
    for (size_t i = 0; i < b.length(); i++)
    {
        addUnsigned(*read_buffer, components[i], *write_buffer, i);

        Array *t = read_buffer;
        read_buffer = write_buffer;
        write_buffer = t;
    }
    
    delete write_buffer;
    delete[] components;

    return read_buffer;
}

// Algorithm for subtraction by hand
Array* BigInteger::divUnsigned(const Array &a, const Array &b) const
{
    Array *result_p = new Array(a.length());
    Array *minuend_p = new Array(a.length());
    Array &minuend = *minuend_p;
    Array subtrahend(b.length() + 1);
    subtrahend.fill(0);
    minuend.fill(0);

    for (int i = a.length() - 1; i >= 0; i--)
    {
        shiftRight(minuend);
        minuend[0] = a[i];
        int multiplier = howManyFit(minuend, b);
        (*result_p)[i] = multiplier;
        mulByDigit(b, multiplier, subtrahend);
        Array buffor = minuend;
        subUnsigned(buffor, subtrahend, minuend);
    }

    delete minuend_p;
    return result_p;
}

std::pair<Array*, bool> BigInteger::addSigned(  const Array &a, bool a_neg, 
                                                const Array &b, bool b_neg) const
{
    Array *result = new Array(std::max(a.length(), b.length()) + 1);
    bool negate = false;

    if (a_neg != b_neg)
    {
        // Signs don't match -> do subtraction
        const Array *left = &a, *right = &b;
        if (a_neg)
        {
            const Array *temp = left; // Put negative number on the 'right' side
            left = right;
            right = temp;
        }
        if (compareUnsigned(*left, *right) > 0)
        {
            // If negative number is bigger, put it on the left side
            // do left-right and negate result
            const Array *temp = left; 
            left = right;
            right = temp;
            negate = true;
        }
        subUnsigned(*left, *right, *result);
    }
    else
    {
        // Signs match -> do addition
        if (a_neg)
            negate = true;
        addUnsigned(a, b, *result);
    }

    return std::pair<Array*, bool>(result, negate);
}

int BigInteger::compare(const BigInteger &a, const BigInteger &b) const
{
    if(a.m_negative == b.m_negative) {
        if(a.m_negative == false) 
            return compareUnsigned(*a.m_digits, *b.m_digits);
        else
            return compareUnsigned(*b.m_digits, *a.m_digits);
    } else {
        if(a.m_negative == true) 
            return 1;
        else 
            return -1;
    }
}

BigInteger::BigInteger(Array *table, bool negative)
{
    m_digits = table;
    m_negative = negative;
};

BigInteger::BigInteger()
{
    m_digits = new Array(0);
    m_negative = false;
}

BigInteger::BigInteger(int number)
{
    if (number == 0)
    {
        m_digits = new Array(0);
        m_negative = false;
        return;
    }
    else if (number < 0)
    {
        m_negative = true;
        number = -number;
    }
    else
    {
        m_negative = false;
    }

    int digit_count = ceil(log10(1.f * number + 1));
    m_digits = new Array(digit_count);
    intToDigitArray(number, digit_count, *m_digits);
}

BigInteger::BigInteger(const BigInteger &other)
{
    m_negative = other.m_negative;
    m_digits = new Array(*other.m_digits);
}

BigInteger BigInteger::operator-() const
{
    if (m_digits->length() == 0)
        return BigInteger(0);

    Array *copy = new Array(*m_digits);
    return BigInteger(copy, !m_negative);
}

BigInteger BigInteger::operator+(const BigInteger &other) const
{
    std::pair<Array*, bool> c = addSigned(
        *this->m_digits, this->m_negative, 
        *other.m_digits, other.m_negative
    );
    return BigInteger(c.first, c.second);
}

BigInteger BigInteger::operator-(const BigInteger &other) const
{
    std::pair<Array*, bool> c = addSigned(
        *this->m_digits, this->m_negative, 
        *other.m_digits, !other.m_negative
    );
    return BigInteger(c.first, c.second);
}

BigInteger BigInteger::operator*(const BigInteger &other) const
{
    Array *result = mulUnsigned(*m_digits, *other.m_digits);
    return BigInteger(result, m_negative != other.m_negative);
}

BigInteger BigInteger::operator/(const BigInteger &other) const
{
    if (compareUnsigned(*m_digits, *other.m_digits) == 1)
        return BigInteger(0);   // divisior is bigger than divident
    if (compareUnsigned(Array(0), *other.m_digits) == 0)
        return BigInteger(0);   // divisor is 0

    Array *res = divUnsigned(*m_digits, *other.m_digits);
    bool res_negative = m_negative != other.m_negative;
    return BigInteger(res, res_negative);
}

BigInteger BigInteger::operator++() const
{
    return (*this) + BigInteger(1);
}

BigInteger BigInteger::operator--() const
{
    return (*this) - BigInteger(1);
}

bool BigInteger::operator<(const BigInteger &other) const
{
    return compare(*this, other) == 1;
}

bool BigInteger::operator<=(const BigInteger &other) const
{
    return compare(*this, other) != -1;
}

bool BigInteger::operator==(const BigInteger &other) const
{
    return compare(*this, other) == 0;
}

bool BigInteger::operator!=(const BigInteger &other) const
{
    return compare(*this, other) != 0;
}

bool BigInteger::operator>=(const BigInteger &other) const
{
    return compare(*this, other) != 1;
}

bool BigInteger::operator>(const BigInteger &other) const
{
    return compare(*this, other) == -1;
}

std::string BigInteger::toString() const
{
    std::string str = "";

    int i = m_digits->length() - 1;
    while ((*m_digits)[i] == 0) // Skip zeros
        i--;

    for (; i >= 0; i--) // Write numbers to string
        str += '0' + (*m_digits)[i];

    if (str == "") // replace emtpy string with 0
        str = "0";

    if (m_negative && str != "0") // add negative sign
        str = "-" + str;

    return str;
}
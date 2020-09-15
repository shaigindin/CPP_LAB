// Created by shai.gindin on 8/27/19.
//

#include "GField.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include "GFNumber.h"

/**
* check whether p is prime or not
* @return _n const reference
*/
bool GField::isPrime(long p)
{
    p = labs(p);
    if (p <= 1)
    {
        return false;
    }
    long squareN = (long) sqrt(p);
    for (long i = 2; i <= squareN; i++)
    {
        if ( (p % i) == 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * A constructor.
 * intialize p and l from user's input
 */
GField::GField(long p, long l)
{
    p = labs(p);
    _checkInputValidity(p, l);
    _l = l;
    _p = p;
}

/**
* operator= overloading
* @param other - the other object to copy from
* @return - reference to this object
*/
GField& GField::operator=(const GField &other)
{
    this->_l = other._l;
    this->_p = other._p;
    return *this;
}

/**
 * this global function prints the object to output stream
 * @param out - output object
 * @param field - field object
 * @return
 */
std::ostream &operator<<(std::ostream &out, const GField &field)
{
    return out << "GF(" << field._p << "**" << field._l << ")";
}



void GField::_checkInputValidity(long p, long l)
{
    assert(p >= 2);
    assert(l > 0);
    assert(isPrime(p));
}

/**
 * this global function gets data from user to field object
 * @param in
 * @param field
 * @return
 */
std::istream &operator>>(std::istream &in, GField &field)
{
    in >> field._p >> field._l;
    field._checkInputValidity(field._p, field._l);
    return in;
}

GFNumber GField::gcd(const GFNumber &a, const GFNumber &b) const
{
    assert(a.getField() == b.getField());
    assert(a.getField() == *this);
    long result = _gcdHelper(a.getNumber(), b.getNumber());
    return GFNumber(result, a.getField());
}

long GField::_gcdHelper(long a, long b) const
{
    while (a >= 0 && b >= 0)
    {
        if (a == 0)
        {
            return b;
        }
        else if (b == 0)
        {
            return a;
        }
        else if (a == b)
        {
            return a;
        }
        else if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    return 0; // to avoidwarning. the code never reach hear.
}

/**
 * this function get long and return GFNumber object
 * @param k
 * @return
 */
GFNumber GField::createNumber(long k)
{
    return GFNumber(k, *this);
}

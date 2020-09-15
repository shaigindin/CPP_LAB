
#include <random>
#include <iostream>
#include "GFNumber.h"
#include <cassert>
#include <cmath>

using std::cout;

const int FAILURE = -1;
const int FINISH = 1;
const int NOT_FINISH = 0;

/**
 * checks whtether _number is prime
 * @return
 */
bool GFNumber::getIsPrime()
{
    long fieldNum = _number % _gfield.getOrder();
    return GField::isPrime(fieldNum);
}

/**
 *  this function recieve long n and convert it to the field number i.e if infinte field of 7: 8 -> 1
 * @param n
 * @return
 */
long GFNumber::_convertToFieldNum(long n)
{
    if (n < 0)
    {
        return (n % _gfield.getOrder()) + _gfield.getOrder();
    }
    else
    {
        return n % _gfield.getOrder();
    }

}

/**
 * function find the number primes
 * @return
 */
GFNumber*GFNumber::getPrimeFactors(int* n)
{
    GFNumber* copyArray = nullptr;
    if (!_flag)
    {
        _findPrimes(_number);
        _flag = true;
    }
    copyArray = new GFNumber[_sizeOfArray];
    for (int i = 0; i < _sizeOfArray; i++)
    {
        copyArray[i] = GFNumber(_arr[i], getField());
    }
    if (_sizeOfArray == 1)
    {
        *n = 0;
    }
    else
    {
        *n = _sizeOfArray;
    }
    return copyArray;
}

/**
 * function check whether two GFNumbers are with the same field
 * @param other
 * @return
 */
bool GFNumber::_isSameField(const GFNumber &other) const
{
    return other._gfield == _gfield ;
}

/**
 * this global function prints the object to output stream
 * @param out - output object
 * @param field - GFNumber object
 * @return
 */
ostream &operator<<(ostream &out, const GFNumber &gfnumber)
{
    out << gfnumber._number << " " << gfnumber._gfield;
    return out;
}

/**
 * this global function gets data from user to field object
 * @param in
 * @param field
 * @return
 */
istream& operator>>(istream &in, GFNumber &gfNumber)
{
    long n, p, l;
    in >> n >> p >> l;
    GField tempField(p, l);
    GFNumber tempGFNumber(n, tempField);
    gfNumber = tempGFNumber;
    return in;
}

/**
 * add two objects
 * @param other
 * @return
 */
const GFNumber GFNumber::operator+(const GFNumber &other) const
{
    assert(_isSameField(other));
    return GFNumber(_number + other._number, _gfield);
}

/**
 * add one object to other object
 * @param other
 * @return
 */
GFNumber& GFNumber::operator+=(const GFNumber &other)
{
    assert(_isSameField(other));
    _number = _convertToFieldNum(this->_number + other._number);
    return *this;
}

/**
 * subtract two objects
 * @param other
 * @return
 */
const GFNumber GFNumber::operator-(const GFNumber &other) const
{
    assert(_isSameField(other));
    return GFNumber(_number - other._number, _gfield);
}

/**
 * add one object to other object
 * @param other
 * @return
 */
GFNumber &GFNumber::operator-=(const GFNumber &other)
{
    assert(_isSameField(other));
    _number = _convertToFieldNum(_number - other._number);
    return *this;
}

/**
 * Multiple two objects
 * @param other
 * @return
 */
const GFNumber GFNumber::operator*(const GFNumber &other) const
{
    assert(_isSameField(other));
    return GFNumber(_number * other._number, _gfield);
}

/**
 * multiple one object with other object and saves it to this field
 * @param other
 * @return
 */
GFNumber &GFNumber::operator*=(const GFNumber &other)
{
    assert(_isSameField(other));
    _number = _convertToFieldNum(_number * other._number);
    return *this;
}

/**
 * return GFNumber which is the reamaning of this dvided by other
 * @param other
 * @return
 */
const GFNumber GFNumber::operator%(const GFNumber &other) const
{
    assert(_isSameField(other));
    assert(other._number != 0);
    return GFNumber(_number % other._number, _gfield);
}

/**
 * calculate the reamaning of this dvided by other and saves it to this field
 * @param other
 * @return
 */
GFNumber &GFNumber::operator%=(const GFNumber &other)
{
    assert(_isSameField(other));
    assert(other._number != 0);
    _number = _convertToFieldNum(_number % other._number);
    return *this;
}

/**
 * return true if two objects  are equal
 * @param other
 * @return
 */
bool GFNumber::operator==(const GFNumber &other)
{
    return (_gfield == other._gfield) && (_number == other._number);
}

/**
 * return true if two objects are not equal
 * @param other
 * @return
 */
bool GFNumber::operator!=(const GFNumber &other)
{
    return (_gfield != other._gfield) || (_number != other._number);
}

/**
 * return true if this object is bigger than other
 * @param other
 * @return
 */
bool GFNumber::operator>(const GFNumber &other)
{
    assert(_isSameField(other));
    return (_number > other._number);
}

/**
 * return true if this object is bigger or equal than other
 * @param other
 * @return
 */
bool GFNumber::operator>=(const GFNumber &other)
{
    assert(_isSameField(other));
    return (_number >= other._number);
}

/**
 * return true if this object is smaller than other
 * @param other
 * @return
 */
bool GFNumber::operator<(const GFNumber &other)
{
    assert(_isSameField(other));
    return (_number < other._number);
}

/**
 * return true if this object is smaller or equal than other
 * @param other
 * @return
 */
bool GFNumber::operator<=(const GFNumber &other)
{
    assert(_isSameField(other));
    return (_number <= other._number);
}

/**
 * add object with long
 * @param other
 * @return
 */
const GFNumber GFNumber::operator+(long other) const
{
    return GFNumber(other, _gfield) + *this;
}

/**
 * add long to this object
 * @param other
 * @return
 */
GFNumber& GFNumber::operator+=(long other)
{
    return (*this += GFNumber(other, _gfield));
}

/**
 * subtract (object - long)
 * @param other
 * @return
 */
const GFNumber GFNumber::operator-(long other) const
{

    return *this - GFNumber(other, _gfield);
}

/**
 * subtract long from object
 * @param other
 * @return
 */
GFNumber &GFNumber::operator-=(long other)
{
    return (*this -= GFNumber(other, _gfield));
}

/**
 * Multiple this objects with long
 * @param other
 * @return
 */
const GFNumber GFNumber::operator*(long other) const
{
    return *this * GFNumber(other, _gfield);
}

/**
 * multiple one object with long and saves it to this field
 * @param other
 * @return
 */
GFNumber &GFNumber::operator*=(long other)
{
    return (*this *= GFNumber(other, _gfield));
}

/**
 * return GFNumber which is the reamaning of this divided by other
 * @param other
 * @return
 */
const GFNumber GFNumber::operator%(long other) const
{
    return *this % GFNumber(other, getField());
}

/**
 * calculate the reamaning of this dvided by other and saves it to this field
 * @param other
 * @return
 */
GFNumber& GFNumber::operator%=(long other)
{
    GFNumber temp(other, getField());
    *this = *this % temp;
    return *this;
}

long GFNumber::_pollardRho(long n)
{
    long num =  n;
    long a = _getRandomNum(num);
    long b = a;
    long d = 1;
    while (d == 1)
    {
        a = _pollardFunction(a, num);
        b = _pollardFunction(_pollardFunction(b, num), num);
        d = getField()._gcdHelper(labs(a - b), num);
        if (d == num)
        {
            return FAILURE;
        }
    }
    return d;
}


/**
 * function find random number from 1 to n-1
 * @param n
 * @return
 */
long GFNumber::_getRandomNum(long n)
{
    //this code is copied from stack overflow because i didnt know how to random long safely
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long> dis(1, (unsigned long)n-1);
    return dis(gen);
}

/**
 * this function takes n and puts it in X^2+1 and return result
 * @param n
 * @return
 */
long GFNumber::_pollardFunction(long a, long n)
{
    return ((a*a) + 1) % n;
}

/**
 * return true if long and object  are equal
 * @param other
 * @return
 */
bool GFNumber::operator==(long other)
{
    return (*this == GFNumber(other, getField()));
}

/**
 * this function gets an array and extend it by one and add a number
 * @param arr - aray of longs
 * @param n  - element needed to add
 */
void GFNumber::_append(long n)
{
    long *temp = new long[_sizeOfArray + 1];
    for (int i = 0; i < _sizeOfArray; i++)
    {
        temp[i] = _arr[i];
    }
    temp[_sizeOfArray] = n;
    delete[] _arr;
    _arr = temp;
    _sizeOfArray++;
}



/**
 * find primes in the usual way
 * @param p - the number i want to find its prime
 * @param n - a reference to the original number i want to find is primes.
 */

void GFNumber::_findPrimeHelper(long p, long &n)
{
    for (int i = 3; i <= sqrt(p); i = i + 2) //because i care only from odd numbers so i add two each time
    {
        while (p % i == 0)
        {
            _append(i);
            p = p / i;
            n = n / i;
        }
    }
    if (p > 2) // it means p is prime
    {
        _append(p);
        n = n / p;
    }
}

/**
 * this function prints the prime which the number made from
 */
void GFNumber::printFactors()
{
    fflush(stdout);
    if (!_flag) //if flag is true it means there is allready prime factors of _number
    {
        _findPrimes(_number);
        fflush(stdout);
        _flag = true;
    }
    fflush(stdout);
    if (_sizeOfArray == 1) // it means _number is prime itself
    {
        cout << _number << "=" << _number << "*1" << std::endl;
    }
    else
    {
        cout << _number << "=";
        for (int i = 0; i < _sizeOfArray; i++)
        {
            if (i == _sizeOfArray - 1) //it is mean it is the last element in the array
            {
                cout << _arr[i] << std::endl;
            }
            else
            {
                cout << _arr[i] << "*";
            }
        }
    }

}

/**
 * find the primes of n using two ways of algorithms. the usual and pollards
 */
void GFNumber::_findPrimes(long n)
{
    int check = _checkPriorConditions(n);
    if (check == FINISH)
    {
        return;
    }
    long p = _pollardRho(n); // now i am sure n is odd and not prime
    while ( p != FAILURE) // if p is -1 it means Polard algorithm failed
    {
        if (GField::isPrime(p))
        {
            _append(p);
            n = n / p;
        }
        else
        {
            _findPrimeHelper(p, n);
        }
        p = _pollardRho(n);
    }
    long nDammy = n; // i want to save code so i call fine prime helper with a dammy variable
    _findPrimeHelper(n, nDammy);
}

/**
 * this function helps with pre calculation for findprimes. i did it to make findprimes function shorter
 * @param n
 */
int GFNumber::_checkPriorConditions(long& n)
{
    fflush(stdout);
    if ((n == 1) || (n == 0)) //deals with special cases 1 and 0
    {
        _append(n);
        return FINISH;
    }
    while (n % 2 == 0) // if n is still even. divided by two and add 2 to primes array
    {
        _append(2);
        n = n / 2;
    }
    if (n == 1) // if n ==1 it means _number = 2^x , x is a positive integer
    {
        return FINISH;
    }
    if (GField::isPrime(n)) // if n is prime
    {
        _append(n);
        return FINISH;
    }
    return NOT_FINISH;
}

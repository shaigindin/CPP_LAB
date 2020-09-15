
#ifndef EX1FINAL_GFNUMBER_H
#define EX1FINAL_GFNUMBER_H
#include "GField.h"
#include <iostream>

using std::ostream;
using std::istream;

/**
 * GFNumbewr is calss which represent a number in GFIELD
 */
class GFNumber
{
private:
    /* ------------------------------------- Private Fields ----------------------------------------------- */

    GField _gfield; /** a gfield object which the GFNumber belgogns to*/
    long _number; /** the number of the object*/
    bool _flag; /** indicator if the function getprime was called once or not*/
    int _sizeOfArray; /** holds the number of element in the primes */
    long* _arr; /** holds the prime numbers of n*/



    /* ------------------------------------- Private Methods ----------------------------------------------- */

    /**
     *  this function recieve long n and convert it to the field number i.e if infinte field of 7: 8 -> 1
     * @param n
     * @return
     */
    long _convertToFieldNum(long n);

    /**
     * this function helps with pre calculation for findprimes. i did it to make findprimes function shorter
     * @param n
     */
    int _checkPriorConditions(long& n);

    /**
     * function check whether two GFNumbers are with the same field
     * @param other
     * @return
     */
    bool _isSameField(const GFNumber &other) const;



    /**
     * function find random number from 1 to n-1
     * @param n
     * @return
     */
    long _getRandomNum(long n);

    /**
     * this function gets an array and extend it by one and add a number
     * @param arr - aray of longs
     * @param n  - element needed to add
     */
    void _append(long n);

    /**
     * find the primes of n using two ways of algorithms. the usual and pollards
     */
    void _findPrimes(long n);

    /**
     * find primes in the usual way
     * @param p - the number i want to find its prime
     * @param n - a reference to the original number i want to find is primes.
     */
    void _findPrimeHelper(long p, long &n);

    /**
     * this function takes n and puts it in X^2+1 and return result
     * @param n
     * @return
     */
    long _pollardFunction(long a, long n);

    /**
    * method uses polard algo to find prime of n
    * @param n
    * @return
    */
    long _pollardRho(long n);

public:

    /* ------------------------------------- Constructors ----------------------------------------------- */

    /**
     * A constructor.
     * intialize _number and _gfield
     */
    GFNumber(long n, const GField& gfield): _gfield(gfield), _flag(false),
                                            _sizeOfArray(0), _arr(nullptr)
    {
        _number = _convertToFieldNum(n);
    }

    /**
     * a constructor which intilize _number from user and default field (2,1)
     * @param n
     */
    GFNumber(long n) : GFNumber(n, GField(2, 1) ) {}

    /**
     * default constructor
     */
    GFNumber() : GFNumber(0, GField(2, 1) ) {}

    /**
     * free dynamic memory of _arr;
     */
    ~GFNumber()
    {
        delete[] _arr;
    }

    /* ------------------------------------- Public Methods ----------------------------------------------- */

    /**
     * this function prints the prime which the number made from
     */
    void printFactors();


    /**
     * _number getter
     * @return
     */
    long getNumber() const
    {
        return _number;
    }

    /**
     * field getter
     * @return
     */
    GField getField() const
    {
        return _gfield;
    }

    /**
     * checks whtether _number is prime
     * @return
     */
    bool getIsPrime();

    /**
     * function find the number primes
     * @return
     */
    GFNumber* getPrimeFactors(int* n);

    /* ------------------------------------- Operators ----------------------------------------------- */


    /**
     * add two objects
     * @param other
     * @return
     */
    const GFNumber operator+(const GFNumber& other) const;

    /**
     * add object with long
     * @param other
     * @return
     */
    const GFNumber operator+(long other) const;

    /**
     * add one object to other object
     * @param other
     * @return
     */
    GFNumber& operator +=(const GFNumber& other);

    /**
     * add long to this object
     * @param other
     * @return
     */
    GFNumber& operator +=(long other);

    /**
     * subtract two objects
     * @param other
     * @return
     */
    const GFNumber operator-(const GFNumber& other) const;

    /**
     * subtract (object - long)
     * @param other
     * @return
     */
    const GFNumber operator-(long other) const;

    /**
     * add one object to other object
     * @param other
     * @return
     */
    GFNumber& operator-=(const GFNumber& other);

    /**
     * subtract long from object
     * @param other
     * @return
     */
    GFNumber& operator-=(long other);

    /**
     * Multiple two objects
     * @param other
     * @return
     */
    const GFNumber operator*(const GFNumber& other) const;

    /**
     * Multiple this objects with long
     * @param other
     * @return
     */
    const GFNumber operator*(long other) const;

    /**
     * multiple one object with other object and saves it to this field
     * @param other
     * @return
     */
    GFNumber& operator*=(const GFNumber& other);

    /**
     * multiple one object with long and saves it to this field
     * @param other
     * @return
     */
    GFNumber& operator*=(long other);

    /**
     * return GFNumber which is the reamaning of this dvided by other
     * @param other
     * @return
     */
    const GFNumber operator%(const GFNumber& other) const;

    /**
     * return GFNumber which is the reamaning of this divided by other
     * @param other
     * @return
     */
    const GFNumber operator%(long other) const;

    /**
     * calculate the reamaning of this dvided by other and saves it to this field
     * @param other
     * @return
     */
    GFNumber& operator%=(const GFNumber& other);

    /**
     * calculate the reamaning of this dvided by other and saves it to this field
     * @param other
     * @return
     */
    GFNumber& operator%=(long other);

    /**
     * return true if two objects  are equal
     * @param other
     * @return
     */
    bool operator==(const GFNumber &other);

    /**
     * return true if long and object  are equal
     * @param other
     * @return
     */
    bool operator==(long other);

    /**
     * return true if two objects are not equal
     * @param other
     * @return
     */
    bool operator!=(const GFNumber &other);

    /**
     * return true if this object is bigger than other
     * @param other
     * @return
     */
    bool operator>(const GFNumber& other);

    /**
     * return true if this object is bigger or equal than other
     * @param other
     * @return
     */
    bool operator>=(const GFNumber& other);

    /**
     * return true if this object is smaller than other
     * @param other
     * @return
     */
    bool operator<(const GFNumber& other);

    /**
     * return true if this object is smaller or equal than other
     * @param other
     * @return
     */
    bool operator<=(const GFNumber& other);


    /* ------------------------------------- Friends ----------------------------------------------- */

    /**
     * this global function prints the object to output stream
     * @param out - output object
     * @param field - GFNumber object
     * @return
     */
    friend ostream& operator<<(ostream& out, const GFNumber& gfnumber);

    /**
     * this global function gets data from user to field object
     * @param in
     * @param field
     * @return
     */
    friend istream& operator>>(istream& in, GFNumber& gfNumber);
};


#endif //EX1FINAL_GFNUMBER_H
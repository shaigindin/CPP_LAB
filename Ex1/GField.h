// Created by shai.gindin on 8/27/19.
//

#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H
#include <cmath>
#include <iostream>

/**
 * let the compiler knows that there is such a calss
 */
class GFNumber;



/**
 *  GField class.
 *  This class represents a Field with |Fn|=l^p .
 */
class GField
{
private:

    /* ------------------------------------- Fields ----------------------------------------------- */

    long _p; /** the smallest number of times one must use the ring's multiplicative identity (1) in a sum to
            * get the additive identity (0) */

    long _l; /** the degree of the field */

    /* ------------------------------------- Private Methods ----------------------------------------------- */

    /**
     * a private function which checks whther the inpt p is prime and positive and l is integer bigger -1
     * @param p - long which represent prime number
     * @param l - long which represent the degree.
     */
    void _checkInputValidity(long p, long l);

    /**
     * calculate the gcd of a and b
     * @param a - long
     * @param b - long
     * @return  = the gcd of a and b
     */
    long _gcdHelper(long a, long b) const;

public:

    /* ------------------------------------- Constructors ----------------------------------------------- */

    /**
     * A constructor.
     * intialize p and l from user's input
     */
    GField(long p, long l);

    /**
     * A constructor.
     * intialize p and 1(default stettings) from user's input.
     */
    GField(long p) : GField(p, 1) {}

    /**
     * A constructor.
    * intialize 2 and l as default settings
    */
    GField() : GField(2, 1) {}

    /**
     * copy constructor that behave like default copy constructor
     * @param other - the other objject to copy
     */
    GField(const GField &other): GField(other._p, other._l) {}

    //    ~GField();


    /* ------------------------------------- Public Methods ----------------------------------------------- */

    /**
    * Access method for the _p value.
    * @return _p const reference
    */
    const long& getChar()
    {
        return _p;
    }

    /**
    * Access method for the _l value.
    * @return _l const reference
    */
    const long& getDegree()
    {
        return _l;
    }

    /**
    * Access method for the _n value.
    * @return _n const reference
    */
    long getOrder()
    {
        return (long) powl(_p, _l);
    }



    /**
     * this method calculate the gcd of two GFNumber objects
     * @param a
     * @param b
     * @return
     */
    GFNumber gcd(const GFNumber& a, const GFNumber& b) const;

    /**
     * this function get long and return GFNumber object
     * @param k
     * @return
     */
    GFNumber createNumber(long k);

    /* ------------------------------------- Operators ----------------------------------------------- */

    /**
    * operator= overloading
    * @param other - the other object to copy from
    * @return - reference to this object
    */
    GField& operator=(const GField &other);

    /**
     * check whether two fields are equal
     * @param other
     * @return  true or false
     */
    bool operator==(const GField& other) const
    {
        return (powl(_p, _l) == powl(other._p, other._l));
    }

    /**
     * check whether two fields are not equal
     * @param other
     * @return
     */
    bool operator!=(const GField& other) const
    {
        return (powl(_p, _l) != powl(other._p, other._l));
    }



    /* ------------------------------------- Static ----------------------------------------------- */

    /**
    * check whether p is prime or not
    * @return _n const reference
    */
    static bool isPrime(long p);

    /* ------------------------------------- Friends ----------------------------------------------- */

    /**
     * this global function prints the object to output stream
     * @param out - output object
     * @param field - field object
     * @return
     */
    friend std::ostream& operator<<(std::ostream& out, const GField& field);


    /**
     * this global function gets data from user to field object
     * @param in
     * @param field
     * @return
     */
    friend std::istream& operator>>(std::istream& in, GField& field);

    /**
     * to use GCD helper function
     */
    friend GFNumber;
};

#endif //EX1_GFIELD_H
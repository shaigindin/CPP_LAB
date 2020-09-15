//
// Created by shai gindin on 06/09/2019.
//

#ifndef CPPEX2_FRACTAL_H
#define CPPEX2_FRACTAL_H


/**
 * Ftactal class is an abstract class which all the real Fractals inheirets from
 */
class Fractal
{
protected:
    int depth{}; /** keep the demension of the fractal*/
    int base{}; /** keep the base table of the smallest unit of the Fractal*/
    int size{}; /** keep the size of the array (width / height) of the fractal*/
    char** _p{}; /**  array of chars which represnt the Fractal shape*/
    bool flag{}; /** if array is already filled so no need to do it again*/

    /**
     * a static function which print the shape
     * @param size - the size of the array
     * @param p - pointer to the array
     */
    static void printShape(int size, char** p);

    /**
     * free the memory for pointer _p 2d array
     * @param _p
     * @param size
     */
    static void deleteArray(char** _p, int size);

    /**
     * allocate memory for pointer _p 2d array
     * @param _p
     * @param size
     */
    char** allocateMemoryForArray(int size);

    /**
     * this static funcion copy one array to another
     * @param _p
     * @param pOther
     * @param size
     */
    static void copyArray(char** _p, char** pOther, int size);

public:

    /**
     * default constructor
     */
    Fractal() = default;

    /**
     * Constructor
     * @param n - dimension
     * @param base - base for calculation the array size
     */
    Fractal(int n, int base);

    /**
     * copy constructor of Fractal
     * @param other
     */
    Fractal(const Fractal& other);

    /**
     * move constructor
     * @param other
     */
    Fractal(Fractal && other) noexcept;

    /**
     * operator =
     * @param other
     * @return
     */
    Fractal& operator=(const Fractal& other);

    /**
     * move assigment
     * @param other
     * @return
     */
    Fractal& operator=(Fractal && other) noexcept;

    /**
     * destructor
     */
    virtual ~Fractal();

    /**
     * abstract function draw. draw the Fractal Shape with ASCII art on screen
     */
    virtual void draw() = 0;

    /**
     * a static function which create the correct shape and send a pointer back
     * @param n
     * @param shapeType
     * @return
     */
    static Fractal* listFactory(int n, int shapeType);


};


#endif //CPPEX2_FRACTAL_H

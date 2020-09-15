//
// Created by shai gindin on 06/09/2019.
//
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Include *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

#include <iostream>
#include "Fractal.h"
#include <cmath>

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Global Constants  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

static const char BLANK = ' '; /** fill the grid with blank color */
static const char COLOR = '#'; /** fill the grid with "color" */
static const int ADJUST_ARRAY_INDEX_BY_ONE = 1; /** adjust the index by one */
static const int MOVE_ONE_GRID = 1; /** Adjust grid index by one  */
static const int MOVE_TWO_GRIDS = 2; /** Adjust grid index by two  */
static const int MOVE_THREE_GRIDS = 3; /** Adjust grid index by three  */
static const int FIRST_GRID = 1; /** the first grid in the table (not index) */
static const int BASE_TABLE_FOR_DUST = 3; /** the base table is 3x3*/
static const int BASE_TABLE_FOR_SIEVE = 2; /** the base table is 2x2 */
static const int BASE_TABLE_FOR_CARPET = 3; /** the base table is 3x3 */
static const int MOVE_ONE_LEVEL_DOWN = 1;  /** adjust the index by one */
static const int BASE_CASE = 1; /** the base case of recursion */

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Using Shortcuts  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

using std::cout;
using std::endl;

//-------------------==================== Inner Class Dust  ======================---------------

/**
 * this class represent a Cantor Dust Fractal
 */
class Dust : public Fractal
{
private:
    /**
     * this helper function build the array which represent the shape of the fractal using recursion
     * @param level - the depth of the recursion
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param x2 - the buttom right index of the range (x2,y2)
     * @param y2 - the buttom right index of the range (x2,y2)
     * @param size - the current size of the range
     * @param symbol - the symbol which fill the cells in the range
     */
    void _buildArray(int level, int x1, int y1, int x2, int y2, int size, char symbol)
    {
        size = size / BASE_TABLE_FOR_DUST;
        if (level == BASE_CASE)
        {
            _putInArray(x1 , y1 , symbol);
        }
        else
        {
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 , y1 , x1 + size - MOVE_ONE_GRID,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 , y1 + size ,
                    x1 + size - MOVE_ONE_GRID,
                        y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID , size , BLANK);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 , y1 + MOVE_TWO_GRIDS * size ,
                        x1 + size - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID, size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + size , y1 ,
                        x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID, size, BLANK);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + size , y1 + size,
                        x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID,
                        y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID,
                        size , BLANK);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + size ,
                    y1 + (MOVE_TWO_GRIDS * size),
                    x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID , size , BLANK);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + MOVE_TWO_GRIDS * size , y1 ,
                        x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + MOVE_TWO_GRIDS * size,
                    y1 + size , x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID,
                        y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID , size , BLANK);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + MOVE_TWO_GRIDS * size ,
                        y1 + (MOVE_TWO_GRIDS * size) ,
                        x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID , size , symbol);
        }
    }

    /**
     * this helper function puts the symbol in the basic range area of the array
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param symbol  - # or ' '
     */
    void _putInArray(int x1, int y1, char symbol)
    {
        x1 -= ADJUST_ARRAY_INDEX_BY_ONE;
        y1 -= ADJUST_ARRAY_INDEX_BY_ONE;

        _p[x1][y1] = symbol;
        _p[x1][y1 + MOVE_ONE_GRID] = BLANK;
        _p[x1][y1 + MOVE_TWO_GRIDS] = symbol;

        _p[x1 + MOVE_ONE_GRID][y1] = BLANK;
        _p[x1 + MOVE_ONE_GRID][y1 + MOVE_ONE_GRID] = BLANK;
        _p[x1 + MOVE_ONE_GRID][y1 + MOVE_TWO_GRIDS] = BLANK;

        _p[x1 + MOVE_TWO_GRIDS][y1] = symbol;
        _p[x1 + MOVE_TWO_GRIDS][y1 + MOVE_ONE_GRID] = BLANK;
        _p[x1 + MOVE_TWO_GRIDS][y1 + MOVE_TWO_GRIDS] = symbol;
    }

public:

    /**
     * Dust Constructor
     * @param n
     */
    explicit Dust(int n) : Fractal(n, BASE_TABLE_FOR_DUST)
    {
        if (_p == nullptr)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * copy constructor
     * @param other
     */
    Dust(const Dust& other) : Fractal(other) {}

    /**
     *
     * @param other
     * @return
     */
    Dust& operator=(const Dust& other) = default;


    /**
     *
     * @param other
     * @return
     */
    Dust& operator=(Dust && other) noexcept = default;

    /**
     * move constructor
     * @param other
     */
    Dust(Dust && other) = default;

    /**
     * draw the Fractal Shape with ASCII art on secreen
     */
    void draw() override
    {
        if (!flag)
        {
            int x1 = FIRST_GRID;
            int y1 = FIRST_GRID;
            int x2 = size;
            int y2 = size;
            _buildArray(depth , x1 , y1 , x2 , y2 , size , COLOR);
            flag = true;
        }
        Fractal::printShape(size, _p);
    }
    // need to add operators and move?
};

//--------------================== END Of Inner Class Dust  ==========================-------------

//---------------====================  Inner Class Carpet      =====================---------------

/**
 * this class represent a Sierpinski Carpet Fractal
 */
class Carpet : public Fractal
{
private:

    /**
     * this helper function build the array which represent the shape of the fractal using recursion
     * @param level - the depth of the recursion
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param x2 - the buttom right index of the range (x2,y2)
     * @param y2 - the buttom right index of the range (x2,y2)
     * @param size - the current size of the range
     * @param symbol - the symbol which fill the cells in the range
     */
    void _buildArray(int level, int x1, int y1, int x2, int y2, int size, char symbol)
    {
        size = size / BASE_TABLE_FOR_CARPET;
        if (level == BASE_CASE)
        {
            _putInArray(x1 , y1 , symbol);

        }
        else
        {
            _buildArray(level - MOVE_ONE_GRID , x1 , y1 , x1 + size - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 , y1 + size ,
                    x1 + size - MOVE_ONE_GRID ,
                    y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 , y1 + MOVE_TWO_GRIDS * size ,
                        x1 + size - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 + size , y1 ,
                        x1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 + size , y1 + size ,
                         x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                         y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID ,
                         size , BLANK);
            _buildArray(level - MOVE_ONE_GRID , x1 + size ,
                    y1 + (MOVE_TWO_GRIDS * size) ,
                    x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID ,
                        size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 + MOVE_TWO_GRIDS * size , y1 ,
                        x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 + MOVE_TWO_GRIDS * size ,
                     y1 + size , x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID ,
                     y1 + MOVE_TWO_GRIDS * size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_GRID , x1 + MOVE_TWO_GRIDS * size ,
                        y1 + (MOVE_TWO_GRIDS * size) ,
                        x1 + (MOVE_THREE_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + MOVE_THREE_GRIDS * size - MOVE_ONE_GRID , size , symbol);
        }
    }

    /**
     * this helper function puts the symbol in the basic range area of the array
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param symbol  - # or ' '
     */
    void _putInArray(int x1, int y1, char symbol)
    {
        x1 -= ADJUST_ARRAY_INDEX_BY_ONE;
        y1 -= ADJUST_ARRAY_INDEX_BY_ONE;

        _p[x1][y1] = symbol;
        _p[x1][y1 + MOVE_ONE_GRID] = symbol;
        _p[x1][y1 + MOVE_TWO_GRIDS] = symbol;

        _p[x1 + MOVE_ONE_GRID][y1] = symbol;
        _p[x1 + MOVE_ONE_GRID][y1 + MOVE_ONE_GRID] = BLANK;
        _p[x1 + MOVE_ONE_GRID][y1 + MOVE_TWO_GRIDS] = symbol;

        _p[x1 + MOVE_TWO_GRIDS][y1] = symbol;
        _p[x1 + MOVE_TWO_GRIDS][y1 + MOVE_ONE_GRID] = symbol;
        _p[x1 + MOVE_TWO_GRIDS][y1 + MOVE_TWO_GRIDS] = symbol;
    }

public:

    /**
     * defualt constructor
     */
    Carpet() : Fractal() {};

    /**
     * constructor
     * @param n
     */
    explicit Carpet(int n) : Fractal(n, BASE_TABLE_FOR_CARPET)
    {
        if (_p == nullptr)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * copy constructor
     * @param other
     */
    Carpet(const Carpet& other) : Fractal(other) {}

    /**
     * move constructor
     * @param other
     */
    Carpet(Carpet && other) = default;

    /**
     *
     * @param other
     * @return
     */
    Carpet& operator=(Carpet && other) noexcept = default;

    /**
     * operator =
     */
     Carpet& operator=(const Carpet& other) = default;

    /**
     * draw the Fractal Shape with ASCII art on screen
     */
    void draw() override
    {
        if (!flag)
        {
            int x1 = FIRST_GRID;
            int y1 = FIRST_GRID;
            int x2 = size;
            int y2 = size;
            _buildArray(depth , x1 , y1 , x2 , y2 , size , COLOR);
            flag = true;
        }
        Fractal::printShape(size, _p);
    }
    // need to add operators and move?
};

//-----------------=================  END of Inner Class Carpet   =================-----------------

//-------------------=================  Inner Class Sieve  ====================-------------------

/**
 * this class represent a Sierpinski Carpet Fractal
 */
class Sieve : public Fractal
{
private:

    /**
     * this helper function build the array which represent the shape of the fractal using recursion
     * @param level - the depth of the recursion
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param x2 - the buttom right index of the range (x2,y2)
     * @param y2 - the buttom right index of the range (x2,y2)
     * @param size - the current size of the range
     * @param symbol - the symbol which fill the cells in the range
     */
    void _buildArray(int level, int x1, int y1, int x2, int y2, int size, char symbol)
    {
        size = size / BASE_TABLE_FOR_SIEVE;
        if (level == BASE_CASE)
        {
            _putInArray(x1, y1, symbol);
        }
        else
        {
            _buildArray(level - MOVE_ONE_LEVEL_DOWN ,
                    x1 , y1 , x1 + size - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 , y1 + size ,
                    x1 + size - MOVE_ONE_GRID ,
                    y1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                     size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + size , y1 ,
                        x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + size - MOVE_ONE_GRID , size , symbol);
            _buildArray(level - MOVE_ONE_LEVEL_DOWN , x1 + size , y1 + size ,
                        x1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID ,
                        y1 + (MOVE_TWO_GRIDS * size) - MOVE_ONE_GRID , size , BLANK);
        }
    }

    /**
     * this helper function puts the symbol in the basic range area of the array
     * @param x1 - the upper left index of the range (x1,y1)
     * @param y1 - the upper left index of the range (x1,y1)
     * @param symbol  - # or ' '
     */
    void _putInArray(int x1, int y1, char symbol)
    {
        x1 -= ADJUST_ARRAY_INDEX_BY_ONE;
        y1 -= ADJUST_ARRAY_INDEX_BY_ONE;

        _p[x1][y1] = symbol;
        _p[x1][y1 + MOVE_ONE_GRID] = symbol;
        _p[x1 + MOVE_ONE_GRID][y1] = symbol;
        _p[x1 + MOVE_ONE_GRID][y1 + MOVE_ONE_GRID] = BLANK;
    }

public:

    /**
     * construcor
     * @param n
     */
    explicit Sieve(int n) : Fractal(n, BASE_TABLE_FOR_SIEVE)
    {
        if (_p == nullptr)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * copy constructor
     * @param other
     */
    Sieve(const Sieve& other) : Fractal(other) {}

    /**
     *
     * @param other
     * @return
     */
    Sieve& operator=(const Sieve& other) = default;
    /**
     * move constructor
     * @param other
     */
    Sieve(Sieve && other) = default;

    /**
     *
     * @param other
     * @return
     */
    Sieve& operator=(Sieve && other) noexcept = default;

    /**
     * draw the Fractal Shape with ASCII art on screen
     */
    void draw() override
    {
        if (!flag)
        {
            int x1 = FIRST_GRID;
            int y1 = FIRST_GRID;
            int x2 = size;
            int y2 = size;
            _buildArray(depth , x1 , y1 , x2 , y2 , size , COLOR);
            flag = true;
        }
        Fractal::printShape(size, _p);
    }
};

//-------------------==========================  END of Inner Class Dust   ======================-------------------

/**
 * a static function which print the shape
 * @param size - the size of the array
 * @param p - pointer to the array
 */
void Fractal::printShape(int size, char **p)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << p[i][j];
        }
        cout << endl;
    }
}

/**
 * Constructor
 * @param n - dimension
 * @param base - base for calculation the array size
 */
Fractal::Fractal(int n, int base) : depth(n), base(base), size(pow(base, depth)), flag(false)
{
    _p = allocateMemoryForArray(size);
}

/**
 * allocate memory for pointer _p 2d array
 * @param _p
 * @param size
 */
char** Fractal::allocateMemoryForArray(int size)
{
    try
    {
        _p = new char*[size];
        for(int i = 0; i < size; ++i)
        {
            _p[i] = new char[size];
        }
    }
    catch (const std::bad_alloc& e)
    {
        _p = nullptr;
    }
    return _p;
}


/**
 * destructor
 */
Fractal::~Fractal()
{
    Fractal::deleteArray(_p, size);
}

/**
 * free the memory for pointer _p 2d array
 * @param _p
 * @param size
 */
void Fractal::deleteArray(char **_p, int size)
{
    if (_p != nullptr)
    {
        for(int i = 0; i < size; ++i)
        {
            delete[] _p[i];
        }
        delete[] _p;
    }
}

/**
 * a static function which create the correct shape and send a pointer back
 * @param n
 * @param shapeType
 * @return
 */
Fractal* Fractal::listFactory(int n, int shapeType)
{
    Fractal* dammy = nullptr;
    switch(shapeType)
    {
        case 1: return new(std::nothrow) Carpet(n);
        case 2: return new (std::nothrow) Sieve(n);
        case 3: return new (std::nothrow) Dust(n);
        default: return dammy;
    }
}

/**
 * copy constructor of Fractal
 * @param other
 */
Fractal::Fractal(const Fractal &other) : Fractal(other.depth, other.base)
{
    flag = other.flag;
    if (flag)
    {
        copyArray(_p, other._p, size);
    }
}

/**
 * move constructor
 * @param other
 */
Fractal::Fractal(Fractal && other) noexcept
{
    depth = other.depth;
    base = other.base;
    size = other.size;
    _p = other._p;
    other._p = nullptr;
    flag = other.flag;
}

/**
 * operator =
 * @param other
 * @return
 */
Fractal& Fractal::operator=(const Fractal &other)
{
    depth = other.depth;
    base = other.base;
    Fractal::deleteArray(_p, size);
    size = other.size;
    flag = other.flag;
    _p = Fractal::allocateMemoryForArray(size);
    if (flag)
    {
        copyArray(_p, other._p, size);
    }
    return *this;
}

/**
 * this static funcion copy one array to another
 * @param _p
 * @param pOther
 * @param size
 */
void Fractal::copyArray(char **p , char **pOther, int size)
{
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                p[i][j] = pOther[i][j];
            }
        }
    }
}

/**
 * move assigment
 * @param other
 * @return
 */
Fractal & Fractal::operator=(Fractal && other) noexcept
{
    Fractal::deleteArray(_p, size);
    depth = other.depth;
    base = other.base;
    size = other.size;
    _p = other._p;
    other._p = nullptr;
    flag = other.flag;
    return *this;
}




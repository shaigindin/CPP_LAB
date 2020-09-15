//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Include *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#include <iostream>
#include <string>
#include "Fractal.h"
#include <vector>
#include <fstream>
#include <cmath>
#include <exception>

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Global Constants  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

static const char* BAD_ARGUMENTS_MESSAGE = "Usage: FractalDrawer <file path>"; /**  message */
static const char* READING_MODE = "r"; /** read mode */
static const char*  DELIMITER = ","; /** delimeter in CSV files */
static const char* EMPTY_STRING = ""; /** emtpy string */
static const char* ZERO_TO_NINE_DIGITS =  "0123456789"; /** all the possible digits */
static const char* BAD_INPUT = "Invalid input"; /**  message */
static const char* MEMORY_ALLOCATION_FAILED = "Memory allocation failed"; /**  message */

static const int TYPE_INDEX = 0; /** the index which represent the type value  */
static const int DIMENSION_INDEX = 1; /** the index which represent the Dimension value  */
static const int TWO_ARGUMENTS = 2; /** should be only two number in line i.e 1,1 */
static const int TYPE_MAX = 3; /** there is only 3 types of fractals */
static const int TYPE_MIN = 1; /** there is only 3 types of fractals */
static const int DIMENSION_MAX = 6; /** stricted to 6 dimension only */
static const int DIMENSION_MIN = 1; /**  base case in 1 and not 0 */
static const int FIRST_INDEX = 0; /** first index */
static const int PATH = 1; /** in argv the path is in the 1 index and not 0 */

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Using Shortcuts  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Exception Class  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

/**
 * this class is a Bad input Excepetion class.
 */
class BadInputException : public std::exception
{
public:

    /**
     * return "invali input" message to user
     * @return
     */
    const char* what() const noexcept override
    {
        return BAD_INPUT;
    }
};
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Functions  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
/**
 * this function checks whether type and float
 * @param type
 * @param dimension
 */
void checkIfNumbersValid(float type , float dimension)
{
    if ((type != ceil(type)) || (dimension != ceil(dimension)) || (type < TYPE_MIN) ||
        (type > TYPE_MAX) ||
        (dimension < DIMENSION_MIN) || (dimension > DIMENSION_MAX))
    {
        throw BadInputException();
    }
}

/**
 * boolean function which return true if file exists and falls otherwise
 * @param path - the location of the file
 * @return - true or false
 */
inline bool existFileTest(const std::string &path)
{
    if (FILE *file = fopen(path.c_str() , READING_MODE))
    {
        fclose(file);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * function checks whther string is a legitmit number
 * @param s - string
 * @return - true or false
 */
bool onlyDigits(const string &s)
{
    return s.find_first_not_of(ZERO_TO_NINE_DIGITS) == string::npos;
}

/**
 * checks if the number of arguments is exactly two
 * @param argumentNumber  - the number of arguments
 * @return
 */
inline bool numberOfArguments(int argumentNumber)
{
    return argumentNumber == TWO_ARGUMENTS;
}

/**
 * function get string and split it to elements by delimiter "," and puts it into vector.
 * Code was Inspired by Stack OverFlow answer
 * @param line - a string which represent a line in the CSV
 * @param delimiter - "," comma which separate in CSV Files
 * @return
 */
vector<string> splitLineToWords(const string &line , const string &delimiter)
{
    vector<string> words;
    size_t prev = 0 , position = 0;
    do
    {
        position = line.find(delimiter , prev);
        if (position == string::npos)
        {
            position = line.length();
        }
        string word = line.substr(prev , position - prev);
        if (!word.empty())
        {
            words.push_back(word);
        }
        prev = position + delimiter.length();
    }
    while ( (position < line.length()) && (prev < line.length()) );
    return words;
}

/**
 * this function read csv file and build array of Fractals according to file instructions
 * @param path
 * @param arr
 */
void readCSVFile(const std::string &path , vector<Fractal *> &arr)
{
    std::ifstream file(path);
    vector<string> row;
    string line;
    line = EMPTY_STRING;
    Fractal* tempPointer = nullptr;
    while (getline(file , line))
    {
        row = splitLineToWords(line , DELIMITER);
        if (row.size() != TWO_ARGUMENTS)
        {
            throw BadInputException();
        }
        float type , dimension;
        try
        {
            if ((!onlyDigits(row[TYPE_INDEX])) || (!onlyDigits(row[DIMENSION_INDEX])))
            {
                throw BadInputException();
            }
            type = std::stof(row[TYPE_INDEX]);
            dimension = std::stof(row[DIMENSION_INDEX]);
            checkIfNumbersValid(type , dimension);
            tempPointer = Fractal::listFactory(dimension , type);
            (tempPointer == nullptr) ? throw std::bad_alloc(): arr.push_back(tempPointer);
        }
        catch (const BadInputException& e)
        {
            throw BadInputException();
        }
        catch (const std::bad_alloc& e2)
        {
            throw std::bad_alloc();
        }
    }
}

/**
 * function free the memory of the Ftactals pointer array
 * @param arr
 */
void freeArrayOfFractals(vector<Fractal *> &arr)
{
    for (Fractal *temp: arr)
    {
        delete temp;
    }
}

/**
 * Function Draw the Fractals and then free the memory
 * @param arr
 */
void drawAndFreeArrayOfFractals(vector<Fractal *> &arr)
{

    int currentIndex = arr.size() - 1;
    while (currentIndex >= FIRST_INDEX)
    {
        arr[currentIndex]->draw();
        cout << endl;
        delete arr[currentIndex];
        currentIndex--;
    }
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Main Function  *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

/**
 * main functin
 * @param argc
 * @param argv
 * @return
 */
int main(int argc , char *argv[])
{
    if (!numberOfArguments(argc))
    {
        cerr << BAD_ARGUMENTS_MESSAGE << endl;
        return EXIT_FAILURE;
    }
    if (!existFileTest(argv[PATH]))
    {
        cerr << BAD_INPUT << endl;
        return EXIT_FAILURE;
    }
    vector<Fractal *> arr;
    try
    {
        readCSVFile(argv[PATH] , arr);
    }
    catch (const std::bad_alloc &e)
    {
        freeArrayOfFractals(arr);
        cerr << MEMORY_ALLOCATION_FAILED << endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception &e)
    {
        freeArrayOfFractals(arr);
        cerr << e.what();
        return EXIT_FAILURE;
    }
    drawAndFreeArrayOfFractals(arr);
    return EXIT_SUCCESS;
}
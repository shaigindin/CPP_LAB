#include <iostream>
#include "HashMap.hpp"
#include <string>
#include <algorithm>
#include <fstream>
#include <streambuf>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

static const char* BAD_INPUT = "Invalid input";  /**  message */
static const int SCORE_PATH = 1; /** in argv the path is in the 1 index and not 0 */
static const char* BAD_ARGUMENTS_MESSAGE = "Usage: SpamDetector <database path> <message path> <threshold>"; /**  message */
static const char* READING_MODE = "r"; /** read mode */
static const char* ZERO_TO_NINE_DIGITS =  "0123456789."; /** all the possible digits */
static const int TWO_ARGUMENTS = 2; /** should be only two number in line i.e 1,1 */
static const int SCORE_INDEX = 1; /** the index where the score table path is */
static const int FIRST_DIGIT_INDEX = 0; /** check if the number represented by string start with 0*/
static const char DOT = '.'; /** Dot representation */
static const char ZERO = '0'; /** zero char */
static const int PHRASE_INDEX = 0; /** the phrase index */
static const int ONE_DIGIT = 1; /** if the number is consist only from one char*/
static const int DOT_IN_SECOND_DIGIT = 1; /** check for number like 0.1 */
static const int NUMBER_OF_INPUT_ARGUMENTS = 3; /** must be three args in argv*/
static const int MESSAGE_PATH = 2; /** the path which the message path is in the argv*/
static const int THRESHOLD_PATH = 3; /** the path which the threshold path is in the argv*/
static const int POSITIVE_SCORE = 0; /** the score should be positive */
static const char *const SPAM_MESSAGE = "SPAM"; /** spam message */
static const char *const NOT_SPAM_MESSAGE = "NOT_SPAM"; /** not spam message */
static const char SPACE_DELIMITER = ' '; /**  space delimiter to replace new line char*/
static const char NEW_LINE = '\n'; /** remove from message all new line characters*/
static const char NEW_LINE_WINDOWS = '\r'; /** remove new line ascii from windows */
static const char COMMA = ','; /** remove comma */
static const char* EMPTY_STRING = ""; /** emtpy string */
static const char*  DELIMITER = ","; /** delimeter in CSV files */


/**
 * this function checks whether type and float
 * @param type
 * @param dimension
 */
void checkIfNumbersValid(float number)
{
    if (number < 0)
    {
        throw BadInputException(BAD_INPUT);
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
    int n = std::count(s.begin(), s.end(), DOT);
    if (n > 1)
    {
        return false;
    }
    if  ( (s[FIRST_DIGIT_INDEX] == DOT) || ( (s[FIRST_DIGIT_INDEX] == ZERO) && (s.size() != ONE_DIGIT) &&
                                             (s[DOT_IN_SECOND_DIGIT] != DOT) )
          || (s[s.size() - 1] == DOT) )
    {

        return false;
    }
    return (s.find_first_not_of(ZERO_TO_NINE_DIGITS) == string::npos);
}

/**
 * checks if the number of arguments is exactly two
 * @param argumentNumber  - the number of arguments
 * @return
 */
inline bool numberOfArguments(int argumentNumber)
{
    return argumentNumber == NUMBER_OF_INPUT_ARGUMENTS;
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
        word.erase(std::remove(word.begin(), word.end(), NEW_LINE_WINDOWS), word.end());
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
void readCSVFile(const std::string &path , HashMap<string, float> &map)
{
    std::ifstream file(path);
    vector<string> row;
    string line;
    line = EMPTY_STRING;
    while (getline(file , line))
    {
        row = splitLineToWords(line , DELIMITER);
        if (row.size() != TWO_ARGUMENTS)
        {
            throw BadInputException(BAD_INPUT);
        }
        string phrase;
        float score;
        try
        {
            if  (!onlyDigits(row[SCORE_INDEX]))
            {
                throw BadInputException(BAD_INPUT);
            }
            score = std::stof(row[SCORE_INDEX]);
            phrase = row[PHRASE_INDEX];
            checkIfNumbersValid(score);
            transform(phrase.begin(), phrase.end(), phrase.begin(), ::tolower);
            map.insert(phrase, score);
        }
        catch (const BadInputException& e)
        {
            throw BadInputException(BAD_INPUT);
        }
    }
}

/**
 * check the user input. valid pathes of files and that threshold is a non negative number
 * @param argc
 * @param argv
 */
void checkUserInput(int argc , char *argv[])
{
    if ( (!numberOfArguments(argc - 1)))
    {
        throw BadInputException(BAD_ARGUMENTS_MESSAGE);
    }
    if ((!existFileTest(argv[SCORE_PATH]))  || (!existFileTest(argv[MESSAGE_PATH]))  ||
        (!onlyDigits(argv[THRESHOLD_PATH])))
    {
        throw BadInputException(BAD_INPUT);
    }


}

/**
 * reads message and store in string only low cases chars
 * @param path
 * @return
 */
string readMessage(const string& path)
{
    std::ifstream t(path);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    transform(str.begin() , str.end() , str.begin() , ::tolower); //ASCII to lower
    return str;
}

/**
 * function counts all the score and return it
 * @param message
 * @param map
 * @return
 */
float countScore(string& message, HashMap<string, float>& map)
{
    float counter = 0;
    replace (message.begin(), message.end(), NEW_LINE , SPACE_DELIMITER);
    replace (message.begin(), message.end(), NEW_LINE_WINDOWS , SPACE_DELIMITER);
    for (const auto &p : map)
    {
        int occurrences = 0;
        std::string::size_type pos = 0;
        while ((pos = message.find(p.first, pos )) != std::string::npos)
        {
            ++ occurrences;
            pos += p.first.length();
        }
        counter += (occurrences * p.second);

    }
    return counter;
}

/**
 * main function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc , char *argv[])
{
    HashMap<string , float> map;
    string message;
    float threshold;
    try
    {
        checkUserInput(argc , argv);
        readCSVFile(argv[SCORE_PATH] , map);
        threshold = std::stof(argv[THRESHOLD_PATH]);
        message = readMessage(argv[MESSAGE_PATH]);
        if (threshold <= POSITIVE_SCORE)
        {
            throw BadInputException(BAD_INPUT);
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    float totalScore = countScore(message, map);
    if (totalScore >= threshold)
    {
        cout << SPAM_MESSAGE << endl;
    }
    else
    {
        cout << NOT_SPAM_MESSAGE << endl;
    }

    return 0;
}






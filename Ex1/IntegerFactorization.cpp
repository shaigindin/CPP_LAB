#include "GFNumber.h"
#include <cassert>

using std::endl;

/**
 * main function
 * @return
 */
int main()
{
    GFNumber a, b;
    std::cin >> a >> b;
    if (std::cin.fail())
    {
        assert(false);
    }
    std::cout << a + b << endl << a - b << endl << b - a << endl << a * b << endl;
    a.printFactors();
    b.printFactors();
    return 0;
}
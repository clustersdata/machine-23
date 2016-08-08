/** ***************************************************************************
 *
 *  jmachine:      machine learning toolkit
 *
 *  @file          app/main.cpp
 *  @brief         Implements simple test app
 *
 *  @homepage      https://github.com/jmf1sh/machine
 *  @license       GNU GPLv3 (see LICENSE)
 *  @copyright     Jonathan Fisher 2016
 *  @authors       Jonathan Fisher
 *
 *  ***************************************************************************
 */


#include "DataNode.h"
#include "CSV.h"

#include <iostream>

using namespace jono;
using namespace std;

int main(int argc, const char* argv[])
{
    if (argc != 2) {
        cout << "must give filename as argument" << endl;
        return 0;
    }

    CSV csv;

    csv.open(argv[1]);

    cout << "File has " << csv.nrows() << " rows" << endl;

    return 0;
}

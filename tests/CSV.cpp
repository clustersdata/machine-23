
#include "CSV.h"

#include <iostream>
#include <sstream>
#include <memory>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;

using namespace jono;

string csv_str = "a,\"b\",\"c\"\"\na\" ,def\n1,2,3,4";

int main(int argc, char* argv[])
{
    CSV csv;
    int i(0);

    istringstream stream;
    stream.str(csv_str);

    try {
        while (!stream.eof())
            cout << i++ << "####" << csv.getToken(stream) << "####" << endl;
    }
    catch (std::exception& e) {
        cerr << "ERROR: problem reading csv: " << e.what() << endl;
        return 1;
    }

    return 0;
}

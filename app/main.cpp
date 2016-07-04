
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


#include "DataSet.h"
#include "DataNode.h"

#include <iostream>
#include <memory>

using std::cout;
using std::cerr;
using std::endl;

using namespace jono;
using std::shared_ptr;
using DataPoint = DataSet::DataPoint;


int main(int argc, char* argv[])
{
    DataSet data;

    int n_feature, n_response, data_size;

    n_feature = 3;
    n_response = 2;
    data_size = 100;

    auto& points = data.getPoints();

    for (int i = 0; i < data_size; ++i) {
        auto p = shared_ptr<DataPoint>(new DataPoint);
        p->x.resize(n_feature);
        p->y.resize(n_response);
        points.push_back(p);
    }

    // assert correct number of features
    if ( data.nfeatures() != n_feature) {
        cerr << "ERROR: wrong number of features" << endl;
        return 1;
    }

    // assert correct number of responses
    if ( data.nresponses() != n_response) {
        cerr << "ERROR: wrong number of responses" << endl;
        return 1;
    }


    return 0;
}

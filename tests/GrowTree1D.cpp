
#include "DataSet.h"
#include "TreeLearner.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#ifndef M_PI
#define M_PI = 3.14159265358979323846
#endif

#include <iostream>
#include <memory>

using std::cout;
using std::cerr;
using std::endl;
using std::sin;
using std::fabs;

using namespace jono;
using std::shared_ptr;
using DataPoint = DataSet::DataPoint;

using jono::DataSet;
using dvec = jono::DataSet::dvec;

const double g_pi = M_PI;

int main(int argc, char* argv[])
{
    DataSet data;

    int data_size = 100;

    double x_begin = 0.0;
    double x_end = 2*g_pi;

    auto& points = data.getPoints();

    // set up dataset with data sampled from sine curve
    for (int i = 0; i < data_size; ++i) {
        auto p = shared_ptr<DataPoint>(new DataPoint);
        p->x.resize(1);
        p->y.resize(1);

        p->x[0] = x_begin + i * (x_end-x_begin) / data_size;
        p->y[0] = sin(p->x[0]);

        points.push_back(p);
    }

    // create root node of tree


    // error callback
    using ErrorCallback = std::function<double(const DataSet&, const dvec&)>;

    auto error_callback = [](const DataSet& dset, const dvec& y) -> double
    {
        double error = 0.0;
        for (DataSet::pvec::const_iterator it = dset.cbegin(); it != dset.cend(); ++it)
            error += fabs((*it)->y[0]-y[0]);

        return error;
    };

    // loop over depth for error comparison
    int depth = 10;

    TreeLearner root(data);
    root.setErrorCallback(error_callback);


    for (int i = 0; i < 22; ++i) {
        root.grow();
        cout << "Iteration " << i+1 << " total error " << root.totalError() << endl;
    }


    // check that the returned error is what we expected
    if ( root.totalError() > 4.0) {
        cerr << "Test failed: 1d tree reports an error which is too large" << endl;
        return 1;
    }

    cout << root.totalError() << endl;


    return 0;
}

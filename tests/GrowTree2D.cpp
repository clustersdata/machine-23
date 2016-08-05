
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

const double g_pi = 3.14159265358979323846;

int main(int argc, char* argv[])
{
    DataSet data;

    const double N = 20;
    const double L = 5;

    const double dx = L / N;
    const double dy = L / N;

    double x_begin = 0.0;
    double x_end = 2*g_pi;

    auto& points = data.getPoints();

    // set up dataset with data sampled from sine curve
    for (int i = 0; i < N; ++i) {
        for ( int j = 0; j < N; ++j) {
            auto p = shared_ptr<DataPoint>(new DataPoint);
            p->x.resize(2);
            p->y.resize(1);

            double x = i*dx;
            double y = j*dy;


            p->x[0] = x;
            p->x[1] = y;

            p->y[0] = x*x - 2*x + 3*y - y*y + x*y;

            points.push_back(p);
        }
    }

    // create root node of tree


    // error callback
    using ErrorCallback = std::function<double(const DataSet&, const dvec&)>;

    auto error_callback = [=](const DataSet& dset, const dvec& y) -> double
    {
        double error = 0.0;
        for (DataSet::pvec::const_iterator it = dset.cbegin(); it != dset.cend(); ++it)
            error += fabs((*it)->y[0]-y[0]) *dx * dy;

        return error;
    };

    // loop over depth for error comparison
    int depth = 10;

    TreeLearner root(data);
    root.setErrorCallback(error_callback);


    for (int i = 0; i < 300; ++i) {
        root.grow();
        cout << "Iteration " << i+1 << " total error " << root.totalError() << endl;
    }


    // check that the returned error is what we expected
    if ( root.totalError() > 0.648) {
        cerr << "Test failed: 1d tree reports an error which is too large" << endl;
        return 1;
    }

    cout << root.totalError() << endl;


    return 0;
}

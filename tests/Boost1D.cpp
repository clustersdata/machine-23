
#include "DataSet.h"
#include "DataNode.h"


#include <cmath>
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

    auto error_callback = [](DataSet& dset, const dvec& y) -> double
    {
        double error = 0.0;
        for (auto& point: dset.getPoints())
            error += fabs(point->y[0]-y[0]);
        return error;
    };

    // initialize residuals to original data
    DataSet residuals = data;


    // loop over depth for error comparison
    for ( int depth = 0; depth < 5; ++depth) {
        for (int ensemble_size = 0; ensemble_size < 200; ensemble_size += 10) {

            /*resi

            root.partition(0, error_callback, depth);
            root.computeError(error_callback);
            cout << "With depth " << depth << " the total error is " << root.totalError() << endl;
            */
        }
    }

    return 0;
}

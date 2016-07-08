#include "ErrorFunctions.h"

#include <cmath>

using std::fabs;

namespace jono {

double Error::l2(const DataSet &dset, const DataSet::dvec &y)
{
    double error = 0.0;
    for (DataSet::pvec::const_iterator it = dset.cbegin(); it != dset.cend(); ++it)
        for (int i = 0; i < dset.nresponses(); ++i)
            error += std::pow(((*it)->y[i]-y[i]), 2);

    return error;
}

double Error::l1(const DataSet &dset, const DataSet::dvec &y)
{
    double error = 0.0;
    for (DataSet::pvec::const_iterator it = dset.cbegin(); it != dset.cend(); ++it)
        for (int i = 0; i < dset.nresponses(); ++i)
            error += fabs((*it)->y[i]-y[i]);

    return error;
}



}

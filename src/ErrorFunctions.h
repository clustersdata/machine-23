#ifndef JONO_ERROR_H
#define JONO_ERROR_H

#include "DataSet.h"

#include <functional>

namespace jono {

namespace Error {

    using Callback = std::function<double(const DataSet&, const DataSet::dvec&)>;

    //! l2 norm as error function
    double l2(const DataSet&, const DataSet::dvec&);

    //! l1 norm as error function
    double l1(const DataSet&, const DataSet::dvec&);

} // namespace Error

} // namespace jono

#endif // JONO_ERROR_H

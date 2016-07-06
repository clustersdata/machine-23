#include "AverageLearner.h"

namespace jono {



DataSet::dvec AverageLearner::predict(const DataSet::dvec &x) const
{
    return m_average;
}


void AverageLearner::learn(DataSet &dataSet)
{
    m_average = dataSet.averageResponse();
}





} // namespace jono

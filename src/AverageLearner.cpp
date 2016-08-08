/** ***************************************************************************
 *
 *  jmachine:      machine learning toolkit
 *
 *  @file          src/AverageLearner.cpp
 *  @brief         Implements class AverageLearner
 *
 *  @homepage      https://github.com/jmf1sh/machine
 *  @license       GNU GPLv3 (see LICENSE)
 *  @copyright     Jonathan Fisher 2016
 *  @authors       Jonathan Fisher
 *
 *  ***************************************************************************
 */

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

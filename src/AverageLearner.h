#ifndef JONO_AVERAGELEARNER_H
#define JONO_AVERAGELEARNER_H

// includes from standard library
#include <vector>
#include <memory>
#include <map>
#include <string>

// includes from jono library
#include "DataFrame.h"
#include "DataSet.h"
#include "ILearner.h"

namespace jono {

//! Learn the average value of a data set
class AverageLearner: public ILearner  {
public:
    AverageLearner(): ILearner(), m_average() {}
    ~AverageLearner() {}

    //! Return a prediction of the model
    virtual DataSet::dvec predict(DataSet::dvec& x) const override final;

    //! Return the error of the prediction vs. sample
    virtual double error(DataSet& dataSet) const override final;

    //! Learn the model from a given data set
    virtual void learn(DataSet& dataSet) override final;

private:
    //! Stored average value
    DataSet::dvec m_average;
};



} // namespace jono

#endif // JONO_AVERAGELEARNER_H

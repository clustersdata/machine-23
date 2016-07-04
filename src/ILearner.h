#ifndef JONO_ILEARNER_H
#define JONO_ILEARNER_H

// includes from standard library
#include <vector>
#include <memory>
#include <map>
#include <string>

// includes from jono library
#include "DataFrame.h"
#include "DataSet.h"

namespace jono {

//! Abstract interface for simple learner
class ILearner {
public:

    void setParameter(const std::string& name, double value);
    double getParameter(const std::string& name) const;
    std::map<std::string, double>& parameters() const;

    virtual DataSet::dvec predict(DataSet::dev& x) const = 0;
    virtual double error(DataSet& dataSet) const = 0;
    virtual void learn(DataSet& dataSet) = 0;
private:

protected:
    std::map<std::string, double> m_parameters;
};



} // namespace jono

#endif // JONO_DATASET_H

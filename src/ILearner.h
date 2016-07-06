#ifndef JONO_ILEARNER_H
#define JONO_ILEARNER_H

// includes from standard library
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <functional>

// includes from jono library
#include "DataFrame.h"
#include "DataSet.h"
#include "Error.h"

namespace jono {

//! Abstract interface for simple learner
class ILearner {
public:
    using Factory = std::function<ILearner*(void)>;

    ILearner(): m_parameters(), m_errorCallback(Error::l2) {}
    virtual ~ILearner() {}

    //! Set the error callback function
    void setErrorCallback(Error::Callback error);

    //! Set a parameter of the model
    void setParameter(const std::string& name, double value);

    //! Return the value of a given parameter of the model
    double parameter(const std::string& name) const;

    //! Return the map of all parameters
    std::map<std::string, double>& parameters();

    //! Return list of named parameters
    std::vector<std::string> parameterNames() const;

    //! Return a prediction of the model
    virtual DataSet::dvec predict(const DataSet::dvec& x) const = 0;

    //! Return vector of predictions for entire data set
    virtual std::vector<DataSet::dvec> predict(DataSet& dset) const;

    //! Return the error of the prediction vs. sample
    virtual double error(DataSet& dataSet) const;

    //! Learn the model from a given data set
    virtual void learn(DataSet& dataSet) = 0;

protected:
    //! Map of parameters of the model used to control learning
    std::map<std::string, double> m_parameters;
    Error::Callback m_errorCallback;
};



} // namespace jono

#endif // JONO_ILEARNER_H

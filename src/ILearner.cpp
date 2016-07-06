#include "ILearner.h"

namespace jono {

void ILearner::setErrorCallback(Error::Callback error)
{
    m_errorCallback = error;

    if ( !m_errorCallback)
        m_errorCallback = Error::l2;
}

void ILearner::setParameter(const std::string &name, double value)
{
    m_parameters[name] = value;
}

double ILearner::parameter(const std::string &name) const
{
    std::map<std::string, double>::const_iterator it = m_parameters.find(name);

    if ( it != m_parameters.end())
        return it->second;
    else
        return 0.0;
}

std::map<std::string, double> &ILearner::parameters()
{
    return m_parameters;
}

std::vector<std::string> ILearner::parameterNames() const
{
    std::vector<std::string> names;
    std::map<std::string, double>::const_iterator it;

    names.reserve(m_parameters.size());

    for (it = m_parameters.begin(); it != m_parameters.end(); ++it)
        names.push_back(it->first);

    return names;
}

std::vector<DataSet::dvec> ILearner::predict(DataSet &dset) const
{
    std::vector<DataSet::data_ptr> points = dset.getPoints();
    std::vector<DataSet::dvec> prediction;

    prediction.reserve(points.size());

    for (auto& p : points)
        prediction.push_back(p->x);

    return prediction;
}

double ILearner::error(DataSet &dataSet) const
{
    if (!m_errorCallback)
        return 0.0;

    return -1.0;
}




} // namespace jono

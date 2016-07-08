#include "DataSet.h"


#include <vector>
#include <algorithm>

namespace jono {

DataSet::DataSet()
{

}

DataSet::DataSet(DataSet &&other):
    points(std::move(other.points))
{

}

DataSet::DataSet(const DataSet &other):
    points(other.points)
{

}

DataSet& DataSet::operator=(const DataSet &other)
{
    points = other.points;
    return *this;
}


DataSet::~DataSet()
{

}

void DataSet::sort(int feature)
{
    auto compare = [=] (const data_ptr& a, const data_ptr& b) -> bool
    {
        return a->x[feature] < b->x[feature];
    };

    std::sort(points.begin(), points.end(), compare);
}

DataSet DataSet::slice(int begin, int end)
{
    pvec::iterator it_begin = points.begin() + begin;
    pvec::iterator it_end = points.begin() + end;

    DataSet dataSlice;
    dataSlice.points.resize(end-begin);

    auto data_it = dataSlice.points.begin();

    for (auto it = it_begin; it != it_end; ++it, ++data_it)
        *data_it = *it;

    return dataSlice;
}

DataSet::pvec &DataSet::getPoints()
{
    return points;
}

DataSet::dvec DataSet::averageResponse()
{
    int n_responses = nresponses();

    dvec average(n_responses);
    double factor = 1.0 / static_cast<double>(points.size());

    for (auto& p: points)
        for (int i = 0; i < n_responses; ++i)
            average[i] += p->y[i] * factor;

    return average;
}

int DataSet::nfeatures() const
{
    if ( points.size() < 1)
        return 0;

    return points[0]->x.size();
}

int DataSet::nresponses() const
{
    if ( points.size() < 1)
        return 0;

    return points[0]->y.size();
}

DataSet::pvec::const_iterator DataSet::cbegin() const
{
    return points.cbegin();
}

DataSet::pvec::const_iterator DataSet::cend() const
{
    return points.cend();
}

} // namespace jono

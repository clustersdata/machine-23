#include "TreeLearner.h"

namespace jono {

TreeLearner::TreeLearner():
    m_left(),
    m_right(),
    is_leaf(true),
    feature_index(-1),
    feature_value(0.0),
    m_data(),
    prediction(),
    error(0.0)
{

}

TreeLearner::TreeLearner(const DataSet& dataSet): TreeLearner()
{
    m_data = dataSet;
}



TreeLearner::~TreeLearner()
{

}


void TreeLearner::partition(int feature, int depth)
{
    // recursion too deep
    if ( depth < 0 )
        return;

    // this shouldn't be called on a node which is not a leaf!!
    if ( !is_leaf)
        return;

    // set up current node
    feature_index = feature;
    is_leaf = false;
    m_left = node_ptr(new TreeLearner);
    m_right = node_ptr(new TreeLearner);
    m_left->is_leaf = true;
    m_right->is_leaf = true;

    // sort dataset by feature
    m_data.sort(feature);
    int begin, end, i;

    int best_index = -1;
    double min_error = -1.0;
    end = m_data.getPoints().size();

    for ( i = begin = 0; i != end; ++i) {

        DataSet data1(m_data.slice(begin, i));
        DataSet data2(m_data.slice(i, end));

        dvec ave1 = data1.averageResponse();
        dvec ave2 = data2.averageResponse();

        double err1 = m_errorCallback(data1, ave1);
        double err2 = m_errorCallback(data2, ave2);
        double error = err1 + err2;

        // this index does a better job!
        if ( best_index < 0 || error < min_error) {
            feature_value = m_data.getPoints()[i]->x[feature_index];

            m_left->m_data = data1;
            m_left->prediction = ave1;
            m_left->error = err1;

            m_right->m_data = data2;
            m_right->prediction = ave2;
            m_right->error = err2;

            best_index = i;
            min_error = error;
        }
    }

    // now that we are a node and not a leaf, we can release the data
    m_data.getPoints().clear();

    // recurse if necessary
    if (depth > 0) {
        m_left->partition(feature, depth-1);
        m_right->partition(feature, depth-1);
    }
}

void TreeLearner::computeError()
{
    if (is_leaf)
        error = m_errorCallback(m_data, prediction);
    else {
        m_left->computeError();
        m_right->computeError();
    }
}

DataSet::dvec TreeLearner::predict(const DataSet::dvec &x) const
{
    if (is_leaf)
        return prediction;

    // else, have to traverse the tree
    if ( x[feature_index] < feature_value)
        return m_left->predict(x);
    else
        return m_right->predict(x);
}

void TreeLearner::learn(DataSet &dataSet)
{
    //! First, we initialize
    m_left.reset();
    m_right.reset();

    is_leaf = true;
    error = 0.0;
    m_data = dataSet;



}

double TreeLearner::totalError()
{
    if (!is_leaf)
        return m_left->totalError() + m_right->totalError();
    else
        return error;
}




} // namespace jono

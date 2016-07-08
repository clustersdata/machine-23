#include "TreeLearner.h"

namespace jono {

TreeLearner::TreeLearner():
    m_left(),
    m_right(),
    m_isLeaf(true),
    m_featureIndex(-1),
    m_featureValue(0.0),
    m_data(),
    m_prediction(),
    m_error(0.0)
{

}

TreeLearner::TreeLearner(const DataSet& dataSet): TreeLearner()
{
    m_data = dataSet;
    m_prediction.resize(m_data.nresponses());
}



TreeLearner::~TreeLearner()
{

}

void TreeLearner::grow()
{
    // grow in a greedy manner: find the worst performing leaf
    TreeLearner* splitLeaf = worstLeaf();

    double best_error = -1.0;
    int best_feature = -1;

    // iterate over features to find the best one
    for (int feature = 0; feature < splitLeaf->m_data.nfeatures(); ++feature) {
        TreeLearner node;
        node.m_errorCallback = splitLeaf->m_errorCallback;
        node.m_data = splitLeaf->m_data;
        node.m_isLeaf = true;

        // split along feature
        node.partition(feature, 0);

        // update as necessary
        if ( best_feature < 0 || best_error > node.totalError() ) {
            best_feature = feature;
            best_error = node.totalError();
            splitLeaf->m_error = best_error;
            splitLeaf->m_left = std::move(node.m_left);
            splitLeaf->m_right = std::move(node.m_right);
        }
    }

    splitLeaf->m_isLeaf = false;
}


void TreeLearner::partition(int feature, int depth)
{
    // recursion too deep
    if ( depth < 0 )
        return;

    // this shouldn't be called on a node which is not a leaf!!
    if ( !m_isLeaf)
        return;

    // set up current node
    m_featureIndex = feature;
    m_isLeaf = false;
    m_left = node_ptr(new TreeLearner);
    m_right = node_ptr(new TreeLearner);
    m_left->m_isLeaf = true;
    m_right->m_isLeaf = true;

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
            m_featureValue = m_data.getPoints()[i]->x[m_featureIndex];

            m_left->m_data = data1;
            m_left->m_prediction = ave1;
            m_left->m_error = err1;
            m_left->m_errorCallback = m_errorCallback;

            m_right->m_data = data2;
            m_right->m_prediction = ave2;
            m_right->m_error = err2;
            m_right->m_errorCallback = m_errorCallback;

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
    if (m_isLeaf)
        m_error = m_errorCallback(m_data, m_prediction);
    else {
        m_left->computeError();
        m_right->computeError();
    }
}

DataSet::dvec TreeLearner::predict(const DataSet::dvec &x) const
{
    if (m_isLeaf)
        return m_prediction;

    // else, have to traverse the tree
    if ( x[m_featureIndex] < m_featureValue)
        return m_left->predict(x);
    else
        return m_right->predict(x);
}

void TreeLearner::learn(DataSet &dataSet)
{
    //! First, we initialize
    m_left.reset();
    m_right.reset();

    m_isLeaf = true;
    m_error = 0.0;
    m_data = dataSet;



}

double TreeLearner::totalError()
{
    if (!m_isLeaf)
        return m_left->totalError() + m_right->totalError();
    else
        return m_error;
}

TreeLearner *TreeLearner::worstLeaf()
{
    if (m_isLeaf)
        return this;

    TreeLearner* worst_left = m_left->worstLeaf();
    TreeLearner* worst_right = m_right->worstLeaf();

    return worst_right->m_error >= worst_left->m_error ? worst_right : worst_left;
}




} // namespace jono

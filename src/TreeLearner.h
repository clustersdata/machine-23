#ifndef JONO_TREELEARNER_H
#define JONO_TREELEARNER_H

// includes from standard library
#include <vector>
#include <memory>
#include <functional>

// includes from jono library
#include "DataSet.h"
#include "ILearner.h"

namespace jono {

class TreeLearner: public ILearner {
public:
    using node_ptr = std::unique_ptr<TreeLearner>;
    using dvec = DataSet::dvec;

    TreeLearner();
    TreeLearner(const DataSet& dataSet);
    TreeLearner(const TreeLearner&) = delete;
    ~TreeLearner();

    //! Grow by splitting a node in a greedy manner
    void grow();

    //! Return a prediction of the model
    virtual DataSet::dvec predict(const DataSet::dvec& x) const override final;

    //! Learn the model from a given data set
    virtual void learn(DataSet& dataSet) override final;

    //! Parition the current node along feature
    void partition(int feature, int depth);

    //! Compute error recursively
    void computeError();

    //! Total error as computed recursively
    double totalError();

private:
    //! Find leaf with worst error, used for growing the tree greedily
    TreeLearner* worstLeaf();

    node_ptr m_left, m_right;
    DataSet m_data;
    double m_error, m_featureValue;
    dvec m_prediction;
    int m_featureIndex;
    bool m_isLeaf;

};



} // namespace jono

#endif // JONO_TREELEARNER_H

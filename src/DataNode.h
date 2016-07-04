#ifndef JONO_DATANODE_H
#define JONO_DATANODE_H

// includes from standard library
#include <vector>
#include <memory>
#include <functional>

// includes from jono library
#include "DataSet.h"

namespace jono {

class DataNode {
public:
    using node_ptr = std::unique_ptr<DataNode>;
    using dvec = DataSet::dvec;
    using ErrorCallback = std::function<double(DataSet&, const dvec&)>;

    DataNode();
    DataNode(const DataSet& dataSet);
    DataNode(const DataNode&) = delete;
    ~DataNode();

    //! Find best binary parition for given feature
    void partition(int feature, ErrorCallback callback, int depth = 0);

    //! Return total error. Note: must call computeError before
    double totalError();

    //! Compute total error
    void computeError(ErrorCallback callback);

    //! Predict a response from given feature
    const dvec& predict(const dvec& x);

private:
    node_ptr left, right;
    DataSet data;
    double error, feature_value;
    dvec prediction;
    int feature_index;
    bool is_leaf;

};



} // namespace jono

#endif // JONO_DATASET_H

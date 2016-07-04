#include "DataNode.h"

namespace jono {

DataNode::DataNode():
    left(),
    right(),
    is_leaf(true),
    feature_index(-1),
    feature_value(0.0),
    data(),
    prediction(),
    error(0.0)
{

}

DataNode::DataNode(const DataSet& dataSet): DataNode()
{
    data = dataSet;
}



DataNode::~DataNode()
{

}

void DataNode::partition(int feature, DataNode::ErrorCallback callback, int depth)
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
    left = node_ptr(new DataNode);
    right = node_ptr(new DataNode);
    left->is_leaf = true;
    right->is_leaf = true;

    // sort dataset by feature
    data.sort(feature);
    int begin, end, i;

    int best_index = -1;
    double min_error = -1.0;
    end = data.getPoints().size();

    for ( i = begin = 0; i != end; ++i) {

        DataSet data1(data.slice(begin, i));
        DataSet data2(data.slice(i, end));

        dvec ave1 = data1.averageResponse();
        dvec ave2 = data2.averageResponse();

        double err1 = callback(data1, ave1);
        double err2 = callback(data2, ave2);
        double error = err1 + err2;

        // this index does a better job!
        if ( best_index < 0 || error < min_error) {
            feature_value = data.getPoints()[i]->x[feature_index];

            left->data = data1;
            left->prediction = ave1;
            left->error = err1;

            right->data = data2;
            right->prediction = ave2;
            right->error = err2;

            best_index = i;
            min_error = error;
        }
    }

    // now that we are a node and not a leaf, we can release the data
    data.getPoints().clear();

    // recurse if necessary
    if (depth > 0) {
        left->partition(feature, callback, depth-1);
        right->partition(feature, callback, depth-1);
    }
}

void DataNode::computeError(DataNode::ErrorCallback callback)
{
    if (is_leaf)
        error = callback(data, prediction);
    else {
        left->computeError(callback);
        right->computeError(callback);
    }
}

const DataNode::dvec& DataNode::predict(const DataNode::dvec &x)
{
    if (is_leaf)
        return prediction;

    // else, have to traverse the tree
    if ( x[feature_index] < feature_value)
        return left->predict(x);
    else
        return right->predict(x);
}

double DataNode::totalError()
{
    if (!is_leaf)
        return left->totalError() + right->totalError();
    else
        return error;
}




} // namespace jono

#ifndef JONO_ENSEMBLE_H
#define JONO_ENSEMBLE_H

// includes from standard library
#include <vector>
#include <memory>
#include <functional>

// includes from jono library
#include "DataSet.h"
#include "DataNode.h"

namespace jono {

class Ensemble {
private:
    std::vector<DataNode> trees;
};



} // namespace jono

#endif // JONO_DATASET_H

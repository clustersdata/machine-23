#ifndef JONO_CSV_H
#define JONO_CSV_H

// includes from standard library
#include <iostream>
#include <fstream>

// includes from jono library
#include "DataSet.h"

namespace jono {

class CSV {
public:
    void open(const char* filename);
    void close();

    int nrows();
    int ncols();

private:
    void compute_dimensions();

    std::fstream m_file;

    int m_nrows;
    int m_ncols;
};


} // namespace jono

#endif // JONO_DATASET_H

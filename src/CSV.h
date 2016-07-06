#ifndef JONO_CSV_H
#define JONO_CSV_H

// includes from standard library
#include <iostream>
#include <fstream>
#include <vector>

// includes from jono library
#include "DataSet.h"

namespace jono {

class CSV {
public:
    //! Open for reading
    void open(const char* filename);

    //! Read entire file into memory
    void read();
    void close();

    int nrows();
    int ncols();

private:
    void compute_dimensions();
    void readLine(std::string& line);
    void tokenizeLine(std::vector<std::string>& toks, std::string& line);


    std::fstream m_file;

    int m_nrows;
    int m_ncols;

    std::vector<std::string> m_header;
    std::vector<std::vector<double>> m_rows;
};


} // namespace jono

#endif // JONO_DATASET_H

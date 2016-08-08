#ifndef JONO_CSV_H
#define JONO_CSV_H

// see https://tools.ietf.org/html/rfc4180
//The ABNF grammar [2] appears as follows:
//
//   file = [header CRLF] record *(CRLF record) [CRLF]
//
//   header = name *(COMMA name)
//
//   record = field *(COMMA field)
//
//   name = field
//
//   field = (escaped / non-escaped)
//
//   escaped = DQUOTE *(TEXTDATA / COMMA / CR / LF / 2DQUOTE) DQUOTE
//
//   non-escaped = *TEXTDATA
//
//   COMMA = %x2C
//
//   CR = %x0D ;as per section 6.1 of RFC 2234 [2]



/** ***************************************************************************
 *
 *  jmachine:      machine learning toolkit
 *
 *  @file          src/CSV.h
 *  @brief         Defines class CSV
 *
 *  @homepage      https://github.com/jmf1sh/machine
 *  @license       GNU GPLv3 (see LICENSE)
 *  @copyright     Jonathan Fisher 2016
 *  @authors       Jonathan Fisher
 *
 *  ***************************************************************************
 */


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

    std::string getToken(std::istream& stream);

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

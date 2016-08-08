#include "CSV.h"

#include <cctype>
#include <cwctype>
#include <stdexcept>

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


namespace jono {

/** ***************************************************************************
 *
 *  jmachine:      machine learning toolkit
 *
 *  @file          src/CSV.cpp
 *  @brief         Implements class CSV
 *
 *  @homepage      https://github.com/jmf1sh/machine
 *  @license       GNU GPLv3 (see LICENSE)
 *  @copyright     Jonathan Fisher 2016
 *  @authors       Jonathan Fisher
 *
 *  ***************************************************************************
 */


void jono::CSV::open(const char *filename)
{
    m_file.open(filename);
    m_nrows = -1;
    m_ncols = -1;
}

void CSV::read()
{
    if ( !m_file.is_open() )
        return;

    std::string header, line;
    header.reserve(2048);
    line.reserve(2048);

    m_file.seekp(0, std::ios::beg);
    readLine(header);
}

int CSV::nrows()
{
    if ( !m_file.is_open())
        return 0;

    if ( m_nrows < 0 )
        compute_dimensions();

    return m_nrows;
}

std::string CSV::getToken(std::istream &stream)
{
    std::string tok = "";
    char current;
    char next;
    bool is_wspace(false);
    bool in_string(false);

    // do nothing at end of stream
    while(!stream.eof()) {
        stream.get(current);
        next = stream.peek();

        // comma separation
        if (!in_string && current == ',') {
            break;
        }
        // end of a line
        else if (!in_string && next == '\n') {
            tok += current;
            break;
        }
        // newline gets own token
        else if (!in_string && current == '\n') {
            return "\n";
        }
        // string stuff
        else if (current == '"') {
            // already inside of string
            if (in_string) {
                // double quote inside of string
                if (next == '"') {
                    tok += "\"\"";
                    stream.get(current);
                }
                // end of string
                else {
                    tok += current;
                    in_string = false;
                }
            }
            // start of string
            else {
                tok += current;
                in_string = true;
            }
        }
        // generic case
        else {
            tok += current;
        }

    }

    // todo: eat whitespace at beginning and end
    return tok;
}

void jono::CSV::compute_dimensions()
{
    m_nrows = 0;

    char c;

    while(m_file.get(c))
        if ( c == '\n')
            ++m_nrows;
}

void CSV::readLine(std::string& line)
{
    line = "";

    if (!m_file.is_open())
        return;

    char c;

    while (m_file.get(c))
        if ( c == '\n' )
            break;
        else
            line += c;
}

void CSV::tokenizeLine(std::vector<std::string>& toks, std::string &line)
{
    // loop until the line is exausted
    while ( line.size() != 0 ) {

        // find first non-whitespace character
        int i;
        for (i = 0; i < line.size(); ++i)
            if ( !std::iswspace(line[i]))
                break;

        // eat initial whitespace and
        line = line.substr(i, line.size());

        // nothing left to do
        if (line.size() == 0)
            return;

        // find comma
        int separator = line.find_first_of(',');

        std::string tok = line.substr(0, separator-1);

        // eat trailing whitespace
        for ( i = tok.size()-1; i >= 0; --i)
            if ( !std::iswspace(tok[i]))
                break;

        tok = tok.substr(0, i+1);

        toks.push_back(tok);

    }
}



} // namespace jono

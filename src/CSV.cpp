#include "CSV.h"

#include <cctype>
#include <cwctype>

namespace jono {

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

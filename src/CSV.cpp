#include "CSV.h"

namespace jono {

void jono::CSV::open(const char *filename)
{
    m_file.open(filename);
    m_nrows = -1;
    m_ncols = -1;
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



} // namespace jono

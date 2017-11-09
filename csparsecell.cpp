#include "csparsecell.h"

QString CSparseCell::toString() const
{
    QString str("[");
    for(const int& coord : coords)
        str += QString::number(coord) + ",";
    str.chop(1);
    str += "]:" + QString::number(value) + ";";
    return str;
}

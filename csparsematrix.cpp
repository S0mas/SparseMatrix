#include "csparsematrix.h"
#include <iostream>
#include <QDebug>

CSparseMatrix::CSparseMatrix() : name("def_name")
{
    qDebug().nospace() << "create: " << name;
}

CSparseMatrix::CSparseMatrix(const QString& name) : name(name)
{
    qDebug().nospace() << "create: " << name;
}

CSparseMatrix::CSparseMatrix(const QString& name, const QVector<int> &dimensions) : name(name), dimensions(dimensions)
{
    qDebug().nospace() << "create: " << name;
}

CSparseMatrix::CSparseMatrix(const CSparseMatrix& other) : name(other.name + "_copy"), defaultValue(other.defaultValue), dimensions(other.dimensions), cells(other.cells)
{
    qDebug().nospace() << "create: " << name;
}

CSparseMatrix::~CSparseMatrix()
{
   qDebug().nospace() << "destroy: " << name;
}

void CSparseMatrix::removeCellsWithDefaultValue()
{
    int i = 0;
    for(QVector<CSparseCell>::Iterator it = cells.begin(); it != cells.end(); )
    {
        if(it->value == defaultValue)
            cells.remove(i);
        else
        {
            ++i;
            ++it;
        }
    }
}

void CSparseMatrix::setDefaultValue(const int& newDefaultValue)
{
    defaultValue = newDefaultValue;
    removeCellsWithDefaultValue();
}

std::unique_ptr<CSparseMatrix> CSparseMatrix::getClone() const
{
    return std::unique_ptr<CSparseMatrix>(new CSparseMatrix(*this));
}

bool CSparseMatrix::checkCoords(const QVector<int>& cellCoords) const
{
    //Wrong number of dimensions
    if(dimensions.size() != cellCoords.size())
    {
        qDebug("Error. Wrong number of dimensions.");
        return false;
    }

    //Wrong single dimension size
    for(int i = 0; i < dimensions.size(); ++i)
    {
        if(dimensions[i] < cellCoords[i])
        {
            qDebug("Error. Wrong coordinates.");
            return false;          
        }
    }
    return true;
}

int CSparseMatrix::getCellValue(const QVector<int>& cellCoords) const
{
    if(checkCoords(cellCoords))
    {
        //Looking for requested coords in defined values and return it if exists
        for(const CSparseCell& cell : cells)
        {
            if(cell.coords == cellCoords)
                return cell.value;
        }
        return defaultValue;
    }
    return defaultValue;

}

void CSparseMatrix::setCellValue(const QVector<int>& cellCoords, const int& newCellValue)
{
    if(checkCoords(cellCoords))
    {
        for(CSparseCell& cell : cells)
        {
            if(cell.coords == cellCoords)
            {
                cell.value = newCellValue;
                return;
            }
        }
        cells.push_back(CSparseCell(newCellValue, cellCoords));
    }
}

void CSparseMatrix::setDimensions(const QVector<int>& dimensions)
{
    this->dimensions = dimensions;
}

QString CSparseMatrix::toStringDimensions() const
{
    QString str(name + " size: [");

    for(const int& dimensionSize : dimensions)
            str += QString::number(dimensionSize) + ",";

    str.chop(1);
    str += "]";

    return str;
}

QString CSparseMatrix::toString() const
{
    QString str(toStringDimensions() + " values:");

    for(const CSparseCell& cell : cells)
            str += cell.toString();
     str += " All other cells have value: " + QString::number(defaultValue);
    return str;
}

void CSparseMatrix::operator=(const CSparseMatrix& other)
{
    defaultValue = other.defaultValue;
    cells = other.cells;
    dimensions = other.dimensions;
}

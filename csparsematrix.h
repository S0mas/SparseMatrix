#ifndef CSPARSEMATRIX_H
#define CSPARSEMATRIX_H
#include <QString>
#include <QVector>
#include <memory>
#include "csparsecell.h"

class CSparseMatrix
{
public:
    CSparseMatrix();
    CSparseMatrix(const QString& name);
    CSparseMatrix(const QString& name, const QVector<int> &dimensions);
    CSparseMatrix(const CSparseMatrix& other);
    ~CSparseMatrix();

    QString getName() const { return name; }
    int getCellValue(const QVector<int>& cellCoords) const;
    std::unique_ptr<CSparseMatrix> getClone() const;
    bool checkCoords(const QVector<int>& cellCoords) const;
    void setName(const QString& newName) { name = newName; }
    void removeCellsWithDefaultValue();
    void setDefaultValue(const int& newDefaultValue);
    void setCellValue(const QVector<int> &cellCoords, const int& newCellValue);
    void setDimensions(const QVector<int> &dimensions);
    QVector<int> getDimensions() {return dimensions;}
    QString toStringDimensions() const;
    QString toString() const;

    void operator=(const CSparseMatrix& other);
private:
    QString name;
    int defaultValue;
    QVector<int> dimensions;
    QVector<CSparseCell> cells;
};

#endif // CSPARSEMATRIX_H

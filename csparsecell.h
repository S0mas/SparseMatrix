#ifndef CSPARSECELL_H
#define CSPARSECELL_H
#include <QString>
#include <QVector>

class CSparseCell
{
    friend class CSparseMatrix;
public:
    CSparseCell(){}
    CSparseCell(const int& value, const QVector<int>& cellCoords): value(value), coords(cellCoords){}
    ~CSparseCell(){}

    QString toString() const;
private:
    int value;
    QVector<int> coords;
};

#endif // CSPARSECELL_H

#ifndef CSPARSEMATRIXCONTAINER_H
#define CSPARSEMATRIXCONTAINER_H
#include "csparsematrix.h"

class CSparseMatrixContainer
{
public:
    CSparseMatrixContainer(){}
    ~CSparseMatrixContainer()
    {
        clear();
    }

    void createMatrix(const QVector<int>& dimesions, const QString& name)
    {
        matrixContainer.append(new CSparseMatrix(name, dimesions));
    }


    void cloneMatrix(const CSparseMatrix* matrix)
    {
        matrixContainer.append(new CSparseMatrix(*matrix));
    }

    void removeMatrix(const int& position)
    {
        if(position < matrixContainer.size())
        {
            delete matrixContainer[position];
            matrixContainer.removeAt(position);
        }
        choosenMatrixPosition = -1;
    }
    void clear()
    {
        for(CSparseMatrix* ptr : matrixContainer)
            delete ptr;
        matrixContainer.clear();
        choosenMatrixPosition = -1;
    }

    int choosenMatrixPosition;

    QVector<CSparseMatrix*> matrixContainer;
};

#endif // CSPARSEMATRIXCONTAINER_H

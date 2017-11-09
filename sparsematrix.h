#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <QMainWindow>
#include "ui_sparsematrix.h"
#include "csparsematrixcontainer.h"

namespace Ui {
class SparseMatrix;
}

class SparseMatrix : public QMainWindow
{
    Q_OBJECT
friend void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
public:
    explicit SparseMatrix(QWidget *parent = 0);
    ~SparseMatrix();

private slots:
void on_Clear_clicked();

void on_New_Matrix_clicked();

void on_Clone_Matrix_clicked();

void on_Rename_Matrix_clicked();

void on_Matrix_List_itemClicked(QListWidgetItem *item);

void on_Print_Matrix_clicked();

void on_Set_CellValue_clicked();

void on_Show_All_clicked();

void on_Delete_Matrix_clicked();

void on_Delete_All_clicked();

void on_Change_Default_clicked();

private:
    Ui::SparseMatrix *ui;
    CSparseMatrixContainer container;
    void refreshListOfMatrix();
};

#endif // SPARSEMATRIX_H

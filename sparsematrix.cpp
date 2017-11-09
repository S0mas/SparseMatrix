#include "sparsematrix.h"
#include <QDebug>
#include <QInputDialog>
#include <QDir>

SparseMatrix::SparseMatrix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SparseMatrix)
{
    ui->setupUi(this);
}

SparseMatrix::~SparseMatrix()
{
    delete ui;
}

void SparseMatrix::on_Clear_clicked()
{
    ui->Text_Output->setText("");
}

void SparseMatrix::refreshListOfMatrix()
{
    ui->Matrix_List->clear();
    int i = 0;
    for(const CSparseMatrix* matrix : container.matrixContainer)
    {
        ui->Matrix_List->addItem("[" + QString::number(i++) + "] " + matrix->getName() + " " + matrix->toStringDimensions());
    }
}

void SparseMatrix::on_New_Matrix_clicked()
{
    QString name = "def_name";
    QVector<int> dimensions;

    bool okName;
    bool okDimensions;
    bool okSizes;

    QString text = QInputDialog::getText(this, tr("Matrix creator"),
                                         tr("Enter new Matrix name."), QLineEdit::Normal,
                                         QDir::home().dirName(), &okName);
    if(okName)
    {
        if(text != "")
            name = text;
        int dimensionsNr = QInputDialog::getInt(this, tr("Matrix creator"),
                                        tr("How many dimiensions the matrix should have?"), 1, 0, 2147483647, 1, &okDimensions);
        if(okDimensions)
        {
            QString sizes = QInputDialog::getText(this, tr("Matrix creator"),
                                                 tr("Enter new Matrix dimensions sizes: (Exmaple:5 6 3)"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &okSizes);
            if(okSizes)
            {
                QStringList sizesList = sizes.split(' ', QString::SkipEmptyParts);

                if(sizesList.size() != dimensionsNr)
                    qDebug("Error. Wrong number of dimensions sizes entered, matrix was not created. Entered: %d should be: %u.", sizesList.size(), dimensionsNr);
                else
                {
                    bool okNumber = false;
                    for(const QString& numberString : sizesList)
                    {
                        int number = numberString.toInt(&okNumber, 10);
                        if(okNumber && number > 0)
                            dimensions.append(number);
                        else
                        {
                            qDebug().nospace() << "Error. Wrong input: " << sizes << ". Please enter only numbers separeted using spaces. Correct this part of input:" << numberString;
                            break;
                        }
                    }
                    if(okNumber)
                        container.createMatrix(dimensions, name);
                }
            }
        }
    }
    refreshListOfMatrix();
}

void SparseMatrix::on_Clone_Matrix_clicked()
{
    if(container.choosenMatrixPosition >= 0)
    {
        container.cloneMatrix(container.matrixContainer[container.choosenMatrixPosition]);
        refreshListOfMatrix();
    }
}

void SparseMatrix::on_Rename_Matrix_clicked()
{
    if(container.choosenMatrixPosition >= 0)
    {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Rename matrix"),
                                             tr("Enter new matrix name."), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if(ok)
        {
            container.matrixContainer[container.choosenMatrixPosition]->setName(text);
            refreshListOfMatrix();
        }
    }
}

void SparseMatrix::on_Matrix_List_itemClicked(QListWidgetItem *item)
{
    QStringList list = item->text().split(']', QString::SkipEmptyParts);
    QString str = list.first().split('[', QString::SkipEmptyParts).first();
    container.choosenMatrixPosition = str.toInt();
}

void SparseMatrix::on_Print_Matrix_clicked()
{
    if(container.choosenMatrixPosition >= 0)
        qDebug().nospace() << container.matrixContainer[container.choosenMatrixPosition]->toString();
}

void SparseMatrix::on_Set_CellValue_clicked()
{
    if(container.choosenMatrixPosition >= 0)
    {
        bool okPosition;
        QString sizes = QInputDialog::getText(this, tr("Set call value"),
                                             tr("Enter cell position and new value: (Exmaple:5 6 3)"), QLineEdit::Normal,
                                             QDir::home().dirName(), &okPosition);
        if(okPosition)
        {
            QVector<int> coords;
            QStringList sizesList = sizes.split(' ', QString::SkipEmptyParts);
            int i = container.matrixContainer[container.choosenMatrixPosition]->getDimensions().size();
            if(sizesList.size() - 1 != i)
                qDebug("Error. Wrong number of dimensions sizes entered, value was not set. Entered: %d dimensions, should be: %u.", sizesList.size(), i+1);
            else
            {
                bool okNumber = false;
                for(const QString& numberString : sizesList)
                {
                    int number = numberString.toInt(&okNumber, 10);
                    if(okNumber)
                        coords.append(number);
                    else
                    {
                        qDebug().nospace() << "Error. Wrong input: " << sizes << ". Please enter only numbers separeted using spaces. Correct this part of input:" << numberString;
                        break;
                    }
                }
                if(okNumber)
                {
                    bool inputOk = true;
                    for(QVector<int>::const_iterator it = coords.begin(); it != coords.end() - 1; ++it)
                    {
                        if(*it < 0)
                        {
                            qDebug().nospace() << "Error. Position have to be > 0. Correct this: " << *it;
                            inputOk = false;
                        }
                    }
                    if(inputOk)
                    {
                        int newValue = coords.back();
                        coords.pop_back();
                        container.matrixContainer[container.choosenMatrixPosition]->setCellValue(coords, newValue);
                    }
                }
            }
        }
    }

}

void SparseMatrix::on_Show_All_clicked()
{
    for(const CSparseMatrix* matrix : container.matrixContainer)
        qDebug().nospace() << matrix->toString();
}

void SparseMatrix::on_Delete_Matrix_clicked()
{
    if(container.choosenMatrixPosition >= 0)
    {
        container.removeMatrix(container.choosenMatrixPosition);
        refreshListOfMatrix();
    }
}

void SparseMatrix::on_Delete_All_clicked()
{
    container.clear();
    refreshListOfMatrix();
}

void SparseMatrix::on_Change_Default_clicked()
{
    bool ok;
    if(container.choosenMatrixPosition >= 0)
    {
        int newDefaultValue = QInputDialog::getInt(this, tr("Change default value."),
                                        tr("Enter new default value for matrix"), 1, 0, 2147483647, 1, &ok);
        if(ok)
        {
            container.matrixContainer[container.choosenMatrixPosition]->setDefaultValue(newDefaultValue);
            refreshListOfMatrix();
        }
    }
}

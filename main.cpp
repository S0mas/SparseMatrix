#include "sparsematrix.h"
#include "ui_sparsematrix.h"
#include <QApplication>
#include <QtGlobal>

SparseMatrix* w;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
 if(w)
    w->ui->Text_Output->append(msg);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new SparseMatrix();
    w->show();

    qInstallMessageHandler(myMessageOutput);

    return a.exec();
}

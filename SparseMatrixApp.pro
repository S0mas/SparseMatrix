#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T15:39:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SparseMatrixApp
TEMPLATE = app


SOURCES += main.cpp\
        sparsematrix.cpp \
    csparsecell.cpp \
    csparsematrix.cpp

HEADERS  += sparsematrix.h \
    csparsecell.h \
    csparsematrix.h \
    csparsematrixcontainer.h

FORMS    += sparsematrix.ui

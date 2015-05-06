#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T22:54:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RspMatch_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    ReadPEER.cpp \
    plot_acc_dialog.cpp \
    show_table_dlg.cpp \
    inputfile_define_dialog.cpp \
    run_rspmatch_dlg.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    ReadPEER.h \
    plot_acc_dialog.h \
    show_table_dlg.h \
    inputfile_define_dialog.h \
    run_rspmatch_dlg.h

FORMS    += mainwindow.ui \
    plot_acc_dialog.ui \
    show_table_dlg.ui \
    inputfile_define_dialog.ui \
    run_rspmatch_dlg.ui

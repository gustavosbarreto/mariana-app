#-------------------------------------------------
#
# Project created by QtCreator 2013-07-12T15:08:16
#
#-------------------------------------------------

QT       += core gui sql quickwidgets printsupport script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mariana
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cartao.cpp \
    operacao.cpp \
    leitoracartaodialog.cpp \
    novocartao.cpp \
    bancodados.cpp \
	relatoriodata.cpp \
    etiquetas.cpp \
    painter.cpp

HEADERS  += mainwindow.h \
    cartao.h \
    operacao.h \
    leitoracartaodialog.h \
    novocartao.h \
    bancodados.h \
	relatoriodata.h \
    etiquetas.h \
    painter.h

FORMS    += $$PWD/../forms/mainwindow.ui \
    $$PWD/../forms/leitoracartaodialog.ui \
    $$PWD/../forms/novocartao.ui \
	$$PWD/../forms/relatoriodata.ui \
    $$PWD/../forms/etiquetas.ui

RESOURCES += \
    $$PWD/../recursos.qrc


#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QLocale>

int main(int argc, char *argv[])
{
    QLocale::setDefault( QLocale(QLocale::Portuguese, QLocale::Brazil) );

    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/code128.ttf");

    MainWindow w;
    w.showMaximized();
    
    return a.exec();
}

#include "etiquetas.h"
#include "painter.h"
#include "ui_etiquetas.h"

#include <QtQml/QQmlEngine>
#include <QQuickWidget>
#include <QPainter>
#include <QPrinter>
#include <QScriptEngine>
#include <QDebug>

QQuickWidget *w;

Etiquetas::Etiquetas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Etiquetas)
{
    ui->setupUi(this);

    QPrinter printer(QPrinter::ScreenResolution);
       printer.setPageSize(QPrinter::Letter);
       printer.setOutputFormat(QPrinter::PdfFormat);

       printer.setOutputFileName("output.pdf");


    QPixmap pix(612, 792);
    pix.fill(Qt::white);

    QPainter p(&printer);


    Painter painter(&p);

    QFile file("etiquetas.js");
    file.open(QFile::ReadOnly);

    QString scriptContents = file.readAll();

    QScriptEngine engine;
    engine.globalObject().setProperty("canvas", engine.newQObject(&painter));
    QScriptValue val = engine.evaluate(scriptContents);
    qDebug() << engine.uncaughtExceptionLineNumber() << val.toString();

    p.end();


    ui->label->setPixmap(pix);
}

Etiquetas::~Etiquetas()
{
    delete ui;
}

void Etiquetas::on_pushButton_clicked()
{

    QPrinter printer(QPrinter::HighResolution);
       printer.setPageSize(QPrinter::A4);
       printer.setOutputFormat(QPrinter::PdfFormat);

       printer.setOutputFileName("output.pdf");

       QPainter p(&printer);
       w->render(&p);
}

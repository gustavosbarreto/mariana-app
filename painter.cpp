#include "painter.h"

#include <QPainter>
#include <QDebug>

Painter::Painter(QPainter *p) :
    QObject(),
    painter(p)
{
}

void Painter::fillRect(int x, int y, int width, int height)
{
    painter->fillRect(x, y, width, height, painter->brush());
}

void Painter::setFillStyle(const QString &stytle)
{
    painter->setBrush(QColor(stytle));
}

void Painter::stroke() {

}

void Painter::debug(const QString &str)
{
    qDebug() << str;
}


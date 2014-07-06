#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>

class QPainter;

class Painter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fillStyle WRITE setFillStyle)

public:
    explicit Painter(QPainter *p);

public slots:
    void fillRect(int x, int y, int width, int height);
    void setFillStyle(const QString &stytle);
    void stroke();
    void debug(const QString &str);

private:
    QPainter *painter;
};

#endif // PAINTER_H

#ifndef ETIQUETAS_H
#define ETIQUETAS_H

#include <QWidget>

namespace Ui {
class Etiquetas;
}

class Etiquetas : public QWidget
{
    Q_OBJECT
    
public:
    explicit Etiquetas(QWidget *parent = 0);
    ~Etiquetas();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Etiquetas *ui;
};

#endif // ETIQUETAS_H

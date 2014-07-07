#ifndef NOVOCARTAO_H
#define NOVOCARTAO_H

#include <QDialog>

namespace Ui {
class NovoCartao;
}

class NovoCartao : public QDialog
{
    Q_OBJECT
    
public:
    explicit NovoCartao(QWidget *parent = 0);
    ~NovoCartao();
    
private:
    Ui::NovoCartao *ui;
};

#endif // NOVOCARTAO_H

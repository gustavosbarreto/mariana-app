#include "novocartao.h"
#include "ui_novocartao.h"

NovoCartao::NovoCartao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NovoCartao)
{
    ui->setupUi(this);
}

NovoCartao::~NovoCartao()
{
    delete ui;
}

#include "leitoracartaodialog.h"
#include "ui_leitoracartaodialog.h"

#include "cartao.h"

#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

LeitoraCartaoDialog::LeitoraCartaoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeitoraCartaoDialog),
	_verificarExistencia(true)
{
    ui->setupUi(this);
}

LeitoraCartaoDialog::~LeitoraCartaoDialog()
{
    delete ui;
}

void LeitoraCartaoDialog::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if (_barcode.isEmpty()) {
            QMessageBox::critical(this, trUtf8("Erro"), trUtf8("Error ao ler o cartão!"));
            reject();
        }
        else if (_verificarExistencia && !Cartao::existe(_barcode.toLongLong())) {
            QMessageBox::critical(this, "Erro", trUtf8("Cartão não emitido!"));
            reject();
        }
        else
            accept();
        return;
    }

    _barcode.append(e->text());
}

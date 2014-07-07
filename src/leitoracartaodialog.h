#ifndef LEITORACARTAODIALOG_H
#define LEITORACARTAODIALOG_H

#include <QDialog>

namespace Ui {
class LeitoraCartaoDialog;
}

class LeitoraCartaoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LeitoraCartaoDialog(QWidget *parent = 0);
    ~LeitoraCartaoDialog();

	void naoVerificarExistencia() { _verificarExistencia = false; }
    qlonglong id() { return _barcode.toLongLong(); }

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::LeitoraCartaoDialog *ui;

	bool _verificarExistencia;
    QString _barcode;
};

#endif // LEITORACARTAODIALOG_H

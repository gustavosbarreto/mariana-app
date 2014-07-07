#ifndef _RELATORIODATA_H
#define _RELATORIODATA_H

#include "ui_relatoriodata.h"

class RelatorioData: public QDialog
{
	Q_OBJECT

public:
	RelatorioData(QWidget *parent = NULL);

private slots:
	void atualiza(const QDate &data);

private:
	Ui::RelatorioData ui;
};

#endif

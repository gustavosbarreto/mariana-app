#include "relatoriodata.h"
#include "operacao.h"

#include <QDebug>

RelatorioData::RelatorioData(QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);
	
    QList<Operacao> ultimas = Operacao::ultimas();

    ui.tableWidget->setRowCount(ultimas.size());

   foreach (const Operacao &op, ultimas) {
       ui.tableWidget->setItem(ultimas.indexOf(op), 0, new QTableWidgetItem(Operacao::tipo(op)));
       ui.tableWidget->setItem(ultimas.indexOf(op), 1, new QTableWidgetItem(Operacao::valor(op)));
       ui.tableWidget->setItem(ultimas.indexOf(op), 2, new QTableWidgetItem(Operacao::horario(op)));
   }
   
   connect(ui.calendarWidget, SIGNAL(clicked(const QDate &)), SLOT(atualiza(const QDate &)));
}

void RelatorioData::atualiza(const QDate &data)
{	
	QList<Operacao> operacoes = Operacao::dia(data);

    ui.tableWidget->setRowCount(operacoes.size());

    foreach (const Operacao &op, operacoes) {
        ui.tableWidget->setItem(operacoes.indexOf(op), 0, new QTableWidgetItem(Operacao::tipo(op)));
        ui.tableWidget->setItem(operacoes.indexOf(op), 1, new QTableWidgetItem(Operacao::valor(op)));
        ui.tableWidget->setItem(operacoes.indexOf(op), 2, new QTableWidgetItem(Operacao::horario(op)));
    }
}
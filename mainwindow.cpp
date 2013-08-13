#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "leitoracartaodialog.h"
#include "cartao.h"
#include "operacao.h"
#include "bancodados.h"
#include "relatoriodata.h"

#include <QSqlQuery>
#include <QDir>
#include <QDebug>
#include <QSqlError>
#include <QInputDialog>
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMenu *menu = new QMenu;
	QAction *dataAction = new QAction("De uma data", this);
	QAction *cartaoAction = new QAction(trUtf8("De um cartão"), this);
	
	menu->addAction(dataAction);
	menu->addAction(cartaoAction);
	
    //ui->relatorios->setMenu(menu);
	//ui->relatorios->setPopupMode(QToolButton::InstantPopup);

    BancoDados::inicializar();

    atualizarUltimasOperacoes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_novaOperacao_clicked()
{
    LeitoraCartaoDialog d;
    if (d.exec() == QDialog::Rejected)
        return;

    Cartao c(d.id());

    bool ok;
    double value;
    while (true) {
        value = QInputDialog::getDouble(this, "Digite o Valor", "Valor:", 0, 0, 1000000, 2, &ok);
        if (!ok)
            return;

        if (value <= 0) {
            QMessageBox::critical(this, "Debitar", trUtf8("O valor não pode ser ZERO."));
        } else {
            break;
        }
    }

    if (c.creditos() - value < 0) {
        QMessageBox::critical(this, "Debitar", trUtf8("Saldo insuficiente!"));
        return;
    }

    Operacao(c, Operacao::Debito, value, QDateTime::currentDateTime().toTime_t()).salvar();

    atualizarUltimasOperacoes();
}

void MainWindow::on_realizarEstorno_clicked()
{
    LeitoraCartaoDialog d;
    if (d.exec() == QDialog::Rejected)
        return;

    Cartao c(d.id());

    bool ok;
    double value = QInputDialog::getDouble(this, "Digite o Valor", "Valor:", 0, 0, 1000000, 2, &ok);
    if (!ok)
        return;

    Operacao(c, Operacao::Extorno, value, QDateTime::currentDateTime().toTime_t()).salvar();

    atualizarUltimasOperacoes();
}

void MainWindow::on_recarregar_clicked()
{
    LeitoraCartaoDialog d;
    if (d.exec() == QDialog::Rejected)
        return;

    Cartao c(d.id());

    bool ok;
    double value = QInputDialog::getDouble(this, "Digite o Valor", "Valor:", 0, 0, 1000000, 2, &ok);
    if (!ok)
        return;

    Operacao(c, Operacao::Recarga, value, QDateTime::currentDateTime().toTime_t()).salvar();

    atualizarUltimasOperacoes();
}

void MainWindow::on_consultaSaldo_clicked()
{
    LeitoraCartaoDialog d;
    if (d.exec() == QDialog::Rejected)
        return;

    QMessageBox::information(this, "Consultar Saldo", "Saldo atual: " + Cartao::saldo(Cartao(d.id())));
}

void MainWindow::on_emitirCartao_clicked()
{
    bool ok;
    QString nome = QInputDialog::getText(this, trUtf8("Emitir Cartão"), "Nome do Cliente:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString cpf;
    do {
        cpf = QInputDialog::getText(this, trUtf8("Emitir Cartão"), "CPF:", QLineEdit::Normal, "", &ok);
        if (!ok) return;
        if (cpf.isEmpty())
            QMessageBox::critical(this, trUtf8("Emitir Cartão"), trUtf8("Você precisa digitar um CPF!"));
    } while (cpf.isEmpty());

    double valor = QInputDialog::getDouble(this, trUtf8("Emitir Cartão"), trUtf8("Crédito Inicial:"), 0, 0, 1000000, 2, &ok);
    if (!ok) return;

    LeitoraCartaoDialog d;
	d.naoVerificarExistencia();
    if (d.exec() == QDialog::Rejected)
        return;

    if (!Cartao::unico(cpf, d.id())) {
        QMessageBox::critical(this, trUtf8("Emitir Cartão"), trUtf8("Já existe um cartão emitido com esse CPF ou este cartão já está em uso!"));
        return;
    }

    if (Cartao::emitir(nome, cpf, d.id(), valor))
        QMessageBox::information(this, trUtf8("Emitir Cartão"), trUtf8("Cartão emitido com sucesso"));
}

void MainWindow::atualizarUltimasOperacoes()
{
    QList<Operacao> ultimas = Operacao::ultimas();

    ui->tableWidget->setRowCount(ultimas.size());

   foreach (const Operacao &op, ultimas) {
       ui->tableWidget->setItem(ultimas.indexOf(op), 0, new QTableWidgetItem(Operacao::tipo(op)));
       ui->tableWidget->setItem(ultimas.indexOf(op), 1, new QTableWidgetItem(Operacao::valor(op)));
       ui->tableWidget->setItem(ultimas.indexOf(op), 2, new QTableWidgetItem(Operacao::horario(op)));
   }
}

void MainWindow::on_recuperarCartao_clicked()
{
    bool ok;
    QString cpf = QInputDialog::getText(this, trUtf8("Recuperar Cartão"), "CPF do Cliente:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;
    LeitoraCartaoDialog d(this);
    if (d.exec() == QDialog::Rejected)
        return;
}

void MainWindow::on_relatorios_clicked()
{
	RelatorioData d(this);
	d.exec();
}

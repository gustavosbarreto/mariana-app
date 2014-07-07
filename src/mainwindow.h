#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_novaOperacao_clicked();

    void on_realizarEstorno_clicked();

    void on_recarregar_clicked();

    void on_consultaSaldo_clicked();

    void on_emitirCartao_clicked();

    void on_recuperarCartao_clicked();
	
	void on_relatorios_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    void atualizarUltimasOperacoes();
};

#endif // MAINWINDOW_H

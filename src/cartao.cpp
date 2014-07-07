#include "cartao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "bancodados.h"

Cartao::Cartao(qlonglong id)
{
    _id = id;
}

double Cartao::creditos()
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("SELECT * FROM cartoes WHERE codigo=%1").arg(_id));
    q.next();
    return q.value(3).toDouble();
}

bool Cartao::recarregar(float valor)
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("UPDATE cartoes SET creditos=creditos+%1 WHERE codigo=%2").arg(valor).arg(_id));
}

bool Cartao::extornar(float valor)
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("UPDATE cartoes SET creditos=creditos+%1 WHERE codigo=%2").arg(valor).arg(_id));
}

bool Cartao::debitar(float valor)
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("UPDATE cartoes SET creditos=creditos-%1 WHERE codigo=%2").arg(valor).arg(_id));
    return !q.lastError().isValid();
}

bool Cartao::emitir(const QString &nome, const QString &cpf, qlonglong codigo, double valor)
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("INSERT INTO cartoes(nome,cpf,creditos,codigo) VALUES('%1','%2',%3,%4)").arg(nome).arg(cpf).arg(valor).arg(codigo));
    return !q.lastError().isValid();
}

QString Cartao::saldo(Cartao c)
{
    return QLocale().toCurrencyString(c.creditos());
}

QString Cartao::cliente(Cartao c)
{
    QSqlQuery q(BancoDados::db);
    q.exec(QString("SELECT * FROM cartoes WHERE codigo=%1").arg(c.id()));
    q.next();
    qDebug() << q.value(2);
    return "";
}

bool Cartao::unico(const QString &cpf, qlonglong codigo)
{
    QSqlQuery q1(BancoDados::db);
    q1.exec(QString("SELECT * FROM cartoes WHERE codigo=%1 OR cpf='%2'").arg(codigo).arg(cpf));
    return !q1.first();
}

bool Cartao::existe(qlonglong codigo)
{
    QSqlQuery q1(BancoDados::db);
    q1.exec(QString("SELECT * FROM cartoes WHERE codigo=%1").arg(codigo));
    return q1.first();
}

bool Cartao::existe(const QString &cpf)
{
    QSqlQuery q1(BancoDados::db);
    q1.exec(QString("SELECT * FROM cartoes WHERE cpf='%1'").arg(cpf));
    return q1.first();
}

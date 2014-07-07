#include "operacao.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>

#include "bancodados.h"

Operacao::Operacao(Cartao cartao, Tipo tipo, float valor, qlonglong data)
{
    _cartao = cartao;
    _tipo = tipo;
    _valor = valor;
    _data = data;
}

void Operacao::salvar()
{
    QSqlQuery query(BancoDados::db);
    query.exec(QString("INSERT INTO operacoes(tipo,valor,cartao_id,data) VALUES(%1,%2,%3,%4)").arg(_tipo).arg(_valor).arg(_cartao.id()).arg(_data));
    qDebug() << query.lastError().text();

    if (_tipo == Debito)
        _cartao.debitar(_valor);
    else if (_tipo == Recarga)
        _cartao.recarregar(_valor);
    else if (_tipo == Extorno)
        _cartao.extornar(_valor);
}

QList<Operacao> Operacao::ultimas()
{
    QList<Operacao> list;

    QSqlQuery q(BancoDados::db);
    q.exec(QString("SELECT * FROM operacoes WHERE data>=%1 ORDER BY data DESC LIMIT 1000").arg(QDateTime(QDate::currentDate()).toTime_t()));

    while (q.next()) {
        qlonglong id = q.value(0).toLongLong();
        qlonglong tipo = q.value(1).toLongLong();
        double valor = q.value(2).toDouble();
        qlonglong cartao = q.value(3).toLongLong();
        qlonglong data = q.value(4).toLongLong();

        Operacao op(Cartao(cartao), (Tipo)tipo, valor, data);
        op.setId(id);

        list << op;
    }

    return list;
}

QList<Operacao> Operacao::dia(const QDate &data)
{
    QList<Operacao> list;

    QSqlQuery q(BancoDados::db);
    q.exec(QString("SELECT * FROM operacoes WHERE data>=%1 AND data<=%2 ORDER BY data DESC LIMIT 1000").arg(QDateTime(data).toTime_t()).arg(QDateTime(data.addDays(1)).toTime_t()));

    while (q.next()) {
        qlonglong id = q.value(0).toLongLong();
        qlonglong tipo = q.value(1).toLongLong();
        double valor = q.value(2).toDouble();
        qlonglong cartao = q.value(3).toLongLong();
        qlonglong data = q.value(4).toLongLong();

        Operacao op(Cartao(cartao), (Tipo)tipo, valor, data);
        op.setId(id);

        list << op;
    }

    return list;
}

QString Operacao::valor(Operacao op)
{
    return QLocale().toCurrencyString(op.valor());
}

QString Operacao::tipo(Operacao op)
{
    if (op.tipo() == Debito)
        return QObject::trUtf8("Débito");
    if (op.tipo() == Extorno)
        return QObject::trUtf8("Extorno");
    if (op.tipo() == Recarga)
        return QObject::trUtf8("Recarga");

    return "";
}

QString Operacao::horario(Operacao op)
{
    return QDateTime::fromTime_t(op.data()).toString("HH:mm:ss");
}

#ifndef CARTAO_H
#define CARTAO_H

#include <QString>
#include <QSqlDatabase>

class Cartao
{
public:
    Cartao() { }
    Cartao(qlonglong id);

    qlonglong id() { return _id; }

    double creditos();

    bool recarregar(float valor);
    bool extornar(float valor);
    bool debitar(float valor);

    static QString saldo(Cartao c);
    static QString cliente(Cartao c);

    static bool emitir(const QString &nome, const QString &cpf, qlonglong codigo, double valor);
    static bool unico(const QString &cpf, qlonglong codigo);
    static bool existe(qlonglong codigo);
    static bool existe(const QString &cpf);

private:
    qlonglong _id;
};

#endif // CARTAO_H

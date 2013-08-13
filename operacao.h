#ifndef OPERACAO_H
#define OPERACAO_H

#include <cartao.h>
#include <QMap>
#include <QVariant>

class Operacao
{
public:
    enum Tipo {
        Debito = 1,
        Recarga,
        Extorno
    };

    Operacao(Cartao cartao, Tipo tipo, float valor, qlonglong data);

    qlonglong id() const { return _id; }
    void setId(qlonglong id) { _id = id; }

    float valor() const { return _valor; }
    Tipo tipo() const { return _tipo; }
    qlonglong data() const { return _data; }

    void salvar();

    static QList<Operacao> ultimas();
	static QList<Operacao> dia(const QDate &data);

    static QString valor(Operacao op);
    static QString tipo(Operacao op);
    static QString horario(Operacao op);

    bool operator==(const Operacao &op) const { return this->_id == op.id(); }

private:
    qlonglong _id;
    Cartao _cartao;
    Tipo _tipo;
    float _valor;
    qlonglong _data;
};

#endif // OPERACAO_H

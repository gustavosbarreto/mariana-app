#ifndef BANCODADOS_H
#define BANCODADOS_H

#include <QSqlDatabase>

class BancoDados
{
public:
    static void inicializar();
    static QSqlDatabase db;
};

#endif // BANCODADOS_H

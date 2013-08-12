#include "bancodados.h"

#include <QDir>
#include <QSqlQuery>

QSqlDatabase BancoDados::db = QSqlDatabase();

void BancoDados::inicializar()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::toNativeSeparators(QDir::home().path().append(QDir::separator()).append("mariana.sql")));
    db.open();

    if (db.tables().isEmpty()) {
        QSqlQuery q(db);
        q.exec("CREATE TABLE 'cartoes' ('id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,'nome' varchar(255) default NULL, 'cpf' varchar(255) default NULL, 'creditos' REAL default NULL, 'codigo' INTEGER NOT NULL);");
        q.exec("CREATE TABLE 'operacoes' ('id' INTEGER PRIMARY KEY,'tipo' INTEGER NOT NULL,'valor' REAL default 0,'cartao_id' INTEGER default NULL,'data' INTEGER NOT NULL);");
    }
}

#include "databaseconnection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QSqlDatabase>
#include <QDebug>

void DataBaseConnection::insertarPaises() {
    QSqlQuery insertar;
    insertar.prepare("INSERT INTO paises (nombre, utc) VALUES (:nombre, :utc)");
    insertar.bindValue(":nombre", "Argentina");
    insertar.bindValue(":utc", "-10800");
    insertar.bindValue(":nombre", "Estados Unidos");
    insertar.bindValue(":utc", "-18000");
    insertar.bindValue(":nombre", "España");
    insertar.bindValue(":utc", "3580");
    if (insertar.exec()){
        qDebug()<<"Pais se inserto en tabla";
    }else{
        qDebug()<<"ERROR  en carga entregas"<<insertar.lastError();
    }
}

void DataBaseConnection::crearTablaPaises(QSqlDatabase mDatabase) {
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS paises("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nombre VARCHAR(100),"
                    "utc  VARCHAR(30) "
                     ");");
    QSqlQuery crear;
    crear.prepare(consulta);
   if (!mDatabase.tables().contains(QLatin1String("paises"))) {
        if (crear.exec()){
            insertarPaises();
            qDebug()<<"La tabla paises existe o se creo correctamente";
        }else{
            qDebug()<<"ERROR "<<crear.lastError();
        }
    }
}

DataBaseConnection::DataBaseConnection(const QString &databaseName,
                                       const int &port,
                                       const QString &user,
                                       const QString &password) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(databaseName);
    mDatabase.setPort(port);
    mDatabase.setUserName(user);
    mDatabase.setPassword(password);
    if(mDatabase.open()){
        qDebug()<<"Base de datos conectada..";
    }else{
        qDebug()<<" ERROR Base de datos NO conectada..";
    }
    crearTablaPaises(mDatabase);
}

QString DataBaseConnection::getUTCbyPais(QString pais) {
    QString consulta;
    consulta.append("SELECT UTC FROM paises WHERE nombre = '")
            .append(pais)
            .append("'");
    QSqlQuery query;
    query.prepare(consulta);
    query.exec();
    query.value(0).toString();
 }

void DataBaseConnection::borrarPaises() {
    QString consultaEliminar;
    consultaEliminar.append("DELETE FROM paises");
    QSqlQuery eliminar;
    eliminar.prepare(consultaEliminar);
    if (eliminar.exec()){
        qDebug()<<"Pais se ELIMNINOOOOO en tabla";
    }else{
        qDebug()<<"ERROR  en carga entregas"<<eliminar.lastError();
    }
}

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>

class DataBaseConnection {
public:
    DataBaseConnection(const QString &databaseName,
                       const int &port,
                       const QString &user,
                       const QString &password);

private:
    QSqlDatabase mDatabase;
    QString mDatabaseName;
    int mPort;
    QString mUser;
    QString mPassword;

    void insertarPaises();
    void crearTablaPaises(QSqlDatabase mDatabase);
    QString getUTCbyPais(QString pais);
    void borrarPaises();

};

#endif // DATABASECONNECTION_H

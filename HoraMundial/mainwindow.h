#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "databaseconnection.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QSqlQueryModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildComboBoxPaises();
    QTime actualizaHora();

private slots:
    void showTime();
    void on_cmbPaises_currentTextChanged();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *mModel;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H

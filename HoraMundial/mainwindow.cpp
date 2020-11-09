#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnection.h"
#include <QTimer>
#include <QDateTime>
#include <QStringList>
#include <iostream>
using namespace std;
#include <QSqlQuery>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    const DataBaseConnection dbC = DataBaseConnection("horamundial.sqlite", 3307,
                    "root", "");
    ui->setupUi(this);
    mModel = nullptr;
    QTimer *timer = new QTimer(this);
    buildComboBoxPaises();
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
 }

void MainWindow::showTime() {
    QString timeText = actualizaHora().toString("hh : mm : ss");
    ui->DigitalClock->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    ui->DigitalClock->setWordWrap(true);
    ui->DigitalClock->setText(timeText);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::buildComboBoxPaises() {
    QSqlQuery query;
    query.prepare("SELECT * FROM paises");
    query.exec();
    qDebug()<<"ERROR "<<query.result();
    while(query.next()) {
        ui->cmbPaises->addItem(query.value(1).toString());
       qDebug()<<"ERROR "<<query.value(0).toString();
       qDebug()<<"ERROR "<<query.value(1).toString();
       qDebug()<<"ERROR "<<query.value(2).toString();
    }
 }

void MainWindow::on_cmbPaises_currentTextChanged() {
    showTime();
}

QTime MainWindow::actualizaHora() {
    QString valuePais = ui->cmbPaises->currentText();
    QTime time;
    if (valuePais == "Argentina"){
        time = QTime::currentTime().addSecs(-10800);
   } else if (valuePais == "España"){
        time = QTime::currentTime().addSecs(3580);
    } else if (valuePais == "Estados Unidos"){
         time = QTime::currentTime().addSecs(-18000);
    }
   return time;
}

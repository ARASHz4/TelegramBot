#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sendmessage.h"
#include "getupdate.h"
#include "getme.h"
#include "slsettings.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SLSettings::setToken(ui->lineEditToken->text());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSendMessage_clicked()
{
    SendMessage SMD(this);
    SMD.exec();
}

void MainWindow::on_pushButtonGetUpdate_clicked()
{
    GetUpdate GUD(this);
    GUD.exec();
}

void MainWindow::on_pushButtonGetMe_clicked()
{
    GetMe GMD(this);
    GMD.exec();
}

#include "sendmessage.h"
#include "ui_sendmessage.h"

#include <QDebug>

SendMessage::SendMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);


}

SendMessage::~SendMessage()
{
    delete ui;
}

void SendMessage::on_pushButtonSend_clicked()
{
    qDebug()<<"a";
    BSM = new Bot();
    qDebug()<<"b";
    BSM->SendMessage(ui->lineEditChatID->text(), ui->plainTextEditMessage->toPlainText(), true);
}

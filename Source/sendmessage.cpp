#include "sendmessage.h"
#include "ui_sendmessage.h"

#include <QDebug>

SendMessage::SendMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendMessage)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

SendMessage::~SendMessage()
{
    delete ui;
}

void SendMessage::on_pushButtonSend_clicked()
{
    BSM = new Bot();
    BSM->SendMessage(ui->lineEditChatID->text(), ui->plainTextEditMessage->toPlainText(), true);
}

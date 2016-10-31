#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <QDialog>

#include "bot.h"

namespace Ui {
class SendMessage;
}

class SendMessage : public QDialog
{
    Q_OBJECT

public:
    explicit SendMessage(QWidget *parent = 0);
    ~SendMessage();

private slots:
    void on_pushButtonSend_clicked();

private:
    Ui::SendMessage *ui;

    //BSM : Bot Seand Message
    Bot *BSM;
};

#endif // SENDMESSAGE_H

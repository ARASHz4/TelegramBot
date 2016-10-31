#ifndef GETME_H
#define GETME_H

#include <QDialog>
#include "bot.h"

namespace Ui {
class GetMe;
}

class GetMe : public QDialog
{
    Q_OBJECT

public:
    explicit GetMe(QWidget *parent = 0);
    ~GetMe();

private slots:
    void readJson();

    void Download_Completed();

    void on_okPushButton_clicked();

private:
    Ui::GetMe *ui;

    //BGM : Bot Get Message
    Bot *BGM;
};

#endif // GETME_H

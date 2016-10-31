#ifndef GETUPDATE_H
#define GETUPDATE_H

#include <QDialog>

#include <bot.h>

namespace Ui {
class GetUpdate;
}

class GetUpdate : public QDialog
{
    Q_OBJECT

public:
    explicit GetUpdate(QWidget *parent = 0);
    ~GetUpdate();

private slots:
    void Download_Completed();

    void on_pushButton_clicked();

private:
    Ui::GetUpdate *ui;

    //BGU: Bot Get Update
    Bot BGU;
};

#endif // GETUPDATE_H

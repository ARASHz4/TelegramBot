#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bot.h"
#include "slsettings.h"
#include "options.h"
#include "about.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QSystemTrayIcon>

namespace Ui {
class BotWindow;
}

class BotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BotWindow(QWidget *parent = 0);
    ~BotWindow();

private:
    Ui::BotWindow *ui;

    QSystemTrayIcon *TBTray;

    //BGU: Bot Get Update
    Bot *BGU;

public slots:
    void Start();

private slots:
    void closeEvent(QCloseEvent *CloseEvant);

    void on_actionGetUpdate_triggered();

    void Download_Completed();

    void on_actionSendMessage_triggered();

    void on_actionGetMe_triggered();

    void on_actionOptions_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

};

#endif // MAINWINDOW_H

#include "botwindow.h"
#include "ui_botwindow.h"
#include "sendmessage.h"
#include "getme.h"
#include "slsettings.h"

#include <QDebug>

BotWindow::BotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BotWindow)
{
    ui->setupUi(this);

    Start();
}

BotWindow::~BotWindow()
{
    delete ui;
}

void BotWindow::Start()
{
    qDebug()<<"1";

    TBTray = new QSystemTrayIcon;

    ui->retranslateUi(this);

    //Bot Window Size & Post Setting
    {
        int x, y, w, h, toolBarArea;
        bool window_max, window_fuls;
        std::tie(x, y, w, h, toolBarArea, window_max, window_fuls) = SLSettings::LoadBotWindow();

        if(x != 0 || y != 0 || w != 0 || h != 0)
        {
            this->setGeometry(x, y, w, h);
        }

        addToolBar(Qt::ToolBarArea(toolBarArea), ui->mainToolBar);

        if(window_max)
        {
            showMaximized();
        }

        if(window_fuls)
        {
            showFullScreen();
        }
    }


    QList<QAction *> ActionList;
    QMenu *TrayMenu = new QMenu(this);

    ActionList <<ui->actionAbout <<TrayMenu->addSeparator() <<TrayMenu->addSeparator() <<ui->actionRestoreWindow <<ui->actionExit;
    TrayMenu->addActions(ActionList);



    TBTray->connect(TBTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
                    SLOT(RestoreWindowTrigger(QSystemTrayIcon::ActivationReason)));



    #if !defined(Q_OS_MAC)
    TBTray->setIcon(QIcon(":/Icon/Icons/Small Icon.png"));
    #else
    TBTray->setIcon(QIcon(":/Icon/Icons/Small Icon BW.png"));
    #endif
    qDebug()<<"2";
    TBTray->setContextMenu(TrayMenu);

    TBTray->show();



//    if(QApplication::arguments().count() >= 2)
//    {
//        if(QApplication::arguments()[1] != "-start")
//        {
//            show();
//        }
//    }
//    else
//    {
//        show();
//    }
}

void BotWindow::closeEvent(QCloseEvent *CloseEvant)
{
    if(SLSettings::MinimizeToTray())
    {
        CloseEvant->ignore();

        this->hide();
    }
    else
    {
        TBTray->hide();

        SLSettings::SaveBotWindow(this->geometry().x(), this->geometry().y(), this->geometry().width(),
                                    this->geometry().height(), toolBarArea(ui->mainToolBar), isMaximized(), isFullScreen());
    }
}

void BotWindow::on_actionGetUpdate_triggered()
{
    BGU = new Bot();
    BGU->getUpdate();

    connect(BGU, SIGNAL (downloaded()), this, SLOT (Download_Completed()));
    connect(BGU, SIGNAL (downloadError()), this, SLOT (showDownloadError()));
}

void BotWindow::Download_Completed()
{
    ui->botPlainTextEdit->setPlainText(QString(BGU->downloadedData()));
}

void BotWindow::on_actionSendMessage_triggered()
{
    SendMessage SMD(this);
    SMD.exec();
}

void BotWindow::on_actionGetMe_triggered()
{
    GetMe GMD(this);
    GMD.exec();
}

void BotWindow::on_actionOptions_triggered()
{
    Options OD(this);
    OD.exec();
}

void BotWindow::on_actionExit_triggered()
{
    TBTray->hide();

    SLSettings::SaveBotWindow(this->geometry().x(), this->geometry().y(), this->geometry().width(),
                                this->geometry().height(), toolBarArea(ui->mainToolBar), isMaximized(), isFullScreen());

    exit(1);
}

void BotWindow::on_actionAbout_triggered()
{
    About AD(this);
    AD.exec();
}

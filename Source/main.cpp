#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication TelegramBot(argc, argv);

    TelegramBot.setOrganizationName("ARASHz4");
    TelegramBot.setApplicationName("Telegram Bot");
    TelegramBot.setApplicationVersion("1.0.0 Alpha");
    TelegramBot.setOrganizationDomain("arashz4.com");

    MainWindow w;
    w.show();

    return TelegramBot.exec();
}

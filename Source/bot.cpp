#include "bot.h"
#include "slsettings.h"

#include <QDebug>
#include <QMessageBox>

Bot::Bot(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void Bot::SendMessage(QString chatID, QString MessageText, bool disableNotification)
{
    reply = manager->get(QNetworkRequest(QUrl("https://api.telegram.org/bot" + SLSettings::Token()
                                      + "/sendMessage?chat_id=" + chatID
                                      + "&text=" + MessageText + "&text="
                                      + QString(disableNotification))));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT (fileDownloaded()));

}

void Bot::getUpdate()
{
    reply = manager->get(QNetworkRequest(QUrl("https://api.telegram.org/bot" + SLSettings::Token() + "/getUpdates")));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT (fileDownloaded()));
}

void Bot::error(QNetworkReply::NetworkError)
{
    //DLE = reply->errorString();
    reply->deleteLater();

    emit downloadError();
}

void Bot::fileDownloaded()
{
    DownloadedData = reply->readAll();
    reply->deleteLater();

    emit downloaded();

    QMessageBox msgBox;
    msgBox.setText("sanded");
    msgBox.exec();
}

QByteArray Bot::downloadedData() const
{
    return DownloadedData;
}

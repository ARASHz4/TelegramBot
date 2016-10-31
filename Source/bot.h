#ifndef BOT_H
#define BOT_H

#include <QString>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>

#include <QObject>

class Bot : public QObject
{
    Q_OBJECT
public:
    explicit Bot(QObject *parent = 0);

    QByteArray downloadedData() const;

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray DownloadedData;

signals:
    void downloaded();

    void downloadError();

public slots:
    void SendMessage(QString chatID, QString MessageText, bool disableNotification);

    void getUpdate();

private slots:
    void error(QNetworkReply::NetworkError);

    void fileDownloaded();
};

#endif // BOT_H

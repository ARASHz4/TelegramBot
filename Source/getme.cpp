#include "getme.h"
#include "ui_getme.h"
#include "bot.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

GetMe::GetMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetMe)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    BGM = new Bot();

    BGM->getMe();

    connect(BGM, SIGNAL (downloaded()), this, SLOT (Download_Completed()));
    connect(BGM, SIGNAL (downloadError()), this, SLOT (showDownloadError()));
}

GetMe::~GetMe()
{
    delete ui;
}

void GetMe::Download_Completed()
{
    ui->plainTextEdit->setPlainText(QString(BGM->downloadedData()));

    readJson();
}

void GetMe::readJson()
{
    QString val = QString(BGM->downloadedData());

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("result"));

    QJsonObject item = value.toObject();

    ui->botNameLabel->setText(item["first_name"].toString());
    ui->botUserNameLabel->setText(item["username"].toString());
    ui->botIDLabel->setText(QString::number(item["id"].toInt()));
}

void GetMe::on_okPushButton_clicked()
{
    close();
}

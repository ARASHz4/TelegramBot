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
    QString val;
    val = QString(BGM->downloadedData());

    qWarning() << val;
    /*QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("result"));
    qWarning() << value;
    QJsonObject item = value.toObject();
    qWarning() << tr("QJsonObject of description: ") << item;

    //incase of string value get value and convert into string
    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue subobj = item["description"];
    qWarning() << subobj.toString();

    //incase of array get array and convert into string
    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    QJsonArray test = item["imp"].toArray();
    qWarning() << test[1].toString();*/
}

void GetMe::on_okPushButton_clicked()
{
    close();
}

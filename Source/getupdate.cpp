#include "getupdate.h"
#include "ui_getupdate.h"

GetUpdate::GetUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetUpdate)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    BGU.getUpdate();

    connect(&BGU, SIGNAL (downloaded()), this, SLOT (Download_Completed()));
    connect(&BGU, SIGNAL (downloadError()), this, SLOT (showDownloadError()));
}

GetUpdate::~GetUpdate()
{
    delete ui;
}

void GetUpdate::Download_Completed()
{
    //QString DataAsString = QTextCodec::codecForMib(1015)->toUnicode(BGU.downloadedData());

    ui->plainTextEdit->setPlainText(QString(BGU.downloadedData()));
}
void GetUpdate::on_pushButton_clicked()
{

}

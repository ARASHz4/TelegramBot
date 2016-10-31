#include "slsettings.h"

QString SLSettings::token;

SLSettings::SLSettings(QObject *parent) : QObject(parent)
{

}


QString SLSettings::Token()
{
    return token;
}

void SLSettings::setToken(QString value)
{
    token = value;
}

#ifndef SLSETTINGS_H
#define SLSETTINGS_H

#include <QObject>

class SLSettings : public QObject
{
    Q_OBJECT
public:
    explicit SLSettings(QObject *parent = 0);

    static QString Token();
    static void setToken(QString value);

private:
    static QString token;

signals:

public slots:
};

#endif // SLSETTINGS_H

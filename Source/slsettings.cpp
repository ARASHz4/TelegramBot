#include "slsettings.h"

QString SLSettings::token;
int SLSettings::language;
bool SLSettings::automaticLanguage, SLSettings::minimizeToTray, SLSettings::runStartUp;

SLSettings::SLSettings()
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

void SLSettings::setMinimizeToTray(bool value)
{
    minimizeToTray = value;
}

bool SLSettings::MinimizeToTray()
{
    return minimizeToTray;
}

void SLSettings::setLanguage(int value)
{
    language = value;
}

int SLSettings::Language()
{
    return language;
}

void SLSettings::setRunStartUp(bool value)
{
    runStartUp = value;
}

bool SLSettings::RunStartUp()
{
    return runStartUp;
}

void SLSettings::setAutomaticLanguage(bool value)
{
    automaticLanguage = value;
}

bool SLSettings::AutomaticLanguage()
{
    return automaticLanguage;
}

void SLSettings::LoadSettings()
{
    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());
    SettingsTB.beginGroup("Options");

    //General
    {
        SLSettings::setToken(SettingsTB.value("Token").toString());

        if((QString(SettingsTB.value("MinimizeToTray").toString()).isEmpty())
                || (QString(SettingsTB.value("MinimizeToTray").toString())!="true"
                    && QString(SettingsTB.value("MinimizeToTray").toString())!="false"))
        {
            SettingsTB.setValue("MinimizeToTray", "true");
        }
        SLSettings::setMinimizeToTray(SettingsTB.value("MinimizeToTray").toBool());

        if((QString(SettingsTB.value("RunStartUp").toString()).isEmpty())
                || (QString(SettingsTB.value("RunStartUp").toString())!="true"
                    && QString(SettingsTB.value("RunStartUp").toString())!="false"))
        {
            SettingsTB.setValue("RunStartUp", "true");
        }
        SLSettings::setRunStartUp(SettingsTB.value("RunStartUp").toBool());

        if(RunStartUp())
        {
            #if defined(Q_OS_WIN)
            QSettings settingAddStartUp("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settingAddStartUp.setValue(QApplication::applicationName(), "\"" +
                                       QDir::toNativeSeparators(QApplication::applicationFilePath()) + "\" " + "-start");
            #elif defined(Q_OS_MAC)
            QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/LaunchAgents/arashz4.telegrambot.plist");
            if(file.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&file);
                stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                          "\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"
                          "\n<plist version=\"1.0\">"
                          "\n<dict>"
                          "\n	<key>Label</key>"
                          "\n	<string>arashz4.telegrambot</string>"
                          "\n	<key>ProgramArguments</key>"
                          "\n	<array>"
                          "\n       <string>" + QApplication::applicationFilePath() + "</string>"
                          "\n       <string>-start</string>"
                          "\n   </array>"
                          "\n   <key>RunAtLoad</key>"
                          "\n   <true/>"
                          "\n</dict>"
                          "\n</plist>" << endl;
            }
            #elif defined(Q_OS_LINUX)
            QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.config/autostart/TelegramBot.desktop");

            if(!QDir(QFileInfo(file).path()).exists())
            {
                QDir().mkdir(QFileInfo(file).path());
            }

            if(file.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&file);
                stream << "[Desktop Entry]\nType=Application\nExec=" + QApplication::applicationDirPath() + "/TelegramBot.sh -start" +
                          "\nHidden=false\nNoDisplay=false\nX-GNOME-Autostart-enabled=true\nName=Telegram Bot" << endl;
            }
            #endif
        }
    }

    //Language
    {
        if(!SettingsTB.value("Language").toString().isEmpty() &&
                (SettingsTB.value("Language").toInt() == 0
                 || SettingsTB.value("Language").toInt() == QLocale::English
                 || SettingsTB.value("Language").toInt() == QLocale::Persian))
        {
            SLSettings::setLanguage(SettingsTB.value("Language").toInt());
        }
        else
        {
            SLSettings::setLanguage(0);
            SettingsTB.setValue("Language", SLSettings::Language());
        }

        QTranslator *Translator = new QTranslator;

        if(SLSettings::Language() == 0)
        {
            if(QLocale::system().language() == QLocale::English)
            {
                Translator->load(":/Language/Language/English.qm");
                QApplication::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::English);
            }
            else if(QLocale::system().language() == QLocale::Persian)
            {
                Translator->load(":/Language/Language/Persian.qm");
                QApplication::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::Persian);
            }
            else
            {
                Translator->load(":/Language/Language/English.qm");
                QApplication::installTranslator(Translator);

                SLSettings::setLanguage(QLocale::English);
            }

            SLSettings::setAutomaticLanguage(true);
        }
        else
        {
            if(SLSettings::Language() == QLocale::English)
            {
                Translator->load(":/Language/Language/English.qm");
                QApplication::installTranslator(Translator);
            }
            else if(SLSettings::Language() == QLocale::Persian)
            {
                Translator->load(":/Language/Language/Persian.qm");
                QApplication::installTranslator(Translator);
            }

            SLSettings::setAutomaticLanguage(false);
        }

        if(SLSettings::Language() == QLocale::English)
        {
            QApplication::setLayoutDirection(Qt::LeftToRight);
        }
        else if(SLSettings::Language() == QLocale::Persian)
        {
            QApplication::setLayoutDirection(Qt::RightToLeft);
        }
    }

    SettingsTB.endGroup();
}

void SLSettings::SaveSettings()
{
    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());
    SettingsTB.beginGroup("Options");

    SettingsTB.setValue("Token", SLSettings::Token());

    SettingsTB.setValue("MinimizeToTray", SLSettings::MinimizeToTray());

    SettingsTB.setValue("RunStartUp", SLSettings::RunStartUp());

    if(RunStartUp())
    {
        #if defined(Q_OS_WIN)
        QSettings settingAddStartUp("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settingAddStartUp.setValue(QApplication::applicationName(), "\"" +
                                   QDir::toNativeSeparators(QApplication::applicationFilePath()) + "\" " + "-start");
        #elif defined(Q_OS_MAC)
        QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/LaunchAgents/arashz4.telegrambot.plist");
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                      "\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"
                      "\n<plist version=\"1.0\">"
                      "\n<dict>"
                      "\n	<key>Label</key>"
                      "\n	<string>arashz4.telegrambot</string>"
                      "\n	<key>ProgramArguments</key>"
                      "\n	<array>"
                      "\n       <string>" + QApplication::applicationFilePath() + "</string>"
                      "\n       <string>-start</string>"
                      "\n   </array>"
                      "\n   <key>RunAtLoad</key>"
                      "\n   <true/>"
                      "\n</dict>"
                      "\n</plist>" << endl;
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle(QObject::tr("Startup Error"));
            msg.setWindowIcon(QIcon(":/Icon/Icons/Big Icon.png"));
            msg.setText(QObject::tr("Can't save to startup"));
            msg.setButtonText(QMessageBox::Ok, QObject::tr("OK"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
        }
        #elif defined(Q_OS_LINUX)
        QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                   + "/.config/autostart/TelegramBot.desktop");

        if(!QDir(QFileInfo(file).path()).exists())
        {
            QDir().mkdir(QFileInfo(file).path());
        }

        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "[Desktop Entry]\nType=Application\nExec=" + QApplication::applicationDirPath() + "/TelegramBot.sh -start"
                      + "\nHidden=false\nNoDisplay=false\nX-GNOME-Autostart-enabled=true\nName=Telegram Bot" << endl;
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle(QObject::tr("Startup Error"));
            msg.setWindowIcon(QIcon(":/Icon/Icons/Big Icon.png"));
            msg.setText(QObject::tr("Can't save to startup"));
            msg.setInformativeText(QObject::tr("Please make sure you have the correct permission in :\n")
                                   + "~/.config/autostart/TelegramBot.desktop");
            msg.setButtonText(QMessageBox::Ok, QObject::tr("OK"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
        }
        #endif
    }
    else
    {
        #if defined(Q_OS_WIN)
        QSettings settingDeleteStartUp("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settingDeleteStartUp.remove(QApplication::applicationName());
        #elif defined(Q_OS_MAC)
        QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/Library/LaunchAgents/arashz4.telegrambot.plist");
        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                      "\n<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">"
                      "\n<plist version=\"1.0\">"
                      "\n<dict>"
                      "\n	<key>Label</key>"
                      "\n	<string>arashz4.telegrambot</string>"
                      "\n	<key>ProgramArguments</key>"
                      "\n	<array>"
                      "\n       <string>" + QApplication::applicationFilePath() + "</string>"
                      "\n       <string>-start</string>"
                      "\n   </array>"
                      "\n   <key>RunAtLoad</key>"
                      "\n   <false/>"
                      "\n</dict>"
                      "\n</plist>" << endl;
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle(QObject::tr("Startup Error"));
            msg.setWindowIcon(QIcon(":/Icon/Icons/Big Icon.png"));
            msg.setText(QObject::tr("Can't save to startup"));
            msg.setButtonText(QMessageBox::Ok, QObject::tr("OK"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
        }
        #elif defined(Q_OS_LINUX)
        QFile file(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                   + "/.config/autostart/TelegramBot.desktop");

        if(!QDir(QFileInfo(file).path()).exists())
        {
            QDir().mkdir(QFileInfo(file).path());
        }

        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "[Desktop Entry]\nType=Application\nExec=" + QApplication::applicationDirPath() + "/TelegramBot.sh -start"
                      + "\nHidden=false\nNoDisplay=false\nX-GNOME-Autostart-enabled=false\nName=Telegram Bot" << endl;
        }
        else
        {
            QMessageBox msg;
            msg.setIcon(QMessageBox::Warning);
            msg.setWindowTitle(QObject::tr("Startup Error"));
            msg.setWindowIcon(QIcon(":/Icon/Icons/Big Icon.png"));
            msg.setText(QObject::tr("Can't save to startup"));
            msg.setInformativeText(QObject::tr("Please make sure you have the correct permission in :\n")
                                   + "~/.config/autostart/TelegramBot.desktop");
            msg.setButtonText(QMessageBox::Ok, QObject::tr("OK"));
            msg.setStandardButtons(QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Ok);
            msg.exec();
        }
        #endif
    }

    if(SLSettings::AutomaticLanguage())
    {
        SettingsTB.setValue("Language", 0);
    }
    else
    {
        SettingsTB.setValue("Language", SLSettings::Language());
    }

    SettingsTB.endGroup();
}

std::tuple<int, int, int, int, int, bool, bool> SLSettings::LoadBotWindow()
{
    QRect ScreenSize = QApplication::desktop()->screenGeometry();

    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());
    SettingsTB.beginGroup("BotWindowSizePos");

    if(SettingsTB.value("toolBarArea").toInt() != Qt::TopToolBarArea && SettingsTB.value("toolBarArea").toInt() != Qt::RightToolBarArea
    && SettingsTB.value("toolBarArea").toInt() != Qt::LeftToolBarArea && SettingsTB.value("toolBarArea").toInt() != Qt::BottomToolBarArea)
    {
        SettingsTB.setValue("toolBarArea", Qt::TopToolBarArea);
    }

    if((QString(SettingsTB.value("window_max").toString()).isEmpty())
         || (QString(SettingsTB.value("window_max").toString())!="true"
         && QString(SettingsTB.value("window_max").toString())!="false"))
    {
        SettingsTB.setValue("window_max", "false");
    }

    if((QString(SettingsTB.value("window_fuls").toString()).isEmpty())
         || (QString(SettingsTB.value("window_fuls").toString())!="true"
         && QString(SettingsTB.value("window_fuls").toString())!="false"))
    {
        SettingsTB.setValue("window_fuls", "false");
    }

    if((SettingsTB.value("window_posx").toInt() != 0 && SettingsTB.value("window_posy").toInt() != 0) &&
       (SettingsTB.value("window_sizew").toInt() <= ScreenSize.width() && SettingsTB.value("window_sizeh").toInt() <= ScreenSize.height()))
    {
        return std::make_tuple(SettingsTB.value("window_posx").toInt(), SettingsTB.value("window_posy").toInt(),
                               SettingsTB.value("window_sizew").toInt(), SettingsTB.value("window_sizeh").toInt(),
                               SettingsTB.value("toolBarArea").toInt(), SettingsTB.value("window_max").toBool(),
                               SettingsTB.value("window_fuls").toBool());
    }
    else
    {
        return std::make_tuple(0, 0, 0, 0, SettingsTB.value("toolBarArea").toInt(),
                               SettingsTB.value("window_max").toBool(), SettingsTB.value("window_fuls").toBool());
    }

    SettingsTB.endGroup();
}

void SLSettings::SaveBotWindow(int x, int y, int w, int h, int toolBarArea, bool window_max, bool window_fuls)
{
    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());

    SettingsTB.beginGroup("BotWindowSizePos");

    if(window_max == false && window_fuls == false)
    {
        SettingsTB.setValue("window_posx", x);
        SettingsTB.setValue("window_posy", y);

        SettingsTB.setValue("window_sizew", w);
        SettingsTB.setValue("window_sizeh", h);
    }

    SettingsTB.setValue("toolBarArea", toolBarArea);

    SettingsTB.setValue("window_max", window_max);
    SettingsTB.setValue("window_fuls", window_fuls);

    SettingsTB.endGroup();
}

std::tuple<int, int, int, int> SLSettings::LoadOptionsWindow()
{
    QRect ScreenSize = QApplication::desktop()->screenGeometry();

    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());
    SettingsTB.beginGroup("OptionsWindowSizePos");

    if((SettingsTB.value("window_posx").toInt() != 0 && SettingsTB.value("window_posy").toInt() != 0) &&
       (SettingsTB.value("window_sizew").toInt() <= ScreenSize.width() && SettingsTB.value("window_sizeh").toInt() <= ScreenSize.height()))
    {
        return std::make_tuple(SettingsTB.value("window_posx").toInt(), SettingsTB.value("window_posy").toInt(),
                               SettingsTB.value("window_sizew").toInt(), SettingsTB.value("window_sizeh").toInt());
    }
    else
    {
        return std::make_tuple(0, 0, 0, 0);
    }
    SettingsTB.endGroup();
}

void SLSettings::SaveOptionsWindow(int x, int y, int w, int h)
{
    QSettings SettingsTB (QApplication::organizationName(), QApplication::applicationName());

    SettingsTB.beginGroup("OptionsWindowSizePos");

    SettingsTB.setValue("window_posx", x);
    SettingsTB.setValue("window_posy", y);

    SettingsTB.setValue("window_sizew", w);
    SettingsTB.setValue("window_sizeh", h);

    SettingsTB.endGroup();
}

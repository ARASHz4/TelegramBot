#ifndef SLSETTINGS_H
#define SLSETTINGS_H

#include <QSettings>
#include <QApplication>
#include <QDesktopWidget>
#include <QLocale>
#include <QTranslator>
#include <QDir>

class SLSettings
{
public:
    SLSettings();

    static QString Token();

    static void setToken(QString value);

    static void setMinimizeToTray(bool value);

    static bool MinimizeToTray();

    static void setRunStartUp(bool value);

    static bool RunStartUp();

    static void SaveSettings();

    static void LoadSettings();

    static void setLanguage(int value);

    static int Language();

    static void setAutomaticLanguage(bool value);

    static bool AutomaticLanguage();

    static std::tuple<int, int, int, int, int, bool, bool> LoadBotWindow();

    static void SaveBotWindow(int x, int y, int w, int h, int toolBarArea, bool window_max, bool window_fuls);

    static std::tuple<int, int, int, int> LoadOptionsWindow();

    static void SaveOptionsWindow(int x, int y, int w, int h);

private:
    static QString token;
    static bool automaticLanguage, minimizeToTray, runStartUp;
    static int language;
};

#endif // SLSETTINGS_H

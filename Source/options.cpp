#include "options.h"
#include "ui_options.h"


Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Start();
}

Options::~Options()
{
    delete ui;
}

void Options::Start()
{
    int x, y, w, h;
    std::tie(x, y, w, h) = SLSettings::LoadOptionsWindow();

    if(x != 0 || y != 0 || w != 0 || h != 0)
    {
        this->setGeometry(x, y, w, h);
    }

    OK.connect(&OK, SIGNAL(clicked()), this, SLOT(OKButton()));
    Cancel.connect(&Cancel, SIGNAL(clicked()), this, SLOT(CancelButton()));
    Apply.connect(&Apply, SIGNAL(clicked()), this, SLOT(ApplyButton()));
    RestoreDefaults.connect(&RestoreDefaults, SIGNAL(clicked()), this, SLOT(RestoreDefaultsButton()));
    OK.setText(tr("OK"));
    Cancel.setText(tr("Cancel"));
    Apply.setText(tr("Apply"));
    RestoreDefaults.setText(tr("Restore Defaults"));
    OK.setDefault(true);

    ui->OptionsButtonBox->addButton(&OK, QDialogButtonBox::AcceptRole);
    ui->OptionsButtonBox->addButton(&Cancel, QDialogButtonBox::RejectRole);
    ui->OptionsButtonBox->addButton(&Apply, QDialogButtonBox::ApplyRole);
    ui->OptionsButtonBox->addButton(&RestoreDefaults, QDialogButtonBox::ResetRole);

    ui->listWidgetOptions->setCurrentRow(0);
    ui->LanguageComboBox->insertSeparator(1);

    Load();
}

void Options::on_listWidgetOptions_currentRowChanged(int currentRow)
{
    if(currentRow == 0)
    {
        ui->OptionsGroupBox->setTitle(tr("General"));

        ui->tokenLabel->setVisible(true);
        ui->tokenLineEdit->setVisible(true);
        ui->launchStartupCheckBox->setVisible(true);
        ui->minimizeToTrayCheckBox->setVisible(true);

        ui->LanguageLabel->setVisible(false);
        ui->LanguageComboBox->setVisible(false);
    }
    else if (currentRow == 1)
    {
        ui->OptionsGroupBox->setTitle(tr("Language"));

        ui->LanguageLabel->setVisible(true);
        ui->LanguageComboBox->setVisible(true);

        ui->tokenLabel->setVisible(false);
        ui->tokenLineEdit->setVisible(false);
        ui->launchStartupCheckBox->setVisible(false);
        ui->minimizeToTrayCheckBox->setVisible(false);
    }
}

void Options::Load()
{
    //General
    {
        ui->tokenLineEdit->setText(SLSettings::Token());
        ui->minimizeToTrayCheckBox->setChecked(SLSettings::MinimizeToTray());
        ui->launchStartupCheckBox->setChecked(SLSettings::RunStartUp());
    }

    //Language
    {
        if(SLSettings::AutomaticLanguage())
        {
            ui->LanguageComboBox->setCurrentIndex(0);
        }
        else
        {
            if(SLSettings::Language() == QLocale::English)
            {
                ui->LanguageComboBox->setCurrentIndex(2);
            }
            else if(SLSettings::Language() == QLocale::Persian)
            {
                ui->LanguageComboBox->setCurrentIndex(3);
            }
        }
    }
}

void Options::Save()
{
    //General
    {
        SLSettings::setToken(ui->tokenLineEdit->text());

        SLSettings::setMinimizeToTray(ui->minimizeToTrayCheckBox->isChecked());

        SLSettings::setRunStartUp(ui->launchStartupCheckBox->isChecked());
    }

    //Language
    {
        if(ui->LanguageComboBox->currentIndex() == 0)
        {
            SLSettings::setLanguage(0);
        }
        else if(ui->LanguageComboBox->currentIndex() == 2)
        {
            SLSettings::setLanguage(QLocale::English);
        }
        else if(ui->LanguageComboBox->currentIndex() == 3)
        {
            SLSettings::setLanguage(QLocale::Persian);
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

        if(SLSettings::Language() == QLocale::English || SLSettings::Language())
        {
            QApplication::setLayoutDirection(Qt::LeftToRight);
        }
        else if(SLSettings::Language() == QLocale::Persian)
        {
            QApplication::setLayoutDirection(Qt::RightToLeft);
        }
    }

    SLSettings::SaveSettings();
}

void Options::OKButton()
{
    Save();
    close();
}

void Options::CancelButton()
{
    close();
}

void Options::ApplyButton()
{
    Save();

    int cl = ui->LanguageComboBox->currentIndex();

    ui->retranslateUi(this);
    OK.setText(tr("OK"));
    Cancel.setText(tr("Cancel"));
    Apply.setText(tr("Apply"));
    RestoreDefaults.setText(tr("Restore Defaults"));

    if(ui->listWidgetOptions->currentRow() == 0)
    {
        ui->OptionsGroupBox->setTitle(tr("General"));
    }
    else if (ui->listWidgetOptions->currentRow() == 1)
    {
        ui->OptionsGroupBox->setTitle(tr("Language"));
    }

    ui->LanguageComboBox->insertSeparator(1);
    ui->LanguageComboBox->setCurrentIndex(cl);
}

void Options::RestoreDefaultsButton()
{
    SLSettings::setMinimizeToTray(true);
    SLSettings::setAutomaticLanguage(true);
    SLSettings::setLanguage(0);

    Load();
}

void Options::closeEvent (QCloseEvent *)
{
    SLSettings::SaveOptionsWindow(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height());

    this->hide();
}

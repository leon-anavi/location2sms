/*
* ============================================================================
*  Name         : languageswidget.h
*  Part of      : location2sms
*  Description  : manage languages
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef LANGUAGESWIDGET_H
#define LANGUAGESWIDGET_H

//Standard includes
#include <QTranslator>

//Project specific includes
#include "settingslistwidget.h"

class LanguagesWidget : public SettingsListWidget
{
    Q_OBJECT
public:
    explicit LanguagesWidget(Settings* pSettings, QWidget *parent = 0);

    virtual ~LanguagesWidget();

    /**
      * Read settings and load appropriate language
      *
      * @return nothing
      */
    void loadSettings();

private slots:

    void select();

public slots:

private:

    QTranslator m_Translator;

protected:

    //overload from QWidget
    void changeEvent(QEvent* event);

    //overload SettingsListWidget
    QString getLabelText() const;

    QString getButtonText() const;

private:

    void loadBulgarian();

    void loadEnglish();

    void loadTurkish();

    void loadGerman();

    void loadRomanian();

    void loadGreek();

    void loadDutch();

    void loadCzech();

    void loadIndonesian();

    void loadRussian();

    void loadFinnish();

    void loadSelectedLanguage();

};

#endif // LANGUAGESWIDGET_H

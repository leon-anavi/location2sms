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
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTranslator>
#include <QLabel>

//Project specific includes
#include "settings.h"

class LanguagesWidget : public QWidget
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
    void loadLanguageSettings();

    /**
      * resize
      *
      * @param nPosX postion X
      * @param nPosY position Y
      * @param nWidth Width
      * @param nHeight Height
      *
      * @return nothing
      */
    void resizeGUI(int nPosX, int nPosY, int nWidth, int nHeight);

protected:

    //overload from QWidget
    void paintEvent(QPaintEvent* event);

    //overload from QWidget
    void changeEvent(QEvent* event);

signals:

    void mapChanged();

    void langWidgetClosed();

private slots:

    void selectLang();

public slots:

private:

    Settings* m_pSettings;

    QVBoxLayout* m_pLangWidgetLayout;

    QLabel* m_pLangLabel;

    QLabel* m_pMapsLabel;

    QListWidget* m_pLangList;

    QListWidget* m_pMapsList;

    QPushButton* m_pLangSelect;

    QTranslator m_Translator;

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

    void loadSelectedLanguage();

    QString getLabelMap() const;

    QString getLabelLanguage() const;

};

#endif // LANGUAGESWIDGET_H

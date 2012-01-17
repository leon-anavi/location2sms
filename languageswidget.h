#ifndef LANGUAGESWIDGET_H
#define LANGUAGESWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QTranslator>

class LanguagesWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguagesWidget(QWidget *parent = 0);

    virtual ~LanguagesWidget();

    /**
      * Is application started for first time
      *
      * @return bool
      */
    bool isAppStartedForFirstTime() const;

    /**
      * set if the application is started for first time or not
      *
      * @param bIsFirstTime
      *
      * @return noting
      */
    void setIsAppStartedForFirstTime(bool bIsFirstTime);

    /**
      * Read settings and load appropriate language
      *
      * @return nothing
      */
    void loadLanguageSettings();

protected:

    //overload from QWidget
    void paintEvent(QPaintEvent* event);

signals:

    void langClosed();

private slots:

    void selectLang();

public slots:

private:

    QVBoxLayout* m_pLangWidgetLayout;

    QListWidget* m_pLangList;

    QPushButton* m_pLangSelect;

    QTranslator m_Translator;

    QString m_sSettingsFile;

    bool m_bIsAppStartedForFirstTime;

    int m_nSelectedLanguage;

private:

    void loadBulgarian();

    void loadEnglish();

    void loadTurkish();

    void loadGerman();

    void loadRomanian();

    void loadSettings();

    void saveSettings();

    void loadSelectedLanguage();

};

#endif // LANGUAGESWIDGET_H

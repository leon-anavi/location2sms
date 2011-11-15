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

private:

    void loadBulgarian();

    void loadEnglish();

    void loadTurkish();

};

#endif // LANGUAGESWIDGET_H

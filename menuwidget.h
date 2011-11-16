#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = 0);

    virtual ~MenuWidget();

signals:

    void showHelp();

    void showLang();

private slots:

    void handleHelp();

    void handleLang();

    void handleExit();

private:

    void initGui();

private:

    //controls
    QLabel* m_pControlLabel;

    QPushButton* m_pControlLang;

    QPushButton* m_pControlHelp;

    QPushButton* m_pControlExit;

    QHBoxLayout* m_pControlBar;

};

#endif // MENUWIDGET_H

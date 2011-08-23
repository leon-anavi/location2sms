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

signals:

    void showHelp();

private slots:

    void handleHelp();

    void handleExit();

private:

    void initGui();

private:

    //controls
    QHBoxLayout* m_pControlBar;

    QLabel* m_pControlLabel;

    QPushButton* m_pControlHelp;

    QPushButton* m_pControlExit;

};

#endif // MENUWIDGET_H

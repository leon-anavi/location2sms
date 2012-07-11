/*
* ============================================================================
*  Name         : custommessagebox.h
*  Part of      : location2sms
*  Description  : Custom message box
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2012
* ============================================================================
*/

#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

//Standard includes
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class CustomMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit CustomMessageBox(QWidget *parent = 0);

    virtual ~CustomMessageBox();

    QPushButton* addButton(const QString& sText);

    QLabel* addLabel(const QString& sText);

    void finalizeWidget();

    QPushButton* getLastClickedButton();

protected:

    //overload from QWidget
    void paintEvent(QPaintEvent* event);

signals:

    void buttonClicked();

private slots:

    void handleButtonClicked();

private:

    QVBoxLayout* m_pLayout;

    QPushButton* m_pLastPressedButton;
};

#endif // CUSTOMMESSAGEBOX_H

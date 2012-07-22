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
#include <QCheckBox>

class CustomMessageBox : public QWidget
{
    Q_OBJECT

public:

    explicit CustomMessageBox(QWidget *parent = 0);

    virtual ~CustomMessageBox();

    QPushButton* addButton(const QString& sText);

    QCheckBox* addCheckBox(const QString& sText);

    QLabel* addLabel(const QString& sText);

    void addSpacer();

    QPushButton* getLastClickedButton();

    void clear();

    /**
      * get message tag
      *
      * @return int
      */
    int getTag() const;

    /**
      * set message tag
      *
      * @param mTag
      *
      * @return nothing
      */
    void setTag(int nTag);

private:

    void clearLayout(QLayout* pLayout);

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

    //message identification
    int m_nTag;
};

#endif // CUSTOMMESSAGEBOX_H

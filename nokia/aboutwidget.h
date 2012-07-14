/*
* ============================================================================
*  Name         : aboutwidget.h
*  Part of      : location2sms
*  Description  : Show about information
*  Author     	: Leon Anavi
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

//Standard includes
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class AboutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent = 0);

    virtual ~AboutWidget();

protected:

    //overload from QWidget
    void paintEvent(QPaintEvent* event);

    //overload from QWidget
    void mousePressEvent(QMouseEvent* event);

    //overload from QWidget
    void changeEvent(QEvent* event);

private:

    QString getInfoText() const;

signals:

    void aboutClosed();

private:

    QVBoxLayout* m_pAboutWidgetLayout;

    QLabel* m_pAboutInfo;

};

#endif // ABOUTWIDGET_H

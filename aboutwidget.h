#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

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

signals:

    void aboutClosed();

private:

    QVBoxLayout* m_pAboutWidgetLayout;

    QLabel* m_pAboutInfo;

};

#endif // ABOUTWIDGET_H

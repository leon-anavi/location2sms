#ifndef PROXYWIDGET_H
#define PROXYWIDGET_H

#include <QDeclarativeItem>
#include "mainwindow.h"

/*
 * KNOWN ISSUES:
 * - No Harmattan style - https://bugreports.qt.nokia.com/browse/QTBUG-20617
 *   Workaround: Stylesheets (?)
 * - QMenuBar and QToolBar should not be used
 */

class QWidget;
class QGraphicsProxyWidget;

class ProxyWidget : public QDeclarativeItem
{
    Q_OBJECT
public:
    explicit ProxyWidget(QDeclarativeItem *parent = 0);

protected:
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF & oldGeometry);

private:
    MainWindow *mEmbeddedWidget;
    QGraphicsProxyWidget *mProxyWidget;
};

#endif // PROXYWIDGET_H

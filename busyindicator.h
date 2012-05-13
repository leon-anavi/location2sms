/*
* ============================================================================
*  Name         : busyindicator.h
*  Part of      : location2sms
*  Description  : Busy indicator
*  Author     	: ZapB, Leon Anavi
*  Tutorial     : http://qt-project.org/wiki/Busy_Indicator_for_QML
*  Email		: leon@anavi.org
*  License      : GNU General Public License version 3 (GPLv3)
*
*  Copyright (c) 2011-12
* ============================================================================
*/

#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

//Standard includes
#include <QDeclarativeItem>

class BusyIndicator : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY( qreal innerRadius READ innerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged )
    Q_PROPERTY( qreal outerRadius READ outerRadius WRITE setOuterRadius NOTIFY outerRadiusChanged )
    Q_PROPERTY( QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged )
    Q_PROPERTY( QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged )
    Q_PROPERTY( qreal actualInnerRadius READ actualInnerRadius NOTIFY actualInnerRadiusChanged )
    Q_PROPERTY( qreal actualOuterRadius READ actualOuterRadius NOTIFY actualOuterRadiusChanged )

public:
    explicit BusyIndicator( QDeclarativeItem* parent = 0 );

    virtual ~BusyIndicator();

    void setInnerRadius( const qreal& innerRadius );
    qreal innerRadius() const;

    void setOuterRadius( const qreal& outerRadius );
    qreal outerRadius() const;

    void setBackgroundColor( const QColor& color );
    QColor backgroundColor() const;

    void setForegroundColor( const QColor& color );
    QColor foregroundColor() const;

    qreal actualInnerRadius() const;
    qreal actualOuterRadius() const;

    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );

signals:
    void innerRadiusChanged();
    void outerRadiusChanged();
    void backgroundColorChanged();
    void foregroundColorChanged();
    void actualInnerRadiusChanged();
    void actualOuterRadiusChanged();

protected slots:
    virtual void updateSpinner();

private:
    // User settable properties
    qreal m_innerRadius; // In range (0, m_outerRadius]
    qreal m_outerRadius; // (m_innerRadius, 1]
    QColor m_backgroundColor;
    QColor m_foregroundColor;

    // The calculated size, inner and outer radii
    qreal m_size;
    qreal m_actualInnerRadius;
    qreal m_actualOuterRadius;

    QString m_cacheKey;
};

#endif // BUSYINDICATOR_H

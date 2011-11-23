/****************************************************************************
** Meta object code from reading C++ file 'busyindicator.h'
**
** Created: Wed Nov 23 09:23:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../busyindicator.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'busyindicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BusyIndicator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       6,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      36,   14,   14,   14, 0x05,
      57,   14,   14,   14, 0x05,
      82,   14,   14,   14, 0x05,
     107,   14,   14,   14, 0x05,
     134,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     161,   14,   14,   14, 0x09,

 // properties: name, type, flags
     183,  177, (QMetaType::QReal << 24) | 0x00495103,
     195,  177, (QMetaType::QReal << 24) | 0x00495103,
     214,  207, 0x43495103,
     230,  207, 0x43495103,
     246,  177, (QMetaType::QReal << 24) | 0x00495001,
     264,  177, (QMetaType::QReal << 24) | 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,

       0        // eod
};

static const char qt_meta_stringdata_BusyIndicator[] = {
    "BusyIndicator\0\0innerRadiusChanged()\0"
    "outerRadiusChanged()\0backgroundColorChanged()\0"
    "foregroundColorChanged()\0"
    "actualInnerRadiusChanged()\0"
    "actualOuterRadiusChanged()\0updateSpinner()\0"
    "qreal\0innerRadius\0outerRadius\0QColor\0"
    "backgroundColor\0foregroundColor\0"
    "actualInnerRadius\0actualOuterRadius\0"
};

const QMetaObject BusyIndicator::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_BusyIndicator,
      qt_meta_data_BusyIndicator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BusyIndicator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BusyIndicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BusyIndicator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BusyIndicator))
        return static_cast<void*>(const_cast< BusyIndicator*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int BusyIndicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: innerRadiusChanged(); break;
        case 1: outerRadiusChanged(); break;
        case 2: backgroundColorChanged(); break;
        case 3: foregroundColorChanged(); break;
        case 4: actualInnerRadiusChanged(); break;
        case 5: actualOuterRadiusChanged(); break;
        case 6: updateSpinner(); break;
        default: ;
        }
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = innerRadius(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = outerRadius(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = backgroundColor(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = foregroundColor(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = actualInnerRadius(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = actualOuterRadius(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setInnerRadius(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setOuterRadius(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: setForegroundColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void BusyIndicator::innerRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BusyIndicator::outerRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BusyIndicator::backgroundColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void BusyIndicator::foregroundColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void BusyIndicator::actualInnerRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void BusyIndicator::actualOuterRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Wed 13. Jun 00:13:23 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   12,   11,   11, 0x0a,
      62,   11,   11,   11, 0x08,
      84,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     118,   11,   11,   11, 0x08,
     132,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     164,   11,   11,   11, 0x08,
     184,  177,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0geoPositionInfo\0"
    "positionUpdated(QGeoPositionInfo)\0"
    "handleSmsSendButton()\0handleEmailSendButton()\0"
    "loadMap()\0loadAddress()\0loadMapShortUrl()\0"
    "handleAbout()\0handleLang()\0nValue\0"
    "rotateSpinner(int)\0mapChanged()\0"
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: positionUpdated((*reinterpret_cast< QGeoPositionInfo(*)>(_a[1]))); break;
        case 1: handleSmsSendButton(); break;
        case 2: handleEmailSendButton(); break;
        case 3: loadMap(); break;
        case 4: loadAddress(); break;
        case 5: loadMapShortUrl(); break;
        case 6: handleAbout(); break;
        case 7: handleLang(); break;
        case 8: rotateSpinner((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: mapChanged(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

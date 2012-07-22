/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Sun 22. Jul 20:40:29 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
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
     128,   11,   11,   11, 0x08,
     141,   11,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     221,  214,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     253,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     302,   11,   11,   11, 0x08,
     321,   11,   11,   11, 0x08,
     341,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0geoPositionInfo\0"
    "positionUpdated(QGeoPositionInfo)\0"
    "handleSmsSendButton()\0handleEmailSendButton()\0"
    "handlePanicButton()\0requestMap()\0"
    "loadMap()\0loadAddress()\0loadMapShortUrl()\0"
    "showOptionsMenu()\0handleLang()\0nValue\0"
    "rotateSpinner(int)\0mapChanged()\0"
    "enableLocationData()\0showEnableLocationDataMsg()\0"
    "handleMessageBox()\0handleOptionsMenu()\0"
    "handleSettingsMenu()\0"
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
        case 3: handlePanicButton(); break;
        case 4: requestMap(); break;
        case 5: loadMap(); break;
        case 6: loadAddress(); break;
        case 7: loadMapShortUrl(); break;
        case 8: showOptionsMenu(); break;
        case 9: handleLang(); break;
        case 10: rotateSpinner((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: mapChanged(); break;
        case 12: enableLocationData(); break;
        case 13: showEnableLocationDataMsg(); break;
        case 14: handleMessageBox(); break;
        case 15: handleOptionsMenu(); break;
        case 16: handleSettingsMenu(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

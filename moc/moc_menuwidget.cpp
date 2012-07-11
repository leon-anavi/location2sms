/****************************************************************************
** Meta object code from reading C++ file 'menuwidget.h'
**
** Created: Wed 11. Jul 11:25:17 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../menuwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      23,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MenuWidget[] = {
    "MenuWidget\0\0showHelp()\0showLang()\0"
    "handleHelp()\0handleLang()\0handleExit()\0"
};

const QMetaObject MenuWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuWidget,
      qt_meta_data_MenuWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MenuWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MenuWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MenuWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWidget))
        return static_cast<void*>(const_cast< MenuWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showHelp(); break;
        case 1: showLang(); break;
        case 2: handleHelp(); break;
        case 3: handleLang(); break;
        case 4: handleExit(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MenuWidget::showHelp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MenuWidget::showLang()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

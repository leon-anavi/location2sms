/****************************************************************************
** Meta object code from reading C++ file 'languageswidget.h'
**
** Created: Sun 22. Jul 17:05:35 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../languageswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'languageswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LanguagesWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LanguagesWidget[] = {
    "LanguagesWidget\0\0select()\0"
};

const QMetaObject LanguagesWidget::staticMetaObject = {
    { &SettingsListWidget::staticMetaObject, qt_meta_stringdata_LanguagesWidget,
      qt_meta_data_LanguagesWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LanguagesWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LanguagesWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LanguagesWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LanguagesWidget))
        return static_cast<void*>(const_cast< LanguagesWidget*>(this));
    return SettingsListWidget::qt_metacast(_clname);
}

int LanguagesWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SettingsListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: select(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

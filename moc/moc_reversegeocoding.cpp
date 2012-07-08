/****************************************************************************
** Meta object code from reading C++ file 'reversegeocoding.h'
**
** Created: Sun 8. Jul 14:52:04 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../reversegeocoding.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reversegeocoding.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReverseGeocoding[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReverseGeocoding[] = {
    "ReverseGeocoding\0\0addressRetrieved()\0"
    "parseAddress()\0"
};

const QMetaObject ReverseGeocoding::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReverseGeocoding,
      qt_meta_data_ReverseGeocoding, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReverseGeocoding::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReverseGeocoding::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReverseGeocoding::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReverseGeocoding))
        return static_cast<void*>(const_cast< ReverseGeocoding*>(this));
    return QObject::qt_metacast(_clname);
}

int ReverseGeocoding::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addressRetrieved(); break;
        case 1: parseAddress(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ReverseGeocoding::addressRetrieved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

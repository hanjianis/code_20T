/****************************************************************************
** Meta object code from reading C++ file 'CK_Manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../DeviceMgr/CK_Manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CK_Manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CK_Manager_t {
    QByteArrayData data[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CK_Manager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CK_Manager_t qt_meta_stringdata_CK_Manager = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CK_Manager"
QT_MOC_LITERAL(1, 11, 25), // "UpdateCheckResultCKSignle"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 8), // "datatype"
QT_MOC_LITERAL(4, 47, 3), // "nId"
QT_MOC_LITERAL(5, 51, 4) // "fVal"

    },
    "CK_Manager\0UpdateCheckResultCKSignle\0"
    "\0datatype\0nId\0fVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CK_Manager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,    3,    4,    5,

       0        // eod
};

void CK_Manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CK_Manager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateCheckResultCKSignle((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CK_Manager::*)(int , int , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CK_Manager::UpdateCheckResultCKSignle)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CK_Manager::staticMetaObject = { {
    QMetaObject::SuperData::link<ISysCheckItem::staticMetaObject>(),
    qt_meta_stringdata_CK_Manager.data,
    qt_meta_data_CK_Manager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CK_Manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CK_Manager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CK_Manager.stringdata0))
        return static_cast<void*>(this);
    return ISysCheckItem::qt_metacast(_clname);
}

int CK_Manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ISysCheckItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CK_Manager::UpdateCheckResultCKSignle(int _t1, int _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

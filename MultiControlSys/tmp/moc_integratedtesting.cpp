/****************************************************************************
** Meta object code from reading C++ file 'integratedtesting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../integratedtesting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'integratedtesting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IntegratedTesting_t {
    QByteArrayData data[14];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IntegratedTesting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IntegratedTesting_t qt_meta_stringdata_IntegratedTesting = {
    {
QT_MOC_LITERAL(0, 0, 17), // "IntegratedTesting"
QT_MOC_LITERAL(1, 18, 17), // "UpdateCheckResult"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 8), // "datatype"
QT_MOC_LITERAL(4, 46, 3), // "nId"
QT_MOC_LITERAL(5, 50, 4), // "fVal"
QT_MOC_LITERAL(6, 55, 11), // "AddTaskItem"
QT_MOC_LITERAL(7, 67, 13), // "AutoTestData&"
QT_MOC_LITERAL(8, 81, 4), // "data"
QT_MOC_LITERAL(9, 86, 17), // "AddTaskItemResult"
QT_MOC_LITERAL(10, 104, 22), // "sig_showAutoTestWidget"
QT_MOC_LITERAL(11, 127, 23), // "sig_showAutoTestWidget1"
QT_MOC_LITERAL(12, 151, 15), // "sig_endTaskItem"
QT_MOC_LITERAL(13, 167, 15) // "CkOnlineTimeout"

    },
    "IntegratedTesting\0UpdateCheckResult\0"
    "\0datatype\0nId\0fVal\0AddTaskItem\0"
    "AutoTestData&\0data\0AddTaskItemResult\0"
    "sig_showAutoTestWidget\0sig_showAutoTestWidget1\0"
    "sig_endTaskItem\0CkOnlineTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IntegratedTesting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    1,   56,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,
      10,    0,   62,    2, 0x06 /* Public */,
      11,    0,   63,    2, 0x06 /* Public */,
      12,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void IntegratedTesting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IntegratedTesting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateCheckResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->AddTaskItem((*reinterpret_cast< AutoTestData(*)>(_a[1]))); break;
        case 2: _t->AddTaskItemResult((*reinterpret_cast< AutoTestData(*)>(_a[1]))); break;
        case 3: _t->sig_showAutoTestWidget(); break;
        case 4: _t->sig_showAutoTestWidget1(); break;
        case 5: _t->sig_endTaskItem(); break;
        case 6: _t->CkOnlineTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IntegratedTesting::*)(int , int , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::UpdateCheckResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IntegratedTesting::*)(AutoTestData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::AddTaskItem)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IntegratedTesting::*)(AutoTestData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::AddTaskItemResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IntegratedTesting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::sig_showAutoTestWidget)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (IntegratedTesting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::sig_showAutoTestWidget1)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (IntegratedTesting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IntegratedTesting::sig_endTaskItem)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IntegratedTesting::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IntegratedTesting.data,
    qt_meta_data_IntegratedTesting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IntegratedTesting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IntegratedTesting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IntegratedTesting.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IntegratedTesting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void IntegratedTesting::UpdateCheckResult(int _t1, int _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IntegratedTesting::AddTaskItem(AutoTestData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IntegratedTesting::AddTaskItemResult(AutoTestData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IntegratedTesting::sig_showAutoTestWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void IntegratedTesting::sig_showAutoTestWidget1()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void IntegratedTesting::sig_endTaskItem()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

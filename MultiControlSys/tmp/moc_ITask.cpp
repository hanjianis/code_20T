/****************************************************************************
** Meta object code from reading C++ file 'ITask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ITask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITask.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ITask_t {
    QByteArrayData data[10];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ITask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ITask_t qt_meta_stringdata_ITask = {
    {
QT_MOC_LITERAL(0, 0, 5), // "ITask"
QT_MOC_LITERAL(1, 6, 11), // "AddTaskItem"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 13), // "AutoTestData&"
QT_MOC_LITERAL(4, 33, 4), // "data"
QT_MOC_LITERAL(5, 38, 17), // "AddTaskItemResult"
QT_MOC_LITERAL(6, 56, 19), // "UpdateToolTipSignal"
QT_MOC_LITERAL(7, 76, 3), // "str"
QT_MOC_LITERAL(8, 80, 20), // "StopSignleTestSignal"
QT_MOC_LITERAL(9, 101, 11) // "TmDelaySlot"

    },
    "ITask\0AddTaskItem\0\0AutoTestData&\0data\0"
    "AddTaskItemResult\0UpdateToolTipSignal\0"
    "str\0StopSignleTestSignal\0TmDelaySlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ITask[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,
       8,    0,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ITask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ITask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddTaskItem((*reinterpret_cast< AutoTestData(*)>(_a[1]))); break;
        case 1: _t->AddTaskItemResult((*reinterpret_cast< AutoTestData(*)>(_a[1]))); break;
        case 2: _t->UpdateToolTipSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->StopSignleTestSignal(); break;
        case 4: _t->TmDelaySlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ITask::*)(AutoTestData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ITask::AddTaskItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ITask::*)(AutoTestData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ITask::AddTaskItemResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ITask::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ITask::UpdateToolTipSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ITask::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ITask::StopSignleTestSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ITask::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ITask.data,
    qt_meta_data_ITask,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ITask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ITask.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ITask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ITask::AddTaskItem(AutoTestData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ITask::AddTaskItemResult(AutoTestData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ITask::UpdateToolTipSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ITask::StopSignleTestSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

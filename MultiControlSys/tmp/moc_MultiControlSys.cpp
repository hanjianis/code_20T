/****************************************************************************
** Meta object code from reading C++ file 'MultiControlSys.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../MultiControlSys.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MultiControlSys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MultiControlSys_t {
    QByteArrayData data[11];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MultiControlSys_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MultiControlSys_t qt_meta_stringdata_MultiControlSys = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MultiControlSys"
QT_MOC_LITERAL(1, 16, 10), // "on_timeout"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "on_quit_clicked"
QT_MOC_LITERAL(4, 44, 23), // "on_btnauto_test_clicked"
QT_MOC_LITERAL(5, 68, 24), // "on_btnself_check_clicked"
QT_MOC_LITERAL(6, 93, 22), // "on_btn_history_clicked"
QT_MOC_LITERAL(7, 116, 19), // "on_btnparam_clicked"
QT_MOC_LITERAL(8, 136, 18), // "on_btntest_clicked"
QT_MOC_LITERAL(9, 155, 19), // "on_btn_help_clicked"
QT_MOC_LITERAL(10, 175, 18) // "slot_pictureChange"

    },
    "MultiControlSys\0on_timeout\0\0on_quit_clicked\0"
    "on_btnauto_test_clicked\0"
    "on_btnself_check_clicked\0"
    "on_btn_history_clicked\0on_btnparam_clicked\0"
    "on_btntest_clicked\0on_btn_help_clicked\0"
    "slot_pictureChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MultiControlSys[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MultiControlSys::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MultiControlSys *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_timeout(); break;
        case 1: _t->on_quit_clicked(); break;
        case 2: _t->on_btnauto_test_clicked(); break;
        case 3: _t->on_btnself_check_clicked(); break;
        case 4: _t->on_btn_history_clicked(); break;
        case 5: _t->on_btnparam_clicked(); break;
        case 6: _t->on_btntest_clicked(); break;
        case 7: _t->on_btn_help_clicked(); break;
        case 8: _t->slot_pictureChange(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MultiControlSys::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MultiControlSys.data,
    qt_meta_data_MultiControlSys,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MultiControlSys::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MultiControlSys::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MultiControlSys.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MultiControlSys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

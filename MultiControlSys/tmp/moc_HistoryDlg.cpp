/****************************************************************************
** Meta object code from reading C++ file 'HistoryDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../HistoryDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HistoryDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HistoryDlg_t {
    QByteArrayData data[15];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HistoryDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HistoryDlg_t qt_meta_stringdata_HistoryDlg = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HistoryDlg"
QT_MOC_LITERAL(1, 11, 10), // "on_timeout"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "on_query_clicked"
QT_MOC_LITERAL(4, 40, 15), // "on_quit_clicked"
QT_MOC_LITERAL(5, 56, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(6, 76, 18), // "on_btn_del_clicked"
QT_MOC_LITERAL(7, 95, 17), // "on_printf_clicked"
QT_MOC_LITERAL(8, 113, 20), // "on_btn_close_clicked"
QT_MOC_LITERAL(9, 134, 19), // "on_btn_open_clicked"
QT_MOC_LITERAL(10, 154, 22), // "on_btn_compare_clicked"
QT_MOC_LITERAL(11, 177, 20), // "on_btn_other_clicked"
QT_MOC_LITERAL(12, 198, 21), // "on_btn_pailie_clicked"
QT_MOC_LITERAL(13, 220, 21), // "on_btn_export_clicked"
QT_MOC_LITERAL(14, 242, 21) // "on_btn_printf_clicked"

    },
    "HistoryDlg\0on_timeout\0\0on_query_clicked\0"
    "on_quit_clicked\0on_checkBox_clicked\0"
    "on_btn_del_clicked\0on_printf_clicked\0"
    "on_btn_close_clicked\0on_btn_open_clicked\0"
    "on_btn_compare_clicked\0on_btn_other_clicked\0"
    "on_btn_pailie_clicked\0on_btn_export_clicked\0"
    "on_btn_printf_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistoryDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HistoryDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HistoryDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_timeout(); break;
        case 1: _t->on_query_clicked(); break;
        case 2: _t->on_quit_clicked(); break;
        case 3: _t->on_checkBox_clicked(); break;
        case 4: _t->on_btn_del_clicked(); break;
        case 5: _t->on_printf_clicked(); break;
        case 6: _t->on_btn_close_clicked(); break;
        case 7: _t->on_btn_open_clicked(); break;
        case 8: _t->on_btn_compare_clicked(); break;
        case 9: _t->on_btn_other_clicked(); break;
        case 10: _t->on_btn_pailie_clicked(); break;
        case 11: _t->on_btn_export_clicked(); break;
        case 12: _t->on_btn_printf_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject HistoryDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_HistoryDlg.data,
    qt_meta_data_HistoryDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HistoryDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistoryDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HistoryDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int HistoryDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

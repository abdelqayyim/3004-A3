/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../A3/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "fireBtnClicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "powerBtnClicked"
QT_MOC_LITERAL(4, 43, 16), // "blockDoorClicked"
QT_MOC_LITERAL(5, 60, 16), // "closeDoorClicked"
QT_MOC_LITERAL(6, 77, 15), // "openDoorClicked"
QT_MOC_LITERAL(7, 93, 14), // "helpBtnClicked"
QT_MOC_LITERAL(8, 108, 15), // "upButtonClicked"
QT_MOC_LITERAL(9, 124, 17), // "downButtonClicked"
QT_MOC_LITERAL(10, 142, 24), // "colorsElevatorsAndFloors"
QT_MOC_LITERAL(11, 167, 13), // "getFloorIndex"
QT_MOC_LITERAL(12, 181, 11), // "std::string"
QT_MOC_LITERAL(13, 193, 9), // "numFloors"
QT_MOC_LITERAL(14, 203, 12), // "numElevators"
QT_MOC_LITERAL(15, 216, 32), // "initializeElevatorArrayPositions"
QT_MOC_LITERAL(16, 249, 12), // "setUserFloor"
QT_MOC_LITERAL(17, 262, 8), // "newValue"
QT_MOC_LITERAL(18, 271, 10), // "setTimeout"
QT_MOC_LITERAL(19, 282, 21), // "std::function<void()>"
QT_MOC_LITERAL(20, 304, 8), // "function"
QT_MOC_LITERAL(21, 313, 5) // "delay"

    },
    "MainWindow\0fireBtnClicked\0\0powerBtnClicked\0"
    "blockDoorClicked\0closeDoorClicked\0"
    "openDoorClicked\0helpBtnClicked\0"
    "upButtonClicked\0downButtonClicked\0"
    "colorsElevatorsAndFloors\0getFloorIndex\0"
    "std::string\0numFloors\0numElevators\0"
    "initializeElevatorArrayPositions\0"
    "setUserFloor\0newValue\0setTimeout\0"
    "std::function<void()>\0function\0delay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    2,   88,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      18,    2,   97,    2, 0x08 /* Private */,

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
    0x80000000 | 12, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 19, QMetaType::Int,   20,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fireBtnClicked(); break;
        case 1: _t->powerBtnClicked(); break;
        case 2: _t->blockDoorClicked(); break;
        case 3: _t->closeDoorClicked(); break;
        case 4: _t->openDoorClicked(); break;
        case 5: _t->helpBtnClicked(); break;
        case 6: _t->upButtonClicked(); break;
        case 7: _t->downButtonClicked(); break;
        case 8: _t->colorsElevatorsAndFloors(); break;
        case 9: { std::string _r = _t->getFloorIndex((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->initializeElevatorArrayPositions(); break;
        case 11: { int _r = _t->setUserFloor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setTimeout((*reinterpret_cast< std::function<void()>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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

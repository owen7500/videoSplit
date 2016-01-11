/****************************************************************************
** Meta object code from reading C++ file 'videogui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../videogui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videogui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_videoGUI_t {
    QByteArrayData data[20];
    char stringdata[442];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_videoGUI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_videoGUI_t qt_meta_stringdata_videoGUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "videoGUI"
QT_MOC_LITERAL(1, 9, 22), // "on_fileOpenBtn_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "on_closeBtn_clicked"
QT_MOC_LITERAL(4, 53, 20), // "on_cancelBtn_clicked"
QT_MOC_LITERAL(5, 74, 26), // "on_splitProcessBtn_clicked"
QT_MOC_LITERAL(6, 101, 7), // "showImg"
QT_MOC_LITERAL(7, 109, 14), // "getOutFileName"
QT_MOC_LITERAL(8, 124, 33), // "on_messageTextBrowser_textCha..."
QT_MOC_LITERAL(9, 158, 28), // "on_setOutputAction_triggered"
QT_MOC_LITERAL(10, 187, 26), // "on_displayAction_triggered"
QT_MOC_LITERAL(11, 214, 30), // "on_frameDifAlgAction_triggered"
QT_MOC_LITERAL(12, 245, 38), // "on_multiThrhldFramedifAction_..."
QT_MOC_LITERAL(13, 284, 26), // "on_vibeAlgAction_triggered"
QT_MOC_LITERAL(14, 311, 27), // "on_fileOpenAction_triggered"
QT_MOC_LITERAL(15, 339, 23), // "on_exitAction_triggered"
QT_MOC_LITERAL(16, 363, 10), // "closeEvent"
QT_MOC_LITERAL(17, 374, 12), // "QCloseEvent*"
QT_MOC_LITERAL(18, 387, 26), // "on_versionAction_triggered"
QT_MOC_LITERAL(19, 414, 27) // "on_usedToolAction_triggered"

    },
    "videoGUI\0on_fileOpenBtn_clicked\0\0"
    "on_closeBtn_clicked\0on_cancelBtn_clicked\0"
    "on_splitProcessBtn_clicked\0showImg\0"
    "getOutFileName\0on_messageTextBrowser_textChanged\0"
    "on_setOutputAction_triggered\0"
    "on_displayAction_triggered\0"
    "on_frameDifAlgAction_triggered\0"
    "on_multiThrhldFramedifAction_triggered\0"
    "on_vibeAlgAction_triggered\0"
    "on_fileOpenAction_triggered\0"
    "on_exitAction_triggered\0closeEvent\0"
    "QCloseEvent*\0on_versionAction_triggered\0"
    "on_usedToolAction_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_videoGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    1,  113,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void videoGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        videoGUI *_t = static_cast<videoGUI *>(_o);
        switch (_id) {
        case 0: _t->on_fileOpenBtn_clicked(); break;
        case 1: _t->on_closeBtn_clicked(); break;
        case 2: _t->on_cancelBtn_clicked(); break;
        case 3: _t->on_splitProcessBtn_clicked(); break;
        case 4: _t->showImg(); break;
        case 5: _t->getOutFileName(); break;
        case 6: _t->on_messageTextBrowser_textChanged(); break;
        case 7: _t->on_setOutputAction_triggered(); break;
        case 8: _t->on_displayAction_triggered(); break;
        case 9: _t->on_frameDifAlgAction_triggered(); break;
        case 10: _t->on_multiThrhldFramedifAction_triggered(); break;
        case 11: _t->on_vibeAlgAction_triggered(); break;
        case 12: _t->on_fileOpenAction_triggered(); break;
        case 13: _t->on_exitAction_triggered(); break;
        case 14: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 15: _t->on_versionAction_triggered(); break;
        case 16: _t->on_usedToolAction_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject videoGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_videoGUI.data,
      qt_meta_data_videoGUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *videoGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *videoGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_videoGUI.stringdata))
        return static_cast<void*>(const_cast< videoGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int videoGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'questionlister.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QuestionLister/questionlister.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'questionlister.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuestionLister_t {
    QByteArrayData data[9];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuestionLister_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuestionLister_t qt_meta_stringdata_QuestionLister = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QuestionLister"
QT_MOC_LITERAL(1, 15, 33), // "on_questionList_currentRowCha..."
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 10), // "currentRow"
QT_MOC_LITERAL(4, 61, 34), // "on_questionList_currentTextCh..."
QT_MOC_LITERAL(5, 96, 11), // "currentText"
QT_MOC_LITERAL(6, 108, 31), // "on_removeQuestionButton_clicked"
QT_MOC_LITERAL(7, 140, 28), // "on_addQuestionButton_clicked"
QT_MOC_LITERAL(8, 169, 36) // "on_questionList_itemSelection..."

    },
    "QuestionLister\0on_questionList_currentRowChanged\0"
    "\0currentRow\0on_questionList_currentTextChanged\0"
    "currentText\0on_removeQuestionButton_clicked\0"
    "on_addQuestionButton_clicked\0"
    "on_questionList_itemSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuestionLister[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QuestionLister::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QuestionLister *_t = static_cast<QuestionLister *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_questionList_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_questionList_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_removeQuestionButton_clicked(); break;
        case 3: _t->on_addQuestionButton_clicked(); break;
        case 4: _t->on_questionList_itemSelectionChanged(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QuestionLister::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QuestionLister.data,
    qt_meta_data_QuestionLister,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QuestionLister::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuestionLister::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuestionLister.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QuestionLister::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

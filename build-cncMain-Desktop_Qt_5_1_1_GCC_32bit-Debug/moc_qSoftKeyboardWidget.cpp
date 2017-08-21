/****************************************************************************
** Meta object code from reading C++ file 'qSoftKeyboardWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cncMain/qSoftKeyboardWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qSoftKeyboardWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QSoftkeyboardWidget_t {
    QByteArrayData data[4];
    char stringdata[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QSoftkeyboardWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QSoftkeyboardWidget_t qt_meta_stringdata_QSoftkeyboardWidget = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 26),
QT_MOC_LITERAL(2, 47, 0),
QT_MOC_LITERAL(3, 48, 12)
    },
    "QSoftkeyboardWidget\0excuteSoftKeyboardFunction\0"
    "\0clickPressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSoftkeyboardWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void QSoftkeyboardWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSoftkeyboardWidget *_t = static_cast<QSoftkeyboardWidget *>(_o);
        switch (_id) {
        case 0: _t->excuteSoftKeyboardFunction((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->clickPressed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSoftkeyboardWidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSoftkeyboardWidget::excuteSoftKeyboardFunction)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QSoftkeyboardWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QSoftkeyboardWidget.data,
      qt_meta_data_QSoftkeyboardWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *QSoftkeyboardWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSoftkeyboardWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QSoftkeyboardWidget.stringdata))
        return static_cast<void*>(const_cast< QSoftkeyboardWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QSoftkeyboardWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QSoftkeyboardWidget::excuteSoftKeyboardFunction(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

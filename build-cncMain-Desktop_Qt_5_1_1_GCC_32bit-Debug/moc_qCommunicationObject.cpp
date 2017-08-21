/****************************************************************************
** Meta object code from reading C++ file 'qCommunicationObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cncMain/qCommunicationObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qCommunicationObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QCommunicationObject_t {
    QByteArrayData data[7];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QCommunicationObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QCommunicationObject_t qt_meta_stringdata_QCommunicationObject = {
    {
QT_MOC_LITERAL(0, 0, 20),
QT_MOC_LITERAL(1, 21, 7),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 9),
QT_MOC_LITERAL(4, 40, 6),
QT_MOC_LITERAL(5, 47, 10),
QT_MOC_LITERAL(6, 58, 12)
    },
    "QCommunicationObject\0refresh\0\0onOffLine\0"
    "linked\0updateData\0buildConnect\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCommunicationObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x05,
       3,    1,   35,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a,
       6,    0,   39,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QCommunicationObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCommunicationObject *_t = static_cast<QCommunicationObject *>(_o);
        switch (_id) {
        case 0: _t->refresh(); break;
        case 1: _t->onOffLine((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateData(); break;
        case 3: _t->buildConnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QCommunicationObject::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommunicationObject::refresh)) {
                *result = 0;
            }
        }
        {
            typedef void (QCommunicationObject::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCommunicationObject::onOffLine)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QCommunicationObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QCommunicationObject.data,
      qt_meta_data_QCommunicationObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *QCommunicationObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCommunicationObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCommunicationObject.stringdata))
        return static_cast<void*>(const_cast< QCommunicationObject*>(this));
    return QObject::qt_metacast(_clname);
}

int QCommunicationObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QCommunicationObject::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QCommunicationObject::onOffLine(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

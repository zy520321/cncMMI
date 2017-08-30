/****************************************************************************
** Meta object code from reading C++ file 'tcpClientSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../communicationPlugin/tcpClientSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpClientSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpClientSocket_t {
    QByteArrayData data[20];
    char stringdata[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TcpClientSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TcpClientSocket_t qt_meta_stringdata_TcpClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 17),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 2),
QT_MOC_LITERAL(4, 38, 11),
QT_MOC_LITERAL(5, 50, 28),
QT_MOC_LITERAL(6, 79, 3),
QT_MOC_LITERAL(7, 83, 7),
QT_MOC_LITERAL(8, 91, 15),
QT_MOC_LITERAL(9, 107, 20),
QT_MOC_LITERAL(10, 128, 12),
QT_MOC_LITERAL(11, 141, 11),
QT_MOC_LITERAL(12, 153, 3),
QT_MOC_LITERAL(13, 157, 11),
QT_MOC_LITERAL(14, 169, 14),
QT_MOC_LITERAL(15, 184, 7),
QT_MOC_LITERAL(16, 192, 11),
QT_MOC_LITERAL(17, 204, 14),
QT_MOC_LITERAL(18, 219, 28),
QT_MOC_LITERAL(19, 248, 12)
    },
    "TcpClientSocket\0signalDisconneted\0\0"
    "id\0signalError\0QAbstractSocket::SocketError\0"
    "err\0qintptr\0connectToServer\0"
    "retryConnectToServer\0slotWriteMsg\0"
    "const char*\0msg\0OnConnected\0OnDisconnected\0"
    "OnError\0socketError\0OnStateChanged\0"
    "QAbstractSocket::SocketState\0eSocketState\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClientSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x05,
       4,    2,   62,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    0,   67,    2, 0x0a,
       9,    0,   68,    2, 0x0a,
      10,    1,   69,    2, 0x0a,
      13,    0,   72,    2, 0x08,
      14,    0,   73,    2, 0x08,
      15,    1,   74,    2, 0x08,
      17,    1,   77,    2, 0x08,

 // signals: parameters
    QMetaType::Int, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,   16,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void TcpClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClientSocket *_t = static_cast<TcpClientSocket *>(_o);
        switch (_id) {
        case 0: { int _r = _t->signalDisconneted((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->signalError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1])),(*reinterpret_cast< qintptr(*)>(_a[2]))); break;
        case 2: _t->connectToServer(); break;
        case 3: _t->retryConnectToServer(); break;
        case 4: _t->slotWriteMsg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->OnConnected(); break;
        case 6: _t->OnDisconnected(); break;
        case 7: _t->OnError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->OnStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef int (TcpClientSocket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::signalDisconneted)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpClientSocket::*_t)(QAbstractSocket::SocketError , qintptr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientSocket::signalError)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TcpClientSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpClientSocket.data,
      qt_meta_data_TcpClientSocket,  qt_static_metacall, 0, 0}
};


const QMetaObject *TcpClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClientSocket.stringdata))
        return static_cast<void*>(const_cast< TcpClientSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
int TcpClientSocket::signalDisconneted(int _t1)
{
    int _t0 = int();
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
void TcpClientSocket::signalError(QAbstractSocket::SocketError _t1, qintptr _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

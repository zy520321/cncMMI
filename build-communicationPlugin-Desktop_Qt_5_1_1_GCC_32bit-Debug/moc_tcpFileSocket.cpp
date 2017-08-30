/****************************************************************************
** Meta object code from reading C++ file 'tcpFileSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../communicationPlugin/tcpFileSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpFileSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpFileSocket_t {
    QByteArrayData data[17];
    char stringdata[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_TcpFileSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_TcpFileSocket_t qt_meta_stringdata_TcpFileSocket = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 14),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 9),
QT_MOC_LITERAL(4, 40, 14),
QT_MOC_LITERAL(5, 55, 8),
QT_MOC_LITERAL(6, 64, 21),
QT_MOC_LITERAL(7, 86, 10),
QT_MOC_LITERAL(8, 97, 9),
QT_MOC_LITERAL(9, 107, 11),
QT_MOC_LITERAL(10, 119, 18),
QT_MOC_LITERAL(11, 138, 12),
QT_MOC_LITERAL(12, 151, 15),
QT_MOC_LITERAL(13, 167, 8),
QT_MOC_LITERAL(14, 176, 8),
QT_MOC_LITERAL(15, 185, 11),
QT_MOC_LITERAL(16, 197, 14)
    },
    "TcpFileSocket\0signalChgState\0\0isConnect\0"
    "signalSendFile\0fileName\0signalSendFileContent\0"
    "OnSendFile\0OnGetFile\0OnReadyRead\0"
    "OnReadyReceiveFile\0SendFileHead\0"
    "SendFileContent\0GoOnSend\0numBytes\0"
    "OnConnected\0OnDisconnected\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpFileSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x05,
       4,    1,   77,    2, 0x05,
       6,    0,   80,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    1,   81,    2, 0x0a,
       8,    1,   84,    2, 0x0a,
       9,    0,   87,    2, 0x08,
      10,    0,   88,    2, 0x08,
      11,    1,   89,    2, 0x08,
      12,    0,   92,    2, 0x08,
      13,    1,   93,    2, 0x08,
      15,    0,   96,    2, 0x08,
      16,    0,   97,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::LongLong,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpFileSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpFileSocket *_t = static_cast<TcpFileSocket *>(_o);
        switch (_id) {
        case 0: _t->signalChgState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->signalSendFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->signalSendFileContent(); break;
        case 3: _t->OnSendFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->OnGetFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->OnReadyRead(); break;
        case 6: _t->OnReadyReceiveFile(); break;
        case 7: _t->SendFileHead((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->SendFileContent(); break;
        case 9: { bool _r = _t->GoOnSend((*reinterpret_cast< qint64(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: _t->OnConnected(); break;
        case 11: _t->OnDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpFileSocket::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpFileSocket::signalChgState)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpFileSocket::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpFileSocket::signalSendFile)) {
                *result = 1;
            }
        }
        {
            typedef void (TcpFileSocket::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpFileSocket::signalSendFileContent)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject TcpFileSocket::staticMetaObject = {
    { &TcpClientSocket::staticMetaObject, qt_meta_stringdata_TcpFileSocket.data,
      qt_meta_data_TcpFileSocket,  qt_static_metacall, 0, 0}
};


const QMetaObject *TcpFileSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpFileSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpFileSocket.stringdata))
        return static_cast<void*>(const_cast< TcpFileSocket*>(this));
    return TcpClientSocket::qt_metacast(_clname);
}

int TcpFileSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TcpClientSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TcpFileSocket::signalChgState(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpFileSocket::signalSendFile(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpFileSocket::signalSendFileContent()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE

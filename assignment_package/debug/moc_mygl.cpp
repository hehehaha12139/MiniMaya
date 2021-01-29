/****************************************************************************
** Meta object code from reading C++ file 'mygl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mygl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGL_t {
    QByteArrayData data[14];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGL_t qt_meta_stringdata_MyGL = {
    {
QT_MOC_LITERAL(0, 0, 4), // "MyGL"
QT_MOC_LITERAL(1, 5, 12), // "nextHalfEdge"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "symHalfEdge"
QT_MOC_LITERAL(4, 31, 12), // "halfEdgeFace"
QT_MOC_LITERAL(5, 44, 14), // "halfEdgeVertex"
QT_MOC_LITERAL(6, 59, 14), // "vertexHalfEdge"
QT_MOC_LITERAL(7, 74, 12), // "faceHalfEdge"
QT_MOC_LITERAL(8, 87, 8), // "sendFace"
QT_MOC_LITERAL(9, 96, 5), // "Face*"
QT_MOC_LITERAL(10, 102, 10), // "sendVertex"
QT_MOC_LITERAL(11, 113, 7), // "Vertex*"
QT_MOC_LITERAL(12, 121, 12), // "sendHalfEdge"
QT_MOC_LITERAL(13, 134, 9) // "HalfEdge*"

    },
    "MyGL\0nextHalfEdge\0\0symHalfEdge\0"
    "halfEdgeFace\0halfEdgeVertex\0vertexHalfEdge\0"
    "faceHalfEdge\0sendFace\0Face*\0sendVertex\0"
    "Vertex*\0sendHalfEdge\0HalfEdge*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    0,   63,    2, 0x06 /* Public */,
       7,    0,   64,    2, 0x06 /* Public */,
       8,    1,   65,    2, 0x06 /* Public */,
      10,    1,   68,    2, 0x06 /* Public */,
      12,    1,   71,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 13,    2,

       0        // eod
};

void MyGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyGL *_t = static_cast<MyGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextHalfEdge(); break;
        case 1: _t->symHalfEdge(); break;
        case 2: _t->halfEdgeFace(); break;
        case 3: _t->halfEdgeVertex(); break;
        case 4: _t->vertexHalfEdge(); break;
        case 5: _t->faceHalfEdge(); break;
        case 6: _t->sendFace((*reinterpret_cast< Face*(*)>(_a[1]))); break;
        case 7: _t->sendVertex((*reinterpret_cast< Vertex*(*)>(_a[1]))); break;
        case 8: _t->sendHalfEdge((*reinterpret_cast< HalfEdge*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::nextHalfEdge)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::symHalfEdge)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::halfEdgeFace)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::halfEdgeVertex)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::vertexHalfEdge)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::faceHalfEdge)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)(Face * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::sendFace)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)(Vertex * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::sendVertex)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (MyGL::*_t)(HalfEdge * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyGL::sendHalfEdge)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject MyGL::staticMetaObject = {
    { &OpenGLContext::staticMetaObject, qt_meta_stringdata_MyGL.data,
      qt_meta_data_MyGL,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGL.stringdata0))
        return static_cast<void*>(const_cast< MyGL*>(this));
    return OpenGLContext::qt_metacast(_clname);
}

int MyGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenGLContext::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MyGL::nextHalfEdge()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyGL::symHalfEdge()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyGL::halfEdgeFace()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyGL::halfEdgeVertex()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MyGL::vertexHalfEdge()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MyGL::faceHalfEdge()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MyGL::sendFace(Face * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MyGL::sendVertex(Vertex * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MyGL::sendHalfEdge(HalfEdge * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

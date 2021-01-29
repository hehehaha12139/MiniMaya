/****************************************************************************
** Meta object code from reading C++ file 'mesh.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mesh.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mesh.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Mesh_t {
    QByteArrayData data[13];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Mesh_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Mesh_t qt_meta_stringdata_Mesh = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Mesh"
QT_MOC_LITERAL(1, 5, 10), // "sendVertex"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 7), // "Vertex*"
QT_MOC_LITERAL(4, 25, 1), // "v"
QT_MOC_LITERAL(5, 27, 8), // "sendFace"
QT_MOC_LITERAL(6, 36, 5), // "Face*"
QT_MOC_LITERAL(7, 42, 1), // "f"
QT_MOC_LITERAL(8, 44, 12), // "sendHalfEdge"
QT_MOC_LITERAL(9, 57, 9), // "HalfEdge*"
QT_MOC_LITERAL(10, 67, 2), // "he"
QT_MOC_LITERAL(11, 70, 8), // "sendRoot"
QT_MOC_LITERAL(12, 79, 16) // "QTreeWidgetItem*"

    },
    "Mesh\0sendVertex\0\0Vertex*\0v\0sendFace\0"
    "Face*\0f\0sendHalfEdge\0HalfEdge*\0he\0"
    "sendRoot\0QTreeWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Mesh[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,
      11,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,

       0        // eod
};

void Mesh::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Mesh *_t = static_cast<Mesh *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendVertex((*reinterpret_cast< Vertex*(*)>(_a[1]))); break;
        case 1: _t->sendFace((*reinterpret_cast< Face*(*)>(_a[1]))); break;
        case 2: _t->sendHalfEdge((*reinterpret_cast< HalfEdge*(*)>(_a[1]))); break;
        case 3: _t->sendRoot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Mesh::*_t)(Vertex * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mesh::sendVertex)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Mesh::*_t)(Face * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mesh::sendFace)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Mesh::*_t)(HalfEdge * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mesh::sendHalfEdge)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Mesh::*_t)(QTreeWidgetItem * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Mesh::sendRoot)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Mesh::staticMetaObject = {
    { &Drawable::staticMetaObject, qt_meta_stringdata_Mesh.data,
      qt_meta_data_Mesh,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Mesh::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Mesh::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Mesh.stringdata0))
        return static_cast<void*>(const_cast< Mesh*>(this));
    return Drawable::qt_metacast(_clname);
}

int Mesh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Drawable::qt_metacall(_c, _id, _a);
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
void Mesh::sendVertex(Vertex * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Mesh::sendFace(Face * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Mesh::sendHalfEdge(HalfEdge * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Mesh::sendRoot(QTreeWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

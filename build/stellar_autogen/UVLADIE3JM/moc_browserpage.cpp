/****************************************************************************
** Meta object code from reading C++ file 'browserpage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/browserpage.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'browserpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_BrowserPage_t {
    uint offsetsAndSizes[32];
    char stringdata0[12];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[13];
    char stringdata5[6];
    char stringdata6[13];
    char stringdata7[9];
    char stringdata8[13];
    char stringdata9[3];
    char stringdata10[12];
    char stringdata11[5];
    char stringdata12[16];
    char stringdata13[18];
    char stringdata14[27];
    char stringdata15[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_BrowserPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_BrowserPage_t qt_meta_stringdata_BrowserPage = {
    {
        QT_MOC_LITERAL(0, 11),  // "BrowserPage"
        QT_MOC_LITERAL(12, 10),  // "urlChanged"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 3),  // "url"
        QT_MOC_LITERAL(28, 12),  // "titleChanged"
        QT_MOC_LITERAL(41, 5),  // "title"
        QT_MOC_LITERAL(47, 12),  // "loadProgress"
        QT_MOC_LITERAL(60, 8),  // "progress"
        QT_MOC_LITERAL(69, 12),  // "loadFinished"
        QT_MOC_LITERAL(82, 2),  // "ok"
        QT_MOC_LITERAL(85, 11),  // "iconChanged"
        QT_MOC_LITERAL(97, 4),  // "icon"
        QT_MOC_LITERAL(102, 15),  // "newTabRequested"
        QT_MOC_LITERAL(118, 17),  // "downloadRequested"
        QT_MOC_LITERAL(136, 26),  // "QWebEngineDownloadRequest*"
        QT_MOC_LITERAL(163, 8)   // "download"
    },
    "BrowserPage",
    "urlChanged",
    "",
    "url",
    "titleChanged",
    "title",
    "loadProgress",
    "progress",
    "loadFinished",
    "ok",
    "iconChanged",
    "icon",
    "newTabRequested",
    "downloadRequested",
    "QWebEngineDownloadRequest*",
    "download"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_BrowserPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       4,    1,   59,    2, 0x06,    3 /* Public */,
       6,    1,   62,    2, 0x06,    5 /* Public */,
       8,    1,   65,    2, 0x06,    7 /* Public */,
      10,    1,   68,    2, 0x06,    9 /* Public */,
      12,    1,   71,    2, 0x06,   11 /* Public */,
      13,    1,   74,    2, 0x06,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QUrl,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QIcon,   11,
    QMetaType::Void, QMetaType::QUrl,    3,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject BrowserPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_BrowserPage.offsetsAndSizes,
    qt_meta_data_BrowserPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_BrowserPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BrowserPage, std::true_type>,
        // method 'urlChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>,
        // method 'titleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'loadProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'loadFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'iconChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QIcon &, std::false_type>,
        // method 'newTabRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>,
        // method 'downloadRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWebEngineDownloadRequest *, std::false_type>
    >,
    nullptr
} };

void BrowserPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BrowserPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->urlChanged((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 1: _t->titleChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->loadProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->loadFinished((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->iconChanged((*reinterpret_cast< std::add_pointer_t<QIcon>>(_a[1]))); break;
        case 5: _t->newTabRequested((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        case 6: _t->downloadRequested((*reinterpret_cast< std::add_pointer_t<QWebEngineDownloadRequest*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWebEngineDownloadRequest* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BrowserPage::*)(const QUrl & );
            if (_t _q_method = &BrowserPage::urlChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(const QString & );
            if (_t _q_method = &BrowserPage::titleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(int );
            if (_t _q_method = &BrowserPage::loadProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(bool );
            if (_t _q_method = &BrowserPage::loadFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(const QIcon & );
            if (_t _q_method = &BrowserPage::iconChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(const QUrl & );
            if (_t _q_method = &BrowserPage::newTabRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (BrowserPage::*)(QWebEngineDownloadRequest * );
            if (_t _q_method = &BrowserPage::downloadRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *BrowserPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BrowserPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BrowserPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BrowserPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BrowserPage::urlChanged(const QUrl & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BrowserPage::titleChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BrowserPage::loadProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BrowserPage::loadFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void BrowserPage::iconChanged(const QIcon & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void BrowserPage::newTabRequested(const QUrl & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void BrowserPage::downloadRequested(QWebEngineDownloadRequest * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
namespace {
struct qt_meta_stringdata_NexusWebPage_t {
    uint offsetsAndSizes[8];
    char stringdata0[13];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NexusWebPage_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NexusWebPage_t qt_meta_stringdata_NexusWebPage = {
    {
        QT_MOC_LITERAL(0, 12),  // "NexusWebPage"
        QT_MOC_LITERAL(13, 18),  // "newWindowRequested"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 3)   // "url"
    },
    "NexusWebPage",
    "newWindowRequested",
    "",
    "url"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NexusWebPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QUrl,    3,

       0        // eod
};

Q_CONSTINIT const QMetaObject NexusWebPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWebEnginePage::staticMetaObject>(),
    qt_meta_stringdata_NexusWebPage.offsetsAndSizes,
    qt_meta_data_NexusWebPage,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NexusWebPage_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NexusWebPage, std::true_type>,
        // method 'newWindowRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QUrl &, std::false_type>
    >,
    nullptr
} };

void NexusWebPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NexusWebPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newWindowRequested((*reinterpret_cast< std::add_pointer_t<QUrl>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NexusWebPage::*)(const QUrl & );
            if (_t _q_method = &NexusWebPage::newWindowRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *NexusWebPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NexusWebPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NexusWebPage.stringdata0))
        return static_cast<void*>(this);
    return QWebEnginePage::qt_metacast(_clname);
}

int NexusWebPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEnginePage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void NexusWebPage::newWindowRequested(const QUrl & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

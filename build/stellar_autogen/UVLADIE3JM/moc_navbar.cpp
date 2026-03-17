/****************************************************************************
** Meta object code from reading C++ file 'navbar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/navbar.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navbar.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_NavButton_t {
    uint offsetsAndSizes[8];
    char stringdata0[10];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NavButton_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NavButton_t qt_meta_stringdata_NavButton = {
    {
        QT_MOC_LITERAL(0, 9),  // "NavButton"
        QT_MOC_LITERAL(10, 7),  // "clicked"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 7)   // "opacity"
    },
    "NavButton",
    "clicked",
    "",
    "opacity"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NavButton[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       1,   21, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x06,    2 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QReal, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject NavButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_NavButton.offsetsAndSizes,
    qt_meta_data_NavButton,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NavButton_t,
        // property 'opacity'
        QtPrivate::TypeAndForceComplete<qreal, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NavButton, std::true_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NavButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NavButton *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavButton::*)();
            if (_t _q_method = &NavButton::clicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<NavButton *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->opacity(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<NavButton *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setOpacity(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *NavButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavButton.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NavButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void NavButton::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
namespace {
struct qt_meta_stringdata_UrlBar_t {
    uint offsetsAndSizes[2];
    char stringdata0[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_UrlBar_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_UrlBar_t qt_meta_stringdata_UrlBar = {
    {
        QT_MOC_LITERAL(0, 6)   // "UrlBar"
    },
    "UrlBar"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_UrlBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject UrlBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QLineEdit::staticMetaObject>(),
    qt_meta_stringdata_UrlBar.offsetsAndSizes,
    qt_meta_data_UrlBar,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_UrlBar_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<UrlBar, std::true_type>
    >,
    nullptr
} };

void UrlBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *UrlBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UrlBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UrlBar.stringdata0))
        return static_cast<void*>(this);
    return QLineEdit::qt_metacast(_clname);
}

int UrlBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_NavBar_t {
    uint offsetsAndSizes[26];
    char stringdata0[7];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[12];
    char stringdata5[15];
    char stringdata6[14];
    char stringdata7[12];
    char stringdata8[16];
    char stringdata9[14];
    char stringdata10[14];
    char stringdata11[13];
    char stringdata12[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_NavBar_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_NavBar_t qt_meta_stringdata_NavBar = {
    {
        QT_MOC_LITERAL(0, 6),  // "NavBar"
        QT_MOC_LITERAL(7, 8),  // "navigate"
        QT_MOC_LITERAL(16, 0),  // ""
        QT_MOC_LITERAL(17, 3),  // "url"
        QT_MOC_LITERAL(21, 11),  // "backClicked"
        QT_MOC_LITERAL(33, 14),  // "forwardClicked"
        QT_MOC_LITERAL(48, 13),  // "reloadClicked"
        QT_MOC_LITERAL(62, 11),  // "homeClicked"
        QT_MOC_LITERAL(74, 15),  // "bookmarkClicked"
        QT_MOC_LITERAL(90, 13),  // "showBookmarks"
        QT_MOC_LITERAL(104, 13),  // "showDownloads"
        QT_MOC_LITERAL(118, 12),  // "showSettings"
        QT_MOC_LITERAL(131, 16)   // "translateClicked"
    },
    "NavBar",
    "navigate",
    "",
    "url",
    "backClicked",
    "forwardClicked",
    "reloadClicked",
    "homeClicked",
    "bookmarkClicked",
    "showBookmarks",
    "showDownloads",
    "showSettings",
    "translateClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_NavBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x06,    1 /* Public */,
       4,    0,   77,    2, 0x06,    3 /* Public */,
       5,    0,   78,    2, 0x06,    4 /* Public */,
       6,    0,   79,    2, 0x06,    5 /* Public */,
       7,    0,   80,    2, 0x06,    6 /* Public */,
       8,    0,   81,    2, 0x06,    7 /* Public */,
       9,    0,   82,    2, 0x06,    8 /* Public */,
      10,    0,   83,    2, 0x06,    9 /* Public */,
      11,    0,   84,    2, 0x06,   10 /* Public */,
      12,    0,   85,    2, 0x06,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject NavBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_NavBar.offsetsAndSizes,
    qt_meta_data_NavBar,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_NavBar_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NavBar, std::true_type>,
        // method 'navigate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'backClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'forwardClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reloadClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'homeClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'bookmarkClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showBookmarks'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showDownloads'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'translateClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NavBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NavBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->navigate((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->backClicked(); break;
        case 2: _t->forwardClicked(); break;
        case 3: _t->reloadClicked(); break;
        case 4: _t->homeClicked(); break;
        case 5: _t->bookmarkClicked(); break;
        case 6: _t->showBookmarks(); break;
        case 7: _t->showDownloads(); break;
        case 8: _t->showSettings(); break;
        case 9: _t->translateClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavBar::*)(const QString & );
            if (_t _q_method = &NavBar::navigate; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::backClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::forwardClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::reloadClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::homeClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::bookmarkClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::showBookmarks; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::showDownloads; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::showSettings; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (NavBar::*)();
            if (_t _q_method = &NavBar::translateClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject *NavBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NavBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void NavBar::navigate(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NavBar::backClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NavBar::forwardClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NavBar::reloadClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NavBar::homeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NavBar::bookmarkClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void NavBar::showBookmarks()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void NavBar::showDownloads()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void NavBar::showSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void NavBar::translateClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 utf8

DEFINES += _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

RC_ICONS = F:\WangLingZhi\FingerMSVC\icon\ico.ico


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
msvc
｛
     QMAKE_CFLAGS += /utf-8

     QMAKE_CXXFLAGS += /utf-8
｝
SOURCES += \
    Finger.cpp \
    Login.cpp \
    Setting.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FPModule_SDK.h \
    Finger.h \
    Login.h \
    Setting.h \
    dialog.h \
    mainwindow.h

FORMS += \
    Finger.ui \
    Login.ui \
    Setting.ui \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/./ -lFPModule_SDK

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./FPModule_SDK.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/./libFPModule_SDK.a

RESOURCES += \
    icon/icon.qrc

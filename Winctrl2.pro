TARGET = KeyLinker

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    keyselectiondialog.cpp \
    keysimulator.cpp \
    main.cpp \
    setdelaydialog.cpp \
    widget.cpp

HEADERS += \
    keyselectiondialog.h \
    keysimulator.h \
    setdelaydialog.h \
    widget.h

FORMS += \
    KeySelectionDialog.ui \
    keyselectiondialog.ui \
    setdelaydialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -LC:/Users/Fallmoon/Downloads/Interception/Interception/library/x64/ -linterception

INCLUDEPATH += C:/Users/Fallmoon/Downloads/Interception/Interception/library
DEPENDPATH += C:/Users/Fallmoon/Downloads/Interception/Interception/library

RESOURCES += \
    Res.qrc

RC_ICONS = RealTitleIcon.ico

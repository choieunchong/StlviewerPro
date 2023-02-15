QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cutform.cpp \
    lightwidgetform.cpp \
    main.cpp \
    shadingform.cpp \
    widget.cpp

HEADERS += \
    cutform.h \
    lightwidgetform.h \
    shadingform.h \
    widget.h

FORMS += \
    cutform.ui \
    lightwidgetform.ui \
    shadingform.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

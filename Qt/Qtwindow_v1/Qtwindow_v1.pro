QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    newwindow.cpp \
    newwindow2.cpp \
    qcustomplot.cpp

HEADERS += \
    DriverType.h \
    Driver_app.h \
    mainwindow.h \
    newwindow.h \
    newwindow2.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    newwindow.ui \
    newwindow2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Driver.dll \
    Driver.lib \
    HP2000_wrapper.dll \
    catnap.ico \
    catnap.png \
    dark.png \
    libusb0.dll \
    light.jpg

RC_ICONS = catnap.ico

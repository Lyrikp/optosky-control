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
    peakset.cpp \
    qcustomplot.cpp

HEADERS += \
    DriverType.h \
    Driver_app.h \
    findpeaks.h \
    mainwindow.h \
    newwindow.h \
    newwindow2.h \
    peakset.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    newwindow.ui \
    newwindow2.ui \
    peakset.ui

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
    light.jpg \
    svgsource/alarm-warning-line.svg \
    svgsource/bar-chart-grouped-line.svg \
    svgsource/building-3-line.svg \
    svgsource/chat-forward-line.svg \
    svgsource/chat-poll-line.svg \
    svgsource/check-line.svg \
    svgsource/close-line.svg \
    svgsource/contrast-2-fill.svg \
    svgsource/file-3-line.svg \
    svgsource/file-transfer-line.svg \
    svgsource/find-replace-line.svg \
    svgsource/focus-2-fill.svg \
    svgsource/folder-info-line.svg \
    svgsource/git-commit-line.svg \
    svgsource/image-add-fill.svg \
    svgsource/information-line.svg \
    svgsource/line-chart-line.svg \
    svgsource/link.svg \
    svgsource/login-circle-fill.svg \
    svgsource/logout-circle-r-line.svg \
    svgsource/menu-add-line.svg \
    svgsource/moon-cloudy-fill.svg \
    svgsource/palette-line.svg \
    svgsource/pause-circle-fill.svg \
    svgsource/play-circle-fill.svg \
    svgsource/play-line.svg \
    svgsource/rhythm-line.svg \
    svgsource/ruler-line.svg \
    svgsource/settings-6-line.svg \
    svgsource/spectrum-line.svg \
    svgsource/sticky-note-line.svg \
    svgsource/stop-circle-fill.svg \
    svgsource/stop-line.svg \
    svgsource/subtract-line.svg \
    svgsource/timer-line.svg \
    svgsource/tools-fill.svg \
    svgsource/zoom-in-line.svg \
    svgsource/zoom-out-line.svg

RC_ICONS = catnap.ico

INCLUDEPATH += "D:\OpenCV\opencv\build\include" \

               "D:\OpenCV\opencv\build\include\opencv2"

LIBS += -LD:\OpenCV\opencv\build\x64\vc15\lib

QT       += core gui
QT += widgets
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
charge.cpp \
chargedetail.cpp \
chargedia.cpp \
countdia.cpp \
datetimedialog.cpp \
main.cpp \
mainwindow.cpp \
qhmaskwidget.cpp



HEADERS += \
    charge.h \
    chargedetail.h \
    chargedia.h \
    connectionData.h \
    countdia.h \
    datetimedialog.h \
    mainwindow.h \
    qhmaskwidget.h

FORMS += \
    charge.ui \
    chargedetail.ui \
    chargedia.ui \
    countdia.ui \
    mainwindow.ui \
    qhmaskwidget.ui

TRANSLATIONS += \
    ManageCar_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

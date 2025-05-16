QT       += core gui
QT       += sql
QT       += multimedia
CONFIG  += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    achievements.cpp \
    daiban.cpp \
    homepage.cpp \
    main.cpp \
    personal_details.cpp \
    positivetiming.cpp \
    selfdefined.cpp \
    setting.cpp \
    settingpage.cpp \
    shuju.cpp \
    tomatoclock.cpp

HEADERS += \
    ../../../../qtsql 2/qtsql/shuju.h \
    ../../../../qtsql 2/qtsql/shuju.h \
    achievements.h \
    daiban.h \
    homepage.h \
    personal_details.h \
    positivetiming.h \
    selfdefined.h \
    setting.h \
    settingpage.h \
    shuju.h \
    tomatoclock.h

FORMS += \
    achievements.ui \
    daiban.ui \
    homepage.ui \
    personal_details.ui \
    positivetiming.ui \
    selfdefined.ui \
    setting.ui \
    settingpage.ui \
    shuju.ui \
    tomatoclock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

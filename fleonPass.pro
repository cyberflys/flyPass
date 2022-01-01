QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    shes.cpp

HEADERS += \
    mainwindow.h \
    shes.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rez.qrc

DISTFILES += \
    images/bckg.png \
    images/bckg.xcf \
    images/main.png \
    passwords/Idesga \
    passwords/Suckit \
    passwords/Tinder \
    passwords/Twitter \
    passwords/c3958 \
    passwords/decrypt \
    passwords/encrypt \
    passwords/feffw \
    passwords/key.key

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    game.cpp \
    main.cpp \
    inicio.cpp \
    selector.cpp \
    selectormundos.cpp \
    sprites.cpp

HEADERS += \
    background.h \
    game.h \
    inicio.h \
    selector.h \
    selectormundos.h \
    sprites.h

FORMS += \
    game.ui \
    inicio.ui \
    selector.ui \
    selectormundos.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Musiquita.qrc \
    Naves.qrc \
    Restante.qrc \
    SoundEfects.qrc
